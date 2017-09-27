#include <gui/btcontrol_screen/BTControlView.hpp>
#include <gui/btcontrol_screen/BTControlPresenter.hpp>
#include <gui/framework/DevicePort.h>
#ifndef SIMULATOR
#include <fsl_debug_console.h>
#endif
BTControlPresenter::BTControlPresenter(BTControlView& v):
DemoPresenter(v),
view(v)
{
}

void BTControlPresenter::activate()
{
    if (mControlData.isBTEnable()) {
        Bluetooth_Scan_Start();
        view.setBluetoothState(true);
    } else {
        view.setBluetoothState(false);
    }
}

void BTControlPresenter::deactivate()
{
    Bluetooth_Scan_Stop();
}


void BTControlPresenter::enableBlueTooth()
{
    Bluetooth_Open();
    /*model->switchBluetooth(true);*/
    view.startAnimation();
}

void BTControlPresenter::disableBlueTooth()
{
    Bluetooth_Close();
    /*model->switchBluetooth(false);*/
#ifdef SIMULATOR
    //mControlData.enableBTState(false);
#endif
}

/*
void BTControlPresenter::setBluetoothState(bool state)
{
    view.stopAnimation();
    view.setBluetoothState(state);
}

void BTControlPresenter::updateListMenuElements()
{
    view.updateListMenuElements();
}
*/

void BTControlPresenter::onBluetoothStateChange(bool state) {
    view.stopAnimation();
    view.setBluetoothState(state);

    if (state) {
        Bluetooth_Scan_Start();
    } else {
        Bluetooth_Scan_Stop();
    }
}

void BTControlPresenter::onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strDeviceName, touchgfx::Unicode::UnicodeChar* strAddress) {
    view.updateListMenuElements(strDeviceName, strAddress);
}


void BTControlPresenter::onBluetoothScanComplete(int num) {

}
