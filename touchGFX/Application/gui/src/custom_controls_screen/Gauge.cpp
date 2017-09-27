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
#include <gui/custom_controls_screen/Gauge.hpp>
#include <touchgfx/Color.hpp>

Gauge::Gauge() :
    gaugeAnimationRunning(false),
    gaugeAnimationDuration(10),
    easingEquation(EasingEquations::backEaseOut)
{
    add(background);
    add(needleShadow);
    add(needle);
    add(center);
}

Gauge::~Gauge()
{
}


void Gauge::setBitmaps(Bitmap backgroundBmp, Bitmap centerBmp)
{
    background.setBitmap(backgroundBmp);
    background.setXY(0, 0);

    center.setBitmap(centerBmp);
    center.setXY((background.getWidth() - center.getWidth()) / 2, (background.getHeight() - center.getHeight()) / 2);

    colorPainter.setColor(Color::getColorFrom24BitRGB(0xAE, 0x18, 0x24));
    needle.setPosition(0, 0, background.getWidth(), background.getHeight());
    needle.setOrigin(background.getWidth() / 2, background.getHeight() / 2);
    needle.setPainter(colorPainter);

    shadowPainter.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0), 60);
    needleShadow.setPosition(0, 0, background.getWidth(), background.getHeight());
    needleShadow.setOrigin(background.getWidth() / 2, background.getHeight() / 2);
    needleShadow.setPainter(shadowPainter);


    setWidth(background.getWidth());
    setHeight(background.getHeight());
}

void Gauge::setLimits(int newMinValue, int newMaxValue, int newMinDegree, int newMaxDegree)
{
    minValue = newMinValue;
    maxValue = newMaxValue;
    minDegree = newMinDegree;
    maxDegree = newMaxDegree;

    degreesPerValue = ((maxDegree - minDegree) / ((float)maxValue - minValue));

    currentValue = minValue;
    needle.updateAngle((int)((currentValue - minValue) * degreesPerValue) + minDegree);
    needleShadow.updateAngle((int)((currentValue - minValue) * degreesPerValue) + minDegree);
}

void Gauge::setValue(int newValue)
{
    if (newValue > maxValue)
    {
        newValue = maxValue;
    }
    else if (newValue < minValue)
    {
        newValue = minValue;
    }
    deltaValue = newValue - currentValue;

    Application::getInstance()->registerTimerWidget(this);
    gaugeAnimationRunning = true;
    gaugeAnimationCounter = 0;
}

int Gauge::getValue()
{
    return currentValue;
}

void Gauge::setAnimationDuration(uint16_t animationDuration)
{
    gaugeAnimationDuration = animationDuration;
}

void Gauge::setEasingEquation(EasingEquation newEasingEquation)
{
    easingEquation = newEasingEquation;
}

void Gauge::handleTickEvent()
{
    if (gaugeAnimationRunning)
    {
        if (gaugeAnimationCounter <= gaugeAnimationDuration)
        {
            int16_t delta = easingEquation(gaugeAnimationCounter, 0, deltaValue, gaugeAnimationDuration);

            needle.updateAngle((int)(((currentValue + delta) - minValue) * degreesPerValue)  + minDegree);
            needleShadow.updateAngle((int)(((currentValue + delta) - minValue) * degreesPerValue)  + minDegree);
            gaugeAnimationCounter++;
        }
        else
        {
            // End of animation
            gaugeAnimationRunning = false;
            gaugeAnimationCounter = 0;
            Application::getInstance()->unregisterTimerWidget(this);

            currentValue = currentValue + deltaValue;
        }
    }
}
