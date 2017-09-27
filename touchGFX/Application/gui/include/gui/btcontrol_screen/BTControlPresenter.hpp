#ifndef BTCONTROL_PRESENTER_HPP
#define BTCONTROL_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class BTControlView;

class BTControlPresenter : public DemoPresenter
{
public:
    BTControlPresenter(BTControlView& v);

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
    virtual void enableBlueTooth();
    virtual void disableBlueTooth();
    /*void setBluetoothState(bool);
    void updateListMenuElements();*/
    virtual ~BTControlPresenter() {};
    virtual void onBluetoothStateChange(bool state);
    virtual void onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strDeviceName, touchgfx::Unicode::UnicodeChar* strAddress);
    virtual void onBluetoothScanComplete(int num);

private:
    BTControlPresenter();

    BTControlView& view;
};


#endif // BTCONTROL_PRESENTER_HPP
