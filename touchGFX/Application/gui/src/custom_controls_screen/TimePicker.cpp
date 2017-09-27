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
#include <gui/custom_controls_screen/TimePicker.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>

TimePicker::TimePicker()
:onSelectedElementChanged(this, &TimePicker::selectedElementChangedHandler)
{
    background.setBitmap(Bitmap(BITMAP_TIMEPICKER_MAIN_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    colortype normalTextColor = Color::getColorFrom24BitRGB(0x31, 0x31, 0x31);
    colortype selectedTextColor = Color::getColorFrom24BitRGB(0x00, 0x8A, 0xFF);
    colortype selectedBackgroundColor = Color::getColorFrom24BitRGB(0xF5, 0xF5, 0xF5);//0xF5,0xF5,0xF5

    hours.setXY(45, 9);
    hours.setup(55, 118, 10, 52, T_TIMEPICKER_HOURS);
    hours.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 47, 27);
    hours.setElementSelectedCallback(onSelectedElementChanged);
    add(hours);

    minutes.setXY(155, 9);
    minutes.setup(55, 118, 10, 52, T_TIMEPICKER_MINUTES);
    minutes.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, 47, 27);//83,42
    minutes.setElementSelectedCallback(onSelectedElementChanged);
    add(minutes);

    shadowTop.setBitmap(Bitmap(BITMAP_TIMEPICKER_TOP_SHADOW_OVERLAY_ID));
    shadowTop.setXY(0, 9);
    add(shadowTop);

    shadowBottom.setBitmap(Bitmap(BITMAP_TIMEPICKER_BOTTOM_SHADOW_OVERLAY_ID));
    shadowBottom.setXY(0, background.getHeight() - shadowBottom.getHeight() - 9);
    add(shadowBottom);

    glassOverlay.setBitmap(Bitmap(BITMAP_DATEPICKER_GLASS_OVERLAY_ID));
    glassOverlay.setXY(-65, (background.getHeight() - glassOverlay.getHeight()) / 2);
    add(glassOverlay);


    /*Unicode::snprintf(timepickerSelectShowBuffer, 5, "%02d", 0);
    timepickerSelectShow.setWildcard(timepickerSelectShowBuffer);
    timepickerSelectShow.setTypedText(TypedText(T_TIMEPICKER_SELECTEDSHOW));
    timepickerSelectShow.setXY(78, 101);
    timepickerSelectShow.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    add(timepickerSelectShow);*/


    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

TimePicker::~TimePicker()
{

}

//void TimePicker::setday(int index, int duration, EasingEquation equation)
//{
//    days.setSelectedIndex(index, duration, equation);
//}

void TimePicker::sethour(int index, int duration, EasingEquation equation)
{
    hours.setSelectedIndex(index, duration, equation);
}

void TimePicker::setMinute(int index, int duration, EasingEquation equation)
{
    minutes.setSelectedIndex(index, duration, equation);
}

void TimePicker::reset()
{
    hours.reset();
    minutes.reset();
}

void TimePicker::setTimeUtils(TimeUtils mTimeUtils)
{
    currTimeUtils = mTimeUtils;
}

void TimePicker::selectedElementChangedHandler(const WheelSelector& wheel, const int& index)
{
    // Adjust the number of days in the selected month/year
    /*hours.getSelectedIndex() + 1, 
    minutes.getSelectedIndex()*/
    currTimeUtils.setCurrentTime(hours.getSelectedIndex(), minutes.getSelectedIndex());
}

