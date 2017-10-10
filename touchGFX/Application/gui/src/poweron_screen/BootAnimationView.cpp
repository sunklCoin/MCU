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
#include <gui/poweron_screen/BootAnimationView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>
void BootAnimationView::setupScreen()
{
	// Setup background image
	background.setBitmap(Bitmap(BITMAP_CONTROLS_BACKGROUND_ID));
	background.setXY(0, 0);
	add(background);
	// Setup tick counter
	tickCounter = 0;

	loadingTxt.setTypedText(TypedText(T_LOADINGTXT));
	loadingTxt.setPosition(0, 100,240,50);
	loadingTxt.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
	add(loadingTxt);

	// Image Progress Bar - Displays an image as the progress bar. The image is anchored at the end of the bar
	imageProgress.setBackground(Bitmap(BITMAP_IMAGE_PROGRESS_BACKGROUND_ID));
	imageProgress.setXY(30, 150);
	imageProgress.setProgressIndicatorPosition(2, 2, imageProgress.getWidth() - (2 * 2), imageProgress.getHeight() - (2 * 2));
	imageProgress.setRange(0, 180);
	imageProgress.setBitmap(BITMAP_PROGRESS_STRIPE_ID);
	imageProgress.setDirection(AbstractDirectionProgress::RIGHT);
	imageProgress.setAnchorAtZero(false);
	add(imageProgress);

	// Remember to add widgets to container.
	// They must be added from bottom and out, or else upper layer(s)
	// may block view of elements below.

}

void BootAnimationView::updateProgress(uint16_t tick)
{
    imageProgress.setValue(tick % 181);
	imageProgress.setDirection((tick / 181) % 2 == 0 ? AbstractDirectionProgress::RIGHT : AbstractDirectionProgress::RIGHT);
}

void BootAnimationView::handleTickEvent()
{
    updateProgress(tickCounter++);
#ifdef SIMULATOR
    if ((tickCounter % 100 == 0) && (tickCounter > 50))//10000
#else
	if ((tickCounter % 100 == 0) && (tickCounter > 500))//10000
#endif
	{
        static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
        static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuScreenTransition();
	}
}
