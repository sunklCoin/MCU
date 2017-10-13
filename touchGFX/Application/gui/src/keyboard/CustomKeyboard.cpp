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
#include <gui/keyboard/CustomKeyboard.hpp>
#include <gui/common/Utils.hpp>
CustomKeyboard::CustomKeyboard() : keyboard(),
    modeBtnTextArea(),
    capslockPressed(this, &CustomKeyboard::capslockPressedHandler),
    backspacePressed(this, &CustomKeyboard::backspacePressedHandler),
    modePressed(this, &CustomKeyboard::modePressedHandler),
    keyPressed(this, &CustomKeyboard::keyPressedhandler),
    alphaKeys(true),
    uppercaseKeys(false),
    firstCharacterEntry(false)
{
    //Set the callbacks for the callback areas of the keyboard and set its layout.
    layout.callbackAreaArray[0].callback = &capslockPressed;
    layout.callbackAreaArray[1].callback = &backspacePressed;
    layout.callbackAreaArray[2].callback = &modePressed;
    keyboard.setKeyListener(keyPressed);

    //keyboard.setPosition(0, 133, 240, 186);
    keyboard.setTextIndentation();
    //Allocate the buffer associated with keyboard.
    memset(buffer, 0, sizeof(buffer));
    keyboard.setBuffer(buffer, BUFFER_SIZE);

    uppercaseKeys = true;
    firstCharacterEntry = true;

    //modeBtnTextArea.setPosition(5, 196, 56, 40);
    modeBtnTextArea.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

	setKeyMappingList();
    add(keyboard);
    add(modeBtnTextArea);
}


void CustomKeyboard::setupScreen(int keyboardX, int keyboardY, int width, int Height, int textAreaX,int textAreaY)
{
	keyboard.setPosition(keyboardX, keyboardY, width, Height);
	modeBtnTextArea.setPosition(1, keyboardY + KEYBOARD_KEY_OFFSET_Y + 145, 34, 41);
	layout.textAreaPosition.x = textAreaX;
	layout.textAreaPosition.y = textAreaY;
	keyboard.setLayout(&layout);
	updateEditArea();
}

void CustomKeyboard::setKeyMappingList()
{
    if (alphaKeys)
    {
        modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
        if (uppercaseKeys)
        {
            keyboard.setKeymappingList(&keyMappingListAlphaUpper);
        }
        else
        {
            keyboard.setKeymappingList(&keyMappingListAlphaLower);
        }
    }
    else
    {
        modeBtnTextArea.setTypedText(TypedText(T_NUMMODE));
        if (uppercaseKeys)
        {
            keyboard.setKeymappingList(&keyMappingListNumUpper);
        }
        else
        {
            keyboard.setKeymappingList(&keyMappingListNumLower);
        }
    }
}

void CustomKeyboard::backspacePressedHandler()
{
    uint16_t pos = keyboard.getBufferPosition();
    if (pos > 0)
    {
        //Delete the previous entry in the buffer and decrement the position.
        buffer[pos - 1] = 0;
        keyboard.setBufferPosition(pos - 1);

        //Change keymappings if we have reached the first position.
        if (1 == pos)
        {
            firstCharacterEntry = true;
            uppercaseKeys = true;
            setKeyMappingList();
        }
    }
}

void CustomKeyboard::capslockPressedHandler()
{
    uppercaseKeys = !uppercaseKeys;
    setKeyMappingList();
}

void CustomKeyboard::modePressedHandler()
{
    alphaKeys = !alphaKeys;

    // if we have changed back to alpha and still has no chars in the buffer,
    // we show upper case letters.
    if (firstCharacterEntry && alphaKeys)
    {
        uppercaseKeys = true;
    }
    else
    {
        uppercaseKeys = false;
    }
    setKeyMappingList();
}

void CustomKeyboard::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
    // After the first keypress, the keyboard will shift to lowercase.
    if (firstCharacterEntry && keyChar != 0)
    {
        firstCharacterEntry = false;
        uppercaseKeys = false;
        setKeyMappingList();
    }
	//textEdit->invalidate();
	updateEditArea();
}
//void CustomKeyboard::setTextAreaHandle(TextAreaWithOneWildcard* passwordEdit, Unicode::UnicodeChar* passwordEditBuffer){
//	memset(passwordEditBuffer, 0, sizeof(passwordEditBuffer));
//	keyboard.setBuffer(passwordEditBuffer, BUFFER_SIZE);
//	textEdit = passwordEdit;
//}

void CustomKeyboard::setTouchable(bool touch)
{
    Container::setTouchable(touch);
    keyboard.setTouchable(touch);
}

void CustomKeyboard::setKeyboardHandle(GenericCallback<Unicode::UnicodeChar*>& keyCallback)
{
	m_onKey_callback = &keyCallback;
}

void CustomKeyboard::updateEditArea() 
{
	if (m_onKey_callback && m_onKey_callback->isValid())
	{
		m_onKey_callback->execute(buffer);
	}
}

void CustomKeyboard::clearBuffer() {
    memset(buffer, 0, sizeof(buffer));
    keyboard.setBufferPosition(0);
}
