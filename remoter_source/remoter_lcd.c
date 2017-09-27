/*
 * remoter_lcd.c
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#include "remoter_lcd.h"

/* Frame end flag. */
static volatile bool s_frameEndFlag;

/* FRAMEBUFFER_ADDR */
#if (defined(__CC_ARM) || defined(__GNUC__))
__attribute__((aligned(16)))
#elif defined(__ICCARM__)
#pragma data_alignment = 16
#else
#error Toolchain not support.
#endif
uint16_t *lcd_framebuffer = (uint16_t *) SDRAM_BASE_ADDR;
extern const unsigned char gImage_logo[45000];
void BackLight_InitPWM(void)
{
    sctimer_config_t config;
    sctimer_pwm_signal_param_t pwmParam;
    uint32_t event;

    CLOCK_AttachClk(kMCLK_to_SCT_CLK);

    CLOCK_SetClkDiv(kCLOCK_DivSctClk, 2, true);

    SCTIMER_GetDefaultConfig(&config);

    SCTIMER_Init(SCT0, &config);

    pwmParam.output = kSCTIMER_Out_5;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = 5;

    SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_CenterAlignedPwm, 1000U, CLOCK_GetFreq(kCLOCK_Sct), &event);
}

#if GUI_TYPE_EMWIN
void APP_LCD_IRQHandler(void)
{
    uint32_t intStatus = LCDC_GetEnabledInterruptsPendingStatus(APP_LCD);

    LCDC_ClearInterruptsStatus(APP_LCD, intStatus);

    if (intStatus & kLCDC_VerticalCompareInterrupt)
    {
        s_frameEndFlag = true;
    }
    __DSB();
}
#endif

status_t APP_LCDC_Init(void)
{
    /* Initialize the display. */
    lcdc_config_t lcdConfig;

    LCDC_GetDefaultConfig(&lcdConfig);

    lcdConfig.panelClock_Hz = LCD_PANEL_CLK;
    lcdConfig.ppl = LCD_PPL;
    lcdConfig.hsw = LCD_HSW;
    lcdConfig.hfp = LCD_HFP;
    lcdConfig.hbp = LCD_HBP;
    lcdConfig.lpp = LCD_LPP;
    lcdConfig.vsw = LCD_VSW;
    lcdConfig.vfp = LCD_VFP;
    lcdConfig.vbp = LCD_VBP;
    lcdConfig.polarityFlags = LCD_POL_FLAGS;
#if GUI_TYPE_EMWIN
    lcdConfig.upperPanelAddr = VRAM_ADDR;
    lcdConfig.swapRedBlue = false;
#elif GUI_TYPE_TOUCHGFX
    lcdConfig.upperPanelAddr = (uint32_t)lcd_framebuffer;
    lcdConfig.swapRedBlue = true;
    lcdConfig.dataFormat = kLCDC_WinCeMode;
#else
    lcdConfig.upperPanelAddr = (uint32_t)lcd_framebuffer;
#endif
    lcdConfig.bpp = kLCDC_16BPP565;
    lcdConfig.display = kLCDC_DisplayTFT;
//    lcdConfig.swapRedBlue = false;
//    lcdConfig.dataFormat = kLCDC_WinCeMode;

    LCDC_Init(APP_LCD, &lcdConfig, LCD_INPUT_CLK_FREQ);

#if GUI_TYPE_EMWIN
    /* Trigger interrupt at start of every vertical back porch. */
    LCDC_SetVerticalInterruptMode(APP_LCD, kLCDC_StartOfBackPorch);
    LCDC_EnableInterrupts(APP_LCD, kLCDC_VerticalCompareInterrupt);
    NVIC_EnableIRQ(APP_LCD_IRQn);
#endif
    LCDC_Start(APP_LCD);
    LCDC_PowerUp(APP_LCD);

    return kStatus_Success;
}

void GPIO_RS_Init(void)
{
	gpio_pin_config_t rs_config = {
	    kGPIO_DigitalOutput, 0,
	  };

	gpio_pin_config_t reset_config = {
		kGPIO_DigitalOutput, 0,
	};

	GPIO_PinInit(GPIO, LCM_WR_GPIO_PORT, LCM_WR_GPIO_PIN, &rs_config);
	GPIO_PinInit(GPIO, LCM_RESET_GPIO_PORT, LCM_RESET_GPIO_PIN, &reset_config);

	PRINTF("%s:init rs & reset pins \r\n", __func__);
}


void my_mdelay(int ms)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 10000 * ms; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

struct spi_lcd_cmd{
	uint8_t command;
	uint8_t len;
	int delay_ms;
}cmds[] = {
	/*Display setting*/
	{0x11, 0, 120},
	{0x36, 1, 0},
	{0x3a, 1, 0},
	{0x21, 0, 0},

	/*ST7789V Frame rate setting*/
	{0xb1, 3, 0},
	{0xb0, 2, 0},
	{0xb2, 5, 0},
	{0xb7, 1, 0},

	/*ST7789V Power setting*/
	{0xb8, 3, 0},
	{0xbb, 1, 0},
	{0xc0, 1, 0},
	{0xc2, 1, 0},
	{0xc3, 1, 0},
	{0xc4, 1, 0},
	{0xc6, 1, 0},
	{0xd0, 2, 0},
	{0xe8, 1, 0},
	{0xe9, 3, 0},

	/*ST7789V gamma setting*/
	{0xe0, 14, 0},
	{0xe1, 14, 0},
	{0x29, 0, 0},

};

uint8_t spi_lcd_datas[] = {
	0x00,                       //cmd:0x36
	0x55,						//cmd:0x3a

	0x40, 0x18, 0x1a,           //cmd:0xb1
	0x11, 0xF0,                 //cmd:0xb0
	0x05, 0x05, 0x00, 0x33, 0x33,//cmd:0xb2
	0x35,                       //cmd:0xb7

	0x2f, 0x2b, 0x2f,           //cmd:0xb8
	0x20,                       //cmd:0xbb
	0x2c,                       //cmd:0xc0
	0x01,                       //cmd:0xc2
	0x0b,                       //cmd:0xc3
	0x20,                       //cmd:0xc4
	0x11,                       //cmd:0xc6
	0xa4, 0xa1,                 //cmd:0xd0
	0x03,                       //cmd:0xe8
	0x0d, 0x12, 0x00,           //cmd:0xe9

	0xd0, 0x06, 0x0b, 0x0a, 0x09, 0x05, 0x2e, 0x43, 0x44, 0x09, 0x16, 0x15, 0x23, 0x27,//cmd:0xe0
	0xd0, 0x06, 0x0b, 0x09, 0x08, 0x06, 0x2e, 0x44, 0x44, 0x3a, 0x15, 0x15, 0x23, 0x26,//cmd:0xe1
};


uint8_t LCD_SPI_Init(void)
{
	spi_master_config_t masterConfig;
	uint32_t sourceClock = 12000000;

	/* attach 12 MHz clock to SPI? */
	CLOCK_AttachClk(LCM_SPI_FLEXCOMM);

	NVIC_SetPriority(LCM_SPI_IRQ, SPI_NVIC_PRIO + 1);

	SPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = 500000;
	masterConfig.sselNum = LCD_SPI_SSEL;

	status_t status = SPI_MasterInit(LCM_SPI_INDEX, &masterConfig, sourceClock);
	if (status != kStatus_Success)
	{
		PRINTF("SPI master: error during initialization. \r\n");
		return -1;
	}

	return 0;
}

uint8_t SPI_Writedata(uint8_t inData, uint8_t *outData)
{
	spi_transfer_t xfer;

	xfer.txData = &inData;
	xfer.dataSize = 1;
	xfer.rxData = outData;
	xfer.configFlags |= kSPI_FrameAssert;

	status_t status = SPI_MasterTransferBlocking(LCM_SPI_INDEX, &xfer);
	 if (status == kStatus_Success)
	{
		//PRINTF("SPI master transfer completed successfully.\r\n");
		return 0;
	}
	else
	{
		//PRINTF("SPI master transfer completed with error.\r\n");
		return -1;
	}
}

uint8_t SPI_WriteCmd(uint8_t inData, uint8_t *outData)
{
	return SPI_Writedata(inData, outData);
}

void LCD_IC_Init()
{
	uint8_t ret;
	uint8_t recvData;

	ret = LCD_SPI_Init();
	if (ret) {
		PRINTF("SPI_Init error.\r\n");
		//return;
	}

	/*reset lcd*/
	GPIO_WritePinOutput(GPIO, LCM_RESET_GPIO_PORT, LCM_RESET_GPIO_PIN, 1);
	my_mdelay(20);
	GPIO_WritePinOutput(GPIO, LCM_RESET_GPIO_PORT, LCM_RESET_GPIO_PIN, 0);
	my_mdelay(20);
	GPIO_WritePinOutput(GPIO, LCM_RESET_GPIO_PORT, LCM_RESET_GPIO_PIN, 1);
	my_mdelay(120);

	PRINTF("%s: start to download lcd ic init code...\r\n", __func__);
	int i, j;
	uint8_t recvCmds[ARRAY_SIZE(cmds)] = {0};
	int n = 0;//to record the position of array spi_lcd_datas

	for(i = 0; i < ARRAY_SIZE(cmds); i++)
	{
		/*set RS to low for cmd*/
		GPIO_WritePinOutput(GPIO, LCM_WR_GPIO_PORT, LCM_WR_GPIO_PIN, 0);
		SPI_WriteCmd(cmds[i].command, &recvCmds[i]);
		for(j = 0; j < cmds[i].len; j++)
		{
			/*set RS to high for data*/
			GPIO_WritePinOutput(GPIO, LCM_WR_GPIO_PORT, LCM_WR_GPIO_PIN, 1);
			SPI_Writedata(spi_lcd_datas[n++], &recvData);
		}

		if(cmds[i].delay_ms)
		{
			my_mdelay(cmds[i].delay_ms);
		}
	}

	PRINTF("%s: finish download lcd ic init code...\r\n", __func__);
}

void LCD_ST7789V_Init(void)
{
    /* before LCD_SPI_Init(), should init the RS & reset pin*/
    GPIO_RS_Init();
    /*download the init code for lcd*/
    LCD_IC_Init();
}

int LCM_Init(void)
{
	status_t status = kStatus_Success;
	int i = 0,count = 0;
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 0
	int size = sizeof(gImage_logo) / sizeof((gImage_logo[0]));
#endif
    /* Route Main clock to LCD. */
    CLOCK_AttachClk(kMCLK_to_LCD_CLK);
    /* LCD Clk */
    CLOCK_EnableClock(LCM_WR_GPIO_CLOCK);
	CLOCK_EnableClock(LCM_RESET_GPIO_CLOCK);
	CLOCK_SetClkDiv(kCLOCK_DivLcdClk, 1, true);
    /* SDRAM ?? */
    CLOCK_EnableClock(kCLOCK_InputMux);

    /*for (i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    	lcd_framebuffer[i] = 0x0; // Black*/
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
    for (i = 0; i < LCD_HEIGHT; i++){
  	  for(int j = 0; j < LCD_WIDTH; j++){
  		  if(i >= LCD_LOGO_START_Y && i < LCD_LOGO_START_Y + LCD_LOGO_HEIGHT){
  			  if(j >= LCD_LOGO_START_X && j < LCD_LOGO_START_X + LCD_LOGO_WIDTH){
               lcd_framebuffer[i * LCD_WIDTH + j]  = 0xFFFF - 0xFFFF/(((j - LCD_LOGO_START_X)/10 + 1) *((i - LCD_LOGO_START_Y)/10 + 1));
  			  }else{
  				lcd_framebuffer[i * LCD_WIDTH + j] = 0x0; // Black
  			  }
  		  }else{
  			lcd_framebuffer[i * LCD_WIDTH + j] = 0x0; // Black
  		  }
  	  }
    }
#else
    for (i = 0; i < LCD_HEIGHT; i++){
  	  for(int j = 0; j < LCD_WIDTH; j++){
  		  if(i >= LCD_LOGO_START_Y && i < LCD_LOGO_START_Y + LCD_LOGO_HEIGHT){
  			  if(j >= LCD_LOGO_START_X && j < LCD_LOGO_START_X + LCD_LOGO_WIDTH){
                    if(count < size){
                    	lcd_framebuffer[i * LCD_WIDTH + j]  = ((((gImage_logo[count + 1]&0x00ff)<<8) | gImage_logo[count])) & 0xFFFF;
                        count += 2;
                    }
  			  }else{
  				lcd_framebuffer[i * LCD_WIDTH + j] = 0x0; // Black
  			  }
  		  }else{
  			lcd_framebuffer[i * LCD_WIDTH + j] = 0x0; // Black
  		  }
  	  }
    }
#endif

#if LCD_IC_ST7789V
	LCD_ST7789V_Init();
#endif

    /* Initialize LCD controller */
    status = APP_LCDC_Init();
    if (status != kStatus_Success)
    {
        PRINTF("LCD init failed\n");
    }
 //   assert(status == kStatus_Success);

    return (status == kStatus_Success);
}
