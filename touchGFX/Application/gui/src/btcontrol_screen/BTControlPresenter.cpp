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
    if (mControlData().isBTEnable()) {
        Bluetooth_Scan_Start();
        view.setBluetoothState(true);
    } else {
        view.setBluetoothState(false);
    }
}

void BTControlPresenter::deactivate()
{
    ///Bluetooth_Scan_Stop();
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

void BTControlPresenter::onBluetoothStateChange(bool state) {
    view.stopAnimation();
    view.setBluetoothState(state);

    if (state) {
        Bluetooth_Scan_Start();
        view.startAnimation();
    } else {
        ///Bluetooth_Scan_Stop();
    }
}

void BTControlPresenter::onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[]) {
    view.updateListMenuElements(strName, address);
    view.updateListMenuLayout();
}

void BTControlPresenter::onBluetoothScanComplete(int num) {
    //view.updateListMenuLayout();
    view.stopAnimation();
}

void BTControlPresenter::onBluetoothConnected(bool status, uint8_t address[]) {
    if (status) {
        view.setCustomListStatus(cesConnected);
    } else {
        view.setCustomListStatus(cesConnectError);
    }
    view.stopListAnimation();
    view.updateListMenuLayout();
}

void BTControlPresenter::onBluetoothDisonnected(int reason, uint8_t address[]) {
    view.stopListAnimation();
    view.updateListMenuLayout();
}

void BTControlPresenter::onBluetoothBonded(bool status, int bonded, uint8_t address[]) {
    view.stopListAnimation();
    view.updateListMenuLayout();
}

