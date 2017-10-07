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
#include <gui/common/TimeUtils.hpp>

// temporary solution for getting day of week
uint16_t days_in_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

#ifdef SIMULATOR 
#include <ctime>
#ifndef _MSC_VER
#include <sys/time.h>
#endif /* _MSC_VER*/
// used only for testing under simulator
int16_t dbg_minutes_shift = 0;
#else
extern "C" {
#include "FreeRTOS.h"
#include "task.h"
}
uint32_t my_portTICK_PERIOD_MS = portTICK_PERIOD_MS;
#endif
uint16_t glb_year = 2017;
uint8_t glb_month = 9;
uint8_t glb_day = 1;
eDaysOfWeek glb_day_of_week = eDayOfWeek_Tuesday;
uint8_t glb_hour = 0;
uint8_t glb_minute = 0;
uint8_t glb_second = 0;
uint32_t glb_prev_msecs = 0;
bool glb_timeFormat = true;
bool glb_analogClock = true;

TimeUtils::TimeUtils()
{
    hours = glb_hour;
    minutes = glb_minute;
    seconds = glb_second;
    milliseconds = glb_prev_msecs;
    
}
uint8_t TimeUtils::isLeapYear(uint16_t year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1;
    else
        return 0;
}

uint8_t TimeUtils::calculatorCurrDayOfWeek(uint16_t year, uint8_t month, uint8_t day)
{
#if 0
    // w: week;y:year;c:century;m:month;d:day
    w = y + [y / 4] + [c / 4] - 2c + [26(m + 1) / 10] + d - 1
#else
    uint8_t leapYearFlag = 0;
    uint8_t year_base = 0, month_base = 0;
    uint8_t week;
    uint8_t monthofCommonYear[] = { 0, 3, 3, 6, 1, 4, 0, 3, 5, 0, 3, 5 };
    uint8_t monthofLeapYear[] = { 0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6 };
    leapYearFlag = isLeapYear(year);
    if (leapYearFlag == 0){
        year_base = 1;
        month_base = monthofCommonYear[month - 1];
    }
    else{
        year_base = 2;
        month_base = monthofLeapYear[month - 1];
    } 
   
    week = (year + year / 4 + year / 400 - year / 100 - year_base + month_base + day) % 7;
#endif
    return week;
}

void TimeUtils::setCurrentDateTime(uint16_t year, uint8_t month, uint8_t dayOfMonth, eDaysOfWeek dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second)
{
#ifdef SIMULATOR 
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);
    dbg_minutes_shift = (hour * 60 + minute) - (timenow.tm_hour * 60 + timenow.tm_min);
#endif
#else
    glb_year = year;
    glb_month = month;
    glb_day = dayOfMonth;
    glb_day_of_week = dayOfWeek;
    glb_hour = hour;
    glb_minute = minute;
    glb_second = second;
    glb_prev_msecs = xTaskGetTickCount();
#endif
}

void TimeUtils::setCurrentDate(uint16_t year, uint8_t month, uint8_t dayOfMonth)
{
#if 0//def SIMULATOR 
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);
	glb_year = year;
	glb_month = month;
	glb_month = dayOfMonth;
#endif
#else
    glb_year = year;
    glb_month = month;
    glb_day = dayOfMonth;
    uint8_t weekValue = calculatorCurrDayOfWeek(year, month, dayOfMonth);
    glb_day_of_week = (eDaysOfWeek)((weekValue == 0) ? 7 : weekValue);
#endif
}

void TimeUtils::setCurrentTime(uint8_t hour, uint8_t minute)
{
#ifdef SIMULATOR 
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);
    dbg_minutes_shift = (hour * 60 + minute) - (timenow.tm_hour * 60 + timenow.tm_min);
#endif
#else
    glb_hour = hour;
    glb_minute = minute;
#endif
}

#ifndef SIMULATOR
void TimeUtils::secondElapsed()
{
    glb_second++;
    if (glb_second == 60) {
        glb_second = 0;
        glb_minute++;
        if (glb_minute == 60) {
            glb_minute = 0;
            glb_hour++;
            if (glb_hour == 24) {
                glb_day++;
                if (glb_day_of_week == eDayOfWeek_Sunday)
                    glb_day_of_week = eDayOfWeek_Monday;
                else
                    glb_day_of_week = (eDaysOfWeek)((uint8_t)(glb_day_of_week)+1);
                if ((((glb_month == 11) || (glb_month == 4) || (glb_month == 6) || (glb_month == 9)) && (glb_day == 30)) ||
                    (((glb_month == 12) || (glb_month == 1) || (glb_month == 3) || (glb_month == 5) || (glb_month == 7) || (glb_month == 8) || (glb_month == 10)) && (glb_day == 31)) ||
                    ((glb_month == 2) && (glb_day == 28))){
                    glb_day = 1;
                    glb_month++;
                    if (glb_month == 13) {
                        glb_month = 1;
                        glb_year++;
                    }
                }
            }
        }

    }
}

void TimeUtils::updateTime()
{
    uint32_t mSecs = xTaskGetTickCount();// / portTICK_PERIOD_MS;
    while ((mSecs - glb_prev_msecs) > 1000) {
        glb_prev_msecs += 1000;
        secondElapsed();
        hours = glb_hour;
        minutes = glb_minute;
        seconds = glb_second;
        milliseconds = glb_prev_msecs;
    }
}

uint8_t TimeUtils::getSecond()
{
    return glb_second;
}
#else
void TimeUtils::secondElapsed()
{
    glb_second++;
    if (glb_second == 60) {
        glb_second = 0;
        glb_minute++;
        if (glb_minute == 60) {
            glb_minute = 0;
            glb_hour++;
            if (glb_hour == 24) {
                glb_day++;
                if (glb_day_of_week == eDayOfWeek_Sunday)
                    glb_day_of_week = eDayOfWeek_Monday;
                else
                    glb_day_of_week = (eDaysOfWeek)((uint8_t)(glb_day_of_week)+1);
                if ((((glb_month == 11) || (glb_month == 4) || (glb_month == 6) || (glb_month == 9)) && (glb_day == 30)) ||
                    (((glb_month == 12) || (glb_month == 1) || (glb_month == 3) || (glb_month == 5) || (glb_month == 7) || (glb_month == 8) || (glb_month == 10)) && (glb_day == 31)) ||
                    ((glb_month == 2) && (glb_day == 28))){
                    glb_day = 1;
                    glb_month++;
                    if (glb_month == 13) {
                        glb_month = 1;
                        glb_year++;
                    }
                }
            }
        }

    }
}

void TimeUtils::updateTime()
{
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    uint32_t mSecs = 0;//timenow.tm_sec;// / portTICK_PERIOD_MS;
    glb_prev_msecs = 0;
    secondElapsed();
    hours = timenow.tm_hour;//  glb_hour;
    minutes = timenow.tm_min;// glb_minute;
    seconds = timenow.tm_sec;// glb_second;
    milliseconds = glb_prev_msecs;
}

uint8_t TimeUtils::getSecond()
{
    return glb_second;
}
#endif


void TimeUtils::getCurrentTime24(uint8_t & hour, uint8_t & minute, uint8_t & second)
{
    hour = 11;
    minute = 11;
    second = 11;
#ifdef SIMULATOR 
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);
    uint16_t tot_minutes = (timenow.tm_hour * 60 + timenow.tm_min + dbg_minutes_shift + 1440) % 1440;
    hour = (uint8_t)((double)tot_minutes / 60.0);
    minute = tot_minutes - (hour * 60);
    second = (uint8_t)timenow.tm_sec;
#endif
#else
    hour = glb_hour;
    minute = glb_minute;
    second = glb_second;
#endif
}

void TimeUtils::getCurrentTime12(uint8_t & hour, uint8_t & minute, uint8_t & second, bool & is_pm)
{
    is_pm = false;
    getCurrentTime24(hour, minute, second);
    if (hour >= 12) {
        is_pm = true;
    }
    if (hour > 12) {
        hour -= 12;
    }
}

uint32_t TimeUtils::getCurrentTimeInSeconds()
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    getCurrentTime24(hour, minute, second);
    return hour * 3600 + minute * 60 + second;
}

void TimeUtils::getCurrentDate(uint16_t & year, uint8_t & month, uint8_t & dayOfMonth, eDaysOfWeek & dayOfWeek)
{
    year = 11;
    month = 11;
    dayOfMonth = 11;
    dayOfWeek = eDayOfWeek_Monday;

#if 0//def SIMULATOR 
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);
    // SYSTEMTIME days are Sunday=0, Monday=1,...,
    dayOfWeek = (eDaysOfWeek)((timenow.tm_wday == 0) ? 7 : timenow.tm_wday);
    dayOfMonth = (uint8_t)timenow.tm_mday;
    month = (uint8_t)timenow.tm_mon;
    year = (uint16_t)timenow.tm_year;
#else
    timeval timenow;
    gettimeofday(&timenow, NULL);

    currentTime.hours = (timenow.tv_sec / 60 / 60) % 24;
    currentTime.minutes = (timenow.tv_sec / 60) % 60;
    currentTime.seconds = timenow.tv_sec % 60;
    currentTime.milliseconds = timenow.tv_usec / 1000;
#endif
#else
    year = glb_year;
    month = glb_month;
    dayOfMonth = glb_day;
    dayOfWeek = glb_day_of_week;
	uint8_t weekValue = calculatorCurrDayOfWeek(year, month, dayOfMonth);
	dayOfWeek = (eDaysOfWeek)((weekValue == 0) ? 7 : weekValue);
#endif
}

void TimeUtils::getCurrentDateBitmaps(uint16_t & month, uint16_t & dayOfWeek, uint8_t & dayOfMonth)
{
    uint16_t _year;
    uint8_t _month;
    uint8_t _dayOfMonth;
    eDaysOfWeek _dayOfWeek;
    getCurrentDate(_year, _month, _dayOfMonth, _dayOfWeek);
    month = T_JAN; // default
    switch (_month) {
        case 2: month = T_FEB; break;
        case 3: month = T_MAR; break;
        case 4: month = T_APR; break;
        case 5: month = T_MAY; break;
        case 6: month = T_JUN; break;
        case 7: month = T_JUL; break;
        case 8: month = T_AUG; break;
        case 9: month = T_SEP; break;
        case 10: month = T_OCT; break;
        case 11: month = T_NOV; break;
        case 12: month = T_DEC; break;
    }

    dayOfWeek = T_MONDAY; // default
    switch (_dayOfWeek) {
        case eDayOfWeek_Tuesday: dayOfWeek = T_TUESDAY; break;
        case eDayOfWeek_Wednesday: dayOfWeek = T_WEDNESDAY; break;
        case eDayOfWeek_Thursday: dayOfWeek = T_THURSDAY; break;
        case eDayOfWeek_Friday: dayOfWeek = T_FRIDAY; break;
        case eDayOfWeek_Saturday: dayOfWeek = T_SATURDAY; break;
        case eDayOfWeek_Sunday: dayOfWeek = T_SUNDAY; break;
    }
    dayOfMonth = _dayOfMonth;
}


// temporary calculation of day of week, later it should be removed and day of week is received from the Web Service
// works only unitl september 2017
// based on the fact that Oct 1, 2016 is Saturday

uint16_t quick_sum[12] = { 92, 123, 151, 182, 212, 243, 273, 304, 335, 0, 31, 61 };
eDaysOfWeek quick_day[7] = { eDayOfWeek_Friday, eDayOfWeek_Saturday, eDayOfWeek_Sunday, eDayOfWeek_Monday, eDayOfWeek_Tuesday, eDayOfWeek_Wednesday, eDayOfWeek_Thursday };

eDaysOfWeek TimeUtils::GetDayOfWeek(uint8_t month, uint8_t dayOfMonth)
{
    return quick_day[(((quick_sum[month - 1] + dayOfMonth) % 7))];
}

bool TimeUtils::is24Hour()
{
    return glb_timeFormat;

}

bool TimeUtils::isAnalogClock()
{
    return glb_analogClock;
}

void TimeUtils::set24Hour(bool enable)
{
    glb_timeFormat = enable;
}

void TimeUtils::setAnalogClock(bool enable)
{
    glb_analogClock = enable;
}