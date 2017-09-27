#ifndef MAINMENU_VIEW_HPP
#define MAINMENU_VIEW_HPP

#include <gui_generated/mainmenu_screen/MainMenuViewBase.hpp>
#include <gui/mainmenu_screen/MainMenuPresenter.hpp>
#include <gui/common/DemoView.hpp>
#include <gui/common/ImageMenu.hpp>
#include <touchgfx/widgets/Box.hpp>

class MainMenuView : public DemoView<MainMenuPresenter>
{
public:
    MainMenuView();
    virtual ~MainMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
	enum callbackIds
	{
		DEMO_MENU_BLUETOOTH_SCREEN_ID = 0,
		DEMO_MENU_WIFI_SCREEN_ID,
		DEMO_MENU_REMOTER_SCREEN_ID,
		DEMO_MENU_MIC_SCREEN_ID,
		DEMO_MENU_TIME_SCREEN_ID,
		DEMO_MENU_SETTING_SCREEN_ID,
		NUMBER_OF_IDS
	};

	Box background;
	ImageMenu imageMenu;

	Callback<MainMenuView, const uint8_t> onImageMenuItemSelected;

	void imageMenuItemSelected(const uint8_t callbackID);
};

#endif // MAINMENU_VIEW_HPP
