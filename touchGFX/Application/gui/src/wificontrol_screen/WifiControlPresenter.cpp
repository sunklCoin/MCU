#include <gui/wificontrol_screen/WifiControlView.hpp>
#include <gui/wificontrol_screen/WifiControlPresenter.hpp>
#include <gui/framework/DevicePort.h>

WifiControlPresenter::WifiControlPresenter(WifiControlView& v)
:DemoPresenter(v),
    view(v)
{
}

void WifiControlPresenter::activate()
{

}

void WifiControlPresenter::deactivate()
{

}

void WifiControlPresenter::enableWifi()
{
    Wifi_Open();
    view.startAnimation();
}

void WifiControlPresenter::disableWifi()
{
    Wifi_Close();
    view.stopAnimation();
}

void WifiControlPresenter::setWifiState(bool state)
{
    view.stopAnimation();
    view.setWifiState(state);
}

void WifiControlPresenter::onWifiScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi) {
    view.updateListMenuElements(strName, address, rssi);
}

void WifiControlPresenter::onWifiScanCompleted(int num) {
    view.updateListMenuLayout();
    view.stopAnimation();
    setWifiState(true);
}

void WifiControlPresenter::onWifiConnected(bool status) {
    view.stopListAnimation();
}

void WifiControlPresenter::onWifiDisonnected(int reason) {
    view.stopListAnimation();
}
