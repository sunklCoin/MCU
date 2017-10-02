#include <gui/mainmenu_screen/MainMenuView.hpp>
#include <gui/common/McuLoadSlider.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/FrontendApplication.hpp>

MainMenuView::MainMenuView():
imageMenu(HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT - 40, Bitmap(BITMAP_MAINMENU_BTN_BT_ID).getHeight(), BITMAP_INVALID, BITMAP_INVALID, BITMAP_INVALID),
onImageMenuItemSelected(this, &MainMenuView::imageMenuItemSelected)
{

}

void MainMenuView::setupScreen()
{
	imageMenu.setXY(0, 41);

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
	add(imageMenu);
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
		break;
	case DEMO_MENU_MIC_SCREEN_ID:
		//static_cast<FrontendApplication*>(Application::getInstance())->gotoHomeAutomationScreen();
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
#ifdef SIMULATOR
    key = key - '0';
#endif
	imageMenu.dispatchKeyEvent(key);
}
