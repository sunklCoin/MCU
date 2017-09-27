#include <touchgfx/hal/OSWrappers.hpp>
#include <platform/hal/nxp/mcu/LPC546x/NXP546XHAL.hpp>
#include <touchgfx/lcd/LCD.hpp>

extern "C" 
{
#include "board.h"
#include "fsl_lcdc.h"
}
#undef GPIO
#include <touchgfx/hal/GPIO.hpp>


uint16_t* NXP546XHAL::getTFTFrameBuffer() const
{
    return (uint16_t*)LCD->UPBASE;
}

void NXP546XHAL::setTFTFrameBuffer(uint16_t* adr)
{
    LCD->UPBASE = (uint32_t)adr;
}

void NXP546XHAL::configureInterrupts()
{
    NVIC_SetPriority(DMA0_IRQn, 7);
    NVIC_SetPriority(LCD_IRQn, 7);
}

void NXP546XHAL::disableInterrupts()
{
    NVIC_DisableIRQ(DMA0_IRQn);
    NVIC_DisableIRQ(LCD_IRQn);
}

void NXP546XHAL::enableInterrupts()
{
    NVIC_EnableIRQ(DMA0_IRQn);
    NVIC_EnableIRQ(LCD_IRQn);
}

void NXP546XHAL::enableLCDControllerInterrupt()
{
    LCDC_EnableInterrupts(LCD, kLCDC_VerticalCompareInterrupt);
}

static bool LCD_HasIntPorch()
{
    return ((LCD->CTRL & 0x1000) > 0);
}

static void LCD_SetNextIntPorch()
{
    LCDC_SetVerticalInterruptMode(LCD, kLCDC_StartOfFrontPorch);
}

static void LCD_SetNextIntVideo()
{
    LCDC_SetVerticalInterruptMode(LCD, kLCDC_StartOfVsync);
}

extern "C"
void LCD_IRQHandler(void)
{
    if (LCD->INTMSK & kLCDC_VerticalCompareInterrupt)
    {
        LCDC_ClearInterruptsStatus(LCD,kLCDC_VerticalCompareInterrupt);

        if (LCD_HasIntPorch())
        {
            touchgfx::GPIO::clear(touchgfx::GPIO::VSYNC_FREQ);
            LCD_SetNextIntVideo();
            touchgfx::HAL::getInstance()->frontPorchEntered();
        }
        else
        {
            touchgfx::GPIO::set(touchgfx::GPIO::VSYNC_FREQ);
            LCD_SetNextIntPorch();
            touchgfx::HAL::getInstance()->vSync();
            touchgfx::OSWrappers::signalVSync();
            // Swap frame buffers immediately instead of waiting for the task to be scheduled in.
            // Note: task will also swap when it wakes up, but that operation is guarded and will not have
            // any effect if already swapped.
            touchgfx::HAL::getInstance()->swapFrameBuffers();
        }
    }
}

extern "C"
void DMA_IRQHandler(void)
{
    touchgfx::HAL::getInstance()->signalDMAInterrupt();
}


