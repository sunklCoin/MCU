#include <gui/timeanddate_screen/TimeAndDateView.hpp>
#include <gui/timeanddate_screen/TimeAndDatePresenter.hpp>
#include <gui/common/FrontendApplication.hpp>
TimeAndDatePresenter::TimeAndDatePresenter(TimeAndDateView& v): 
	DemoPresenter(v),
	view(v)
{
}

void TimeAndDatePresenter::activate()
{
//    currTimeUtils = model->getCurrentTime();
}

void TimeAndDatePresenter::deactivate()
{

}

void TimeAndDatePresenter::screenSaverMinorTick()
{
	view.screenSaverMinorTick();
}

