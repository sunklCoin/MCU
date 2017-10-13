/******************************************************************************
*
* @brief     This file is part of the TouchGFX 4.8.0 evaluation distribution.
*
* @author    Draupner Graphics A/S <http://www.touchgfx.com>
*
******************************************************************************
*
* @section Copyright
*
* This file is free software and is provided for example purposes. You may
* use, copy, and modify within the terms and conditions of the license
* agreement.
*
* This is licensed software for evaluation use, any use must strictly comply
* with the evaluation license agreement provided with delivery of the
* TouchGFX software.
*
* The evaluation license agreement can be seen on www.touchgfx.com
*
* @section Disclaimer
*
* DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
* no obligation to support this software. Draupner Graphics A/S is providing
* the software "AS IS", with no express or implied warranties of any kind,
* including, but not limited to, any implied warranties of merchantability
* or fitness for any particular purpose or warranties against infringement
* of any proprietary rights of a third party.
*
* Draupner Graphics A/S can not be held liable for any consequential,
* incidental, or special damages, or any other relief, or for any claim by
* any third party, arising from your use of this software.
*
*****************************************************************************/
#include <gui/common/CustomListElement.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string.h>
#include <touchgfx/widgets/AbstractButton.hpp>

CustomListElement::CustomListElement() : 
    Container(), 
    viewCallback(NULL),
    mNeedPwd(false),
    mNeedDel(false),
    mStatus(cesNone),
    buttonClickedCallback(this, &CustomListElement::buttonClicked)
{
    //
}

void CustomListElement::setupListElement(const Bitmap& bmp)
{
    // Setup background
    buttonImg.setColor(Color::getColorFrom24BitRGB(85, 88, 89));
    buttonImg.setPosition(0, 0, 240, 37 + 2);
    add(buttonImg);

    // Setup 
    btn.setBitmaps(Bitmap(BITMAP_INVALID), Bitmap(BITMAP_ITEM_BUTTON_PRESSED_ID));
    btn.setXY(buttonImg.getWidth() - btn.getWidth(), 0);
    btn.setAction(buttonClickedCallback);
    add(btn);

    smallIcon.setBitmap(bmp);
    smallIcon.setXY(0, /*0*/3);
    add(smallIcon);

    ListMenuEle.setWildcard(mListMenuEleBuffer);
    ListMenuEle.setTypedText(TypedText(T_LISTMENUELETXT));
    ListMenuEle.setPosition(smallIcon.getX() + smallIcon.getWidth() + 5, 9, buttonImg.getWidth() - smallIcon.getWidth(), 20);
    ListMenuEle.setColor(touchgfx::Color::getColorFrom24BitRGB(252, 248, 248));
    add(ListMenuEle);

    taHint.setPosition(smallIcon.getX() + smallIcon.getWidth() + 5, 22, buttonImg.getWidth() - smallIcon.getWidth(), 12);
    taHint.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    taHint.setVisible(false);
    add(taHint);

    // Setup CustomListElement dimensions
    setHeight(buttonImg.getHeight() + 1);
    setWidth(buttonImg.getWidth());
}

void CustomListElement::setStatus(CustomListElementStatus status)
{
    mStatus = status;
    if (status == cesNone) {
        ListMenuEle.setY(9);
        taHint.setVisible(false);
    } else {
        ListMenuEle.setY(2);
        taHint.setVisible(true);
        switch(status) {
            case cesConnecting:
                taHint.setTypedText(TypedText(T_WIFI_CONNECTING));
                break;
            case cesConnected:
                taHint.setTypedText(TypedText(T_WIFI_CONNECT_OK));
                break;
            case cesConnectError:
                taHint.setTypedText(TypedText(T_WIFI_CONNECT_FAIL));
                break;
            case cesDisconnected:
                taHint.setTypedText(TypedText(T_WIFI_DISCONNECT));
                break;
        }
    }

    invalidate();
}

void CustomListElement::setupListElement(uint8_t address[], const Unicode::UnicodeChar* strName, int rssi, bool needPwd) {
    memcpy(mAddress, address, sizeof(mAddress));
    memset(mListMenuEleBuffer, 0, sizeof(mListMenuEleBuffer));
    Unicode::strncpy(mListMenuEleBuffer, strName, LISTMENUELE_SIZE-1);
    mRssi = rssi;
    mNeedPwd = needPwd;
}

void CustomListElement::setupListElement(const Bitmap& bmp, uint8_t address[], const Unicode::UnicodeChar* strName, int rssi, bool needPwd)
{
    setupListElement(address, strName, rssi, needPwd);
    setupListElement(bmp);
    buttonClickedCallback = Callback<CustomListElement, const AbstractButton&> (this, &CustomListElement::buttonClicked);
}

void CustomListElement::buttonClicked(const AbstractButton& source)
{
    // Inform the view of the event
    if (viewCallback != NULL && viewCallback->isValid()) {
        viewCallback->execute(*this);
    }
}
