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
#ifndef ANALOG_CLOCK_HPP
#define ANALOG_CLOCK_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/canvas/Shape.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#elif USE_BPP==4
#include <touchgfx/widgets/canvas/PainterGRAY4.hpp>
#elif USE_BPP==2
#include <touchgfx/widgets/canvas/PainterGRAY2.hpp>
#else
#error Unknown USE_BPP
#endif

using namespace touchgfx;

class AnalogClock : public Container
{
    public:
    AnalogClock();
    virtual ~AnalogClock() {}
    virtual void tearDownScreen();
    virtual void afterTransition();
    /**
    * Updates the hour, minutes and second counters
    * hours: 0-23
    * minutes: 0-59
    * seconds: 0-59
    */
    //void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds);

    // Updates the clock view
    void updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter);
    class SecondClockHand : public Shape<4>
    {
        public:
        SecondClockHand()
        {
            ShapePoint<int> points[4] = { { -1, 0 }, { -1, -74 }, { 1, -74 }, { 1, 0 } };
            setShape(points);
        }
    };

    class MinuteClockHand : public Shape<5>
    {
        public:
        MinuteClockHand()
        {
            ShapePoint<float> points[5] = { { -3.5f, 0 }, { -.7f, -67 }, { 0, -70 }, { .7f, -67 }, { 3.5f, 0 } };
            setShape(points);
        }
    };

    class HourClockHand : public Shape<5>
    {
        public:
        HourClockHand()
        {
            ShapePoint<float> points[5] = { { -4.5f, 2 }, { -1, -43 }, { 0, -45 }, { 1, -43 }, { 4.5f, 2 } };
            setShape(points);
        }
    };
    protected:
    /*
    * Member Declarations
    */
    //uint8_t currentSecondCounter;
    //uint8_t currentMinuteCounter;
    //uint8_t currentHourCounter;

    bool transitionDone;
    bool firstPresenterCall;
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    Circle clockBackground;
    Circle centerDot;
    PainterRGB565 myColorPainter;
    PainterRGB565 DotColorPainter;
#else
    Image clockBackground;
    Image centerDot;
#endif
    SecondClockHand secondHand;
    MinuteClockHand minuteHand;
    HourClockHand hourHand;

#if !defined(USE_BPP) || USE_BPP==16
    PainterRGB565 handColorRed;
    PainterRGB565 handColorWhite;
#elif USE_BPP==24
    PainterRGB888 handColorRed;
    PainterRGB888 handColorWhite;
#elif USE_BPP==4
    PainterGRAY4 handColorRed;
    PainterGRAY4 handColorWhite;
#elif USE_BPP==2
    PainterGRAY2 handColorRed;
    PainterGRAY2 handColorWhite;
#else
#error Unknown USE_BPP
#endif
};



#endif /*ANALOG_CLOCK_HPP*/
