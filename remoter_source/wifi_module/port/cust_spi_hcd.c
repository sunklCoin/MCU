//------------------------------------------------------------------------------
// Copyright (c) Qualcomm Atheros, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to
// the limitations in the disclaimer below) provided that the following conditions are met:
//
// � Redistributions of source code must retain the above copyright notice, this list of conditions and the
//   following disclaimer.
// � Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//   following disclaimer in the documentation and/or other materials provided with the distribution.
// � Neither the name of nor the names of its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. THIS SOFTWARE IS
// PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------
//==============================================================================
// Author(s): ="Atheros"
//==============================================================================
#include <a_config.h>
#include <a_types.h>
#include <a_osapi.h>
#include <driver_cxt.h>
#include <common_api.h>
#include <custom_wlan_api.h>
#include <hif_internal.h>
#include "spi_hcd_if.h"
#include <targaddrs.h>
//by colin
#if MQX_RTOS || MQX_LITE
#include <io_gpio.h>
#include <bsp.h>
#endif
#include "AR6002/hw2.0/hw/mbox_host_reg.h"
#include <atheros_wifi.h>
#include <stdlib.h> 
#include "atheros_wifi_api.h"

/**************************************/
#include "fsl_spi.h"
#include "fsl_spi_freertos.h"
#include "fsl_gpio.h"
#include "fsl_gint.h"

#define IS_DEMO_BOARD 0
#if IS_DEMO_BOARD
#define WIFI_SPI_MASTER SPI9
#define WIFI_SPI_MASTER_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm9)
#define WIFI_SPI_SSEL 0

#define GPIO_WIFI_RESET_PORT 0U
#define GPIO_WIFI_RESET_PIN 17U
#define GPIO_WIFI_HM0_PORT 0U
#define GPIO_WIFI_HM0_PIN 30U

#define WIFI_GINT0_PORT kGINT_Port0
#define GPIO_WIFI_IRQ_PIN 16U
#define WIFI_GINT0_POL_MASK ~(1U << GPIO_WIFI_IRQ_PIN)
#define WIFI_GINT0_ENA_MASK (1U << GPIO_WIFI_IRQ_PIN)
#else
#define WIFI_SPI_MASTER SPI3
#define WIFI_SPI_MASTER_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm3)
#define WIFI_SPI_SSEL 3

#define GPIO_WIFI_RESET_PORT 0U
#define GPIO_WIFI_RESET_PIN 17U
#define GPIO_WIFI_HM0_PORT 0U
#define GPIO_WIFI_HM0_PIN 30U

#define WIFI_GINT0_PORT kGINT_Port0
//#define GPIO_WIFI_IRQ_PIN 16U
#define GPIO_WIFI_IRQ_PIN 29U
#define WIFI_GINT0_POL_MASK ~(1U << GPIO_WIFI_IRQ_PIN)
#define WIFI_GINT0_ENA_MASK (1U << GPIO_WIFI_IRQ_PIN)
#endif
/**************************************/

#define POWER_UP_DELAY (1)

#define HW_SPI_CAPS (HW_SPI_FRAME_WIDTH_8| \
					 HW_SPI_NO_DMA | \
					 HW_SPI_INT_EDGE_DETECT)      

static spi_master_handle_t g_m_handle;
static void SPI_Write_Callback(SPI_Type *base, spi_master_handle_t *masterHandle, status_t status, void *userData);
static void SPI_Read_Callback(SPI_Type *base, spi_master_handle_t *masterHandle, status_t status, void *userData);
static void mDelay(uint16_t ms);
static void Pull_Reset(uint8_t output);
static void SPI_IRQ_Init(void);

static void SPI_IRQ_Init(void)
{
	/* Initialize GINT0 */
	GINT_Init(GINT0);
	/* Setup GINT0 for edge trigger, "OR" mode */
	GINT_SetCtrl(GINT0, kGINT_CombineOr, kGINT_TrigEdge, Custom_HW_InterruptHandler);
	/* Select pins & polarity for GINT0 */
	GINT_ConfigPins(GINT0, WIFI_GINT0_PORT, WIFI_GINT0_POL_MASK, WIFI_GINT0_ENA_MASK);
	/* Enable callbacks for GINT0 */
	GINT_EnableCallback(GINT0);
}

static void mDelay(uint16_t ms)
{
	int i, j;
	for (i = 0; i < ms; i++) {
		for (j = 0; j < 16500; j++) {
			  __asm("NOP"); /* delay */
		}
	}
}
static void Pull_Reset(uint8_t output)
{
	GPIO_WritePinOutput(GPIO, GPIO_WIFI_RESET_PORT, GPIO_WIFI_RESET_PIN, output);
}

QOSAL_VOID 
Custom_Hcd_EnableDisableSPIIRQ(QOSAL_VOID *pCxt, QOSAL_BOOL enable)
{
//	if(enable == A_TRUE){
//		ioctl(GET_DRIVER_CXT(pCxt)->customhcdcxt.int_cxt, GPIO_IOCTL_ENABLE_IRQ, NULL);
//	}else{
//		ioctl(GET_DRIVER_CXT(pCxt)->customhcdcxt.int_cxt, GPIO_IOCTL_DISABLE_IRQ, NULL);  
//	}
//	if (enable == A_TRUE){
//		SPI_EnableInterrupts(EXAMPLE_SPI_MASTER, kSPI_TxLvlIrq | kSPI_RxLvlIrq);
//	} else {
//		SPI_DisableInterrupts(EXAMPLE_SPI_MASTER, kSPI_RxLvlIrq | kSPI_TxLvlIrq);
//	}
}


/*****************************************************************************/
/* Custom_Bus_InOutBuffer - This is the platform specific solution to 
 *  transfer a buffer on the SPI bus.  This solution is always synchronous
 *  regardless of sync param. The function will use the MQX fread and fwrite
 *  as appropriate.
 *      QOSAL_VOID * pCxt - the driver context.
 *      QOSAL_UINT8 *pBuffer - The buffer to transfer.
 *      QOSAL_UINT16 length - the length of the transfer in bytes.
 *      QOSAL_UINT8 doRead - 1 if operation is a read else 0.
 *      QOSAL_BOOL sync - TRUE is synchronous transfer is required else FALSE.
 *****************************************************************************/
A_STATUS 
Custom_Bus_InOutBuffer(QOSAL_VOID *pCxt,
                                    QOSAL_UINT8 *pBuffer,
									QOSAL_UINT16 length, 									
									QOSAL_UINT8 doRead,
                                    QOSAL_BOOL sync)
{
	A_STATUS status = A_OK;
	int i;
	spi_transfer_t xfer = {0};
    
    UNUSED_ARGUMENT(sync);
    /* this function takes advantage of the SPI turbo mode which does not toggle the chip select
     * during the transfer.  Rather the chip select is asserted at the beginning of the transfer
     * and de-asserted at the end of the entire transfer via fflush(). */
    if (doRead) {
		xfer.rxData = (uint8_t *)pBuffer;
		xfer.dataSize = length;
		xfer.txData = NULL;
		xfer.configFlags |= kSPI_FrameAssert;
		SPI_MasterTransferBlocking(WIFI_SPI_MASTER, &xfer);
    } else {
		/* Send to slave */
		xfer.txData = (uint8_t *)pBuffer;
		xfer.rxData = NULL;
		xfer.dataSize = length;
		xfer.configFlags |= kSPI_FrameAssert;
		SPI_MasterTransferBlocking(WIFI_SPI_MASTER, &xfer);
    }

    mDelay(2);
//    printf("doRead = %d, length = %d\r\n", doRead, length);
//    printf("doRead = %d\r\n", doRead);
//    for (i = 0; i < length; i++) {
//    	printf("%s[%d]: 0x%02x\r\n", doRead ? "rx" : "tx", i, pBuffer[i]);
//    }

    return status;
}				


/*****************************************************************************/
/* Custom_Bus_Start_Transfer - This function is called by common layer prior
 *  to starting a new bus transfer. This solution merely sets up the SPI 
 *  mode as a precaution.
 *      QOSAL_VOID * pCxt - the driver context.     
 *      QOSAL_BOOL sync - TRUE is synchronous transfer is required else FALSE.
 *****************************************************************************/
A_STATUS 
Custom_Bus_StartTransfer(QOSAL_VOID *pCxt, QOSAL_BOOL sync)
{
    QOSAL_UINT32 param;
    A_STATUS status = A_OK;

    UNUSED_ARGUMENT(sync);

    return status;
}


/*****************************************************************************/
/* Custom_Bus_Complete_Transfer - This function is called by common layer prior
 *  to completing a bus transfer. This solution calls fflush to de-assert 
 *  the chipselect.
 *      QOSAL_VOID * pCxt - the driver context.     
 *      QOSAL_BOOL sync - TRUE is synchronous transfer is required else FALSE.
 *****************************************************************************/
A_STATUS 
Custom_Bus_CompleteTransfer(QOSAL_VOID *pCxt, QOSAL_BOOL sync)
{
    UNUSED_ARGUMENT(sync);
//    fflush(GET_DRIVER_CXT(pCxt)->customhcdcxt.spi_cxt);
    return A_OK;
}

static void SPI_Write_Callback(SPI_Type *base, spi_master_handle_t *masterHandle, status_t status, void *userData)
{
	printf("SPI_Write_Callback\r\n");
}

static void SPI_Read_Callback(SPI_Type *base, spi_master_handle_t *masterHandle, status_t status, void *userData)
{
	printf("SPI_Read_Callback\r\n");
}

/*****************************************************************************/
/* Custom_Bus_InOut_Token - This is the platform specific solution to 
 *  transfer 4 or less bytes in both directions. The transfer must be  
 *  synchronous. This solution uses the MQX spi ioctl to complete the request.
 *      QOSAL_VOID * pCxt - the driver context.
 *      QOSAL_UINT32 OutToken - the out going data.
 *      QOSAL_UINT8 DataSize - the length in bytes of the transfer.
 *      QOSAL_UINT32 *pInToken - A Buffer to hold the incoming bytes. 
 *****************************************************************************/
A_STATUS 
Custom_Bus_InOutToken(QOSAL_VOID *pCxt,
                           QOSAL_UINT32        OutToken,
                           QOSAL_UINT8         DataSize,
                           QOSAL_UINT32    *pInToken) 
{   
//    SPI_READ_WRITE_STRUCT  spi_buf;
	A_STATUS status = A_OK;
	spi_transfer_t xfer = {0};
	int i;
	uint8_t *destBuf;
	uint8_t *c = &OutToken;

	destBuf = (uint8_t *) malloc(sizeof(uint8_t) * DataSize);
	memset(destBuf, 0, DataSize);

	/* Send to slave */
	xfer.txData = &OutToken;
	xfer.rxData = destBuf;
	xfer.dataSize = DataSize;
//	  SPI_MasterTransferCreateHandle(WIFI_SPI_MASTER, &g_m_handle, SPI_Write_Callback, NULL);
//	  SPI_MasterTransferNonBlocking(WIFI_SPI_MASTER, &g_m_handle, &xfer);
	xfer.configFlags |= kSPI_FrameAssert;
	SPI_MasterTransferBlocking(WIFI_SPI_MASTER, &xfer);

	*pInToken = 0;
	for (i = 0; i < DataSize; i++) {
	  *pInToken |= ((destBuf[i] & 0xff) << (i*8));
	}
//	  printf("OutToken: 0x%08x\r\n", OutToken);
//	  printf("*pInToken = 0x%08x\r\n", *pInToken);
	free(destBuf);

    return status;                                                                        
}

A_STATUS 
Custom_HW_Init(QOSAL_VOID *pCxt)
{
    GPIO_PIN_STRUCT 	pins[2];
    A_CUSTOM_DRIVER_CONTEXT *pCustCxt = GET_DRIVER_CXT(pCxt);
    QOSAL_UINT32 baudrate, endian, input;
    ATHEROS_PARAM_WIFI_STRUCT *pParam;
    A_DRIVER_CONTEXT *pDCxt = GET_DRIVER_COMMON(pCxt);
    spi_master_config_t masterConfig = {0};
    uint32_t sourceClock = 0U;
    gpio_pin_config_t gpio_config = {
		kGPIO_DigitalOutput, 0,
	};

#if IS_DEMO_BOARD
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM9);
#else
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);
#endif
    CLOCK_EnableClock(kCLOCK_Gpio0);
	GPIO_PinInit(GPIO, GPIO_WIFI_RESET_PORT, GPIO_WIFI_RESET_PIN, &gpio_config);
	GPIO_PinInit(GPIO, GPIO_WIFI_HM0_PORT, GPIO_WIFI_HM0_PIN, &gpio_config);

	SPI_IRQ_Init();

    /* Init SPI master */
	/*
	 * masterConfig->enableLoopback = false;
	 * masterConfig->enableMaster = true;
	 * masterConfig->polarity = kSPI_ClockPolarityActiveHigh;
	 * masterConfig->phase = kSPI_ClockPhaseFirstEdge;
	 * masterConfig->direction = kSPI_MsbFirst;
	 * masterConfig->baudRate_Bps = 500000U;
	 */
	SPI_MasterGetDefaultConfig(&masterConfig);
//	masterConfig.polarity = 1;
//	masterConfig.phase = 1;
	sourceClock = WIFI_SPI_MASTER_CLK_FREQ;
	masterConfig.sselNum = (spi_ssel_t)WIFI_SPI_SSEL;
	SPI_MasterInit(WIFI_SPI_MASTER, &masterConfig, sourceClock);

	baudrate = masterConfig.baudRate_Bps;
	printf("baudrate = %d\r\n", baudrate);

   // Reset wifi
	Pull_Reset(1);
	mDelay(15);
	Pull_Reset(0);
	mDelay(15);
	Pull_Reset(1);

	 /* IT is necessary for the custom code to populate the following parameters
	 * so that the common code knows what kind of hardware it is working with. */
	pDCxt->spi_hcd.OperationalClock = baudrate;
	pDCxt->spi_hcd.PowerUpDelay = POWER_UP_DELAY;
	pDCxt->spi_hcd.SpiHWCapabilitiesFlags = HW_SPI_CAPS;
	pDCxt->spi_hcd.MiscFlags |= MISC_FLAG_RESET_SPI_IF_SHUTDOWN;

	return A_OK;
}

A_STATUS 
Custom_HW_DeInit(QOSAL_VOID *pCxt)
{
//#if WLAN_CONFIG_ENABLE_CHIP_PWD_GPIO
//	/* NOTE: if the gpio fails to retain its state after fclose
//	 * then the wifi device will not remain in the off State.
//	 */	
//    fclose(GET_DRIVER_CXT(pCxt)->customhcdcxt.pwd_cxt);
//    GET_DRIVER_CXT(pCxt)->customhcdcxt.pwd_cxt = NULL;
//#endif       
//	/* clean up resources initialized in Probe() */
//    fclose(GET_DRIVER_CXT(pCxt)->customhcdcxt.spi_cxt);
//    GET_DRIVER_CXT(pCxt)->customhcdcxt.spi_cxt = NULL;
//    fclose(GET_DRIVER_CXT(pCxt)->customhcdcxt.int_cxt);
//    GET_DRIVER_CXT(pCxt)->customhcdcxt.int_cxt = NULL;
//    
//#if BSPCFG_ENABLE_ADC_SENSOR
//    GET_DRIVER_CXT(pCxt)->adc_cxt = NULL;
//#endif     
    
    return A_OK;
}


void Custom_HW_InterruptHandler(CUSTOM_HW_INTR_CB HcdCallback, void *pContext) 
{  
        void *pHcdContext ;
	HcdCallback = Hcd_Irq; 
	pHcdContext = pContext;
        (*HcdCallback)(pHcdContext);       
}

QOSAL_VOID 
Custom_HW_PowerUpDown(QOSAL_VOID *pCxt, QOSAL_UINT32 powerUp)
{   
	Pull_Reset(powerUp);
//    QOSAL_UINT32 cmd = (powerUp)?  GPIO_IOCTL_WRITE_LOG1: GPIO_IOCTL_WRITE_LOG0;
//    MQX_FILE_PTR                f=NULL;    
//    if (IO_OK != ioctl (GET_DRIVER_CXT(pCxt)->customhcdcxt.pwd_cxt, cmd, NULL))
//	{
//		A_ASSERT(0);
//	}
//    
//    {
//      cmd = (powerUp)?  GPIO_PIN_STATUS_0: GPIO_PIN_STATUS_1;
//      const uint_32 output_set[] = {
//          BSP_ATHEROS_WIFI_GPIO_FET_PIN | cmd,
//          GPIO_LIST_END
//      };

//      /* Open and set port TC as output to drive LEDs (LED10 - LED13) */
//      f = fopen("gpio:write", (char_ptr) &output_set);
//      cmd = (powerUp)?  GPIO_IOCTL_WRITE_LOG0: GPIO_IOCTL_WRITE_LOG1;

//     if (f)
//          ioctl(f, cmd, NULL);              
//    
//      fclose(f);      
//      f=NULL;
//      
//      cmd = (powerUp)?  GPIO_PIN_STATUS_0: GPIO_PIN_STATUS_1;
//      const uint_32 output1_set[] = {
//          BSP_LED1 | cmd,
//          GPIO_LIST_END
//      };  
//      
//      f = fopen("gpio:write", (char_ptr) &output1_set);
//      cmd = (powerUp)?  GPIO_IOCTL_WRITE_LOG0: GPIO_IOCTL_WRITE_LOG1;

//       if (f)
//            ioctl(f, cmd, NULL);              

//      fclose(f);      
//      f=NULL;
//    }
#if 0
    {
      if(!powerUp)
      {
          //I2C
          GPIOE_PDOR |= 0x3;
          //A1 input
          GPIO_PDDR_REG(PTA_BASE_PTR) &= 0xfffffffd;
          //B18 output, high
          GPIO_PDDR_REG(PTB_BASE_PTR) |= 0x40000;
          GPIOB_PDOR |= 0x40000;
          //B2,B17
          PORT_PCR_REG(PORTB_BASE_PTR, 2) = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK;
          PORT_PCR_REG(PORTB_BASE_PTR, 17) = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK;
          GPIOB_PDDR |= 0x20004;
          GPIOB_PDOR &= 0xFFFDFFFB;
          
          //B3,B16
          PORT_PCR_REG(PORTB_BASE_PTR, 3) = PORT_PCR_MUX(0x5) | PORT_PCR_PE_MASK;
          PORT_PCR_REG(PORTB_BASE_PTR, 16) = PORT_PCR_MUX(0x5) | PORT_PCR_PE_MASK;
          //GPIOB_PDDR &= 0xFFFEFFF7;
      }else
      {
          //I2C
          GPIOE_PDOR &= 0xffffffc;
          //A1 input
          GPIO_PDDR_REG(PTA_BASE_PTR) |= 0x2;
          //B18 output, high
          GPIO_PDDR_REG(PTB_BASE_PTR) &= 0xfffbffff;
          GPIOB_PDOR &= 0xfffbffff;
          //B2,B17  UART0
          PORT_PCR_REG(PORTB_BASE_PTR, 2) = PORT_PCR_MUX(0x3) | PORT_PCR_PE_MASK;
          PORT_PCR_REG(PORTB_BASE_PTR, 17) = PORT_PCR_MUX(0x3) | PORT_PCR_PE_MASK;
          GPIOB_PDDR &= ~(0x20004);
          GPIOB_PDOR |= ~(0xFFFDFFFB);
          
          //B3,B16 UART0
          PORT_PCR_REG(PORTB_BASE_PTR, 3) = PORT_PCR_MUX(0x3) | PORT_PCR_PE_MASK;
          PORT_PCR_REG(PORTB_BASE_PTR, 16) = PORT_PCR_MUX(0x3) | PORT_PCR_PE_MASK;
          //GPIOB_PDDR &= 0xFFFEFFF7;
      }
    }
#endif     
}

#if 0   //TBD
QOSAL_VOID Custom_HW_RegisterInterruptHandler(CUSTOM_HW_INTR_CB *callback, QOSAL_VOID *pContext);
QOSAL_VOID Custom_HW_RegisterSuspendHandler(CUSTOM_HW_SUSPEND_CB *suspendCallback, QOSAL_VOID *pSuspContext);
QOSAL_VOID Custom_HW_RegisterResumeHandler(CUSTOM_HW_RESUME_CB *resumeCallback, QOSAL_VOID *pSuspContext);

QOSAL_VOID Custom_HW_RegisterInterruptHandler(CUSTOM_HW_INTR_CB *callback, QOSAL_VOID *pContext)
{
  //TBD
}

QOSAL_VOID Custom_HW_RegisterSuspendHandler(CUSTOM_HW_SUSPEND_CB *suspendCallback, QOSAL_VOID *pSuspContext) 
{
  //TBD
}

QOSAL_VOID Custom_HW_RegisterResumeHandler(CUSTOM_HW_RESUME_CB *resumeCallback, QOSAL_VOID *pSuspContext)
{
  //TBD
}

#endif  //#if 0 TBD
