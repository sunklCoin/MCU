#include <gui/screensaverclock_screen/AnalogClock.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

AnalogClock::AnalogClock() :
//currentSecondCounter(0),
//currentMinuteCounter(0),
//currentHourCounter(0),
transitionDone(false)
{
    /*analogClockBg.setXY(0, 0);
    analogClockBg.setVisible(false);
    analogClockBg.setBitmap(Bitmap(BITMAP_WATCH5BACKGROUND_ID));

    centerdot.setXY(112, 152);
    centerdot.setVisible(false);
    centerdot.setBitmap(Bitmap(BITMAP_WATCH5FOREGROUND_ID));*/
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    clockBackground.setPosition(0, 0, 228, 308);
#if USE_BPP==1
    myColorPainter.setColor(1);
#else
    myColorPainter.setColor(Color::getColorFrom24BitRGB(0x00, 0xFF, 0xFF));
#endif
    clockBackground.setCenter(122, 162);
    clockBackground.setRadius(100);
    clockBackground.setLineWidth(5);
    clockBackground.setPainter(myColorPainter);
    clockBackground.setVisible(true);
    clockBackground.invalidate();
    add(clockBackground);
#else
    clockBackground.setXY(9, 49);
    clockBackground.setBitmap(Bitmap(BITMAP_WATCH5BACKGROUND_ID));
    add(clockBackground);
#endif
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
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    centerDot.setPosition(0, 0, 228, 308);
    //centerDot.setXY(114, 154);
#if USE_BPP==1
    myColorPainter.setColor(1);
#else
    DotColorPainter.setColor(Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00));
#endif
    centerDot.setCenter(122, 162);
    centerDot.setRadius(5);
    centerDot.setLineWidth(5);
    centerDot.setPainter(DotColorPainter);
    centerDot.setVisible(true);
    centerDot.invalidate();
    add(centerDot);
#else
    centerDot.setXY(114, 154);
    centerDot.setBitmap(Bitmap(BITMAP_WATCH5FOREGROUND_ID));
    add(centerDot);
#endif

}

void AnalogClock::tearDownScreen()
{

}

void AnalogClock::afterTransition()
{
    //DemoView<ClockPresenter>::afterTransition();
    transitionDone = true;
}

void AnalogClock::updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter)
{
    // Updating the clock before transition to the page is done will cause the hands to move unintended.
    // We do allow the first call from the presenter in that case where we do not animate from start.
    secondHand.updateAngle(secondCounter * 6);

    minuteHand.updateAngle(minuteCounter * 6 + secondCounter / 10);

    hourHand.updateAngle(hourCounter * 6 + minuteCounter / 10);
}
