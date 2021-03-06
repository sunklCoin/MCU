/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui/custom_controls_screen/PopModal.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

PopModal::PopModal()
: m_onOK_callback(NULL),
m_onCancel_callback(NULL),
buttonClickedCallback(this, &PopModal::buttonClicked)
{
    setXY(0, 0);
    setShadeColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    setBackground(BitmapId(BITMAP_POP_BACKGROUND_ID));
    setShadeAlpha(150);
    
    /*backgroudBox.setPosition(24, 70, 192, 180);
    backgroudBox.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    backgroudBox.setAlpha(255);
    add(backgroudBox);*/

    txtPop.setPosition(0, 90, 192, 44);
    txtPop.setColor(touchgfx::Color::getColorFrom24BitRGB(46, 88, 122));
    txtPop.setLinespacing(0);
    txtPop.setTypedText(TypedText(T_POWEROFFPOP));
    txtPop.setWideTextAction(WIDE_TEXT_WORDWRAP);
    add(txtPop);

    imgPop.setXY(72, 29);
    imgPop.setBitmap(Bitmap(BITMAP_QUESTION_48_ID));
    add(imgPop);

    buttonOK.setPosition(128, 132, 60, 44);
    buttonOK.setBitmaps(Bitmap(BITMAP_MODAL_BUTTON_ID), Bitmap(BITMAP_MODAL_BUTTON_PRESSED_ID));
    buttonOK.setLabelText(TypedText(T_BUTTONOK));
    buttonOK.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonOK.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonOK.setAction(buttonClickedCallback);
    add(buttonOK);

    buttonCancel.setPosition(4, 132, 60, 44);
    buttonCancel.setBitmaps(Bitmap(BITMAP_MODAL_BUTTON_ID), Bitmap(BITMAP_MODAL_BUTTON_PRESSED_ID));
    buttonCancel.setLabelText(TypedText(T_BUTTONCANCLE));
    buttonCancel.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonCancel.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonCancel.setAction(buttonClickedCallback);
    add(buttonCancel);
}

void PopModal::setupScreen(const BitmapId imgId, const TypedTextId txtId)
{
    imgPop.setBitmap(Bitmap(imgId));
    imgPop.invalidate();

    txtPop.setTypedText(TypedText(txtId));
    txtPop.invalidate();
}

void PopModal::setAddParams(GenericCallback<void>& okCallback, GenericCallback<void>& cancelCallback)
{
    m_onOK_callback = &okCallback;
    m_onCancel_callback = &cancelCallback;
}

void PopModal::buttonClicked(const AbstractButton& source)
{
    if (&source == &buttonOK) {
        if (m_onOK_callback && m_onOK_callback->isValid()) {
            m_onOK_callback->execute();
        }
        hide();
    }
    else if (&source == &buttonCancel) {
        if (m_onCancel_callback && m_onCancel_callback->isValid())	{
            m_onCancel_callback->execute();
        }
        hide();
    }
}
