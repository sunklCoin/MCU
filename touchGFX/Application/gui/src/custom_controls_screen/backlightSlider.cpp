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
#include <gui/custom_controls_screen/BacklightSlider.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>
BacklightSlider::BacklightSlider() :
sliderValueChangedCallback(this, &BacklightSlider::sliderValueChangedCallbackHandler),
sliderValueStartedChangeCallback(this, &BacklightSlider::sliderValueStartedChangeCallbackHandler)
{
    //BackgroundBox.setPosition(0, 0,240,50);
    //BackgroundBox.setColor(touchgfx::Color::getColorFrom24BitRGB(8, 72, 107));
    int level = static_cast<FrontendApplication*>(Application::getInstance())->getControlData().getBackLightLevel();
    BackgroundBox.setBitmap(Bitmap(BITMAP_CONTROLS_MENU_BACKGROUND_ID));
    BackgroundBox.setXY(0, 0);
    add(BackgroundBox);

    slider.setBitmaps(Bitmap(BITMAP_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_BACK_ID), Bitmap(BITMAP_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_FILL_ID), Bitmap(BITMAP_SLIDER_HORIZONTAL_MEDIUM_INDICATORS_SLIDER2_ROUND_NOB_ID));
    slider.setupHorizontalSlider(10, 8, 2, 0, 186);
    slider.setValueRange(0, 128);
    slider.setValue(level);
    slider.setStartValueCallback(sliderValueStartedChangeCallback);
    slider.setNewValueCallback(sliderValueChangedCallback);
    slider.setXY(0, BackgroundBox.getHeight() - slider.getHeight());
    add(slider);

    headlineText.setTypedText(TypedText(T_PERCENTAGE_BAR_HEADLINE));
    headlineText.setXY(slider.getX() + (slider.getWidth() - headlineText.getWidth()) / 2 - 20, BackgroundBox.getY() + 5);
    headlineText.setColor(Color::getColorFrom24BitRGB(0x17, 0x3C, 0x51));
    add(headlineText);

    Unicode::snprintf(percentageTextBuffer, 5, "%d", (int)(100.0f * level / slider.getMaxValue()));
    percentageText.setWildcard(percentageTextBuffer);
    percentageText.setTypedText(TypedText(T_PERCENTAGE_BAR_READOUT));
    percentageText.setPosition(headlineText.getX() + headlineText.getWidth() + 20, headlineText.getY(), 40, headlineText.getHeight());
    percentageText.setColor(Color::getColorFrom24BitRGB(0x17, 0x3C, 0x51));// (0xFF, 0xFF, 0xFF)
    add(percentageText);

    setWidth(BackgroundBox.getWidth());
    setHeight(BackgroundBox.getHeight());
}

BacklightSlider::~BacklightSlider()
{

}

void BacklightSlider::sliderValueStartedChangeCallbackHandler(const Slider& src, int value)
{
    if (&src == &slider)
    {
        //Interaction2
        //When backlightSlider slider adjustment initiated execute C++ code
        //Execute C++ code
       // saveLcdBacklight();
    }
}

void BacklightSlider::sliderValueChangedCallbackHandler(const Slider& src, int value)
{
    if (&src == &slider)
    {
        //Interaction3
        //When backlightSlider value changed execute C++ code
        //Execute C++ code
        currentPercentage = (int)(100.0f * value / slider.getMaxValue());
        Unicode::snprintf(percentageTextBuffer, 5, "%d", currentPercentage);
        percentageText.invalidate();
        static_cast<FrontendApplication*>(Application::getInstance())->getControlData().setBackLightLevel(value);
    }
}
