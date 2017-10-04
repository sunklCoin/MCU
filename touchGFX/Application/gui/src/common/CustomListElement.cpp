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
    buttonClickedCallback(this, &CustomListElement::buttonClicked)
{

}

void CustomListElement::setupListElement(const Bitmap& bmp)
{
    // Setup background
    buttonImg.setColor(Color::getColorFrom24BitRGB(85, 88, 89));
    buttonImg.setPosition(0, 0, 240, 37);
    add(buttonImg);
    // Setup 
    btn.setBitmaps(Bitmap(BITMAP_INVALID), Bitmap(BITMAP_ITEM_BUTTON_PRESSED_ID));
    btn.setXY(buttonImg.getWidth() - btn.getWidth(), 0);
    btn.setAction(buttonClickedCallback);
    add(btn);

    smallIcon.setBitmap(bmp);
    smallIcon.setXY(0, 0);
    add(smallIcon);

    ListMenuEle.setWildcard(mListMenuEleBuffer);
    ListMenuEle.setTypedText(TypedText(T_LISTMENUELETXT));
    ListMenuEle.setPosition(smallIcon.getX() + smallIcon.getWidth() + 5, 10, buttonImg.getWidth() - smallIcon.getWidth(), 20);
    ListMenuEle.setColor(touchgfx::Color::getColorFrom24BitRGB(252, 248, 248));
    add(ListMenuEle);

    // Setup CustomListElement dimensions
    setHeight(buttonImg.getHeight() + 1);
    setWidth(buttonImg.getWidth());
}

void CustomListElement::setupListElement(const Bitmap& bmp, uint8_t address[], const Unicode::UnicodeChar* strName, int rssi)
{
    memcpy(mAddress, address, sizeof(mAddress));
    memset(mListMenuEleBuffer, 0, sizeof(mListMenuEleBuffer));
    Unicode::strncpy(mListMenuEleBuffer, strName, LISTMENUELE_SIZE-1);
    mRssi = rssi;
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

