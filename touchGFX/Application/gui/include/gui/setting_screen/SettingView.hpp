#ifndef SETTING_VIEW_HPP
#define SETTING_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/setting_screen/SettingPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/setting_screen/SettingPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/custom_controls_screen/BacklightSlider.hpp>
#include <gui/custom_controls_screen/CircularProgress.hpp>
#include <gui/custom_controls_screen/SleepSchedule.hpp>

using namespace touchgfx;

class SettingView : public DemoView<SettingPresenter>
{
public:
    SettingView();
    virtual ~SettingView();
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    /*
    * Member Declarations
    */
#if 0//GUI_RESOURCE_ONLY_INTERNAL_FLASH == 0
    CircularProgress backlightSlider;
#else
    CircularProgress sleepSet;
    Image menuBackground;
    BacklightSlider backlightSlider;
    SleepSchedule sleepSchedule;

#endif
    ControlData mControlData;
private:
    Callback<SettingView, const AbstractButton&> onButtonPressed;
    void buttonPressedHandler(const AbstractButton& button);
};

#endif // SETTING_VIEW_HPP
