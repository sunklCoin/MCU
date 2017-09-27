#include <gui/screensaverclock_screen/ScreenSaverClockView.hpp>
#include <gui/screensaverclock_screen/ScreenSaverClockPresenter.hpp>

ScreenSaverClockPresenter::ScreenSaverClockPresenter(ScreenSaverClockView& v)
    : view(v)
{
}

void ScreenSaverClockPresenter::activate()
{
    timeUpdated(model->getCurrentTime());
}

void ScreenSaverClockPresenter::deactivate()
{

}

void ScreenSaverClockPresenter::timeUpdated(Time time)
{
    view.handleTimeUpdated(time.hours, time.minutes, time.seconds,true,true);
}

void ScreenSaverClockPresenter::timeUpdated(TimeUtils mTimeUtils)
{
    Time time;
    mTimeUtils.getCurrentTime24(time.hours, time.minutes,time.seconds);
    view.handleTimeUpdated(time.hours, time.minutes, time.seconds, mTimeUtils.is24Hour(), mTimeUtils.isAnalogClock());
}
		
void ScreenSaverClockPresenter::gotoMainScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuScreenTransition();
}