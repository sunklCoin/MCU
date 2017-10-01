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
#ifndef BACKLIGHT_SLIDER_HPP
#define BACKLIGHT_SLIDER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

/**
* Based on CircularProgress from github repository TOR.
* https://github.com/draupnergraphics/touchgfx-open-repository/tree/master/widgets/CircularProgress
*/
class BacklightSlider : public Container
{
    public:

    BacklightSlider();

    virtual ~BacklightSlider();

    int getValue()
    {
        return currentPercentage;
    }

    protected:
    Image BackgroundBox;
    //Box BackgroundBox;
    Slider slider;

    TextAreaWithOneWildcard percentageText;
    Unicode::UnicodeChar percentageTextBuffer[5];

    TextArea headlineText;

    int currentPercentage;

    /*
    * Callback Handler Declarations
    */
    void sliderValueChangedCallbackHandler(const Slider& src, int value);
    void sliderValueStartedChangeCallbackHandler(const Slider& src, int value);

    /*
    * Callback Declarations
    */
    Callback<BacklightSlider, const Slider&, int> sliderValueChangedCallback;
    Callback<BacklightSlider, const Slider&, int> sliderValueStartedChangeCallback;
};


#endif /* BACKLIGHT_SLIDER_HPP */
