/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.8.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#include <gui/custom_controls_screen/TimeFormatSet.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TimeFormatSet::TimeFormatSet():
buttonCallback(this,&TimeFormatSet::buttonCallbackHandler)
{
    background.setBitmap(Bitmap(BITMAP_CONTROLS_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    setWidth(background.getWidth());
    setHeight(background.getHeight());

    timeFomatExample.setLinespacing(0);

    //timepickerSelectShowBuffer[0] = 0;
    Unicode::snprintf(timepickerSelectShowBuffer, 30, "%02d:%02d", 13, 00);
    timeFomatExample.setWildcard(timepickerSelectShowBuffer);
    timeFomatExample.setTypedText(TypedText(T_TIMEFOMATEXAMPLE));
    //timeFomatExample.setXY(6, 65);
    timeFomatExample.setPosition(6, 65, 90, 20);
    timeFomatExample.setColor(touchgfx::Color::getColorFrom24BitRGB(208, 208, 208));
    add(timeFomatExample);

    timeFormat.setXY(6, 45);
    timeFormat.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    timeFormat.setLinespacing(0);
    timeFormat.setTypedText(TypedText(T_TIMEFORMAT));
    add(timeFormat);

    clockStyleText.setXY(9, 115);
    clockStyleText.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    clockStyleText.setLinespacing(0);
    clockStyleText.setTypedText(TypedText(T_CLOCKSTYLETEXT));
    add(clockStyleText);

    timeFormattoggleBtn.setPosition(192, 45, 43, 30);
    timeFormattoggleBtn.setBitmaps(Bitmap(BITMAP_ON_43X30_ID), Bitmap(BITMAP_OFF_43X30_ID));
    timeFormattoggleBtn.setAction(buttonCallback);
    add(timeFormattoggleBtn);

    clockStyletoggleBtn.setPosition(192, 115, 43, 30);
    clockStyletoggleBtn.setBitmaps(Bitmap(BITMAP_ON_43X30_ID), Bitmap(BITMAP_OFF_43X30_ID));
    clockStyletoggleBtn.setAction(buttonCallback);
    add(clockStyletoggleBtn);
}

TimeFormatSet::~TimeFormatSet()
{

}

void TimeFormatSet::setTimeUtils(TimeUtils mTimeUtils)
{
    currTimeUtils = mTimeUtils;
    timeFormattoggleBtn.forceState(currTimeUtils.is24Hour() == false);
    clockStyletoggleBtn.forceState(currTimeUtils.isAnalogClock() == false);
}

//void TimePicker::setday(int index, int duration, EasingEquation equation)
//{
//    days.setSelectedIndex(index, duration, equation);
//}

void TimeFormatSet::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &timeFormattoggleBtn)
    {
        //enable24format
        //When timeFormattoggleBtn clicked execute C++ code
        //Execute C++ code
        if (timeFormattoggleBtn.getState() == false){
            Unicode::snprintf(timepickerSelectShowBuffer, 30, "%02d:%02d", 13, 00);
            timeFomatExample.invalidate();
            currTimeUtils.set24Hour(true);
        }
        else{
            Unicode::snprintf(timepickerSelectShowBuffer, 30, "%d:%02d PM", 1, 00);
            timeFomatExample.invalidate();
            currTimeUtils.set24Hour(false);
        }
    }
    else if (&src == &clockStyletoggleBtn)
    {
    	bool clock = currTimeUtils.isAnalogClock();
        currTimeUtils.setAnalogClock(!clock);
    }
}