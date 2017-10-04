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
#ifndef CUSTOM_LIST_ELEMENT_HPP
#define CUSTOM_LIST_ELEMENT_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Box.hpp>

using namespace touchgfx;

class MainView;

/**
* CustomListElement is the representation of each entry in our list.
* The list element contains an image and a button.
*/
class CustomListElement : public Container
{
private:
    Image smallIcon;
    Box buttonImg;
    Button btn;
    TextAreaWithOneWildcard ListMenuEle;

    /**
    * Callback that is called when the button is clicked
    */
    Callback<CustomListElement, const AbstractButton&> buttonClickedCallback;
    /**
    * Callback that that notifies the creator of the list element of an event
    */
    GenericCallback< CustomListElement& >* viewCallback;
protected:
    static const uint16_t LISTMENUELE_SIZE = 60;
    static const uint16_t ADDRESS_SIZE = 6;
    uint8_t mAddress[ADDRESS_SIZE];
    int mRssi;

public:
    touchgfx::Unicode::UnicodeChar mListMenuEleBuffer[LISTMENUELE_SIZE];

    CustomListElement();
    /**
    * Initialize this containers widgets
    */
    void setupListElement(const Bitmap& bmp);
    void setupListElement(const Bitmap& bmp, uint8_t address[], const Unicode::UnicodeChar* strName, int rssi = 0);
    int getRssi() {return mRssi; }
	uint8_t* getAddress() { return mAddress; }
    int16_t getIconX() { return getX() + smallIcon.getX(); }
    int16_t getIconY() { return getY() + smallIcon.getY(); }
	void setIconVisible(bool visible) { smallIcon.setVisible(visible); }

    /**
    * Setup the view callback
    */
    void setAction(GenericCallback< CustomListElement& >* callback) {
        viewCallback = callback;
    }

    /**
    * Handler of button click events
    */
    void buttonClicked(const AbstractButton& source);
};

#endif /* CUSTOM_LIST_ELEMENT_HPP */
