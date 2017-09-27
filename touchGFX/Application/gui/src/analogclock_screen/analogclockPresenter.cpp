#include <gui/analogclock_screen/analogclockView.hpp>
#include <gui/analogclock_screen/analogclockPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>

analogclockPresenter::analogclockPresenter(analogclockView& v)
    : view(v)
{
}

void analogclockPresenter::activate()
{
	timeUpdated(model->getCurrentTime());
}

void analogclockPresenter::deactivate()
{

}

void analogclockPresenter::timeUpdated(Time time)
{
	view.handleTimeUpdated(time.hours, time.minutes, time.seconds,true);
}

void analogclockPresenter::timeUpdated(TimeUtils mTimeUtils)
{
    Time time;
    mTimeUtils.getCurrentTime24(time.hours, time.minutes,time.seconds);
    view.handleTimeUpdated(time.hours, time.minutes, time.seconds, mTimeUtils.is24Hour());
}

void analogclockPresenter::gotoMainScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuScreenTransition();
}
