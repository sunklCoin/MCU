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
#include <gui/custom_controls_screen/SleepSchedule.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <stddef.h>

SleepSchedule::SleepSchedule() :
buttonClickedCallback(this, &SleepSchedule::buttonClicked)
{

	//setBackground(BITMAP_SET_TIME_BACKGROUND_ID);
	background.setBitmap(Bitmap(BITMAP_CONTROLS_MENU_BACKGROUND_ID));
	background.setXY(0, 0);
	add(background);

	imageGradiantBGDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_WHEEL_GRADIENT_ID));
	imageGradiantBGDuration.setXY((background.getWidth() - imageGradiantBGDuration.getWidth())/2, WHEELS_TOP_Y);
	add(imageGradiantBGDuration);

	add(wheelDuration);

	imageShadowTopDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_TOP_GRADIENT_ID));
	imageShadowTopDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY());
	add(imageShadowTopDuration);
	imageShadowBottomDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_BOTTOM_GRADIENT_ID));
	imageShadowBottomDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY() + imageGradiantBGDuration.getHeight() - imageShadowBottomDuration.getHeight());
	add(imageShadowBottomDuration);
	glassOverlayDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_GLASS_OVERLAY_ID));
	glassOverlayDuration.setXY(imageGradiantBGDuration.getX() + imageGradiantBGDuration.getWidth() / 2 - glassOverlayDuration.getWidth() / 2,
		imageGradiantBGDuration.getY() + imageGradiantBGDuration.getHeight() / 2 - glassOverlayDuration.getHeight() / 2);
	add(glassOverlayDuration);

	uint16_t normalTextColor = Color::getColorFrom24BitRGB(TEXT_BLACK_ON_WHITE_R, TEXT_BLACK_ON_WHITE_G, TEXT_BLACK_ON_WHITE_B);
	uint16_t selectedTextColor = Color::getColorFrom24BitRGB(PROGRESS_BAR_COLOR_R, PROGRESS_BAR_COLOR_G, PROGRESS_BAR_COLOR_B);
	uint16_t selectedBackgroundColor = Color::getColorFrom24BitRGB(246, 246, 246);

	wheelDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY());
	wheelDuration.setup(imageGradiantBGDuration.getWidth(), imageGradiantBGDuration.getHeight(), 15, imageGradiantBGDuration.getY(), T_TIME_PICKER_DURATION);
	wheelDuration.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, glassOverlayDuration.getY() - imageGradiantBGDuration.getY(), glassOverlayDuration.getHeight());

	SetDefaultTimes();
	setWidth(background.getWidth());
	setHeight(105);
}


void SleepSchedule::buttonClicked(const AbstractButton& source) {
	if (&source == &touchClose) {

	}
	else if (&source == &buttonOK) {
		SetDefaultTimes();
	}
}


void SleepSchedule::SetDefaultTimes() {
	wheelHoures.setSelectedIndex(5, 10);
	wheelMinutes.setSelectedIndex(30, 10);
	wheelDuration.setSelectedIndex(1, 10);
	radioButtonGroup.setSelected(radioButton[0]);
}
