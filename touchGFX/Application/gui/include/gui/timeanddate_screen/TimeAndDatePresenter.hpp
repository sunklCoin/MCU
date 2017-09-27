#ifndef TIMEANDDATE_PRESENTER_HPP
#define TIMEANDDATE_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/DemoPresenter.hpp>
#include <gui/common/TimeUtils.hpp>
using namespace touchgfx;

class TimeAndDateView;

class TimeAndDatePresenter : public DemoPresenter
{
public:
    TimeAndDatePresenter(TimeAndDateView& v);

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
	virtual void screenSaverMinorTick();
    virtual ~TimeAndDatePresenter() {};
    TimeUtils getTimeUtils(){
        return currTimeUtils;
    }

private:
    TimeAndDatePresenter();

    TimeAndDateView& view;

    TimeUtils currTimeUtils;
};


#endif // TIMEANDDATE_PRESENTER_HPP
