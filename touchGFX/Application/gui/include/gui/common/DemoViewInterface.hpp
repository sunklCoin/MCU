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
#ifndef DEMO_VIEW_INTERFACE_HPP
#define DEMO_VIEW_INTERFACE_HPP

#include <touchgfx/hal/Types.hpp>
#include <gui/common/StatusBar.hpp>

using namespace touchgfx;

class DemoViewInterface
{
public:
    virtual ~DemoViewInterface() {}
    virtual void showProcessorLoad(bool visible) {}
    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent) {}
    virtual void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds, bool is24Hour) {}
/*
    virtual void setBluetoothState(bool state) {}
    virtual void updateListMenuElements() {}
*/
    virtual void handleKeyEvent(uint8_t keyValue){}
    virtual void showProcessorLoadStatusBar() {}
    virtual void updateStatusBar(StatusBar::UpdateType updateType = StatusBar::utAll) {}
};

#endif
