#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

using namespace touchgfx;

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
    void resetScreenSaver();

    void gotoMainMenuScreenTransition();
	void gotoCustomControlsScreen();
    void gotoBtControlScreen();
    void gotoClockScreenNoTransition();
    void gotoScreenSaverClockTransition();
    void gotoWifiControlScreen();
private:
	touchgfx::Callback<FrontendApplication> transitionCallback;
    static const int SCREEN_SAVER_TIMEOUT = 180000; // Milliseconds
    void gotoMainMenuScreenTransitionImpl();
	void gotoCustomControlsScreenImpl();
    void gotoBtControlScreenImpl();
    void gotoClockScreenNoTransitionImpl();
    void gotoScreenSaverClockTransitionImpl();
    void gotoWifiControlScreenImpl();
    int tickCounter;
    Time lastClickTime;
    TimeUtils lastClickTimeUtils;
};

#endif // FRONTENDAPPLICATION_HPP
