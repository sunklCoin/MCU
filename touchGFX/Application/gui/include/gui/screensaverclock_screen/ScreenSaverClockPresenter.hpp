#ifndef SCREENSAVERCLOCK_PRESENTER_HPP
#define SCREENSAVERCLOCK_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/TimeUtils.hpp>
using namespace touchgfx;

class ScreenSaverClockView;

class ScreenSaverClockPresenter : public Presenter, public ModelListener
{
public:
    ScreenSaverClockPresenter(ScreenSaverClockView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenSaverClockPresenter() {};

    virtual void timeUpdated(Time time);
	virtual void timeUpdated(TimeUtils mTimeUtils);
    virtual void gotoMainScreen();
private:
    ScreenSaverClockPresenter();

    ScreenSaverClockView& view;
};


#endif // SCREENSAVERCLOCK_PRESENTER_HPP
