#include <gui/wificontrol_screen/WifiControlView.hpp>
#include <gui/framework/DevicePort.h>

WifiControlView::WifiControlView()
:animation(BITMAP_BTN_ANI_01_ID, BITMAP_BTN_ANI_04_ID, 10),
buttonCallback(this, &WifiControlView::buttonCallbackHandler),
animationEndedCallback(this, &WifiControlView::animationEnded),
listElementClickedCallback(this, &WifiControlView::listElementClicked),
onInputPasswordEvent(this, &WifiControlView::InputPasswordEvent),
onCancelPasswordEvent(this, &WifiControlView::CancelPasswordEvent),
tickCount(0),
curElement(NULL)
{
    //menuBg.setXY(0, 0);
    //menuBg.setBitmap(Bitmap(BITMAP_MAIN_BG_240X320PX_ID));
    //add(menuBg);
    switchBtn.setPosition(192, 41, 43, 30);
    switchBtn.setBitmaps(Bitmap(BITMAP_OFF_43X30_ID), Bitmap(BITMAP_ON_43X30_ID));
    switchBtn.setAction(buttonCallback);
    add(switchBtn);

    MenuContainer.setPosition(0, 71, 240, 250);
    add(MenuContainer);

    backBtn.setPosition(0, 41, 30, 30);
    backBtn.setBitmaps(Bitmap(BITMAP_BTNBACK_ID), Bitmap(BITMAP_BTNBACK_PRESSED_ID));
    backBtn.setAction(buttonCallback);
    add(backBtn);

    WifiControlDevicesTitle.setXY(0, 71);
    WifiControlDevicesTitle.setColor(touchgfx::Color::getColorFrom24BitRGB(4, 148, 148));
    WifiControlDevicesTitle.setLinespacing(0);
    WifiControlDevicesTitle.setTypedText(TypedText(T_BTCONTROLDEVICESTITLETXT));
    WifiControlDevicesTitle.setVisible(false);
    add(WifiControlDevicesTitle);

    WifiControlTitle.setPosition(40, 43,150,30);
    WifiControlTitle.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    WifiControlTitle.setLinespacing(0);
    WifiControlTitle.setTypedText(TypedText(T_WIFICONTROLTITLETXT));
    add(WifiControlTitle);

    WifiTurnOnTips.setPosition(0, 140, 240, 230);
    WifiTurnOnTips.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    WifiTurnOnTips.setLinespacing(0);
    WifiTurnOnTips.setWideTextAction(WIDE_TEXT_WORDWRAP);
    WifiTurnOnTips.setTypedText(TypedText(T_WIFITURNONTIPS));
    WifiTurnOnTips.setVisible(false);
    add(WifiTurnOnTips);

    animation.setXY(192, 41);
    animation.setVisible(false);
    add(animation);
    // Position and set the size of the scrollable container.
    // The width is the area is the list element width plus some extra
    // for space between element and scrollbar
    scrollCnt.setPosition(0, 90, 240, 230);
    scrollCnt.add(list);
    add(scrollCnt);

    mList.setAction(&listElementClickedCallback);
    count = 0;
}

void WifiControlView::setupScreen()
{
	add(mInputModal);
	mInputModal.hide();
}

void WifiControlView::tearDownScreen()
{

}

void WifiControlView::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &switchBtn) {
        clearListMenuElements();
        //Interaction1
        //When switchBTBtn clicked execute C++ code
        //Execute C++ code
        if (switchBtn.getState() == true) {
            switchBtn.setVisible(false);
            presenter->enableWifi();
            scrollCnt.setVisible(true);
        } else {
            presenter->disableWifi();
            scrollCnt.setVisible(false);
            scrollCnt.invalidate();
        }
        WifiControlDevicesTitle.setVisible(true == switchBtn.getState());
        WifiTurnOnTips.setVisible(false == switchBtn.getState());
        WifiControlDevicesTitle.invalidate();
        WifiTurnOnTips.invalidate();
    } else if (&src == &backBtn) {
        presenter->backOptionSelected();
    }
}

void WifiControlView::listElementClicked(CustomListElement& element)
{
    // The button of the list element has been pressed
    // so it is removed from the list
    /*list.remove(element);
    scrollCnt.invalidate();*/
    if (Wifi_GetState() != wifi_state_idle || 
        element.getStatus() == cesConnected)
        return;

    curElement = &element;

    if (curElement->isNeedPwd()) {
        mInputModal.setAddParams(element.mListMenuEleBuffer, onInputPasswordEvent, onCancelPasswordEvent);
        mInputModal.clearPassword();
        mInputModal.show();
        mStatusBar.hide();
    } else {
        mList.setCurElement(&element);
        mList.setCurElementStatus(cesConnecting);
        mList.startAnimation();
        Wifi_Connect(curElement->getAddress(), "");
    }
}

void WifiControlView::InputPasswordEvent(strEditBox txtInfo) {
    if (txtInfo.inputTxt != NULL) {
        TOUCH_GFX_LOG("passwor = %s\n", txtInfo.inputTxt);
    }
    mStatusBar.show();

    if (curElement != NULL) {
        mList.setCurElement(curElement);
        mList.setCurElementStatus(cesConnecting);
        mList.startAnimation();
        Wifi_Connect(curElement->getAddress(), txtInfo.inputTxt);
    }
}

void WifiControlView::CancelPasswordEvent() {
    mStatusBar.show();
    stopListAnimation();
}

void WifiControlView::setWifiState(bool state)
{
    switchBtn.forceState(state);
    //setBitmaps(Bitmap(BITMAP_OFF_43X30_ID), Bitmap(BITMAP_ON_43X30_ID));
    switchBtn.setVisible(true);
    switchBtn.invalidate();

    WifiControlDevicesTitle.setVisible(true == state);
    WifiTurnOnTips.setVisible(false == state);

    WifiControlDevicesTitle.invalidate();
    WifiTurnOnTips.invalidate();
}

void WifiControlView::animationEnded(const AnimatedImage& source)
{
    animation.startAnimation(!animation.isReverse(), false, true);
}

/**
* Start the animation in the same direction as it was stopped.
* Change the label text to reflect the state
*/
void WifiControlView::startAnimation()
{
    animation.setVisible(true);
    animation.startAnimation(animation.isReverse(), false, true);
}

/**
* Stop, or pause, the animation.
* Change the label text to reflect the state
*/
void WifiControlView::stopAnimation()
{
    animation.setVisible(false);
    animation.stopAnimation();
}

/**
* Tells whether the animation is running or not.
* @return Returns true if the animation is running, otherwise returns false
*/
bool WifiControlView::isAnimationRunning()
{
    return animation.isRunning();
}

/*void WifiControlView::updateListMenuElements()
{
    memset(ListMenuMap[numberOfListElements].ListMenuEleBuffer, 0, sizeof(ListMenuMap[numberOfListElements].ListMenuEleBuffer));
    if (numberOfListElements == 0){
        Unicode::strncpy(ListMenuMap[numberOfListElements].ListMenuEleBuffer, "Longcheer-office", sizeof(ListMenuMap[numberOfListElements].ListMenuEleBuffer));
    }
    else if (numberOfListElements == 1){
        Unicode::strncpy(ListMenuMap[numberOfListElements].ListMenuEleBuffer, "Hello,world", sizeof(ListMenuMap[numberOfListElements].ListMenuEleBuffer));
    }

    ListMenuMap[numberOfListElements].setupListElement(Bitmap(BITMAP_IC_WIFI_LOCK_SIGNAL_3_DARK_ID));

    ListMenuMap[numberOfListElements].setAction(listElementClickedCallback);
    list.add(ListMenuMap[numberOfListElements]);
    numberOfListElements++;
    scrollCnt.invalidate();
}*/

void WifiControlView::clearListMenuElements() {
    list.removeAll();
    mList.clear();
}

void WifiControlView::makeClearListMenuElements() {
    list.removeAll();
    mList.markClear();
}

void WifiControlView::updateListMenuElements(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi, bool needPwd) {
    uint16_t bmp_id;
    if (needPwd) {
        if (rssi <= 20)
            bmp_id = BITMAP_IC_WIFI_LOCK_SIGNAL_1_DARK_ID;
        else if (rssi <= 40)
            bmp_id = BITMAP_IC_WIFI_LOCK_SIGNAL_2_DARK_ID;
        else if (rssi <= 60)
            bmp_id = BITMAP_IC_WIFI_LOCK_SIGNAL_3_DARK_ID;
        else
            bmp_id = BITMAP_IC_WIFI_LOCK_SIGNAL_4_DARK_ID;
    } else {
        if (rssi <= 20)
            bmp_id = BITMAP_IC_WIFI_SIGNAL_1_DARK_ID;
        else if (rssi <= 40)
            bmp_id = BITMAP_IC_WIFI_SIGNAL_2_DARK_ID;
        else if (rssi <= 60)
            bmp_id = BITMAP_IC_WIFI_SIGNAL_3_DARK_ID;
        else
            bmp_id = BITMAP_IC_WIFI_SIGNAL_4_DARK_ID;
    }

    mList.addElement(address, Bitmap(bmp_id), strName, rssi, needPwd);
}

void WifiControlView::handleTickEvent()
{
    /*if (numberOfListElements < 2){
        updateListMenuElements();
    }*/

    tickCount++;
    if (tickCount % 1500 == 0) {
        if (switchBtn.getState() == true && 
            !mInputModal.isShowing() &&
            Wifi_GetState() == wifi_state_idle) {
            makeClearListMenuElements();
            Wifi_Scan();
            startAnimation();
        }
        tickCount = 0;
    }
}

void WifiControlView::updateListMenuLayout() {
    mList.doClear();
    mList.sort();
    mList.genListLayout(list);
    mList.addAnimation(list);
    scrollCnt.invalidate();
}

void WifiControlView::setCustomListStatus(CustomListElementStatus status) {
    if (status == cesConnected) {
        mList.clearElementStatus(cesConnected);
    }
    mList.setCurElementStatus(status);
}

