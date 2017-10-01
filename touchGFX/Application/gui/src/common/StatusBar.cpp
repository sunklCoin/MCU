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
#include <gui/common/StatusBar.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

StatusBar::StatusBar() 
:animationCounter(0),
animation(BITMAP_BATTRY00_ID, BITMAP_BATTRY04_ID, 10)
{
	//background.setBitmap(Bitmap(BITMAP_DEMO_MCU_LOAD_BACKGROUND_ID));
	//setWidth(background.getWidth());
	//setHeight(background.getHeight());

	//// set background outside container
    background.setHeight(40);
    background.setWidth(240);
    background.setXY(0, 0);
	background.setAlpha(168);
    add(background);

	setWidth(240);
	setHeight(40);

    //DON'T init StatusTimeBuffer
	//Unicode::snprintf(StatusTimeBuffer, 5, "%d", StatusTimeBuffer); 
	StatusTime.setWildcard(StatusTimeBuffer);
	StatusTime.setTypedText(TypedText(T_STATUSTIMEID));
	StatusTime.setPosition(140, 9, 90, 20);
	StatusTime.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
	add(StatusTime);

	StatusWifi.setXY(10, 4);
	StatusWifi.setBitmap(Bitmap(BITMAP_IC_WIFI_SIGNAL_4_DARK_ID));
    StatusWifi.setVisible(mControlData.isWifiEnable());
	add(StatusWifi);

	StatusBluetooth.setXY(55, 4);
	StatusBluetooth.setBitmap(Bitmap(BITMAP_BLUETOOTH_32X32_ID));
    StatusBluetooth.setVisible(mControlData.isBTEnable());
	add(StatusBluetooth);


    gaugeImg.setBitmap(Bitmap(BITMAP_TANK_CONTENT_ID));
    gaugeContainer.setWidth(gaugeImg.getWidth());
    gaugeContainer.setHeight(gaugeImg.getHeight());
    //Set reference point: adjust gauge relative to background container (100% filled)
    gaugeContainer.setXY(101, 13);
    gaugeContainer.add(gaugeImg);
    gaugeImg.moveTo(-(gaugeContainer.getWidth()*(100-mControlData.getBatteryLevel())/100),0);
    gaugeContainer.setVisible(mControlData.isCharging() == false);
    add(gaugeContainer);


    StatusBattery.setXY(100, 12);
    if (mControlData.getBatteryLevel() <= 2){
        StatusBattery.setBitmap(Bitmap(BITMAP_BATTRYLOW_ID));
    }
    else{
        StatusBattery.setBitmap(Bitmap(BITMAP_BATTRY00_ID));
    }
    StatusBattery.setVisible(mControlData.isCharging() == false);
    add(StatusBattery);

    if (StatusBattery.isVisible()){
        if (isAnimationRunning()){
            stopAnimation();
        }
    }

    animation.setXY(100, 4);
    animation.setVisible(mControlData.isCharging() == true);
    add(animation);
    if (animation.isVisible()){
        if (!isAnimationRunning()){
            startAnimation();
        }
    }
}

void StatusBar::updateStatusBar(UpdateType updateType)
{
    if (updateType == utAll || updateType == utTime) {
        StatusTime.invalidate();
    }

    if (updateType == utAll || updateType == utWifi) {
        StatusWifi.setVisible(mControlData.isWifiEnable());
        StatusWifi.invalidate();
    }

    if (updateType == utAll || updateType == utBluetooth) {
        StatusBluetooth.setVisible(mControlData.isBTEnable());
        StatusBluetooth.invalidate();
    }

    if (updateType == utAll || updateType == utBattery) {
        if (mControlData.getBatteryLevel() <= 2){
            StatusBattery.setBitmap(Bitmap(BITMAP_BATTRYLOW_ID ));
        }
        else{
            gaugeImg.moveTo(-(gaugeContainer.getWidth()*(100 - mControlData.getBatteryLevel()) / 100), 0);
        }

        StatusBattery.setVisible(mControlData.isCharging() == false);
        gaugeContainer.setVisible(mControlData.isCharging() == false);
        gaugeContainer.invalidate();
        StatusBattery.invalidate();

        if (mControlData.isCharging() == true){
            animation.setVisible(true);
            if (!isAnimationRunning()){
                startAnimation();
            }
        }
        else{
            animation.setVisible(false);
            if (isAnimationRunning()){
                stopAnimation();
            }
        }
        animation.invalidate();
    }
}

void StatusBar::updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter,bool isTime24Format)
{
	uint8_t tempHourCounter;
	if (hourCounter > 12){
		tempHourCounter = hourCounter - 12;
	}else if (hourCounter == 0){
		tempHourCounter = 12;
    }
    else{
        tempHourCounter = hourCounter;
    }

	if (isTime24Format){
		Unicode::snprintf(StatusTimeBuffer, 10, "%02d:%02d", hourCounter, minuteCounter);
	}
	else{
		if (hourCounter >= 12){
			Unicode::snprintf(StatusTimeBuffer, 10, "%02d:%02d PM", tempHourCounter, minuteCounter);
		}
		else{
			Unicode::snprintf(StatusTimeBuffer, 10, "%02d:%02d AM", tempHourCounter, minuteCounter);
		}
	}
	StatusTime.invalidate();
}

void StatusBar::show()
{
	Application::getInstance()->registerTimerWidget(this);
	state = DOWN_ANIMATION;
    startPositionY = -40;// background.getWidth();
}

void StatusBar::hide()
{
	Application::getInstance()->registerTimerWidget(this);
	state = UP_ANIMATION;
    startPositionY = 0;// background.getX();
}

void StatusBar::handleTickEvent()
{

	uint8_t duration = 12;

	if (animationCounter > duration)
	{
		// End of animation
		state = NO_ANIMATION;
		animationCounter = 0;
		Application::getInstance()->unregisterTimerWidget(this);
	}
	else
	{
        int8_t animationDirection = (state == DOWN_ANIMATION) ? 1 : -1;
        background.moveTo(0, startPositionY + animationDirection * EasingEquations::linearEaseNone(animationCounter, 0, getHeight(), duration));
        StatusTime.setPosition(140, background.getY() + 9, 90, 20);
        StatusTime.invalidate();

        StatusWifi.setXY(10, background.getY() + 4);
        StatusWifi.invalidate();

        StatusBluetooth.setXY(55, background.getY() + 4);
        StatusBluetooth.invalidate();

        gaugeContainer.setXY(101, background.getY() + 13);
        gaugeContainer.invalidate();

        StatusBattery.setXY(100, background.getY() + 12);
        StatusBattery.invalidate();

        animation.setXY(100, background.getY() + 12);
        animation.invalidate();
		animationCounter++;
	}
}


void StatusBar::animationEnded(const AnimatedImage& source)
{
    animation.startAnimation(!animation.isReverse(), false, true);
}

/**
* Start the animation in the same direction as it was stopped.
* Change the label text to reflect the state
*/
void StatusBar::startAnimation()
{
    animation.setVisible(true);
    StatusBattery.setVisible(false);
    animation.startAnimation(animation.isReverse(), false, true);
}

/**
* Stop, or pause, the animation.
* Change the label text to reflect the state
*/
void StatusBar::stopAnimation()
{
    animation.setVisible(false);
    animation.stopAnimation();
}

/**
* Tells whether the animation is running or not.
* @return Returns true if the animation is running, otherwise returns false
*/
bool StatusBar::isAnimationRunning()
{
    return animation.isRunning();
}

//ControlData StatusBar::getControlDate()
//{
//    return;
//}
