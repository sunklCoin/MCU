#ifndef MAINMENU_VIEW_HPP
#define MAINMENU_VIEW_HPP

#include <gui_generated/mainmenu_screen/MainMenuViewBase.hpp>
#include <gui/mainmenu_screen/MainMenuPresenter.hpp>
#include <gui/common/DemoView.hpp>
#include <gui/common/ImageMenu.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/mainmenu_screen/ShortcutContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>

class MainMenuView : public DemoView<MainMenuPresenter>
{
public:
    MainMenuView();
    virtual ~MainMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	virtual void handleKeyEvent(uint8_t key);
	virtual void handleDragEvent(const DragEvent& evt);
	virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& evt);
    //virtual void handleGestureEvent(const GestureEvent& evt);
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
	ShortcutContainer shortcutContainer;

	Callback<MainMenuView, const uint8_t> onImageMenuItemSelected;

	void imageMenuItemSelected(const uint8_t callbackID);

private:
	enum States
	{
		ANIMATE_SWIPE_CANCELLED_LEFT,
		ANIMATE_SWIPE_CANCELLED_RIGHT,
		ANIMATE_LEFT,
		ANIMATE_RIGHT,
		ANIMATE_UPDOWN,
		NO_ANIMATION
	} currentState;

	static const uint8_t NUMBER_OF_SCREENS = 2;
	Container infoScreensViewPort;
	ListLayout infoScreens;

	uint8_t animationCounter;
	int32_t tickCounter;

	int16_t dragY;
	int16_t startY;

	int16_t dragX;
	int16_t animateDistance;
	int16_t startX;
	uint8_t currentScreen;

	void adjustInfoScreens();

	void animateSwipeCancelledLeft();
	void animateSwipeCancelledRight();
	void animateLeft();
	void animateRight();
};

#endif // MAINMENU_VIEW_HPP
