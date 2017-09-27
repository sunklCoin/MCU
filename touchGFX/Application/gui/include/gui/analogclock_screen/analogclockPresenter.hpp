#ifndef ANALOGCLOCK_PRESENTER_HPP
#define ANALOGCLOCK_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class analogclockView;

class analogclockPresenter : public Presenter, public ModelListener
{
public:
    analogclockPresenter(analogclockView& v);

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

    virtual ~analogclockPresenter() {};
	virtual void timeUpdated(Time time);
	virtual void timeUpdated(TimeUtils time);
    virtual void gotoMainScreen();
private:
    analogclockPresenter();

    analogclockView& view;
};


#endif // ANALOGCLOCK_PRESENTER_HPP
