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
#ifndef DIGITAL_CLOCK_HPP
#define DIGITAL_CLOCK_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/canvas/Shape.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

using namespace touchgfx;

class DigitalClock : public Container
{
    public:
    DigitalClock();
    virtual ~DigitalClock() {}
    virtual void tearDownScreen();
    /**
    * Updates the hour, minutes and second counters
    * hours: 0-23
    * minutes: 0-59
    * seconds: 0-59
    */
    //void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds);

    // Updates the clock view
    void updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter, bool is24Hour);
    
    protected:
    /*
    * Member Declarations
    */
    Image DigitalClockBg;
    TextAreaWithOneWildcard timeHourTxt;
    TextAreaWithOneWildcard timeMinTxt;
    TextAreaWithOneWildcard timeAPMTxt;
    TextArea Timedot;

    static const uint16_t TIMEHOURTXT_SIZE = 5;
    touchgfx::Unicode::UnicodeChar timeHourTxtBuffer[TIMEHOURTXT_SIZE];
    static const uint16_t TIMEMINTXT_SIZE = 5;
    touchgfx::Unicode::UnicodeChar timeMinTxtBuffer[TIMEMINTXT_SIZE];
    static const uint16_t TIMEAPMTXT_SIZE = 5;
    touchgfx::Unicode::UnicodeChar timeAPMTxtBuffer[TIMEAPMTXT_SIZE];
};



#endif /*DIGITAL_CLOCK_HPP*/
