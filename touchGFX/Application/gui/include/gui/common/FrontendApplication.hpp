#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

using namespace touchgfx;

enum eScreenId {
	FRONTENDAPPLICATION_BEGIN_SCREEN_ID = 0,
	FRONTENDAPPLICATION_MAINMENU_SCREEN_ID,
	FRONTENDAPPLICATION_CUSTOMCONTROLS_SCREEN_ID,
	FRONTENDAPPLICATION_BTCONTROL_SCREEN_ID,
	FRONTENDAPPLICATION_CLOCK_SCREEN_ID,
	FRONTENDAPPLICATION_SSCLOCK_SCREEN_ID,
	FRONTENDAPPLICATION_WIFICONTROLS_SCREEN_ID,
	FRONTENDAPPLICATION_SETTING_SCREEN_ID,
	FRONTENDAPPLICATION_MIC_SCREEN_ID,
	FRONTENDAPPLICATION_END_SCREEN_ID
};

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    /*virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }*/


    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleTickEvent();
	//add by sunkelong 2017/10/03,for sleep to wakeup
    virtual void handleKeyEvent(uint8_t keyValue);
    void resetScreenSaver();

    void gotoMainMenuScreenTransition();
	void gotoCustomControlsScreen();
    void gotoBtControlScreen();
    void gotoClockScreenNoTransition();
    void gotoScreenSaverClockTransition();
    void gotoWifiControlScreen();
    void gotoSettingScreen();
	void gotoMicScreen();
    ControlData getControlData();
private:
	touchgfx::Callback<FrontendApplication> transitionCallback;
    static const int SCREEN_SAVER_TIMEOUT = 180000; // Milliseconds
    void gotoMainMenuScreenTransitionImpl();
	void gotoCustomControlsScreenImpl();
    void gotoBtControlScreenImpl();
    void gotoClockScreenNoTransitionImpl();
    void gotoScreenSaverClockTransitionImpl();
    void gotoWifiControlScreenImpl();
    void gotoSettingScreenImpl();
	void gotoMicScreenImpl();
    int tickCounter;
    Time lastClickTime;
    TimeUtils lastClickTimeUtils;
    ControlData mControlData;
	int entryScreenId;
};

#endif // FRONTENDAPPLICATION_HPP
