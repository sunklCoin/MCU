#include <gui/timeanddate_screen/TimeAndDateView.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/common/Utils.hpp>
LOCATION_EXTFLASH_ATTRIBUTE
TimeAndDateView::TimeAndDateView() :
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
DemoView(),
#endif
onButtonPressed(this, &TimeAndDateView::buttonPressedHandler),
slideMenuElementSelectedCallback(this, &TimeAndDateView::slideMenuElementSelectedHandler),
threeWayButtonPressedCallback(this, &TimeAndDateView::threeWayButtonPressedHandler),
currentAnimationState(NO_ANIMATION),
tickCounter(0)
{
	//background.setBitmap(Bitmap(BITMAP_CONTROLS_BACKGROUND_ID));
	//background.setXY(0, 41);
	//add(background);
    setDemoVieBackground(BITMAP_CONTROLS_BACKGROUND_ID);
	menuBackground.setBitmap(Bitmap(BITMAP_CONTROLS_MENU_BACKGROUND_ID));
    menuBackground.setXY(0, 41);
	add(menuBackground);

	// Invisible button for navigating in the side menu
    menuUp.setHeight(menuBackground.getHeight());
	menuUp.setWidth(90);
	menuUp.setXY(0, 41);
	menuUp.setAction(onButtonPressed);
	add(menuUp);

	// Invisible button for navigating in the side menu
	menuDown.setXY(150, 41);
    menuDown.setHeight(menuBackground.getHeight());
    menuDown.setWidth(60);
	menuDown.setAction(onButtonPressed);
	add(menuDown);

	slideMenu.setPosition(0, 41, 240, Bitmap(BITMAP_CONTROLS_MENU_BACKGROUND_ID).getHeight());
	slideMenu.setup(3, 0, Bitmap(BITMAP_CONTROL_MENU_ICON_DATEPICKER_SMALL_ID), Bitmap(BITMAP_CONTROL_MENU_ICON_DATEPICKER_LARGE_ID));
	slideMenu.setBitmapsForElement(0, BITMAP_CONTROL_MENU_ICON_DATEPICKER_SMALL_ID, BITMAP_CONTROL_MENU_ICON_DATEPICKER_LARGE_ID);
	slideMenu.setBitmapsForElement(1, BITMAP_CONTROL_MENU_ICON_GAUGE_SMALL_ID, BITMAP_CONTROL_MENU_ICON_GAUGE_LARGE_ID);
	slideMenu.setBitmapsForElement(2, BITMAP_CONTROL_MENU_ICON_PERCENTAGE_SMALL_ID, BITMAP_CONTROL_MENU_ICON_PERCENTAGE_LARGE_ID);
	slideMenu.setAnimationDuration(8);
	slideMenu.setElementSelectedCallback(slideMenuElementSelectedCallback);
	add(slideMenu);

	menuShadowTop.setBitmap(Bitmap(BITMAP_CONTROL_MENU_SHADOW_TOP_ID));
    menuShadowTop.setXY(222, 41);
	add(menuShadowTop);

	menuShadowBottom.setBitmap(Bitmap(BITMAP_CONTROL_MENU_SHADOW_BOTTOM_ID));
    menuShadowBottom.setXY(0, 41);
	add(menuShadowBottom);

	gotoMenuButton.setBitmaps(Bitmap(BITMAP_CONTROL_MENU_BUTTON_ID), Bitmap(BITMAP_CONTROL_MENU_BUTTON_PRESSED_ID));
    gotoMenuButton.setXY(0, 279);
    gotoMenuButton.setAction(onButtonPressed);
	add(gotoMenuButton);

    timeFormatStyle.setXY(0, 133);
    timeFormatStyle.setVisible(false);
    add(timeFormatStyle);

	datePicker.setXY(0, slideMenu.getY() + slideMenu.getHeight()); //datePicker.setXY(0, 133);
	datePicker.setVisible(false);
	add(datePicker);

    timePicker.setXY(0, 133); 
    timePicker.setVisible(false);
    add(timePicker);

	for (int i = 0; i < NUMBER_OF_BARS; i++)
	{
		barAnimationState[i] = NO_ANIMATION;
	}

	slideMenuElementSelectedHandler(slideMenu);
}

TimeAndDateView::~TimeAndDateView()
{
}

void TimeAndDateView::setupScreen()
{
    timeFormatStyle.setTimeUtils(presenter->getTimeUtils());
    timePicker.setTimeUtils(presenter->getTimeUtils());
}

void TimeAndDateView::tearDownScreen()
{

}

void TimeAndDateView::handleTickEvent()
{
	tickCounter++;
}

void TimeAndDateView::startThreeWayProgressBarAnimation()
{
	animationCounter = 0;

	for (int i = 0; i < NUMBER_OF_BARS; i++)
	{
		animationEquation[i] = getRandomEasingEquation();
		animationDuration[i] = Utils::randomNumberBetween(100, 200);
		barAnimationState[i] = ANIMATION_THREE_WAY_RUNNING;
	}
	currentAnimationState = ANIMATION_THREE_WAY_RUNNING;

	statusMessage.setVisible(false);
	statusMessage.invalidate();
}

TimeAndDateView::AnimationState TimeAndDateView::getAnimationState()
{
	if (currentAnimationState == ANIMATION_THREE_WAY_RUNNING)
	{
		for (int i = 0; i < NUMBER_OF_BARS; i++)
		{
			if (barAnimationState[i] == ANIMATION_THREE_WAY_RUNNING)
			{
				return ANIMATION_THREE_WAY_RUNNING;
			}
		}
		return NO_ANIMATION;
	}

	return currentAnimationState;
}

touchgfx::EasingEquation TimeAndDateView::getRandomEasingEquation()
{
	switch (Utils::randomNumberBetween(0, 6))
	{
	case 0:
		return EasingEquations::sineEaseIn;
	case 1:
		return EasingEquations::linearEaseInOut;
	case 2:
		return EasingEquations::quadEaseIn;
	case 3:
		return EasingEquations::cubicEaseOut;
	case 4:
		return EasingEquations::cubicEaseInOut;
	case 5:
		return EasingEquations::linearEaseNone;
	default:
		return EasingEquations::sineEaseIn;
	}
}

void TimeAndDateView::threeWayButtonPressedHandler(const ThreeWayProgressBar& button)
{
	//threeWayProgressBar.setActive(true);
	//startThreeWayProgressBarAnimation();
}

void TimeAndDateView::stopThreeWayProgressBarAnimation()
{
	currentAnimationState = NO_ANIMATION;
}

void TimeAndDateView::buttonPressedHandler(const AbstractButton& button)
{
	if (&button == &menuUp)
	{
		currentAnimationState = NO_ANIMATION;
		slideMenu.animateDown();
	}
	else if (&button == &menuDown)
	{
		currentAnimationState = NO_ANIMATION;
		slideMenu.animateUp();
    }
    else if (&button == &gotoMenuButton)
    {
        presenter->backOptionSelected();
    }
}

void TimeAndDateView::slideMenuElementSelectedHandler(const HorizontalSlideMenu& menu)
{
	int selectedElement = slideMenu.getSelectedElementIndex();

	// Setup menu up/down button. First set default then handle special cases
	menuUp.setTouchable(true);
	menuDown.setTouchable(true);

	if (selectedElement == 0)
	{
		menuUp.setTouchable(false);
	}
	else if (selectedElement == slideMenu.getSize() - 1)
	{
		menuDown.setTouchable(false);
	}
	// Expand the active area of the buttons to make them easier to activate
	menuUp.invalidate();
	menuDown.invalidate();

	// Set the chosen control visible
	datePicker.setVisible(selectedElement == 0);
    timePicker.setVisible(selectedElement == 1);
    timeFormatStyle.setVisible(selectedElement == 2);

	datePicker.invalidate();
    timePicker.invalidate();
    timeFormatStyle.invalidate();


	currentAnimationState = NO_ANIMATION;

   if (datePicker.isVisible())
	{
		datePicker.reset();
		// Set start values before animation
		uint16_t year = 2017;
		uint8_t month = 10, day = 7;
		eDaysOfWeek dayOfWeek = eDayOfWeek_Monday;
		presenter->getTimeUtils().getCurrentDate(year, month, day, dayOfWeek);
		datePicker.setday(14, 0, EasingEquations::backEaseInOut);
		datePicker.setMonth(6, 0, EasingEquations::backEaseInOut);
		datePicker.setYear(8, 0, EasingEquations::backEaseInOut);

		// Start animation to a specific date
		datePicker.setday(day - 1, 40, EasingEquations::backEaseInOut);
		datePicker.setMonth(month - 1, 42, EasingEquations::backEaseInOut);
		datePicker.setYear(year - DatePicker::START_YEAR, 38, EasingEquations::backEaseInOut);
    }
    else if (timePicker.isVisible())
    {
        timePicker.reset();
        uint8_t hour = 23, min = 1, sec = 0;
        presenter->getTimeUtils().getCurrentTime24(hour, min, sec);
        // Set start values before animation
        timePicker.sethour(14, 0, EasingEquations::backEaseInOut);
        timePicker.setMinute(6, 0, EasingEquations::backEaseInOut);

        // Start animation to a specific date
        timePicker.sethour(hour, 40, EasingEquations::backEaseInOut);
        timePicker.setMinute(min, 42, EasingEquations::backEaseInOut);
    }
}

void TimeAndDateView::screenSaverMinorTick()
{
	if (slideMenu.getSelectedElementIndex() == 0)
	{
		buttonPressedHandler(menuDown);
	}
	else if (slideMenu.getSelectedElementIndex() == slideMenu.getSize() - 1)
	{
		buttonPressedHandler(menuUp);
	}
	else
	{
		if (Utils::randomNumberBetween(0, 100) < 50)
		{
			buttonPressedHandler(menuUp);
		}
		else
		{
			buttonPressedHandler(menuDown);
		}
	}
}
