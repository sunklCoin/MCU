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
#include <gui/common/DemoPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <stdlib.h>


DemoPresenter::DemoPresenter(DemoViewInterface& view) :
    viewInterface(view)
{
}

void DemoPresenter::activate()
{
	timeUpdated(model->getCurrentTime());
}

void DemoPresenter::deactivate()
{

}

void DemoPresenter::timeUpdated(Time time)
{
	viewInterface.handleTimeUpdated(time.hours, time.minutes, time.seconds,true);
}

void DemoPresenter::timeUpdated(TimeUtils mTimeUtils)
{
    Time time;
    mTimeUtils.getCurrentTime24(time.hours, time.minutes,time.seconds);
    viewInterface.handleTimeUpdated(time.hours, time.minutes, time.seconds, mTimeUtils.is24Hour());
}

void DemoPresenter::updateStatusBar(StatusBar::UpdateType updateType)
{
    viewInterface.updateStatusBar(updateType);
}

void DemoPresenter::backOptionSelected()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuScreenTransition();
}

void DemoPresenter::mcuLoadSelected()
{
   // model->setMCULoadActive(!model->getMCULoadActive());
   // showProcessorLoad();
}

void DemoPresenter::mcuLoadUpdated(uint8_t mcuLoad)
{
    /*if (model->getMCULoadActive())
    {
        viewInterface.updateProcessorLoad(mcuLoad);
    }*/
}

void DemoPresenter::viewStartupDone()
{
    // Ensure that the mcuLoad is activated on demo screen startup
    // if it was selected on the previous screen
    //if (model->getMCULoadActive())
    //{
    //    showProcessorLoad();
    //}
    showProcessorLoadStatusBar();
}

void DemoPresenter::showProcessorLoad()
{
    //viewInterface.showProcessorLoad(model->getMCULoadActive());
}

void DemoPresenter::showProcessorLoadStatusBar()
{
    viewInterface.showProcessorLoadStatusBar();
}

void DemoPresenter::showScreenSaver()
{
    viewInterface.showScreenSaver();
}

/*
void DemoPresenter::setBluetoothState(bool state)
{
    viewInterface.setBluetoothState(state);
}

void DemoPresenter::updateListMenuElements()
{
    viewInterface.updateListMenuElements();
}
*/