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
#ifndef IMAGEMENU_HPP_
#define IMAGEMENU_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/ImageMenuElement.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#elif USE_BPP==4
#include <touchgfx/widgets/canvas/PainterGRAY4.hpp>
#include <touchgfx/widgets/canvas/PainterGRAY4Bitmap.hpp>
#elif USE_BPP==2
#include <touchgfx/widgets/canvas/PainterGRAY2.hpp>
#include <touchgfx/widgets/canvas/PainterGRAY2Bitmap.hpp>
#elif USE_BPP==1
#include <touchgfx/widgets/canvas/PainterBW.hpp>
#else
#error Unknown USE_BPP
#endif
using namespace touchgfx;

class ImageMenu : public Container
{
public:
    ImageMenu(uint16_t imageMenuWidth, uint16_t imageMenuHeight, uint16_t elementWidth_, BitmapId backButtonImage, BitmapId backButtonPressedImage, BitmapId backgroundItemsImage);
    virtual ~ImageMenu();

    virtual void handleTickEvent();

    void setMenuItemSelectedCallback(GenericCallback< const uint8_t >& callback);

    void addMenuItem(BitmapId buttonId, BitmapId selectedImageId, uint8_t callbackId, TEXTS headline, TEXTS text, bool showDemoButton, bool active = true);

private:
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
#if !defined(USE_BPP) || USE_BPP==16
	PainterRGB565 myColorPainter;
	PainterRGB565 myPressColorPainter;
	PainterRGB565Bitmap myBitmapPainter;
	PainterRGB565Bitmap myBitmapPainter2;
#elif USE_BPP==24
	PainterRGB888 myColorPainter;
	PainterRGB888Bitmap myBitmapPainter;
	PainterRGB888Bitmap myBitmapPainter2;
#elif USE_BPP==4
	PainterGRAY4 myColorPainter;
	PainterGRAY4Bitmap myBitmapPainter;
	PainterGRAY4Bitmap myBitmapPainter2;
#elif USE_BPP==2
	PainterGRAY2 myColorPainter;
	PainterGRAY2Bitmap myBitmapPainter;
	PainterGRAY2Bitmap myBitmapPainter2;
#elif USE_BPP==1
	PainterBW myColorPainter;
#else
#error Unknown USE_BPP
#endif
#endif
    enum States
    {
        ANIMATE_TO_SINGLE_ELEMENT,
        ANIMATE_TO_ALL_ELEMENTS,
        SINGLE_ELEMENT_SHOWING,
        ALL_ELEMENTS_SHOWING
    } currentState;

    uint8_t animationCounter;
    int16_t horizontalScrollAdjustmentTotalDistance;
    int16_t horizontalScrollStartingPosition;

    uint16_t elementWidth;
	uint16_t elementHeight;
    uint8_t elementsInList;
    uint8_t selectedIndex;

    static const uint8_t SIZE = 15;

    struct MenuItem
    {
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
		Circle circle;
#endif
        Button button;
        Image selectedImage;
        uint8_t callbackId;
        TEXTS headline;
        TEXTS text;
        bool active;
        bool showDemoButton;
		TextArea menuText;
    } menuItems[SIZE];

    Image backgroundItems;

    Image logo;
    Button backButton;

    Container viewPortDescriptionField;
    Container descriptionField;
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    Box descriptionFieldBackground;
#else
    Image descriptionFieldBackground;
#endif
    Button descriptionFieldSelectButton;
    TextArea descriptionFieldHeadline;
    TextArea descriptionFieldText;

    Container menuItemContainer;
    ScrollableContainer scrollablemenuItemContainer;

    GenericCallback< const uint8_t >* menuItemSelectedCallback;
    Callback<ImageMenu, const AbstractButton&> onMenuItemSelected;
    Callback<ImageMenu, const AbstractButton&> onDescriptionFieldPressed;

    void menuItemSelectedhandler(const AbstractButton& button);
    void descriptionFieldPressedhandler(const AbstractButton& button);

    void setState(States newState);
    void animateToSingleElement();
    void animateToAllElements();
    void animateToNewSelected();
};


#endif /* IMAGEMENU_HPP_ */
