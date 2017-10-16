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
#ifndef DEMO_PRESENTER_HPP
#define DEMO_PRESENTER_HPP

#include <mvp/Presenter.hpp>
#include <gui/common/DemoViewInterface.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/TimeUtils.hpp>
#include <gui/common/ControlData.hpp>
#include <gui/common/StatusBar.hpp>

using namespace touchgfx;

class DemoPresenter : public Presenter, public ModelListener
{
public:
    DemoPresenter(DemoViewInterface& view);

    void backOptionSelected();
    void mcuLoadSelected();
	/**
	* The activate function is called automatically when this screen is "switched in"
	* (ie. made active). Initialization logic can be placed here.
	*/
	virtual void activate();

	/**
	* The deactivate function is called automatically when this screen is "switched out"
	* (ie. made inactive). Teardown functionality can be placed here.
	*/
	virtual void deactivate();
    virtual void mcuLoadUpdated(uint8_t mcuLoad);

    void viewStartupDone();
	virtual void timeUpdated(Time time);
    virtual void timeUpdated(TimeUtils mTimeUtils);
    virtual void updateStatusBar(StatusBar::UpdateType updateType = StatusBar::utAll);
    virtual void showScreenSaver();
/*
    virtual void setBluetoothState(bool state);
    virtual void updateListMenuElements();
*/
protected:
	DemoViewInterface& viewInterface;

	ControlData mControlData(){
	    return static_cast<FrontendApplication*>(Application::getInstance())->getControlData();
	}
    void showProcessorLoad();
    void showProcessorLoadStatusBar();
};

#endif
