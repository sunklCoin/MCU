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
#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <gui/common/ControlData.hpp>

using namespace touchgfx;

typedef enum {
    sbutAll,
    sbutTime,
    sbutBluetooth,
    sbutWifi,
    sbutBattery
} StatusBarUpdateType;

class StatusBar : public Container
{
public:
    typedef enum {
        utAll,
        utTime,
        utBluetooth,
        utWifi,
        utBattery
    } UpdateType;

    StatusBar();
    //StatusBar(ControlData);
    void updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter, bool isTime24Format);
    void show();
    void showWithNoAnimation();
    void updateStatusBar(UpdateType updateType = utAll);
    void hide();
    void startAnimation();
    void stopAnimation();
    bool isAnimationRunning();
protected:
	enum AnimationState
	{
		DOWN_ANIMATION,
		UP_ANIMATION,
		NO_ANIMATION
	} state;
#if 1
	uint8_t mcuLoad; // mcu load in procent
	Image background;

    AnimatedImage animation;
	/*TextArea mcuLoadHeadline;
	TextAreaWithOneWildcard mcuLoadTxt;
	Unicode::UnicodeChar mcuLoadTxtbuf[5];*/

	int16_t startPositionY;
	uint8_t animationCounter;
#endif
	virtual void handleTickEvent();
    ControlData mControlData;
	Image MainBg;
	TextAreaWithOneWildcard StatusTime;
	Image StatusWifi;
	Image StatusBluetooth;
	Image StatusBattery;
	static const uint16_t STATUSTIME_SIZE = 11;
	Unicode::UnicodeChar StatusTimeBuffer[STATUSTIME_SIZE];
private:
    void animationEnded(const AnimatedImage& source);
    ControlData getControlDate();
};



#endif /*STATUS_BAR_HPP*/
