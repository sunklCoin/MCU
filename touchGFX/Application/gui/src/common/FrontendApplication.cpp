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
#include <gui/mic_screen/MicScreenView.hpp>
#include <gui/mic_screen/MicScreenPresenter.hpp>
#include <gui/poweron_screen/ShutdownAnimationPresenter.hpp>
#include <gui/poweron_screen/ShutdownAnimationView.hpp>
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

    if ((tickCounter % 100 == 0) && (tickCounter > 1000))//10000
    {
	    //add by sunkelong 2017/10/03,goto sleep,first show screensaver,begin
        if ((model.getCurrentTime() - lastClickTimeUtils) >= (sleepScheduleArr[mControlData.getSleepSchedule()] * 1000 - 5*1000))
        {
            /*if (entryScreenId != FRONTENDAPPLICATION_SSCLOCK_SCREEN_ID){
                gotoScreenSaverClockTransition();
            }*/
            model.getModelListener()->showScreenSaver();

        }

        if ((model.getCurrentTime() - lastClickTimeUtils) >= sleepScheduleArr[mControlData.getSleepSchedule()] * 1000)
        {
            if (!mControlData.isSleepState()){
                mControlData.gotoSleep();
            }
            lastClickTimeUtils = model.getCurrentTime();
        }
	    //add by sunkelong 2017/10/03,goto sleep,first show screensaver,end
    }
}


//add by sunkelong 2017/10/03,for sleep to wakeup,begin
void FrontendApplication::handleKeyEvent(uint8_t keyValue)
{
    MVPApplication::handleKeyEvent(keyValue);
    if (mControlData.isSleepState()){
        mControlData.wakeupLcd();
        gotoMainMenuScreenTransition();
    }
    resetScreenSaver();
}
//add by sunkelong 2017/10/03,for sleep to wakeup,end

void FrontendApplication::handleClickEvent(const ClickEvent& evt)
{
    MVPApplication::handleClickEvent(evt);

    // A click event has been registered so reset last click time
    resetScreenSaver();
}

TimeUtils FrontendApplication::getModelTime()
{
	return model.getCurrentTime();
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
	entryScreenId = FRONTENDAPPLICATION_CUSTOMCONTROLS_SCREEN_ID;
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
	entryScreenId = FRONTENDAPPLICATION_BTCONTROL_SCREEN_ID;
}

void FrontendApplication::gotoBtControlScreenImpl()
{
    makeTransition<BTControlView, BTControlPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoClockScreenNoTransition()
{
    transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoClockScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_CLOCK_SCREEN_ID;
}

void FrontendApplication::gotoClockScreenNoTransitionImpl()
{
    makeTransition<analogclockView, analogclockPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainMenuScreenTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoMainMenuScreenTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_MAINMENU_SCREEN_ID;
}

void FrontendApplication::gotoMainMenuScreenTransitionImpl()
{
    makeTransition<MainMenuView, MainMenuPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoScreenSaverClockTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoScreenSaverClockTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_SSCLOCK_SCREEN_ID;
}

void FrontendApplication::gotoScreenSaverClockTransitionImpl()
{
    makeTransition<ScreenSaverClockView, ScreenSaverClockPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoWifiControlScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoWifiControlScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_WIFICONTROLS_SCREEN_ID;
}

void FrontendApplication::gotoWifiControlScreenImpl()
{
    makeTransition<WifiControlView, WifiControlPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSettingScreen()
{
    transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoSettingScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_SETTING_SCREEN_ID;
}

void FrontendApplication::gotoSettingScreenImpl()
{
    makeTransition<SettingView, SettingPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMicScreen()
{
	transitionCallback = Callback< FrontendApplication >(this, &FrontendApplication::gotoMicScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_MIC_SCREEN_ID;
}

void FrontendApplication::gotoMicScreenImpl()
{
	makeTransition<MicScreenView, MicScreenPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

/*
 * Screen Transition Declarations
 */
// boot animation

void FrontendApplication::BootAnimationScreen()
{
    transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::BootAnimationScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
    entryScreenId = FRONTENDAPPLICATION_BOOT_SCREEN_ID;
}

void FrontendApplication::BootAnimationScreenImpl()
{
    makeTransition<BootAnimationView, BootAnimationPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

/*
* Screen Transition Declarations
*/
// shutdown animation

void FrontendApplication::ShutdownAnimationScreen()
{
	transitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::ShutdownAnimationScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
	entryScreenId = FRONTENDAPPLICATION_SHUTDOWN_SCREEN_ID;
}

void FrontendApplication::ShutdownAnimationScreenImpl()
{
	makeTransition<ShutdownAnimationView, ShutdownAnimationPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}