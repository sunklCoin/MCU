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
#ifndef _TIMEPICKER_HPP_
#define _TIMEPICKER_HPP_

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/containers/ModalWindow.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/containers/Container.hpp>
#include <gui/custom_controls_screen/WheelSelector.hpp>

using namespace touchgfx;
// Global color definitions
#define TEXT_BLACK_ON_WHITE_R  (0x29)
#define TEXT_BLACK_ON_WHITE_G  (0x2b)
#define TEXT_BLACK_ON_WHITE_B  (0x30)

#define TEXT_DESHBOARD_DARK_R (0x24)
#define TEXT_DESHBOARD_DARK_G (0x28)
#define TEXT_DESHBOARD_DARK_B (0x2a)

#define PROGRESS_BAR_COLOR_R (0x3e)
#define PROGRESS_BAR_COLOR_G (0xaa)
#define PROGRESS_BAR_COLOR_B (0xe3)

#define TEXT_WHITE_ON_BLACK_R  (0xff)
#define TEXT_WHITE_ON_BLACK_G  (0xff)
#define TEXT_WHITE_ON_BLACK_B  (0xff)

#define MENUOPT_BACKGROUND_R (0x2b)
#define MENUOPT_BACKGROUND_G (0x2f)
#define MENUOPT_BACKGROUND_B (0x32)

#define MENUOPT_LEGEND_BG_R (0x24)
#define MENUOPT_LEGEND_BG_G (0x28)
#define MENUOPT_LEGEND_BG_B (0x2a)

#define MENUOPT_LEGEND_TEXT_R (0x6c)
#define MENUOPT_LEGEND_TEXT_G (0x73)
#define MENUOPT_LEGEND_TEXT_B (0x7a)

class SleepSchedule : public Container {
public:
	virtual ~SleepSchedule() {};

	SleepSchedule();
protected:

	static const uint16_t WHEELS_TOP_Y = 0;

	Image background;
	TextArea textTimeTitle;
	TextArea textDurationTitle;

	Image imageGradiantBGHour;
	Image imageGradiantBGMinute;
	Image imageGradiantBGDuration;
	Image imageShadowTopHour;
	Image imageShadowTopMinute;
	Image imageShadowTopDuration;
	Image imageShadowBottomHour;
	Image imageShadowBottomMinute;
	Image imageShadowBottomDuration;
	RadioButton			radioButton[2];
	RadioButtonGroup<2> radioButtonGroup;
	TextArea textAM;
	TextArea textPM;
	Image glassOverlayHour;
	Image glassOverlayMinute;
	Image glassOverlayDuration;
	TextArea textMinutes;

	WheelSelector wheelHoures;
	WheelSelector wheelMinutes;
	WheelSelector wheelDuration;

	Button buttonOK;
	TouchArea touchClose;

	Callback<SleepSchedule, const AbstractButton&> buttonClickedCallback;
	void buttonClicked(const AbstractButton& source);

	void SetDefaultTimes();

};
#endif //_TIMEPICKER_HPP_