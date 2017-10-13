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
    virtual ~BTControlPresenter() {};
    virtual void onBluetoothStateChange(bool state);
    virtual void onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[]);
    virtual void onBluetoothScanComplete(int num);
    virtual void onBluetoothConnected(bool status, uint8_t address[]);
    virtual void onBluetoothDisonnected(int reason, uint8_t address[]);
    virtual void onBluetoothBonded(bool status, int bonded, uint8_t address[]);

private:
    BTControlPresenter();

    BTControlView& view;
};


#endif // BTCONTROL_PRESENTER_HPP
