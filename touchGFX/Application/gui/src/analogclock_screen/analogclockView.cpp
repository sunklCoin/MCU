#include <gui/analogclock_screen/analogclockView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

analogclockView::analogclockView():
    currentSecondCounter(0),
    currentMinuteCounter(0),
    currentHourCounter(0),
    transitionDone(false),
    onButtonPressed(this, &analogclockView::buttonPressedHandler),
    firstPresenterCall(true)
{

}

LOCATION_EXTFLASH_ATTRIBUTE
void analogclockView::setupScreen()
{
#if 1
    clockBackground.setXY(0, 0);
    clockBackground.setBitmap(Bitmap(BITMAP_WATCH5BACKGROUND_ID));
    add(clockBackground);
    //clockBackground.setBitmap(Bitmap(BITMAP_MAIN_BG_240X320PX_ID));
    handColorRed.setColor(Color::getColorFrom24BitRGB(0xFF, 0x0, 0x0));
    handColorWhite.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    secondHand.setPosition(0, 40, 240, 240);
    secondHand.setOrigin(122, 122);
    secondHand.setPainter(handColorRed);
    add(secondHand);

    minuteHand.setPosition(0, 40, 240, 240);
    minuteHand.setOrigin(122, 122);
    minuteHand.setPainter(handColorWhite);
    add(minuteHand);

    hourHand.setPosition(0, 40, 240, 240);
    hourHand.setOrigin(122, 122);
    hourHand.setPainter(handColorWhite);
    add(hourHand);
    //add(clockBackground);
    centerDot.setXY(114, 154);
    centerDot.setBitmap(Bitmap(BITMAP_WATCH5FOREGROUND_ID));
    add(centerDot);
#endif // 0
#if 0
    analogClock.setXY(0, 0);
    analogClock.setVisible(true);
    add(analogClock);
#endif // 0

    // Invisible button for navigating in the side menu
    gotoMainScreen.setWidth(240);
    gotoMainScreen.setHeight(320);
    gotoMainScreen.setXY(0, 0);
    gotoMainScreen.setAction(onButtonPressed);
    add(gotoMainScreen);
}

void analogclockView::tearDownScreen()
{

}

void analogclockView::afterTransition()
{
	//DemoView<ClockPresenter>::afterTransition();
	transitionDone = true;
}

void analogclockView::handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds, bool is24Hour)
{
#if 1
    currentSecondCounter = seconds;
    currentMinuteCounter = minutes;
    //currentHourCounter counts from 0-59 due to the number of images of the hour hand
    currentHourCounter = ((hours % 12) * 5) + (minutes / 12);

    updateClock(currentHourCounter, currentMinuteCounter, currentSecondCounter);
#endif // 0

}

void analogclockView::updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter)
{
	// Updating the clock before transition to the page is done will cause the hands to move unintended.
	// We do allow the first call from the presenter in that case where we do not animate from start.
	if (transitionDone || firstPresenterCall)
	{
		if (firstPresenterCall)
		{
			// To avoid jump in seconds when opening the view
			secondCounter++;
			firstPresenterCall = false;
		}

		secondHand.updateAngle(secondCounter * 6);

		minuteHand.updateAngle(minuteCounter * 6 + secondCounter / 10);

		hourHand.updateAngle(hourCounter * 6 + minuteCounter / 10);
	}
}

void analogclockView::buttonPressedHandler(const AbstractButton& button)
{
    if (&button == &gotoMainScreen)
    {
        presenter->gotoMainScreen();
    }
}
