/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui/keyboard/InputModal.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
InputModal::InputModal()
: m_onOK_callback(NULL),
m_onCancel_callback(NULL),
buttonClickedCallback(this, &InputModal::buttonClicked),
onUpdateTextEditArea(this, &InputModal::updateTextEditArea)

{
    setBackground(BitmapId(BITMAP_CONTROLS_BACKGROUND_ID), 0, 0);
    setShadeColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    //setShadeAlpha(125);
    boxInput.setPosition(0, 0, 240, 122);
    boxInput.setColor(touchgfx::Color::getColorFrom24BitRGB(247, 249, 250));
    add(boxInput);

    passwordHeadline.setXY(0, 22);
    passwordHeadline.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    passwordHeadline.setLinespacing(0);
    passwordHeadline.setTypedText(TypedText(T_PASSWORDHEADLINE));
    add(passwordHeadline);

	memset(devicenameBuffer,L' ', sizeof(devicenameBuffer));
	devicename.setWildcard(devicenameBuffer);
	devicename.setTypedText(TypedText(T_CONNECTHEADLINE));
    devicename.setXY(0, 0);
    devicename.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    devicename.setLinespacing(0);
    add(devicename);

	memset(passwordEditBuffer, ' ', PASSWORDEDIT_SIZE);
	passwordEdit.setWildcard(passwordEditBuffer);
	passwordEdit.setTypedText(TypedText(T_PASSWORDEDIT));
	passwordEdit.setPosition(13, 42,210,20);
	passwordEdit.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
	passwordEdit.setLinespacing(0);
	add(passwordEdit);

	buttonOK.setPosition(167, 78, 60, 44);
	buttonOK.setBitmaps(Bitmap(BITMAP_MODAL_BUTTON_ID), Bitmap(BITMAP_MODAL_BUTTON_PRESSED_ID));
	buttonOK.setLabelText(TypedText(T_BUTTONOK));
	buttonOK.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	buttonOK.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	add(buttonOK);
	buttonOK.setAction(buttonClickedCallback);

	buttonCancel.setPosition(13, 78, 60, 44);
	buttonCancel.setBitmaps(Bitmap(BITMAP_MODAL_BUTTON_ID), Bitmap(BITMAP_MODAL_BUTTON_PRESSED_ID));
	buttonCancel.setLabelText(TypedText(T_BUTTONCANCLE));
	buttonCancel.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	buttonCancel.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	add(buttonCancel);
	buttonCancel.setAction(buttonClickedCallback);

    boxLine.setPosition(13, 67, 214, 2);
    boxLine.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 171, 245));
    add(boxLine);

	keypad.setPosition(0, 0, 240, 320);
	//setKeyboardHandle function must before setupScreen of keypad
	keypad.setKeyboardHandle(onUpdateTextEditArea);
	keypad.setupScreen(0, 133, 240, 186, 20,-45);
	//keypad.setTextAreaHandle(&passwordEdit, passwordEditBuffer);
	add(keypad);
}

void InputModal::setAddParams(const Unicode::UnicodeChar* strHeadLine, 
    GenericCallback<strEditBox>& okCallback, GenericCallback<>& cancelCallback) {
    memset(devicenameBuffer, 0, sizeof(devicenameBuffer));
    Unicode::strncpy(devicenameBuffer, strHeadLine, DEVICENAME_SIZE - 1);
    devicename.invalidate();
    m_onOK_callback = &okCallback;
    m_onCancel_callback = &cancelCallback;
}

void InputModal::buttonClicked(const AbstractButton& source) {
	strEditBox addInfo = {0};
	memset(&addInfo, 0, sizeof(strEditBox));
	//addInfo.inputTxt = "123456789";
	if (passwordEditBuffer != NULL){
		int i = 0;
		while (passwordEditBuffer[i] != '\0' && i < Unicode::strlen(passwordEditBuffer)){
			addInfo.inputTxt[i] = (uint8_t)passwordEditBuffer[i];
			//TOUCH_GFX_LOG("inputTxt = %c\n", addInfo.inputTxt);
			i++;
		}
	}

	if (&source == &buttonOK) {
		if (m_onOK_callback && m_onOK_callback->isValid()) {
			m_onOK_callback->execute(addInfo);
		}
		hide();
	} else if (&source == &buttonCancel) {
		if (m_onCancel_callback && m_onCancel_callback->isValid())	{
			m_onCancel_callback->execute();
		}
		hide();
       }
}

void InputModal::updateTextEditArea(Unicode::UnicodeChar* buff)
{
	memset(passwordEditBuffer, 0, sizeof(buff));
	Unicode::strncpy(passwordEditBuffer, buff, PASSWORDEDIT_SIZE);
	passwordEdit.invalidate();
}

void InputModal::clearPassword()
{
    memset(passwordEditBuffer, 0, sizeof(passwordEditBuffer));
    keypad.clearBuffer();
}

