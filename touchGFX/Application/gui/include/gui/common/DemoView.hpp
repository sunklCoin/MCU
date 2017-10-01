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
#ifndef DEMO_VIEW_HPP
#define DEMO_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/common/DemoViewInterface.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <BitmapDatabase.hpp>
#include <gui/common/McuLoadSlider.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/StatusBar.hpp>
#include <touchgfx/widgets/Box.hpp>

using namespace touchgfx;

template <class T>
class DemoView : public View<T>, public DemoViewInterface
{
public:
    DemoView() :
        onBackButtonClicked(this, &DemoView::backButtonClickedHandler),
        onMcuLoadClicked(this, &DemoView::mcuLoadClickedHandler)
    {
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
        box1.setPosition(0, 0, 240, 320);
        box1.setColor(touchgfx::Color::getColorFrom24BitRGB(13, 33, 45));
        View<T>::add(box1);
        box2.setPosition(0, 40, 240, 2);
        box2.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
        View<T>::add(box2);
#else
		MainBg.setXY(0, 0);
		MainBg.setBitmap(Bitmap(BITMAP_MAIN_BG_240X320PX_ID));
        View<T>::add(MainBg);
#endif
		// Setup StatusTime with correct initalised buffer
		// for wildcard text
	    //backButton.setBitmaps(Bitmap(BITMAP_DEMO_BACK_BUTTON_ID), Bitmap(BITMAP_DEMO_BACK_BUTTON_PRESSED_ID));

        //backButton.setXY(0, 0);
        //backButton.setAction(onBackButtonClicked);

        //mcuLoadArea.setPosition(0, HAL::DISPLAY_HEIGHT - 54, backButton.getWidth(), 54);
		//mcuLoadArea.setPosition(0, HAL::DISPLAY_HEIGHT - 54, 54, 54);
        //mcuLoadArea.setAction(onMcuLoadClicked);

		mStatusBar.setXY(HAL::DISPLAY_WIDTH - mStatusBar.getWidth(), 0);
    }

    void setDemoVieBackground(BitmapId id)
    {
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 0
        MainBg.setBitmap(Bitmap(id));
        MainBg.invalidate();
#endif
    }

    virtual void afterTransition()
    {
		//StatusTime.setVisible(true);
        View<T>::presenter->viewStartupDone();

        // These widget must be on top and are therefore added here
		View<T>::add(mStatusBar);
        View<T>::add(mcuLoadArea);
        View<T>::add(mcuLoadSlider);
    }

protected:
	/*
	* Member Declarations
	*/
	Button gotoMenuButton;
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    Box box1;
    Box box2;
#endif
	Image MainBg;
	TextAreaWithOneWildcard StatusTime;
	Image StatusWifi;
	Image StatusBluetooth;

	uint8_t currentSecondCounter;
	uint8_t currentMinuteCounter;
	uint8_t currentHourCounter;
	/*
	* Wildcard Buffers
	*/
	static const uint16_t STATUSTIME_SIZE = 11;
	Unicode::UnicodeChar StatusTimeBuffer[STATUSTIME_SIZE];

    Button backButton;
    TouchArea mcuLoadArea;
    McuLoadSlider mcuLoadSlider;
    StatusBar  mStatusBar;
    ControlData mControlData;

    Callback<DemoView, const AbstractButton&> onBackButtonClicked;
    Callback<DemoView, const AbstractButton&> onMcuLoadClicked;

    void backButtonClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->backOptionSelected();
    }

    void mcuLoadClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->mcuLoadSelected();
    }

    // DemoViewInterface impl
    virtual void showProcessorLoad(bool visible)
    {
        // Added to view here to ensure it is in front
        //if (!View<T>::container.contains(mcuLoadSlider))
        {
        //    View<T>::add(mcuLoadSlider);
        }
        (visible) ? mcuLoadSlider.show() : mcuLoadSlider.hide();
    }

    // DemoViewInterface impl
    virtual void showProcessorLoadStatusBar()
    {
        // Added to view here to ensure it is in front
        //if (!View<T>::container.contains(mStatusBar))
        {
        //    View<T>::add(mStatusBar);
        }
        mStatusBar.show();
    }

    void updateStatusBar(StatusBar::UpdateType updateType)
    {
        mStatusBar.updateStatusBar(updateType);
    }

    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent)
    {
        mcuLoadSlider.setValue(mcuLoadInProcent);
    }

	void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds,bool is24Hour)
	{
		currentSecondCounter = seconds;
		currentMinuteCounter = minutes;
		currentHourCounter = hours;
        mStatusBar.updateClock(currentHourCounter, currentMinuteCounter, currentSecondCounter, is24Hour);
	}

	int getActiveDisplayWidth()
	{
		return 240;
	}

	int getActiveDisplayHeight()
	{
		return 320;
	}
};

#endif
