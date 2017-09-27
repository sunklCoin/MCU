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
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>


#ifdef SIMULATOR
#include <ctime>
#ifndef _MSC_VER
#include <sys/time.h>
#endif /* _MSC_VER*/
#else
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <fsl_debug_console.h>
extern "C" {
#include <remoter_message.h>
}
static volatile long lastUs;
extern uint32_t SystemCoreClock;
static int freqMHz;

extern "C"
{
    extern xQueueHandle gui_srv_msg_q;
    xQueueHandle gui_msg_q;
}

#endif /* SIMULATOR */


Model::Model() : modelListener(0),
m_tick_count_down(TICKS_PER_SECOND)
{
#ifndef SIMULATOR
    gui_msg_q = xQueueGenericCreate(1, 1, 0);
#endif
#ifndef SIMULATOR
    lastUs = touchgfx::HAL::getInstance()->getCPUCycles();
    freqMHz = SystemCoreClock / 1000000;
#endif
#ifndef SIMULATOR
    m_prev_second = 0;
#endif
}

#ifndef SIMULATOR
//extern volatile uint32_t mcu_load_pct;
static uint8_t mcuLoadLast = 0;
#endif // SIMULATOR

void Model::tick()
{
	Time previousTime = currentTime;
#ifndef SIMULATOR
    int ret = 0;
    struct_remote_message msg_recv = {0};

        memset(&msg_recv, 0, sizeof(remote_message));
        ret = Message_Receive_NoBlock(&msg_recv);
        if (ret != pdFAIL) {
            if (msg_recv.msg.msg_gui_rsp.msgid != 0) {
                modelListener->dispatchMessage(msg_recv.msg.msg_gui_rsp);
            }
        }
#if 0
   uint16_t msg = 0;
    if (xQueueReceive(gui_msg_q, &msg, 0) == pdTRUE)
    {
        if (msg == 1003)//open bluetooth success
        {
            // Notify current presenter that an alarm is active
            modelListener->setBluetoothState(true);
        }
        else if (msg == 1004)//open bluetooth fail
        {
            // Notify current presenter that an alarm is no longer active
            modelListener->setBluetoothState(false);
        }
    }
#endif
#endif /* SIMULATOR */

#if 0
#ifdef SIMULATOR
#ifdef _MSC_VER
	time_t rawtime;
	struct tm timenow;
	time(&rawtime);
	localtime_s(&timenow, &rawtime);

	currentTime.hours = timenow.tm_hour;
	currentTime.minutes = timenow.tm_min;
	currentTime.seconds = timenow.tm_sec;
	currentTime.milliseconds = 0;

#else
	timeval timenow;
	gettimeofday(&timenow, NULL);

	currentTime.hours = (timenow.tv_sec / 60 / 60) % 24;
	currentTime.minutes = (timenow.tv_sec / 60) % 60;
	currentTime.seconds = timenow.tv_sec % 60;
	currentTime.milliseconds = timenow.tv_usec / 1000;
#endif  /*_MSC_VER*/
#else
	static int milliseconds = 123456;
	//uint8_t mcuLoadPct =  touchgfx::HAL::getInstance()->getMCULoadPct();
	//if (mcuLoadLast != /*mcu_load_pct*/ mcuLoadPct)
	//{
	//	mcuLoadLast = mcuLoadPct;
	//	modelListener->mcuLoadUpdated(mcuLoadLast);
	//}

	//long now = cpu_cycles();
	long now =  touchgfx::HAL::getInstance()->getCPUCycles();
	milliseconds += (now - lastUs + freqMHz / 2) / freqMHz / 1000;
	lastUs = now;
	currentTime.hours = (milliseconds / 1000 / 60 / 60) % 24;
	currentTime.minutes = (milliseconds / 1000 / 60) % 60;
	currentTime.seconds = (milliseconds / 1000) % 60;
	currentTime.milliseconds = milliseconds % 1000;

#endif /* SIMULATOR */
    if (currentTime.seconds != previousTime.seconds)
    {
        if (modelListener)
        {
            modelListener->timeUpdated(currentTime);
            if (currentTime.seconds == 0){
                //   modelListener->setBluetoothState(true);
                //   modelListener->updateListMenuElements();
            }
        }
    }
#endif

#ifndef SIMULATOR
    mTimeUtils.updateTime();
#endif
    bool second_elapsed = false;
#ifdef SIMULATOR
    if (m_tick_count_down > 0) {
        m_tick_count_down--;
        if (m_tick_count_down == 0) {
            if (m_program_seconds_left > 0)
                m_program_seconds_left--;
            m_tick_count_down = TICKS_PER_SECOND;
            second_elapsed = true;
        }
    }
#else /* SIMULATOR */
    uint8_t new_second = mTimeUtils.getSecond();
    if (m_prev_second != new_second){
        m_prev_second = new_second;
        second_elapsed = true;
    }
#endif /* SIMULATOR */
    if (second_elapsed) {
        modelListener->timeUpdated(mTimeUtils);
    }

#ifdef SIMULATOR
    extern void SM_DispatchMessage();

    SM_DispatchMessage();
#endif
}

/*void Model::switchBluetooth(bool onOff)
{
    uint16_t msg = -1;
    if (onOff){
        msg = 1001;//Open bluetooth;
    }
    else{
        msg = 1002;//Close bluetooth;
    }
#ifndef SIMULATOR
    if (gui_srv_msg_q)
    {
        // Notify condenser task to start (blinking LED)
//        xQueueSend(gui_srv_msg_q, &msg, 0);
    }
#endif
}*/
