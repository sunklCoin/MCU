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
#include <gui/common/ImageMenu.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <math.h>


ImageMenu::ImageMenu(uint16_t imageMenuWidth, uint16_t imageMenuHeight, uint16_t elementHeight_, BitmapId backButtonImage, BitmapId backButtonPressedImage, BitmapId backgroundItemsImage) :
currentState(ALL_ELEMENTS_SHOWING),
animationCounter(0),
//elementWidth(elementHeight_),
elementHeight(elementHeight_),
    elementsInList(0),
    selectedIndex(0),
    onMenuItemSelected(this, &ImageMenu::menuItemSelectedhandler),
    onDescriptionFieldPressed(this, &ImageMenu::descriptionFieldPressedhandler)
{
    Application::getInstance()->registerTimerWidget(this);

    //logo.setBitmap(Bitmap(logoImage));
    //logo.setXY(0, 0);
    //logo.setTouchable(true);

    /*backButton.setBitmaps(Bitmap(backButtonImage), Bitmap(backButtonPressedImage));
    backButton.setXY(-backButton.getWidth(), 0);
    backButton.setAction(onDescriptionFieldPressed);*/
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
#if USE_BPP==1
	myColorPainter.setColor(1);
#else
	myColorPainter.setColor(Color::getColorFrom24BitRGB(0x00, 0xFF, 0xFF));
#endif
#endif
    scrollablemenuItemContainer.setXY(logo.getWidth(), 0);
    scrollablemenuItemContainer.setWidth(imageMenuWidth);
    scrollablemenuItemContainer.setHeight(imageMenuHeight);
    scrollablemenuItemContainer.setScrollbarsVisible(false);
    scrollablemenuItemContainer.add(menuItemContainer);
    scrollablemenuItemContainer.setScrollThreshold(10);

    menuItemContainer.setPosition(0, 0, 0, 0);
    //menuItemContainer.setHeight(imageMenuHeight);
	menuItemContainer.setWidth(imageMenuWidth);

    //backgroundItems.setBitmap(Bitmap(backgroundItemsImage));


    uint16_t descriptionFieldX = logo.getWidth() + elementWidth;

    viewPortDescriptionField.setPosition(descriptionFieldX, 0, imageMenuWidth - descriptionFieldX, imageMenuHeight);
    viewPortDescriptionField.setVisible(false);
    viewPortDescriptionField.add(descriptionField);
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    descriptionFieldBackground.setPosition(0, 0,240,320);
    descriptionFieldBackground.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));

    descriptionFieldSelectButton.setPosition(0,40,240,320);
    descriptionFieldSelectButton.setAction(onDescriptionFieldPressed);
#else
    descriptionFieldBackground.setXY(0, 0);
    descriptionFieldBackground.setBitmap(Bitmap(BITMAP_MENU_DESCRIPTION_FIELD_BACKGROUND_ID));

    descriptionFieldSelectButton.setXY(viewPortDescriptionField.getWidth() - Bitmap(BITMAP_MENU_DEMO_BUTTON_ID).getWidth(), viewPortDescriptionField.getHeight() - Bitmap(BITMAP_MENU_DEMO_BUTTON_ID).getHeight());
    descriptionFieldSelectButton.setBitmaps(Bitmap(BITMAP_MENU_DEMO_BUTTON_ID), Bitmap(BITMAP_MENU_DEMO_BUTTON_PRESSED_ID));
    descriptionFieldSelectButton.setAction(onDescriptionFieldPressed);
#endif
    descriptionFieldHeadline.setPosition(18, 26, 240, 36);
    descriptionFieldHeadline.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));

    descriptionFieldText.setPosition(18, 75, 240, 140);
    descriptionFieldText.setColor(Color::getColorFrom24BitRGB(0x00, 0x00, 0x00));

    descriptionField.setPosition(0, 0, descriptionFieldBackground.getWidth(), 320);
    descriptionField.add(descriptionFieldBackground);
    descriptionField.add(descriptionFieldSelectButton);
    descriptionField.add(descriptionFieldHeadline);
    descriptionField.add(descriptionFieldText);

    //add(logo);
    //add(backButton);
    add(scrollablemenuItemContainer);
    add(viewPortDescriptionField);

    for (int i = 0; i < SIZE; ++i)
    {
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
		menuItems[i].circle.setVisible(false);
        menuItemContainer.add(menuItems[i].circle);
#endif
        menuItems[i].button.setVisible(false);
        menuItemContainer.add(menuItems[i].button);
        menuItems[i].selectedImage.setVisible(false);
        menuItemContainer.add(menuItems[i].selectedImage);
		menuItems[i].menuText.setVisible(false);
		menuItemContainer.add(menuItems[i].menuText);
    }
    menuItemContainer.add(backgroundItems);

    setWidth(imageMenuWidth);
    setHeight(imageMenuHeight);
}

ImageMenu::~ImageMenu()
{
    Application::getInstance()->unregisterTimerWidget(this);
}

void ImageMenu::setMenuItemSelectedCallback(GenericCallback< const uint8_t >& callback)
{
    this->menuItemSelectedCallback = &callback;
}

void ImageMenu::handleTickEvent()
{
    if (currentState == ANIMATE_TO_SINGLE_ELEMENT)
    {
        animateToSingleElement();
    }
    else if (currentState == ANIMATE_TO_ALL_ELEMENTS)
    {
        animateToAllElements();
    }
}

void ImageMenu::addMenuItem(BitmapId buttonId, BitmapId selectedImageId, uint8_t callbackId, TEXTS headline, TEXTS text, bool showDemoButton, bool active)
{
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
	menuItems[elementsInList].circle.setPosition(60, menuItemContainer.getHeight(), 120, 120);
	menuItems[elementsInList].circle.setCenter(menuItems[elementsInList].circle.getWidth() / 2, (menuItems[elementsInList].circle.getHeight() - 36) /2);
	menuItems[elementsInList].circle.setRadius(40);
	menuItems[elementsInList].circle.setLineWidth(2);
	menuItems[elementsInList].circle.setPainter(myColorPainter);
	menuItems[elementsInList].circle.setVisible(true);
	menuItems[elementsInList].circle.invalidate();
#endif
    menuItems[elementsInList].button.setBitmaps(Bitmap(buttonId), Bitmap(selectedImageId));
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
	menuItems[elementsInList].button.setXY(95, menuItemContainer.getHeight() + 15);
#else
	menuItems[elementsInList].button.setXY(60, menuItemContainer.getHeight());
#endif
    menuItems[elementsInList].button.setAction(onMenuItemSelected);
    menuItems[elementsInList].button.setVisible(true);
    menuItems[elementsInList].button.invalidate();
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    menuItems[elementsInList].selectedImage.setBitmap(Bitmap(buttonId));
    menuItems[elementsInList].selectedImage.setXY(95, menuItemContainer.getHeight() + 15);
    menuItems[elementsInList].selectedImage.setVisible(true);
#else
    menuItems[elementsInList].selectedImage.setBitmap(Bitmap(selectedImageId));
    menuItems[elementsInList].selectedImage.setXY(menuItems[elementsInList].button.getX(), menuItemContainer.getHeight());
    menuItems[elementsInList].selectedImage.setVisible(false);
#endif
    menuItems[elementsInList].callbackId = callbackId;
    menuItems[elementsInList].headline = headline;
    menuItems[elementsInList].text = text;
    menuItems[elementsInList].active = active;
    menuItems[elementsInList].showDemoButton = showDemoButton;

	menuItems[elementsInList].menuText.setPosition(60, menuItemContainer.getHeight() + 90, 120, 20);
	menuItems[elementsInList].menuText.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
	menuItems[elementsInList].menuText.setTypedText(TypedText(headline));
	menuItems[elementsInList].menuText.setVisible(true);
	menuItems[elementsInList].menuText.invalidate();
    elementsInList++;

    // All elements must be of equal width
    menuItemContainer.setHeight(elementsInList * elementHeight);
	backgroundItems.setXY(0, menuItemContainer.getHeight());

}

void ImageMenu::menuItemSelectedhandler(const AbstractButton& button)
{
    for (uint8_t i = 0; i < elementsInList; ++i)
    {
        if (&menuItems[i].button == &button && menuItems[i].active)
        {
            selectedIndex = i;
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
            horizontalScrollAdjustmentTotalDistance = menuItemContainer.getWidth();// menuItems[i].circle.getX() + menuItemContainer.getX();
#else
            horizontalScrollAdjustmentTotalDistance = menuItems[i].button.getX() + menuItemContainer.getX();
#endif
            horizontalScrollStartingPosition = menuItemContainer.getX();

            descriptionFieldSelectButton.setVisible(menuItems[i].showDemoButton);
            descriptionField.setXY(-descriptionFieldBackground.getWidth(), 0);
            descriptionFieldHeadline.setTypedText(TypedText(menuItems[i].headline));
            descriptionFieldText.setTypedText(TypedText(menuItems[i].text));
            viewPortDescriptionField.setVisible(true);

            // Make the background items visible (if the animation moves the elements in the list
            // beyond the scrollable ares)
            //menuItemContainer.setWidth(elementsInList * elementWidth + backgroundItems.getWidth());
            menuItemContainer.setHeight(elementsInList * elementHeight + backgroundItems.getHeight());
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 0
            menuItems[selectedIndex].selectedImage.setVisible(true);
            menuItems[selectedIndex].selectedImage.invalidate();
#endif
            scrollablemenuItemContainer.setTouchable(false);
            backButton.setTouchable(false);
            setState(ANIMATE_TO_SINGLE_ELEMENT);

			if (menuItemSelectedCallback)
			{
				menuItemSelectedCallback->execute(menuItems[selectedIndex].callbackId);
			}
        }
    }
}

void ImageMenu::descriptionFieldPressedhandler(const AbstractButton& button)
{
    if (&button == &backButton)
    {
        backButton.setTouchable(false);
        setState(ANIMATE_TO_ALL_ELEMENTS);
    }
    else if (&button == &descriptionFieldSelectButton)
    {
        if (menuItemSelectedCallback)
        {
            menuItemSelectedCallback->execute(menuItems[selectedIndex].callbackId);
        }
        static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuScreenTransition();
    }
}

void ImageMenu::setState(States newState)
{
    animationCounter = 1;
    currentState = newState;

    // Make sure that the menu items are not active during animations
    for (uint8_t i = 0; i < elementsInList; ++i)
    {
        menuItems[i].button.setTouchable(currentState == ALL_ELEMENTS_SHOWING);
    }
}

void ImageMenu::animateToSingleElement()
{
    uint8_t horizontalSlideDuration;
    uint8_t descriptionFieldSlideDuration;

#ifdef NXP
    horizontalSlideDuration = 22 + (horizontalScrollAdjustmentTotalDistance / 30);
    descriptionFieldSlideDuration = 26;
#else
    horizontalSlideDuration = 16 + (horizontalScrollAdjustmentTotalDistance / 30);
    descriptionFieldSlideDuration = 20;
#endif

    if (animationCounter <= horizontalSlideDuration)
    {
        // First step: Move the selected item to the left part of the screen
        menuItemContainer.moveTo(horizontalScrollStartingPosition - EasingEquations::quadEaseInOut(animationCounter, 0, horizontalScrollAdjustmentTotalDistance, horizontalSlideDuration), menuItemContainer.getY());
        backButton.moveTo(-backButton.getWidth() + EasingEquations::quadEaseOut(animationCounter, 0, backButton.getWidth(), horizontalSlideDuration), 0);
        scrollablemenuItemContainer.invalidate();
    }
    else if (animationCounter <= horizontalSlideDuration + descriptionFieldSlideDuration)
    {
        // Second step: Show the description field
        int16_t delta = EasingEquations::quadEaseOut(animationCounter - horizontalSlideDuration, 0, descriptionFieldBackground.getWidth(), descriptionFieldSlideDuration);
        descriptionField.moveTo(-descriptionFieldBackground.getWidth() + delta, 0);
    }
    else
    {
        // Final step: stop the animation
        scrollablemenuItemContainer.setTouchable(false);
        backButton.setTouchable(true);
        setState(SINGLE_ELEMENT_SHOWING);
        animationCounter = 0;
    }
    animationCounter++;
}

void ImageMenu::animateToAllElements()
{
    uint8_t horizontalSlideDuration;
    uint8_t descriptionFieldSlideDuration;

#ifdef NXP
    horizontalSlideDuration = 22 + (horizontalScrollAdjustmentTotalDistance / 30);
    descriptionFieldSlideDuration = 26;
#else
    horizontalSlideDuration = 16 + (horizontalScrollAdjustmentTotalDistance / 30);
    descriptionFieldSlideDuration = 20;
#endif

    if (animationCounter <= descriptionFieldSlideDuration)
    {
        // First step: Collaps the description field
        int16_t delta = EasingEquations::quadEaseOut(animationCounter, 0, descriptionFieldBackground.getWidth(), descriptionFieldSlideDuration);
        descriptionField.moveTo(-delta, 0);
    }
    else if (animationCounter <= horizontalSlideDuration + descriptionFieldSlideDuration)
    {
        // Second step: move list back to the position before the animation to single element
        menuItemContainer.moveTo(horizontalScrollStartingPosition - horizontalScrollAdjustmentTotalDistance + EasingEquations::quadEaseInOut(animationCounter - descriptionFieldSlideDuration, 0, horizontalScrollAdjustmentTotalDistance, horizontalSlideDuration), menuItemContainer.getY());
        backButton.moveTo(- EasingEquations::quadEaseIn(animationCounter, 0, backButton.getWidth(), horizontalSlideDuration), 0);
        scrollablemenuItemContainer.invalidate();
    }
    else
    {
        // Final step: stop the animation

        // Make sure that you can not scroll beyond the elements in the list
        menuItemContainer.setWidth(elementsInList * elementWidth);

        menuItems[selectedIndex].selectedImage.setVisible(false);
        menuItems[selectedIndex].selectedImage.invalidate();

        scrollablemenuItemContainer.setTouchable(true);
        backButton.setTouchable(false);
        viewPortDescriptionField.setVisible(false);
        setState(ALL_ELEMENTS_SHOWING);
        animationCounter = 0;
    }
    animationCounter++;

}

