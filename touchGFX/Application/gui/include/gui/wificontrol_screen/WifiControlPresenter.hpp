#ifndef WIFICONTROL_PRESENTER_HPP
#define WIFICONTROL_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/DemoPresenter.hpp>
using namespace touchgfx;

class WifiControlView;

class WifiControlPresenter : public DemoPresenter
{
public:
    WifiControlPresenter(WifiControlView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();
    virtual void enableWifi();
    virtual void disableWifi();
    void setWifiState(bool);
    virtual ~WifiControlPresenter() {};
    virtual void onWifiScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi, bool needPwd);
    virtual void onWifiScanCompleted(int num);
    virtual void onWifiConnected(bool status);
    virtual void onWifiDisonnected(int reason);
private:
    WifiControlPresenter();

    WifiControlView& view;
};


#endif // WIFICONTROL_PRESENTER_HPP
