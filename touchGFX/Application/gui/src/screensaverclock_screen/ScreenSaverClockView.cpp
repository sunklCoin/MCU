#include <gui/screensaverclock_screen/ScreenSaverClockView.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>


ScreenSaverClockView::ScreenSaverClockView():
currentSecondCounter(0),
currentMinuteCounter(0),
currentHourCounter(0),
transitionDone(false),
onButtonPressed(this, &ScreenSaverClockView::buttonPressedHandler),
firstPresenterCall(true)
{
    ScreenSaverClockBg.setXY(0, 0);
    ScreenSaverClockBg.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
    add(ScreenSaverClockBg);

    mAnalogClock.setPosition(0, 0, 240, 320);
    mAnalogClock.setVisible(false);
    add(mAnalogClock);

    mDigitalClock.setPosition(0, 0, 240, 320);
    mDigitalClock.setVisible(false);
    add(mDigitalClock);

    // Invisible button for navigating in the side menu
    gotoMainScreen.setWidth(240);
    gotoMainScreen.setHeight(320);
    gotoMainScreen.setXY(0, 0);
    gotoMainScreen.setAction(onButtonPressed);
    add(gotoMainScreen);
}


void ScreenSaverClockView::setupScreen()
{

}

void ScreenSaverClockView::tearDownScreen()
{

}


void ScreenSaverClockView::afterTransition()
{
    //DemoView<ClockPresenter>::afterTransition();
    transitionDone = true;
}


void ScreenSaverClockView::handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds, bool is24Hour, bool isAnalogClock)
{
#if 1
    currentSecondCounter = seconds;
    currentMinuteCounter = minutes;
    //currentHourCounter counts from 0-59 due to the number of images of the hour hand
    currentHourCounter = ((hours % 12) * 5) + (minutes / 12);
    mAnalogClock.setVisible(isAnalogClock == true);
    mDigitalClock.setVisible(isAnalogClock == false);

    if (isAnalogClock){
        updateClock(currentHourCounter, currentMinuteCounter, currentSecondCounter, is24Hour);
    }
    else{
        updateClock(hours, currentMinuteCounter, currentSecondCounter, is24Hour);
    }

#endif // 0

}

void ScreenSaverClockView::updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter, bool is24Hour)
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
        if (mAnalogClock.isVisible()){
            mAnalogClock.updateClock(hourCounter, minuteCounter, secondCounter);
        }
        else{
            mDigitalClock.updateClock(hourCounter, minuteCounter, secondCounter, is24Hour);
        }
    }
}

void ScreenSaverClockView::buttonPressedHandler(const AbstractButton& button)
{
    if (&button == &gotoMainScreen)
    {
        presenter->gotoMainScreen();
    }
}
