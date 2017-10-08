#include <gui/mainmenu_screen/MainMenuView.hpp>
#include <gui/common/McuLoadSlider.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/FrontendApplication.hpp>

MainMenuView::MainMenuView():
imageMenu(HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - 40, Bitmap(BITMAP_MAINMENU_BTN_BT_ID).getHeight(), BITMAP_INVALID, BITMAP_INVALID, BITMAP_INVALID),
currentState(NO_ANIMATION),
animationCounter(0),
tickCounter(0),
dragX(0),
dragY(0),
infoScreens(EAST),
onImageMenuItemSelected(this, &MainMenuView::imageMenuItemSelected)
{

}

void MainMenuView::setupScreen()
{
	infoScreens.setXY(0, 41);
	//imageMenu.setXY(0, 41);

#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_BT_SMALL_ID, BITMAP_MAINMENU_BTN_PRESSED_ID, DEMO_MENU_BLUETOOTH_SCREEN_ID, T_IMAGE_MAINMENU_BT_HEADLINE, T_IMAGE_MAINMENU_BT_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_WIFI_SMALL_ID, BITMAP_MAINMENU_BTN_PRESSED_ID, DEMO_MENU_WIFI_SCREEN_ID, T_IMAGE_MAINMENU_WIFI_HEADLINE, T_IMAGE_MAINMENU_WIFI_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_REMOTER_SMALL_ID, BITMAP_MAINMENU_BTN_PRESSED_ID, DEMO_MENU_REMOTER_SCREEN_ID, T_IMAGE_MAINMENU_REMOTER_HEADLINE, T_IMAGE_MAINMENU_REMOTER_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_MIC_SMALL_ID, BITMAP_MAINMENU_BTN_PRESSED_ID, DEMO_MENU_MIC_SCREEN_ID, T_IMAGE_MAINMENU_MIC_HEADLINE, T_IMAGE_MAINMENU_MIC_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_TIME_SMALL_ID, BITMAP_MAINMENU_BTN_PRESSED_ID, DEMO_MENU_TIME_SCREEN_ID, T_IMAGE_MAINMENU_TIME_HEADLINE, T_IMAGE_MAINMENU_TIME_TEXT, true);
    imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_ST_SMALL_ID, BITMAP_MAINMENU_BTN_PRESSED_ID, DEMO_MENU_SETTING_SCREEN_ID, T_IMAGE_MAINMENU_SETTINGS_HEADLINE, T_IMAGE_MAINMENU_SETTINGS_TEXT, true);
#else
	imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_BT_ID, BITMAP_MAINMENU_BTN_BT_PRESSED_ID, DEMO_MENU_BLUETOOTH_SCREEN_ID, T_IMAGE_MAINMENU_BT_HEADLINE, T_IMAGE_MAINMENU_BT_TEXT, true);
	imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_WIFI_ID, BITMAP_MAINMENU_BTN_WIFI_PRESSED_ID, DEMO_MENU_WIFI_SCREEN_ID, T_IMAGE_MAINMENU_WIFI_HEADLINE, T_IMAGE_MAINMENU_WIFI_TEXT, true);
	imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_REMOTER_ID, BITMAP_MAINMENU_BTN_REMOTER_PRESSED_ID, DEMO_MENU_REMOTER_SCREEN_ID, T_IMAGE_MAINMENU_REMOTER_HEADLINE, T_IMAGE_MAINMENU_REMOTER_TEXT, true);
	imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_MIC_ID, BITMAP_MAINMENU_BTN_MIC_PRESSED_ID, DEMO_MENU_MIC_SCREEN_ID, T_IMAGE_MAINMENU_MIC_HEADLINE, T_IMAGE_MAINMENU_MIC_TEXT, true);
	imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_TIME_ID, BITMAP_MAINMENU_BTN_TIME_PRESSED_ID, DEMO_MENU_TIME_SCREEN_ID, T_IMAGE_MAINMENU_TIME_HEADLINE, T_IMAGE_MAINMENU_TIME_TEXT, true);
	imageMenu.addMenuItem(BITMAP_MAINMENU_BTN_ST_ID, BITMAP_MAINMENU_BTN_ST_PRESSED_ID, DEMO_MENU_SETTING_SCREEN_ID, T_IMAGE_MAINMENU_SETTINGS_HEADLINE, T_IMAGE_MAINMENU_SETTINGS_TEXT, true);
#endif	
	imageMenu.setMenuItemSelectedCallback(onImageMenuItemSelected);

	infoScreens.add(imageMenu);
	//shortcutContainer.setXY(0, 41);
	infoScreens.add(shortcutContainer);

	infoScreensViewPort.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	infoScreensViewPort.add(infoScreens);
	add(infoScreensViewPort);

	/*dotIndicator.setNumberOfDots(NUMBER_OF_SCREENS);
	dotIndicator.setBitmaps(Bitmap(BITMAP_WEATHER_DOT_NORMAL_ID), Bitmap(BITMAP_WEATHER_DOT_SELECTED_ID));
	dotIndicator.setXY(backButton.getWidth() + ((HAL::DISPLAY_WIDTH - backButton.getWidth() - dotIndicator.getWidth()) / 2), 252);
	add(dotIndicator);*/
}

void MainMenuView::tearDownScreen()
{

}

void MainMenuView::imageMenuItemSelected(const uint8_t callbackID)
{
	switch (callbackID)
	{
	case DEMO_MENU_BLUETOOTH_SCREEN_ID:
		static_cast<FrontendApplication*>(Application::getInstance())->gotoBtControlScreen();
		break;
	case DEMO_MENU_WIFI_SCREEN_ID:
		static_cast<FrontendApplication*>(Application::getInstance())->gotoWifiControlScreen();
		break;
	case DEMO_MENU_REMOTER_SCREEN_ID:
		//static_cast<FrontendApplication*>(Application::getInstance())->gotoAnimatedGraphicsScreen();
		//static_cast<FrontendApplication*>(Application::getInstance())->gotoScreenSaverClockTransition();
		break;
	case DEMO_MENU_MIC_SCREEN_ID:
		static_cast<FrontendApplication*>(Application::getInstance())->gotoMicScreen();
		break;
	case DEMO_MENU_SETTING_SCREEN_ID:
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 0
        static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingScreen();
#endif
		break;
	case DEMO_MENU_TIME_SCREEN_ID:
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 0
		static_cast<FrontendApplication*>(Application::getInstance())->gotoCustomControlsScreen();
#endif
		break;
	default:
		break;
	}
}

//Handles when a key is pressed
void MainMenuView::handleKeyEvent(uint8_t key)
{
	imageMenu.dispatchKeyEvent(key);
}


void MainMenuView::handleTickEvent()
{
	tickCounter++;

	if (currentState == ANIMATE_SWIPE_CANCELLED_LEFT)
	{
		animateSwipeCancelledLeft();
	}
	else if (currentState == ANIMATE_SWIPE_CANCELLED_RIGHT)
	{
		animateSwipeCancelledRight();
	}
	else if (currentState == ANIMATE_LEFT)
	{
		animateLeft();
	}
	else if (currentState == ANIMATE_RIGHT)
	{
		animateRight();
	}
}

void MainMenuView::handleClickEvent(const ClickEvent& evt)
{
	// If an animation is already in progress do not
	// react to clicks
	//if (currentState != NO_ANIMATION)
	//{
//		if (evt.getX() < 120)
	//	{
			DemoView<MainMenuPresenter>::handleClickEvent(evt);
	//	}
//		return;
	//}
	if (evt.getType() == ClickEvent::PRESSED)
	{
		startX = evt.getX();
		startY = evt.getY();
		currentState = NO_ANIMATION;
	}
	else if (evt.getType() == ClickEvent::RELEASED)
	{
		// Save current position for use during animation
		if (abs(startY - evt.getY()) > abs(startX - evt.getX())){
			DemoView<MainMenuPresenter>::handleClickEvent(evt);
			return;
		}
		animateDistance = dragX;
		startX = infoScreens.getX();
		if (abs(dragX) < 40){
			return;
		}

		if (dragX < 0)
		{
			if (currentScreen == NUMBER_OF_SCREENS - 1 || dragX > -120)
			{
				currentState = ANIMATE_SWIPE_CANCELLED_LEFT;
			}
			else
			{
				currentState = ANIMATE_LEFT;
			}
		}
		else if (dragX > 0)
		{
			if (currentScreen == 0 || dragX < 120)
			{
				currentState = ANIMATE_SWIPE_CANCELLED_RIGHT;
			}
			else
			{
				currentState = ANIMATE_RIGHT;
			}
		}

		//adjustInfoScreens();
	}

	//if (60 < evt.getX() && evt.getX() < 180)
	//{
	//	DemoView<MainMenuPresenter>::handleClickEvent(evt);
	//	return;
	//}
}

void MainMenuView::handleDragEvent(const DragEvent& evt)
{
	// If an animation is already in progress do not
	// react to drags
	if (currentState != NO_ANIMATION)
	{
		return;
	}

	dragX += evt.getDeltaX();
	dragY += evt.getDeltaY();
	// Do not show too much background next to end screens
	if (currentScreen == 0 && dragX > MainBg.getWidth())
	{
		dragX = MainBg.getWidth();
	}
	else if (currentScreen == NUMBER_OF_SCREENS - 1 && dragX < -MainBg.getWidth())
	{
		dragX = -MainBg.getWidth();
	}

	if (abs(dragY) > abs(dragX)){
		DemoView<MainMenuPresenter>::handleDragEvent(evt);
		return;
	}
	if (abs(dragX) > 80){
		adjustInfoScreens();
	}
}

void MainMenuView::handleGestureEvent(const GestureEvent& evt)
{
	// Do not accept gestures while animating
	if (currentState != NO_ANIMATION)
	{
		return;
	}

	if (evt.getType() == evt.SWIPE_VERTICAL)
	{
		currentState = ANIMATE_UPDOWN;
		DemoView<MainMenuPresenter>::handleGestureEvent(evt);
		return;
	}

	if (evt.getType() == evt.SWIPE_HORIZONTAL)
	{
		// Save current position for use during animation
		animateDistance = dragX;
		startX = infoScreens.getX();

		if (evt.getVelocity() < 0 && currentScreen < NUMBER_OF_SCREENS - 1)
		{
			currentState = ANIMATE_LEFT;
		}
		else if (evt.getVelocity() > 0 && currentScreen > 0)
		{
			currentState = ANIMATE_RIGHT;
		}
	}
}

void MainMenuView::adjustInfoScreens()
{
	infoScreens.moveTo(-(currentScreen * (HAL::DISPLAY_WIDTH - backButton.getWidth())) + dragX, 41);

	//int alphaAdjustment = (dragX < 0) ? -dragX : dragX;
	//weekInfoBar.setAlpha(255 - alphaAdjustment);
}

void MainMenuView::animateSwipeCancelledLeft()
{
	uint8_t duration = 14;

	if (animationCounter <= duration)
	{
		int16_t delta = EasingEquations::backEaseOut(animationCounter, 0, -animateDistance, duration);
		dragX = animateDistance + delta;

		adjustInfoScreens();
	}
	else
	{
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		dragX = 0;
		adjustInfoScreens();
	}
	animationCounter++;
}

void MainMenuView::animateSwipeCancelledRight()
{
	uint8_t duration = 14;

	if (animationCounter <= duration)
	{
		int16_t delta = EasingEquations::backEaseOut(animationCounter, 0, animateDistance, duration);
		dragX = animateDistance - delta;

		adjustInfoScreens();
	}
	else
	{
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		dragX = 0;
		adjustInfoScreens();
	}
	animationCounter++;
}

void MainMenuView::animateLeft()
{
	uint8_t duration = 10;

	if (animationCounter <= duration)
	{
		int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, infoScreensViewPort.getWidth() + animateDistance, duration);
		dragX = animateDistance - delta;

		adjustInfoScreens();
	}
	else
	{
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		currentScreen++;
		dragX = 0;
		adjustInfoScreens();
		//dotIndicator.goRight();
	}
	animationCounter++;
}

void MainMenuView::animateRight()
{
	uint8_t duration = 10;

	if (animationCounter <= duration)
	{
		int16_t delta = EasingEquations::cubicEaseOut(animationCounter, 0, infoScreensViewPort.getWidth() - animateDistance, duration);
		dragX = animateDistance + delta;

		adjustInfoScreens();
	}
	else
	{
		// Final step: stop the animation
		currentState = NO_ANIMATION;
		animationCounter = 0;
		currentScreen--;
		dragX = 0;
		adjustInfoScreens();
		//dotIndicator.goLeft();
	}
	animationCounter++;
}