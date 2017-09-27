/******************************************************************************
*
* @brief     This file is part of the Sprinklers Demo distribution.
*
* @author    Embedded Partners <http://www.embeddedpartners.co.il> in
*            cooperation with Draupner Graphics A/S <http://www.touchgfx.com>
*
******************************************************************************
*
* @section Copyright
*
* This file is free software and is provided for example purposes. You may
* use, copy, and modify within the terms and conditions of the license
* agreement.
*
* This is licensed software, any use must strictly comply with the signed
* license agreement and associated Terms & Conditions.
*
* Standard Terms & Conditions can be seen on www.touchgfx.com
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
#ifndef _TIMEUTILS_HPP_
#define _TIMEUTILS_HPP_

#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
/* Days of week
*/
enum eDaysOfWeek {
    eDayOfWeek_Monday = 1,
    eDayOfWeek_Tuesday,
    eDayOfWeek_Wednesday,
    eDayOfWeek_Thursday,
    eDayOfWeek_Friday,
    eDayOfWeek_Saturday,
    eDayOfWeek_Sunday
};
class TimeUtils {
    public:
    TimeUtils();
    //curr year is leap year
    uint8_t isLeapYear(uint16_t);
    // get current Day Of Week
    uint8_t calculatorCurrDayOfWeek(uint16_t year, uint8_t month, uint8_t day);
    // get current time in 24 hours format
    void getCurrentTime24(uint8_t & hour, uint8_t & minute, uint8_t & second);

    // get current time in 12 hours (AM/PM) format
    void getCurrentTime12(uint8_t & hour, uint8_t & minute, uint8_t & second, bool & is_pm);

    // get current time in total seconds
    uint32_t getCurrentTimeInSeconds();

    // get current date
    void getCurrentDate(uint16_t & year, uint8_t & month, uint8_t & dayOfMonth, eDaysOfWeek & dayOfWeek);

    // get current date in TEXT betmap ids
    void getCurrentDateBitmaps(uint16_t & month, uint16_t & dayOfWeek, uint8_t & dayOfMonth);

    // set the current date and time
    void setCurrentDateTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, eDaysOfWeek dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second);
    // set the current date
    void setCurrentDate(uint16_t year, uint8_t month, uint8_t dayOfMonth);
    // set the current date and time
    void setCurrentTime(uint8_t hour, uint8_t minute);

    bool operator==(const TimeUtils& other) const
    {
        return ((hours == other.hours) &&
                (minutes == other.minutes) &&
                (seconds == other.seconds) &&
                (milliseconds == other.milliseconds));
    }

    bool operator!=(const TimeUtils& other) const
    {
        return !(*this == other);
    }

    // Returns the time difference as count of milliseconds
    long operator-(const TimeUtils& other) const
    {
        int diff = (hours - other.hours) * 60 * 60 * 1000 +
            (minutes - other.minutes) * 60 * 1000 +
            (seconds - other.seconds) * 1000 +
            (milliseconds - other.milliseconds);
        if (diff < 0)
        {
            diff += 24 * 60 * 60 * 1000;
        }
        return diff;
    }

    static float toSeconds(long milliseconds)
    {
        return milliseconds / (float) 1000.0;
    }

    bool hasValue() const
    {
        return ((hours > 0) ||
                (minutes > 0) ||
                (seconds > 0) ||
                (milliseconds > 0));
    }

    int getValueInSeconds() const
    {
        return hours * 3600 + minutes * 60 + seconds;
    }

    int getValueInMillis() const
    {
        return getValueInSeconds() * 1000 + milliseconds;
    }
#ifndef SIMULATOR
    void updateTime();
    uint8_t getSecond();
#endif

    // get day of week
    eDaysOfWeek GetDayOfWeek(uint8_t month, uint8_t dayOfMonth);

    bool is24Hour();
    bool isAnalogClock();
    void set24Hour(bool enable);
    void setAnalogClock(bool enable);
    private:
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;
#ifndef SIMULATOR
    void secondElapsed();
    uint8_t m_prev_msecs;
#endif
};

#endif // _TIMEUTILS_HPP_
