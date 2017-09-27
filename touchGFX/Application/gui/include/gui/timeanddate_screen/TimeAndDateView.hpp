#ifndef TIMEANDDATE_VIEW_HPP
#define TIMEANDDATE_VIEW_HPP

#include <gui/timeanddate_screen/TimeAndDatePresenter.hpp>
#include <gui/common/DemoView.hpp>
#include <gui/common/DemoView.hpp>
//#include <gui/custom_controls_screen/CustomControlsPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <gui/custom_controls_screen/ThreeWayProgressBar.hpp>
#include <gui/custom_controls_screen/CircularProgress.hpp>
#include <gui/custom_controls_screen/DatePicker.hpp>
#include <gui/custom_controls_screen/TimePicker.hpp>
#include <gui/custom_controls_screen/TimeFormatSet.hpp>
#include <gui/custom_controls_screen/Gauge.hpp>
#include <gui/custom_controls_screen/VerticalSlideMenu.hpp>
#include <gui/custom_controls_screen/HorizontalSlideMenu.hpp>
//class TimeAndDateView : public DemoView<TimeAndDatePresenter>
//{
//public:
//    TimeAndDateView();
//    virtual ~TimeAndDateView() {}
//    virtual void setupScreen();
//    virtual void tearDownScreen();
//protected:
//};



class TimeAndDateView : public DemoView<TimeAndDatePresenter>
{
public:
	TimeAndDateView();
	virtual ~TimeAndDateView();

	virtual void setupScreen();
	virtual void tearDownScreen();

	virtual void handleTickEvent();

	virtual void screenSaverMinorTick();

private:
	Image menuBackground;
	Image background;
	Button menuUp;
	Button menuDown;
	Callback<TimeAndDateView, const AbstractButton&> onButtonPressed;
	void buttonPressedHandler(const AbstractButton& button);


    HorizontalSlideMenu slideMenu;
    Callback<TimeAndDateView, const HorizontalSlideMenu& > slideMenuElementSelectedCallback;
    void slideMenuElementSelectedHandler(const HorizontalSlideMenu& menu);

	Image menuShadowTop;
	Image menuShadowBottom;

	FadeAnimator<TextArea> statusMessage;

	//ThreeWayProgressBar threeWayProgressBar;
	Callback<TimeAndDateView, const ThreeWayProgressBar& > threeWayButtonPressedCallback;
	void threeWayButtonPressedHandler(const ThreeWayProgressBar& button);

	//CircularProgress percentageBar;
	DatePicker datePicker;
    TimePicker timePicker;
    TimeFormatSet timeFormatStyle;
	//Gauge gauge;

	// Animation members
	enum AnimationState
	{
		ANIMATION_THREE_WAY_RUNNING,
		ANIMATION_GAUGE,
		NO_ANIMATION
	};

	AnimationState currentAnimationState;

	int animationCounter;
	int tickCounter;

	// ThreeWayProgressBar animation
	static const int NUMBER_OF_BARS = 3;
	AnimationState barAnimationState[NUMBER_OF_BARS];
	int animationDuration[NUMBER_OF_BARS];
	EasingEquation animationEquation[NUMBER_OF_BARS];

	AnimationState getAnimationState();
	EasingEquation getRandomEasingEquation();
	void startThreeWayProgressBarAnimation();
	void stopThreeWayProgressBarAnimation();
};

#endif // TIMEANDDATE_VIEW_HPP
