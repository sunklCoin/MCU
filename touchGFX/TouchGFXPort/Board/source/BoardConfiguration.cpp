#include <bsp/RemoterTouchController.hpp>
#include <common/TouchGFXInit.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>

#include <platform/hal/nxp/mcu/LPC546x/NXP546XHAL.hpp>
#include <platform/hal/nxp/mcu/LPC546x/NXP546XDMA.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <platform/driver/touch/NoTouchController.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/hal/Buttons.hpp>
#undef GPIO
#include <touchgfx/hal/GPIO.hpp>
#include <stdio.h>
#include <string.h>
#include <platform/core/arm/cortex-m/CortexMMCUInstrumentation.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>

//Driver includes
extern "C" 
{
#include "board.h"
#include "leds.h"  
#include "fsl_debug_console.h"
#include "fsl_lcdc.h"
#include "fsl_lcd_RK043.h"  
#include "fsl_spifi_54608_eval_board.h"
#include "pin_mux.h"
#include "fsl_sctimer.h"
}
/*******************************************************************************
* Definitions
******************************************************************************/
/* SDRAM Address Base */
#define SDRAM_BASE      0xA0000000

/*******************************************************************************
* Prototypes
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/

/* FRAMEBUFFER_ADDR */
#if (defined(__CC_ARM) || defined(__GNUC__))
__attribute__((aligned(16)))
#elif defined(__ICCARM__)
#pragma data_alignment = 16
#else
#error Toolchain not support.
#endif

extern uint16_t *lcd_framebuffer;

//Native display width and height
static const uint16_t DISPLAY_NATIVE_WIDTH  = IMG_WIDTH;
static const uint16_t DISPLAY_NATIVE_HEIGHT = IMG_HEIGHT;

//Linked list memory for scatter-gather DMA. Must contain same number of elements as the height of the display.
#if defined(__ICCARM__)
#pragma data_alignment = 16U
dma_descriptor_t lliMemory[IMG_HEIGHT];
#elif defined(__CC_ARM)
__attribute__((aligned(16U))) dma_descriptor_t lliMemory[IMG_HEIGHT];
#elif defined(__GNUC__)
__attribute__((aligned(16U))) dma_descriptor_t lliMemory[IMG_HEIGHT];
#endif

//Initialize DMA driver with native display height
//NoDMA dma; //Initially we do not want DMA support
NXP546XDMA dma(lliMemory);

//MCU instrumentation for performance monitoring
CortexMMCUInstrumentation mcuInstr;

//16bpp display mode
LCD16bpp display;

//NoTouchController tc;
RemoterTouchController tc;

////////////////////////////////////////////////////////////////////////////////
//////////                      namespace touchgfx                //////////////
////////////////////////////////////////////////////////////////////////////////
namespace touchgfx
{
  
  ////////////////////////////////////////////////////////////////////////////////
  //////////                      touchgfx_init                     //////////////
  ////////////////////////////////////////////////////////////////////////////////
  void touchgfx_init()
  {
    //Instantiate HAL
    HAL& hal = touchgfx_generic_init<NXP546XHAL>(dma, display, tc, DISPLAY_NATIVE_WIDTH, DISPLAY_NATIVE_HEIGHT, 0, 0);
    
    // Init frame buffer at SDRAM
    hal.setFrameBufferStartAddress((uint16_t*)SDRAM_BASE);
    
    //hal.setTouchSampleRate(3);
    
    hal.setFingerSize(1);
    
    // By default frame rate compensation is off.
    // Enable frame rate compensation to smooth out animations in case there is periodic slow frame rates.
    hal.setFrameRateCompensation(false);
    
    // This platform can handle simultaneous DMA and TFT accesses to SDRAM, so disable lock to increase performance.
    hal.lockDMAToFrontPorch(false);
    
    //Set MCU instrumentation and Load calculation
    mcuInstr.init();
    hal.setMCUInstrumentation(&mcuInstr);
    hal.enableMCULoadCalculation(true);
  }
  
  ////////////////////////////////////////////////////////////////////////////////
  //////////                         hw_init                        //////////////
  ////////////////////////////////////////////////////////////////////////////////
  void hw_init()
  {
    status_t status;
    int i;
#if 0
    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    
    /* Route Main clock to LCD. */
    CLOCK_AttachClk(kMCLK_to_LCD_CLK);
    
    /* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    
    // Touch Reset line
    CLOCK_EnableClock(kCLOCK_Gpio2);
    
    // LCD Clk
    CLOCK_SetClkDiv(kCLOCK_DivLcdClk, 1, true);
    
    // SDRAM ?
    CLOCK_EnableClock(kCLOCK_InputMux);
    
    BOARD_InitPins();
    BOARD_BootClock180M();
    BOARD_InitDebugConsole();
    BOARD_InitSDRAM();
    BOARD_InitSPIFI();    
    Board_LED_Init();
#endif
    for (i = 0; i < DISPLAY_NATIVE_WIDTH * DISPLAY_NATIVE_HEIGHT; i++)
    	lcd_framebuffer[i] = 0x0; // Black
    
    status = LCD_RK043_Init();
    if (status != kStatus_Success)
    {
      PRINTF("LCD init failed\n");
    }
    assert(status == kStatus_Success);
    
    /* Set the back light PWM. */
    LCD_Init_BL_PWM();
    
    GPIO::init();
  }
}
