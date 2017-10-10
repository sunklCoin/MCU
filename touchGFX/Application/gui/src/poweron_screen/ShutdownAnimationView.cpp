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
#include <gui/poweron_screen/ShutdownAnimationView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>
void ShutdownAnimationView::setupScreen()
{
	// Setup background image
	background.setBitmap(Bitmap(BITMAP_CONTROLS_BACKGROUND_ID));
	background.setXY(0, 0);
	add(background);
	// Setup tick counter
	tickCounter = 0;

	shuttingdownTxt.setTypedText(TypedText(T_SHUTDOWNTXT));
	shuttingdownTxt.setPosition(0, 100, 240, 50);
	shuttingdownTxt.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	add(shuttingdownTxt);

	// Image Progress Bar - Displays an image as the progress bar. The image is anchored at the end of the bar
	circleProgress.setBackground(Bitmap(BITMAP_CIRCLE_PROGRESS_BACKGROUND_ID));
	circleProgress.setXY(95, 150);
	circleProgress.setRange(0, 500, 12, 1);
	circleProgress.setProgressIndicatorPosition(0, 0, circleProgress.getWidth(), circleProgress.getHeight());
	circleProgress.setCenter(circleProgress.getWidth() / 2, circleProgress.getHeight() / 2);
	circleProgress.setRadius(circleProgress.getWidth() / 2 - 12);
	circleProgressPainter.setBitmap(Bitmap(BITMAP_CIRCLE_PROGRESS_ID));
	circleProgress.setPainter(circleProgressPainter);
	circleProgress.setLineWidth(26);
	circleProgress.setStartEndAngle(-15, 345);
	add(circleProgress);

	// Remember to add widgets to container.
	// They must be added from bottom and out, or else upper layer(s)
	// may block view of elements below.

}

void ShutdownAnimationView::updateProgress(uint16_t tick)
{
	circleProgress.setValue(tick % 601);
	if (tick % 601 == 0)
	{
		// Toggle number of steps in circle updates
		int16_t unused1;
		uint16_t unused2;
		uint16_t steps;
		circleProgress.getRange(unused1, unused1, steps, unused2);

		if (steps == 12)
		{
			circleProgress.setRange(0, 500, 500, 1);
		}
		else
		{
			circleProgress.setRange(0, 500, 12, 1);
		}
	}
}

void ShutdownAnimationView::handleTickEvent()
{
    updateProgress(tickCounter++);
	if ((tickCounter % 100 == 0) && (tickCounter > 100))//10000
	{
		static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
	}
}
