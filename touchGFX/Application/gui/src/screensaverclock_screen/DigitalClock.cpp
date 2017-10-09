#include <gui/screensaverclock_screen/DigitalClock.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>

DigitalClock::DigitalClock()
{
    DigitalClockBg.setXY(0, 21);//(0, 121)
    DigitalClockBg.setBitmap(Bitmap(BITMAP_TIMEPICKER_MAIN_BACKGROUND_ID));
    add(DigitalClockBg);



   // timeHourTxtBuffer[0] = 0;
    /*timeHourTxt.setWildcard(timeHourTxtBuffer);
    timeHourTxt.setLinespacing(0);
    timeHourTxt.setTypedText(TypedText(T_TIMEHOUR));
    timeHourTxt.setXY(12, 182);
    timeHourTxt.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    add(timeHourTxt);*/

    Unicode::snprintf(timeHourTxtBuffer, 5, "%02d", 0);
    timeHourTxt.setWildcard(timeHourTxtBuffer);
    timeHourTxt.setTypedText(TypedText(T_TIMEHOUR));
	timeHourTxt.setXY(20, 52); //(20, 152)
    timeHourTxt.setColor(Color::getColorFrom24BitRGB(0, 0, 0));
    add(timeHourTxt);

    Unicode::snprintf(timeMinTxtBuffer, 5, "%02d", 0);
    timeMinTxt.setWildcard(timeMinTxtBuffer);
    timeMinTxt.setTypedText(TypedText(T_TIMEMIN));
    timeMinTxt.setXY(140, 52);//(140, 152)
    timeMinTxt.setColor(Color::getColorFrom24BitRGB(0, 0, 0));
    add(timeMinTxt);

    Unicode::strncpy(timeAPMTxtBuffer, "PM", 5);
    timeAPMTxt.setWildcard(timeAPMTxtBuffer);
    timeAPMTxt.setTypedText(TypedText(T_SCREENSAVERAPM));
    timeAPMTxt.setPosition(152, 129,60,40);//(152, 229,60,40)
    timeAPMTxt.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    timeAPMTxt.setVisible(false);
    add(timeAPMTxt);

    Timedot.setXY(106, 35);//(106, 135)
    Timedot.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    Timedot.setLinespacing(0);
    Timedot.setTypedText(TypedText(T_TIMEDOT));
    add(Timedot);
}

void DigitalClock::tearDownScreen()
{

}

void DigitalClock::updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter, bool is24Hour)
{
    // Updating the clock before transition to the page is done will cause the hands to move unintended.
    // We do allow the first call from the presenter in that case where we do not animate from start.
    if (!is24Hour){
        timeAPMTxt.setVisible(is24Hour == false);
        if (hourCounter >= 12) {
            Unicode::strncpy(timeAPMTxtBuffer, "PM", 5);
        }
        else{
            Unicode::strncpy(timeAPMTxtBuffer, "AM", 5);
        }
        timeAPMTxt.invalidate();
        if (hourCounter > 12) {
            hourCounter -= 12;
        }
    }

    Unicode::snprintf(timeHourTxtBuffer, 5, "%02d", hourCounter);
    Unicode::snprintf(timeMinTxtBuffer, 5, "%02d", minuteCounter);
    timeHourTxt.invalidate();
    timeMinTxt.invalidate();
}
