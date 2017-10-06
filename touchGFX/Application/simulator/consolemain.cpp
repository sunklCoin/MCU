/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.6.0 standard distribution.
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
#include <platform/hal/simulator/sdl/HALSDL.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <common/TouchGFXInit.hpp>
#include <platform/driver/touch/SDLTouchController.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <platform/driver/lcd/LCD16bpp.hpp>
#elif USE_BPP==24
#include <platform/driver/lcd/LCD24bpp.hpp>
#elif USE_BPP==4
#include <platform/driver/lcd/LCD4bpp.hpp>
#elif USE_BPP==2
#include <platform/driver/lcd/LCD2bpp.hpp>
#elif USE_BPP==1
#include <platform/driver/lcd/LCD1bpp.hpp>
#else
#error Unknown USE_BPP
#endif
#include <gui_generated/common/SimConstants.hpp>
#include <stdlib.h>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <common/TouchGFXInit.hpp>

#define CANVAS_BUFFER_SIZE (9000)

int main(int argc, char** argv)
{
    NoDMA dma; //For windows/linux, DMA transfers are simulated
#if !defined(USE_BPP) || USE_BPP==16
    LCD16bpp lcd;
#elif USE_BPP==24
    LCD24bpp lcd;
#elif USE_BPP==4
    LCD4bpp lcd;
#elif USE_BPP==2
    LCD2bpp lcd;
#elif USE_BPP==1
    LCD1bpp lcd;
#else
#error Unknown USE_BPP
#endif
    SDLTouchController tc;

    // Create hardware layer. Use a display size of 480x272.
	HAL& hal = touchgfx_generic_init<HALSDL>(dma, lcd, tc, SIM_WIDTH, SIM_HEIGHT, 0, 0);

    // Simulate hardware running at 60Hz generating a vsync every 16.6667 ms
    static_cast<HALSDL&>(hal).setVsyncInterval(16.6667f);

    // Initialize SDL
    if (!static_cast<HALSDL&>(hal).sdl_init(argc, argv))
    {
        return EXIT_FAILURE;
    }

	dynamic_cast<HALSDL&>(hal).setWindowTitle("NXP Sprinkler Demo - GUI Simulator, Version 0.1");

	static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
	CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
	CanvasWidgetRenderer::setWriteMemoryUsageReport(true);

    touchgfx::HAL::getInstance()->taskEntry(); //Never returns

    return EXIT_SUCCESS;
}

