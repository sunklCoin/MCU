/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui/btcontrol_screen/BTControlView.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#ifndef SIMULATOR
#include <remoter_messsage_gui.h>
#endif

BTControlView::BTControlView() :
animation(BITMAP_BTN_ANI_01_ID, BITMAP_BTN_ANI_04_ID, 10),
buttonCallback(this, &BTControlView::buttonCallbackHandler),
animationEndedCallback(this, &BTControlView::animationEnded),
listElementClickedCallback(this, &BTControlView::listElementClicked),
numberOfListElements(0)
{
    //menuBg.setXY(0, 0);
    //menuBg.setBitmap(Bitmap(BITMAP_MAIN_BG_240X320PX_ID));
    //add(menuBg);

    switchBTBtn.setPosition(192, 41, 43, 30);
    switchBTBtn.setBitmaps(Bitmap(BITMAP_OFF_43X30_ID), Bitmap(BITMAP_ON_43X30_ID));
    switchBTBtn.setAction(buttonCallback);
    add(switchBTBtn);

    MenuContainer.setPosition(0, 71, 240, 250);
    add(MenuContainer);

    backBtn.setPosition(0, 41, 30, 30);
    backBtn.setBitmaps(Bitmap(BITMAP_BTNBACK_ID), Bitmap(BITMAP_BTNBACK_PRESSED_ID));
    backBtn.setAction(buttonCallback);
    add(backBtn);

    BtControlDevicesTitle.setXY(0, 71);
    BtControlDevicesTitle.setColor(touchgfx::Color::getColorFrom24BitRGB(4, 148, 148));
    BtControlDevicesTitle.setLinespacing(0);
    BtControlDevicesTitle.setTypedText(TypedText(T_BTCONTROLDEVICESTITLETXT));
    BtControlDevicesTitle.setVisible(false);
    add(BtControlDevicesTitle);

    BTControlTitle.setXY(66, 43);
    BTControlTitle.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    BTControlTitle.setLinespacing(0);
    BTControlTitle.setTypedText(TypedText(T_BTCONTROLTITLETXT));
    add(BTControlTitle);

    BtTurnOnTips.setPosition(0, 140, 240, 230);
    BtTurnOnTips.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    BtTurnOnTips.setLinespacing(0);
    BtTurnOnTips.setWideTextAction(WIDE_TEXT_WORDWRAP);
    BtTurnOnTips.setTypedText(TypedText(T_BTTURNONTIPS));
    BtTurnOnTips.setVisible(false);
    add(BtTurnOnTips);

    // Setup background
    //imgBackground.setBitmap(Bitmap(BITMAP_BG_ID));
    //imgBackground.setXY(0, 0);
    //add(imgBackground);
    animation.setXY(192, 41);
    //animation.setDoneAction(animationEndedCallback);
    animation.setVisible(false);
    add(animation);
#if 0

    Unicode::strncpy(listElements[0].ListMenuEleBuffer, "pm", sizeof(listElements[0].ListMenuEleBuffer));
    listElements[0].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID));
    Unicode::strncpy(listElements[1].ListMenuEleBuffer, "am", sizeof(listElements[1].ListMenuEleBuffer));
    listElements[1].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID));
    Unicode::strncpy(listElements[2].ListMenuEleBuffer, "61:13:E8AA:3E:D2", sizeof(listElements[2].ListMenuEleBuffer));//djkqwxz-
    listElements[2].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID));
    //Unicode::snprintf(listElements[3].deviceTextBuffer, 60, "%s", "4");
    //listElements[3].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[3].deviceTextBuffer);
    //Unicode::snprintf(listElements[4].deviceTextBuffer, 60, "%s", "5");
    //listElements[4].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[4].deviceTextBuffer);
    //Unicode::snprintf(listElements[5].deviceTextBuffer, 60, "%s", "6");
    //listElements[5].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[5].deviceTextBuffer);
    //Unicode::snprintf(listElements[6].deviceTextBuffer, 60, "%s", "7");
    //listElements[6].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[6].deviceTextBuffer);
    //Unicode::snprintf(listElements[7].deviceTextBuffer, 60, "%s", "8");
    //listElements[7].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[7].deviceTextBuffer);
    //Unicode::snprintf(listElements[8].deviceTextBuffer, 60, "%s", "9");
    //listElements[8].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[8].deviceTextBuffer);
    //Unicode::snprintf(listElements[9].deviceTextBuffer, 60, "%s", "0");
    //listElements[9].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID), listElements[9].deviceTextBuffer);

    for (uint8_t i = 0; i < 3; ++i){
        listElements[i].setAction(listElementClickedCallback);
        list.add(listElements[i]);
    }

    Unicode::strncpy(ListMenuMap[0].ListMenuEleBuffer, "pm", sizeof(ListMenuMap[0].ListMenuEleBuffer));
    ListMenuMap[0].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID));

    for (uint8_t i = 0; i < 1; ++i){
        ListMenuMap[0].setAction(listElementClickedCallback);
        list.add(ListMenuMap[0]);
    }
#endif // 0
    // Position and set the size of the scrollable container.
    // The width is the area is the list element width plus some extra
    // for space between element and scrollbar
    scrollCnt.setPosition(0, 90, 240, 230);
    scrollCnt.add(list);
    add(scrollCnt);

    count = 0;
}


void BTControlView::setupScreen()
{

}

void BTControlView::tearDownScreen()
{

}


void BTControlView::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &switchBTBtn)
    {
        //Interaction1
        //When switchBTBtn clicked execute C++ code
        //Execute C++ code
        if (switchBTBtn.getState() == true){
            switchBTBtn.setVisible(false);
            presenter->enableBlueTooth();
            scrollCnt.setVisible(true);
        }
        else{
            presenter->disableBlueTooth();
            scrollCnt.setVisible(false);
            list.removeAll();
            scrollCnt.invalidate();
        }
        BtControlDevicesTitle.setVisible(true == switchBTBtn.getState());
        BtTurnOnTips.setVisible(false == switchBTBtn.getState());
        BtControlDevicesTitle.invalidate();
        BtTurnOnTips.invalidate();
    }
    else if (&src == &backBtn)
    {
        presenter->backOptionSelected();
    }
}

void BTControlView::animationEnded(const AnimatedImage& source)
{
    animation.startAnimation(!animation.isReverse(), false, true);
}

void BTControlView::listElementClicked(CustomListElement& element)
{
    // The button of the list element has been pressed
    // so it is removed from the list
    list.remove(element);
    scrollCnt.invalidate();
}

void BTControlView::setBluetoothState(bool state)
{
    switchBTBtn.forceState(state);
    //setBitmaps(Bitmap(BITMAP_OFF_43X30_ID), Bitmap(BITMAP_ON_43X30_ID));
    switchBTBtn.setVisible(true);
    switchBTBtn.invalidate();


    BtControlDevicesTitle.setVisible(true == state);
    BtTurnOnTips.setVisible(false == state);

    BtControlDevicesTitle.invalidate();
    BtTurnOnTips.invalidate();
}


/**
* Start the animation in the same direction as it was stopped.
* Change the label text to reflect the state
*/
void BTControlView::startAnimation()
{
    animation.setVisible(true);
    animation.startAnimation(animation.isReverse(), false, true);
}

/**
* Stop, or pause, the animation.
* Change the label text to reflect the state
*/
void BTControlView::stopAnimation()
{
    animation.setVisible(false);
    animation.stopAnimation();
}

/**
* Tells whether the animation is running or not.
* @return Returns true if the animation is running, otherwise returns false
*/
bool BTControlView::isAnimationRunning()
{
    return animation.isRunning();
}

/*void BTControlView::updateListMenuElements()
{
    Unicode::strncpy(ListMenuMap[numberOfListElements].ListMenuEleBuffer, "djkqwxz-:", sizeof(ListMenuMap[numberOfListElements].ListMenuEleBuffer));
    ListMenuMap[numberOfListElements].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID));

    ListMenuMap[numberOfListElements].setAction(listElementClickedCallback);
    list.add(ListMenuMap[numberOfListElements]);
    numberOfListElements++;
    scrollCnt.invalidate();
}*/

void BTControlView::handleTickEvent()
{
    /*if (numberOfListElements < 20) {
        updateListMenuElements();
    }*/
}

void BTControlView::updateListMenuElements(Unicode::UnicodeChar* strDeviceName, Unicode::UnicodeChar* strAddress) {
    memset(ListMenuMap[numberOfListElements].ListMenuEleBuffer, 0, sizeof(ListMenuMap[numberOfListElements].ListMenuEleBuffer));
    if (Unicode::strlen(strDeviceName) > 0) {
        Unicode::strncpy(ListMenuMap[numberOfListElements].ListMenuEleBuffer, strDeviceName, BT_DEVICENAME_LEN);
    } else {
        Unicode::strncpy(ListMenuMap[numberOfListElements].ListMenuEleBuffer, strAddress, Unicode::strlen(strAddress));
    }
    ListMenuMap[numberOfListElements].setupListElement(Bitmap(BITMAP_BLUETOOTH_32X32_ID));

    ListMenuMap[numberOfListElements].setAction(listElementClickedCallback);
    list.add(ListMenuMap[numberOfListElements]);
    numberOfListElements++;
    scrollCnt.invalidate();
}
