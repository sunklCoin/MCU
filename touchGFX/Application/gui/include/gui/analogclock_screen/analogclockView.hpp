#ifndef ANALOGCLOCK_VIEW_HPP
#define ANALOGCLOCK_VIEW_HPP

#include <gui_generated/analogclock_screen/analogclockViewBase.hpp>
#include <gui/analogclock_screen/analogclockPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/canvas/Shape.hpp>
#include <touchgfx/widgets/Button.hpp>

#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#elif USE_BPP==4
#include <touchgfx/widgets/canvas/PainterGRAY4.hpp>
#elif USE_BPP==2
#include <touchgfx/widgets/canvas/PainterGRAY2.hpp>
#else
#error Unknown USE_BPP
#endif
class analogclockView : public touchgfx::View<analogclockPresenter>
{
public:
    analogclockView();
    virtual ~analogclockView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	virtual void afterTransition();
	/**
	* Updates the hour, minutes and second counters
	* hours: 0-23
	* minutes: 0-59
	* seconds: 0-59
	*/
    void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds, bool is24Hour);

	// Updates the clock view
	void updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter);
	class SecondClockHand : public Shape<4>
	{
	public:
		SecondClockHand()
		{
			ShapePoint<int> points[4] = { { -1, 0 }, { -1, -74 }, { 1, -74 }, { 1, 0 } };
			setShape(points);
		}
	};

	class MinuteClockHand : public Shape<5>
	{
	public:
		MinuteClockHand()
		{
			ShapePoint<float> points[5] = { { -3.5f, 0 }, { -.7f, -67 }, { 0, -70 }, { .7f, -67 }, { 3.5f, 0 } };
			setShape(points);
		}
	};

	class HourClockHand : public Shape<5>
	{
	public:
		HourClockHand()
		{
			ShapePoint<float> points[5] = { { -4.5f, 2 }, { -1, -43 }, { 0, -45 }, { 1, -43 }, { 4.5f, 2 } };
			setShape(points);
		}
	};
protected:
    FrontendApplication& application()
    {
        return *static_cast<FrontendApplication*>(Application::getInstance());
    }

    /*
    * Member Declarations
    */
    //AnalogClock analogClock;

	uint8_t currentSecondCounter;
	uint8_t currentMinuteCounter;
	uint8_t currentHourCounter;

	bool transitionDone;
	bool firstPresenterCall;

	Image clockBackground;
	Image centerDot;
    Button gotoMainScreen;
	SecondClockHand secondHand;
	MinuteClockHand minuteHand;
	HourClockHand hourHand;

#if !defined(USE_BPP) || USE_BPP==16
	PainterRGB565 handColorRed;
	PainterRGB565 handColorWhite;
#elif USE_BPP==24
	PainterRGB888 handColorRed;
	PainterRGB888 handColorWhite;
#elif USE_BPP==4
	PainterGRAY4 handColorRed;
	PainterGRAY4 handColorWhite;
#elif USE_BPP==2
	PainterGRAY2 handColorRed;
	PainterGRAY2 handColorWhite;
#else
#error Unknown USE_BPP
#endif
    Callback<analogclockView, const AbstractButton&> onButtonPressed;
    void buttonPressedHandler(const AbstractButton& button);
};

#endif // ANALOGCLOCK_VIEW_HPP
