#include <new>
#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/analogclock_screen/analogclockView.hpp>
#include <gui/analogclock_screen/analogclockPresenter.hpp>
#include <gui/mainmenu_screen/MainMenuView.hpp>
#include <gui/mainmenu_screen/MainMenuPresenter.hpp>
#include <gui/timeanddate_screen/TimeAndDateView.hpp>
#include <gui/timeanddate_screen/TimeAndDatePresenter.hpp>
#include <gui/custom_controls_screen/CustomControlsView.hpp>
#include <gui/custom_controls_screen/CustomControlsPresenter.hpp>
#include <gui/btcontrol_screen/BTControlView.hpp>
#include <gui/btcontrol_screen/BTControlPresenter.hpp>
#include <gui/wificontrol_screen/WifiControlView.hpp>
#include <gui/wificontrol_screen/WifiControlPresenter.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <gui/screensaverclock_screen/ScreenSaverClockView.hpp>
#include <gui/screensaverclock_screen/ScreenSaverClockPresenter.hpp>
#include <gui/setting_screen/SettingView.hpp>
#include <gui/setting_screen/SettingPresenter.hpp>
using namespace touchgfx;

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap),
    tickCounter(0),
    lastClickTime(0),
    lastClickTimeUtils()
{
}

void FrontendApplication::handleTickEvent()
{
    model.tick();
    MVPApplication::handleTickEvent();

    // Screen saver functionality:
    // Jump to one of the preselected screens if
    // no action has been registered for a screenSaverTimeout (time in milliseconds)
    // (Only do the time check sometimes and not in the start)
    tickCounter++;
    if ((tickCounter % 100 == 0) && (tickCounter > 10000))
    {
        if ((model.getCurrentTime() - lastClickTimeUtils) >= sleepScheduleArr[mControlData.getSleepSchedule()] * 1000)
        {
            gotoScreenSaverClockTransition();
            lastClickTimeUtils = model.getCurrentTime();
        }
    }

}

void FrontendApplication::handleClickEvent(const ClickEvent& evt)
{
    MVPApplication::handleClickEvent(evt);

    // A click event has been registered so reset last click time
    resetScreenSaver();
}

void FrontendApplication::resetScreenSaver()
{
    lastClickTimeUtils = model.getCurrentTime();
}

ControlData FrontendApplication::getControlData()
{
    return mControlData;
}

void FrontendApplication::gotoCustomControlsScreen()
{
	transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoCustomControlsScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoCustomControlsScreenImpl()
{
	//makeTransition< CustomControlsView, CustomControlsPresenter, NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
    makeTransition<TimeAndDateView, TimeAndDatePresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}



void FrontendApplication::gotoBtControlScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoBtControlScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoBtControlScreenImpl()
{
    makeTransition<BTControlView, BTControlPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoClockScreenNoTransition()
{
    transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoClockScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoClockScreenNoTransitionImpl()
{
    makeTransition<analogclockView, analogclockPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainMenuScreenTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoMainMenuScreenTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainMenuScreenTransitionImpl()
{
    makeTransition<MainMenuView, MainMenuPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoScreenSaverClockTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoScreenSaverClockTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoScreenSaverClockTransitionImpl()
{
    makeTransition<ScreenSaverClockView, ScreenSaverClockPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoWifiControlScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoWifiControlScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoWifiControlScreenImpl()
{
    makeTransition<WifiControlView, WifiControlPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSettingScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSettingScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoSettingScreenImpl()
{
    makeTransition<SettingView, SettingPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
