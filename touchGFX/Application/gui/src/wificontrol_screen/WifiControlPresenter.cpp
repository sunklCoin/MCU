#include <gui/wificontrol_screen/WifiControlView.hpp>
#include <gui/wificontrol_screen/WifiControlPresenter.hpp>
#include <gui/framework/DevicePort.h>
#include <gui/common/CustomListElement.hpp>

WifiControlPresenter::WifiControlPresenter(WifiControlView& v)
:DemoPresenter(v),
    view(v)
{
}

void WifiControlPresenter::activate()
{
    if (mControlData().isWifiEnable()) {
        Wifi_Open();
        view.startAnimation();
        setWifiState(true);
    } else {
        view.stopAnimation();
        setWifiState(false);
    }
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
    view.startAnimation();
}

void WifiControlPresenter::setWifiState(bool state)
{
    view.setWifiState(state);
}

void WifiControlPresenter::onWifiScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi, bool needPwd) {
	view.updateListMenuElements(strName, address, rssi, needPwd);
}

void WifiControlPresenter::onWifiScanCompleted(int num) {
    view.updateListMenuLayout();
    view.stopAnimation();
    setWifiState(true);
}

void WifiControlPresenter::onWifiConnected(bool status) {
    if (status) {
        view.setCustomListStatus(cesConnected);
    } else {
        view.setCustomListStatus(cesConnectError);
    }
    view.stopListAnimation();
    view.updateListMenuLayout();
}

void WifiControlPresenter::onWifiDisonnected(int reason) {
    view.setCustomListStatus(cesDisconnected);
    view.stopListAnimation();
    view.updateListMenuLayout();
}

void WifiControlPresenter::onWifiClosed(bool status) {
    view.stopAnimation();
    setWifiState(false);
}
