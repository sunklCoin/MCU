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
#ifndef TIME_PICKER_HPP
#define TIME_PICKER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <BitmapDatabase.hpp>
#include <gui/custom_controls_screen/WheelSelector.hpp>
#include <gui/custom_controls_screen/WheelSelectorExtra.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <gui/common/TimeUtils.hpp>
using namespace touchgfx;

/**
 * @class DatePicker
 *
 * @brief A date picker.
 *        Container with a day, month and year scrollable wheel.
 *
 * @sa Container
 */
class TimePicker : public Container
{
public:
TimePicker();
virtual ~TimePicker();

    void sethour(int index, int duration, EasingEquation equation);
    void setMinute(int index, int duration, EasingEquation equation);

    void reset();
    void setTimeUtils(TimeUtils mTimeUtils);
protected:
    ///static const int START_YEAR = 2012;

    Image background;
    Image shadowTop;
    Image shadowBottom;
    Image glassOverlay;
    TextAreaWithOneWildcard timepickerSelectShow;
    WheelSelector hours;
    WheelSelector minutes;
    TimeUtils currTimeUtils;
    /*
    * Wildcard Buffers
    */
    static const uint16_t TIMEPICKERSELECTSHOW_SIZE = 30;
    touchgfx::Unicode::UnicodeChar timepickerSelectShowBuffer[TIMEPICKERSELECTSHOW_SIZE];

    Callback<TimePicker, const WheelSelector&, const int&> onSelectedElementChanged;
    void selectedElementChangedHandler(const WheelSelector& wheel, const int& index);

    //uint16_t getNumberOfDays(uint16_t month, uint16_t year);

};


#endif /* TIME_PICKER_HPP */
