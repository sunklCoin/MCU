/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: LPC54608J512
package_id: LPC54608J512ET180
mcu_data: ksdk2_0
processor_version: 2.0.2
board: LPCXpresso54608
pin_labels:
- {pin_num: K12, pin_signal: PIO1_1/FC3_RXD_SDA_MOSI/CTIMER0_CAP3/SCT0_GPI5/USB1_OVERCURRENTN, label: WiFi SPI MOSI pin, identifier: WIFI_SPI_MOSI}
- {pin_num: A13, pin_signal: PIO3_3/LCD_VD(17)/FC9_TXD_SCL_MISO, label: LCD WR pin, identifier: LCD_WR}
- {pin_num: C3, pin_signal: PIO2_2/ENET_CRS/FC3_SSEL3/SCT0_OUT6/CTIMER1_MAT1, label: Zigbee reset pin, identifier: ZB_RST}
- {pin_num: E3, pin_signal: PIO3_14/SCT0_OUT4/FC9_RTS_SCL_SSEL1/CTIMER3_MAT1/TRACEDATA(2), label: BLE wake up pin, identifier: BT_WAKEUP}
- {pin_num: A1, pin_signal: PIO0_1/CAN1_TD/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_GPI1/PDM0_DATA, label: Power key, identifier: PWR_KEY}
- {pin_num: D6, pin_signal: PIO0_0/CAN1_RD/FC3_SCK/CTIMER0_MAT0/SCT0_GPI0/PDM0_CLK, label: IR PMW, identifier: ISP_FC3_SCK}
- {pin_num: D2, pin_signal: PIO3_15/FC8_SCK/SD_WR_PRT, label: BLE reserved, identifier: BT_REV}
- {pin_num: P1, pin_signal: PIO2_10/ENET_RX_ER/SD_CARD_DET_N, label: Zigbee uart mode select, identifier: ZB_UART_MODE}
- {pin_num: F3, pin_signal: PIO2_6/ENET_TX_CLK/SD_D(0)/FC1_RTS_SCL_SSEL1/CTIMER0_CAP0, label: Zigbee uart rts, identifier: ZB_UART_RTS}
- {pin_num: B1, pin_signal: PIO2_3/ENET_TXD2/SD_CLK/FC1_RXD_SDA_MOSI/CTIMER2_MAT0, label: Zigbee uart rx, identifier: ZB_UART_RX}
- {pin_num: D3, pin_signal: PIO2_4/ENET_TXD3/SD_CMD/FC1_TXD_SCL_MISO/CTIMER2_MAT1, label: Zigbee uart tx, identifier: ZB_UART_TX}
- {pin_num: C1, pin_signal: PIO2_5/ENET_TX_ER/SD_POW_EN/FC1_CTS_SDA_SSEL0/CTIMER1_MAT2, label: Zigbee uart cts, identifier: ZB_UART_CTS}
- {pin_num: N14, pin_signal: PIO1_24/FC2_RXD_SDA_MOSI/SCT0_OUT1/FC3_SSEL3/EMC_A(12), label: WiFi SPI CS pin, identifier: WIFI_SPI_CS}
- {pin_num: B12, pin_signal: PIO0_22/FC6_TXD_SCL_MISO_WS/UTICK_CAP1/CTIMER3_CAP3/SCT0_OUT3/USB0_VBUS, label: Keyboard int pin, identifier: KB_INT}
- {pin_num: B13, pin_signal: PIO0_29/FC0_RXD_SDA_MOSI/CTIMER2_MAT3/SCT0_OUT8/TRACEDATA(2), label: WiFi int pin, identifier: WIFI_INT}
- {pin_num: A2, pin_signal: PIO0_30/FC0_TXD_SCL_MISO/CTIMER0_MAT0/SCT0_OUT9/TRACEDATA(1), label: WiFi mode select pin, identifier: WIFI_HM0}
- {pin_num: P2, pin_signal: PIO0_10/FC6_SCK/CTIMER2_CAP2/CTIMER2_MAT0/FC1_TXD_SCL_MISO/SWO/ADC0_0, label: Battery Temperature detect, identifier: SWO_TRGT}
- {pin_num: E14, pin_signal: PIO0_17/FC4_SSEL2/SD_CARD_DET_N/SCT0_GPI7/SCT0_OUT0/EMC_OEN/ENET_TXD1, label: WiFi chip power down pin, identifier: WIFI_CHIP_PWD}
- {pin_num: C4, pin_signal: PIO4_16/ENET_MDIO/CTIMER4_MAT3/FC9_TXD_SCL_MISO, label: LCD reset pin, identifier: LCD_RST}
- {pin_num: H11, pin_signal: PIO2_26/LCD_VD(8)/FC3_SCK/CTIMER2_CAP1, label: WiFi SPI CLK pin, identifier: WIFI_SPI_CLK}
- {pin_num: P12, pin_signal: PIO2_19/LCD_VD(1)/FC3_TXD_SCL_MISO/FC7_RXD_SDA_MOSI_DATA/CTIMER3_MAT1, label: WiFi SPI MISO pin, identifier: WIFI_SPI_MISO}
- {pin_num: B2, pin_signal: PIO3_11/MCLK/FC0_SCK/FC1_SCK/TRACEDATA(3), label: Keyboard reset pin, identifier: KB_RST}
- {pin_num: E1, pin_signal: PIO3_16/FC8_RXD_SDA_MOSI/SD_D(4), label: BLE uart rx, identifier: BT_UART_RX}
- {pin_num: K1, pin_signal: PIO3_17/FC8_TXD_SCL_MISO/SD_D(5), label: BLE uart tx, identifier: BT_UART_TX}
- {pin_num: P11, pin_signal: PIO1_22/FC8_RTS_SCL_SSEL1/SD_CMD/CTIMER2_MAT3/SCT0_GPI5/FC4_SSEL3/EMC_CKE(1), label: 'U28[F3]/P1_22-EMC_CKE1', identifier: EMC_CKE1}
- {pin_num: M4, pin_signal: PIO0_16/FC4_TXD_SCL_MISO/CLKOUT/CTIMER1_CAP0/EMC_CSN(0)/ENET_TXD0/ADC0_4, label: Charger enable pin, identifier: CHG_EN}
- {pin_num: M5, pin_signal: PIO0_31/FC0_CTS_SDA_SSEL0/SD_D(2)/CTIMER0_MAT1/SCT0_OUT3/TRACEDATA(0)/ADC0_5, label: BLE int pin, identifier: BT_INT}
- {pin_num: N3, pin_signal: PIO1_0/FC0_RTS_SCL_SSEL1/SD_D(3)/CTIMER0_CAP2/SCT0_GPI4/TRACECLK/ADC0_6, label: Charger detect pin, identifier: CHG_DET}
- {pin_num: N12, pin_signal: PIO1_17/ENET_MDIO/FC8_RXD_SDA_MOSI/SCT0_OUT4/CAN1_TD/EMC_BLSN(0), label: Touchpanel int pin, identifier: TP_INT}
- {pin_num: D1, pin_signal: PIO1_18/FC8_TXD_SCL_MISO/SCT0_OUT5/CAN1_RD/EMC_BLSN(1), label: Fuel Gauge int pin, identifier: FG_INT}
- {pin_num: H14, pin_signal: PIO2_27/LCD_VD(9)/FC9_SCK/FC3_SSEL2, label: Touchpanel reset pin, identifier: TP_RST}
- {pin_num: L2, pin_signal: PIO3_12/SCT0_OUT8/CTIMER3_CAP0/CLKOUT/EMC_CLK(1)/TRACECLK, label: WiFi wake up pin, identifier: WIFI_WAKEUP}
- {pin_num: M6, pin_signal: PIO3_18/FC8_CTS_SDA_SSEL0/SD_D(6)/CTIMER4_MAT0/CAN0_TD/SCT0_OUT5, label: BLE reserved, identifier: BT_REV1}
- {pin_num: J3, pin_signal: PIO3_19/FC8_RTS_SCL_SSEL1/SD_D(7)/CTIMER4_MAT1/CAN0_RD/SCT0_OUT6, label: BLE STA pin, identifier: BT_STA}
- {pin_num: N2, pin_signal: PIO3_20/FC9_SCK/SD_CARD_INT_N/CLKOUT/SCT0_OUT7, label: LCD SPI clock pin, identifier: LCD_SPI_CLK}
- {pin_num: P5, pin_signal: PIO3_21/FC9_RXD_SDA_MOSI/SD_BACKEND_PWR/CTIMER4_MAT3/UTICK_CAP2/ADC0_9, label: LCD SPI MOSI pin, identifier: LCD_SPI_MOSI}
- {pin_num: N5, pin_signal: PIO3_22/FC9_TXD_SCL_MISO/ADC0_10, label: LCD SPI MISO pin, identifier: LCD_SPI_MISO}
- {pin_num: K5, pin_signal: PIO3_26/SCT0_OUT0/FC4_RXD_SDA_MOSI/EMC_A(15), label: BLE STA1 pin, identifier: BT_STA1}
- {pin_num: P14, pin_signal: PIO3_27/SCT0_OUT1/FC4_TXD_SCL_MISO/EMC_A(16), label: BLE reset pin, identifier: BT_RST}
- {pin_num: L13, pin_signal: PIO3_29/SCT0_OUT3/FC4_RTS_SCL_SSEL1/EMC_A(18), label: BLE reset1 pin, identifier: BT_RST1}
- {pin_num: K13, pin_signal: PIO3_30/FC9_CTS_SDA_SSEL0/SCT0_OUT4/FC4_SSEL2/EMC_A(19), label: LCD SPI CS pin, identifier: LCD_SPI_CS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitSDRAMPins();
    BOARD_InitSPIFIPins();
    BOARD_InitUSBPins();
    BOARD_InitSWDPins();
    BOARD_InitLCDPins();
    BOARD_InitAudioPins();
    BOARD_InitIrDAPins();
    BOARD_InitKeyboardPins();
    BOARD_InitChargePins();
    BOARD_InitWiFiPins();
    BOARD_InitBlePins();
    BOARD_InitTouchpanelPins();
    BOARD_InitZigbeePins();
}

#define PIO023_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO023_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO024_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO024_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO025_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO025_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO026_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO026_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO027_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO027_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO028_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO028_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSPIFIPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M13, peripheral: SPIFI0, signal: SPIFI_SCK, pin_signal: PIO0_26/FC2_RXD_SDA_MOSI/CLKOUT/CTIMER3_CAP2/SCT0_OUT5/PDM0_CLK/SPIFI_CLK/USB0_IDVALUE}
  - {pin_num: M7, peripheral: SPIFI0, signal: SPIFI_IO0/SPIFI_MOSI, pin_signal: PIO0_24/FC0_RXD_SDA_MOSI/SD_D(0)/CTIMER2_CAP0/SCT0_GPI0/SPIFI_IO(0)}
  - {pin_num: K8, peripheral: SPIFI0, signal: SPIFI_IO1/SPIFI_MISO, pin_signal: PIO0_25/FC0_TXD_SCL_MISO/SD_D(1)/CTIMER2_CAP1/SCT0_GPI1/SPIFI_IO(1)}
  - {pin_num: L9, peripheral: SPIFI0, signal: 'SPIFI_IO, 3', pin_signal: PIO0_27/FC2_TXD_SCL_MISO/CTIMER3_MAT2/SCT0_OUT6/PDM0_DATA/SPIFI_IO(3)}
  - {pin_num: M9, peripheral: SPIFI0, signal: 'SPIFI_IO, 2', pin_signal: PIO0_28/FC0_SCK/CTIMER2_CAP3/SCT0_OUT7/TRACEDATA(3)/SPIFI_IO(2)/USB0_OVERCURRENTN}
  - {pin_num: N7, peripheral: SPIFI0, signal: SPIFI_CSN, pin_signal: PIO0_23/MCLK/CTIMER1_MAT2/CTIMER3_MAT3/SCT0_OUT4/SPIFI_CSN/ADC0_11}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSPIFIPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSPIFIPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][23] = ((IOCON->PIO[0][23] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO023_FUNC_ALT6)                     /* Selects pin function.: PORT023 (pin N7) is configured as SPIFI_CSN */
      | IOCON_PIO_DIGIMODE(PIO023_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][24] = ((IOCON->PIO[0][24] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO024_FUNC_ALT6)                     /* Selects pin function.: PORT024 (pin M7) is configured as SPIFI_IO(0) */
      | IOCON_PIO_DIGIMODE(PIO024_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][25] = ((IOCON->PIO[0][25] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO025_FUNC_ALT6)                     /* Selects pin function.: PORT025 (pin K8) is configured as SPIFI_IO(1) */
      | IOCON_PIO_DIGIMODE(PIO025_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO026_FUNC_ALT6)                     /* Selects pin function.: PORT026 (pin M13) is configured as SPIFI_CLK */
      | IOCON_PIO_DIGIMODE(PIO026_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][27] = ((IOCON->PIO[0][27] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO027_FUNC_ALT6)                     /* Selects pin function.: PORT027 (pin L9) is configured as SPIFI_IO(3) */
      | IOCON_PIO_DIGIMODE(PIO027_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][28] = ((IOCON->PIO[0][28] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO028_FUNC_ALT6)                     /* Selects pin function.: PORT028 (pin M9) is configured as SPIFI_IO(2) */
      | IOCON_PIO_DIGIMODE(PIO028_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO015_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO015_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO018_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO018_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO019_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO019_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO020_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO020_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO021_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO021_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO02_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO02_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO03_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO03_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO04_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO04_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO05_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO05_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO06_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO06_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO07_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO07_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO08_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO08_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO09_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO09_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO110_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO110_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO111_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO111_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO112_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO112_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO113_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO113_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO114_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO114_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO115_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO115_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO116_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO116_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO119_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO119_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO120_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO120_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO121_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO121_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO122_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO122_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO123_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO123_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO125_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO125_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO126_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO126_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO127_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO127_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO128_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO128_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO129_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO129_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO130_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO130_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO131_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO131_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO14_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO14_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO15_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO15_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO16_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO16_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO17_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO17_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO18_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO18_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO19_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO19_FUNC_ALT6               0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO325_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO325_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDRAMPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: P9, peripheral: EMC, signal: 'EMC_A, 14', pin_signal: PIO3_25/CTIMER4_CAP2/FC4_SCK/EMC_A(14)}
  - {pin_num: M12, peripheral: EMC, signal: 'EMC_A, 13', pin_signal: PIO1_25/FC2_TXD_SCL_MISO/SCT0_OUT2/UTICK_CAP0/EMC_A(13)}
  - {pin_num: M10, peripheral: EMC, signal: 'EMC_A, 11', pin_signal: PIO1_23/FC2_SCK/SCT0_OUT0/ENET_MDIO/FC3_SSEL2/EMC_A(11)}
  - {pin_num: B7, peripheral: EMC, signal: 'EMC_A, 10', pin_signal: PIO1_16/ENET_MDC/FC6_TXD_SCL_MISO_WS/CTIMER1_MAT3/SD_CMD/EMC_A(10)}
  - {pin_num: F10, peripheral: EMC, signal: 'EMC_A, 9', pin_signal: PIO1_27/FC2_RTS_SCL_SSEL1/SD_D(4)/CTIMER0_MAT3/CLKOUT/EMC_A(9)}
  - {pin_num: J10, peripheral: EMC, signal: 'EMC_A, 8', pin_signal: PIO1_26/FC2_CTS_SDA_SSEL0/SCT0_OUT3/CTIMER0_CAP3/UTICK_CAP1/EMC_A(8)}
  - {pin_num: P8, peripheral: EMC, signal: 'EMC_A, 7', pin_signal: PIO1_8/FC0_CTS_SDA_SSEL0/SD_CLK/SCT0_OUT1/FC4_SSEL2/EMC_A(7)}
  - {pin_num: N1, peripheral: EMC, signal: 'EMC_A, 6', pin_signal: PIO1_7/FC0_RTS_SCL_SSEL1/SD_D(1)/CTIMER2_MAT2/SCT0_GPI4/EMC_A(6)}
  - {pin_num: G4, peripheral: EMC, signal: 'EMC_A, 5', pin_signal: PIO1_6/FC0_TXD_SCL_MISO/SD_D(3)/CTIMER2_MAT1/SCT0_GPI3/EMC_A(5)}
  - {pin_num: E4, peripheral: EMC, signal: 'EMC_A, 4', pin_signal: PIO1_5/FC0_RXD_SDA_MOSI/SD_D(2)/CTIMER2_MAT0/SCT0_GPI0/EMC_A(4)}
  - {pin_num: C13, peripheral: EMC, signal: 'EMC_A, 3', pin_signal: PIO0_21/FC3_RTS_SCL_SSEL1/UTICK_CAP3/CTIMER3_MAT3/SCT0_GPI3/SCI0_SCLK/EMC_A(3)/FC7_SCK}
  - {pin_num: D13, peripheral: EMC, signal: 'EMC_A, 2', pin_signal: PIO0_20/FC3_CTS_SDA_SSEL0/CTIMER1_MAT1/CTIMER3_CAP3/SCT0_GPI2/SCI0_IO/EMC_A(2)/FC7_RXD_SDA_MOSI_DATA}
  - {pin_num: C6, peripheral: EMC, signal: 'EMC_A, 1', pin_signal: PIO0_19/FC4_RTS_SCL_SSEL1/UTICK_CAP0/CTIMER0_MAT2/SCT0_OUT2/EMC_A(1)/FC7_TXD_SCL_MISO_WS}
  - {pin_num: C14, peripheral: EMC, signal: 'EMC_A, 0', pin_signal: PIO0_18/FC4_CTS_SDA_SSEL0/SD_WR_PRT/CTIMER1_MAT0/SCT0_OUT1/SCI1_SCLK/EMC_A(0)}
  - {pin_num: L4, peripheral: EMC, signal: EMC_WE, pin_signal: PIO0_15/FC6_CTS_SDA_SSEL0/UTICK_CAP2/CTIMER4_CAP0/SCT0_OUT2/EMC_WEN/ENET_TX_EN/ADC0_3}
  - {pin_num: K6, peripheral: EMC, signal: EMC_CAS, pin_signal: PIO1_9/ENET_TXD0/FC1_SCK/CTIMER1_CAP0/SCT0_OUT2/FC4_CTS_SDA_SSEL0/EMC_CASN}
  - {pin_num: N9, peripheral: EMC, signal: EMC_RAS, pin_signal: PIO1_10/ENET_TXD1/FC1_RXD_SDA_MOSI/CTIMER1_MAT0/SCT0_OUT3/EMC_RASN}
  - {pin_num: K9, peripheral: EMC, signal: 'EMC_DYCS, 0', pin_signal: PIO1_12/ENET_RXD0/FC6_SCK/CTIMER1_MAT1/USB0_PORTPWRN/EMC_DYCSN(0)}
  - {pin_num: C5, peripheral: EMC, signal: 'EMC_D, 15', pin_signal: PIO1_31/MCLK/CTIMER0_MAT2/SCT0_OUT6/FC8_CTS_SDA_SSEL0/EMC_D(15)}
  - {pin_num: A8, peripheral: EMC, signal: 'EMC_D, 14', pin_signal: PIO1_30/FC7_TXD_SCL_MISO_WS/SD_D(7)/SCT0_GPI7/USB1_OVERCURRENTN/USB1_UP_LED/EMC_D(14)}
  - {pin_num: C11, peripheral: EMC, signal: 'EMC_D, 13', pin_signal: PIO1_29/FC7_RXD_SDA_MOSI_DATA/SD_D(6)/SCT0_GPI6/USB1_PORTPWRN/USB1_FRAME/EMC_D(13)}
  - {pin_num: E12, peripheral: EMC, signal: 'EMC_D, 12', pin_signal: PIO1_28/FC7_SCK/SD_D(5)/CTIMER0_CAP2/EMC_D(12)}
  - {pin_num: D4, peripheral: EMC, signal: 'EMC_D, 11', pin_signal: PIO1_4/FC0_SCK/SD_D(0)/CTIMER2_MAT1/SCT0_OUT0/FREQME_GPIO_CLK_A/EMC_D(11)}
  - {pin_num: N8, peripheral: EMC, signal: 'EMC_D, 10', pin_signal: PIO1_21/FC7_CTS_SDA_SSEL0/CTIMER3_MAT2/FC4_RXD_SDA_MOSI/EMC_D(10)}
  - {pin_num: M1, peripheral: EMC, signal: 'EMC_D, 9', pin_signal: PIO1_20/FC7_RTS_SCL_SSEL1/CTIMER3_CAP2/FC4_TXD_SCL_MISO/EMC_D(9)}
  - {pin_num: L1, peripheral: EMC, signal: 'EMC_D, 8', pin_signal: PIO1_19/FC8_SCK/SCT0_OUT7/CTIMER3_MAT1/SCT0_GPI7/FC4_SCK/EMC_D(8)}
  - {pin_num: G12, peripheral: EMC, signal: 'EMC_D, 7', pin_signal: PIO0_9/FC3_SSEL2/SD_POW_EN/FC5_TXD_SCL_MISO/SCI1_IO/EMC_D(7)}
  - {pin_num: H10, peripheral: EMC, signal: 'EMC_D, 6', pin_signal: PIO0_8/FC3_SSEL3/SD_CMD/FC5_RXD_SDA_MOSI/SWO/PDM1_DATA/EMC_D(6)}
  - {pin_num: H12, peripheral: EMC, signal: 'EMC_D, 5', pin_signal: PIO0_7/FC3_RTS_SCL_SSEL1/SD_CLK/FC5_SCK/FC1_SCK/PDM1_CLK/EMC_D(5)/ENET_RX_CLK}
  - {pin_num: A5, peripheral: EMC, signal: 'EMC_D, 4', pin_signal: PIO0_6/FC3_SCK/CTIMER3_CAP1/CTIMER4_MAT0/SCT0_GPI6/EMC_D(4)/ENET_RX_DV, identifier: EMC_D4}
  - {pin_num: E7, peripheral: EMC, signal: 'EMC_D, 3', pin_signal: PIO0_5/CAN0_TD/FC4_RXD_SDA_MOSI/CTIMER3_MAT0/SCT0_GPI5/EMC_D(3)/ENET_MDIO, identifier: EMC_D3}
  - {pin_num: C8, peripheral: EMC, signal: 'EMC_D, 2', pin_signal: PIO0_4/CAN0_RD/FC4_SCK/CTIMER3_CAP0/SCT0_GPI4/EMC_D(2)/ENET_MDC, identifier: EMC_D2}
  - {pin_num: A10, peripheral: EMC, signal: 'EMC_D, 1', pin_signal: PIO0_3/FC3_RXD_SDA_MOSI/CTIMER0_MAT1/SCT0_OUT1/SCT0_GPI3/EMC_D(1), identifier: EMC_D1}
  - {pin_num: E9, peripheral: EMC, signal: 'EMC_D, 0', pin_signal: PIO0_2/FC3_TXD_SCL_MISO/CTIMER0_CAP1/SCT0_OUT0/SCT0_GPI2/EMC_D(0), identifier: EMC_D0}
  - {pin_num: C12, peripheral: EMC, signal: 'EMC_DQM, 1', pin_signal: PIO1_14/ENET_RX_DV/UTICK_CAP2/CTIMER1_MAT2/FC5_CTS_SDA_SSEL0/USB0_UP_LED/EMC_DQM(1)}
  - {pin_num: G10, peripheral: EMC, signal: 'EMC_DQM, 0', pin_signal: PIO1_13/ENET_RXD1/FC6_RXD_SDA_MOSI_DATA/CTIMER1_CAP2/USB0_OVERCURRENTN/USB0_FRAME/EMC_DQM(0)}
  - {pin_num: B4, peripheral: EMC, signal: 'EMC_CLK, 0', pin_signal: PIO1_11/ENET_TX_EN/FC1_TXD_SCL_MISO/CTIMER1_CAP1/USB0_VBUS/EMC_CLK(0)}
  - {pin_num: A11, peripheral: EMC, signal: 'EMC_CKE, 0', pin_signal: PIO1_15/ENET_RX_CLK/UTICK_CAP3/CTIMER1_CAP3/FC5_RTS_SCL_SSEL1/FC4_RTS_SCL_SSEL1/EMC_CKE(0)}
  - {pin_num: P11, peripheral: EMC, signal: 'EMC_CKE, 1', pin_signal: PIO1_22/FC8_RTS_SCL_SSEL1/SD_CMD/CTIMER2_MAT3/SCT0_GPI5/FC4_SSEL3/EMC_CKE(1)}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSDRAMPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSDRAMPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][15] = ((IOCON->PIO[0][15] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO015_FUNC_ALT6)                     /* Selects pin function.: PORT015 (pin L4) is configured as EMC_WEN */
      | IOCON_PIO_DIGIMODE(PIO015_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO018_FUNC_ALT6)                     /* Selects pin function.: PORT018 (pin C14) is configured as EMC_A(0) */
      | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][19] = ((IOCON->PIO[0][19] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO019_FUNC_ALT6)                     /* Selects pin function.: PORT019 (pin C6) is configured as EMC_A(1) */
      | IOCON_PIO_DIGIMODE(PIO019_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][2] = ((IOCON->PIO[0][2] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO02_FUNC_ALT6)                      /* Selects pin function.: PORT02 (pin E9) is configured as EMC_D(0) */
      | IOCON_PIO_DIGIMODE(PIO02_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO020_FUNC_ALT6)                     /* Selects pin function.: PORT020 (pin D13) is configured as EMC_A(2) */
      | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][21] = ((IOCON->PIO[0][21] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO021_FUNC_ALT6)                     /* Selects pin function.: PORT021 (pin C13) is configured as EMC_A(3) */
      | IOCON_PIO_DIGIMODE(PIO021_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][3] = ((IOCON->PIO[0][3] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO03_FUNC_ALT6)                      /* Selects pin function.: PORT03 (pin A10) is configured as EMC_D(1) */
      | IOCON_PIO_DIGIMODE(PIO03_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][4] = ((IOCON->PIO[0][4] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO04_FUNC_ALT6)                      /* Selects pin function.: PORT04 (pin C8) is configured as EMC_D(2) */
      | IOCON_PIO_DIGIMODE(PIO04_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][5] = ((IOCON->PIO[0][5] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO05_FUNC_ALT6)                      /* Selects pin function.: PORT05 (pin E7) is configured as EMC_D(3) */
      | IOCON_PIO_DIGIMODE(PIO05_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][6] = ((IOCON->PIO[0][6] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO06_FUNC_ALT6)                      /* Selects pin function.: PORT06 (pin A5) is configured as EMC_D(4) */
      | IOCON_PIO_DIGIMODE(PIO06_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][7] = ((IOCON->PIO[0][7] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO07_FUNC_ALT6)                      /* Selects pin function.: PORT07 (pin H12) is configured as EMC_D(5) */
      | IOCON_PIO_DIGIMODE(PIO07_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][8] = ((IOCON->PIO[0][8] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO08_FUNC_ALT6)                      /* Selects pin function.: PORT08 (pin H10) is configured as EMC_D(6) */
      | IOCON_PIO_DIGIMODE(PIO08_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][9] = ((IOCON->PIO[0][9] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO09_FUNC_ALT6)                      /* Selects pin function.: PORT09 (pin G12) is configured as EMC_D(7) */
      | IOCON_PIO_DIGIMODE(PIO09_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][10] = ((IOCON->PIO[1][10] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO110_FUNC_ALT6)                     /* Selects pin function.: PORT110 (pin N9) is configured as EMC_RASN */
      | IOCON_PIO_DIGIMODE(PIO110_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][11] = ((IOCON->PIO[1][11] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO111_FUNC_ALT6)                     /* Selects pin function.: PORT111 (pin B4) is configured as EMC_CLK(0) */
      | IOCON_PIO_DIGIMODE(PIO111_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][12] = ((IOCON->PIO[1][12] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO112_FUNC_ALT6)                     /* Selects pin function.: PORT112 (pin K9) is configured as EMC_DYCSN(0) */
      | IOCON_PIO_DIGIMODE(PIO112_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][13] = ((IOCON->PIO[1][13] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO113_FUNC_ALT6)                     /* Selects pin function.: PORT113 (pin G10) is configured as EMC_DQM(0) */
      | IOCON_PIO_DIGIMODE(PIO113_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][14] = ((IOCON->PIO[1][14] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO114_FUNC_ALT6)                     /* Selects pin function.: PORT114 (pin C12) is configured as EMC_DQM(1) */
      | IOCON_PIO_DIGIMODE(PIO114_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][15] = ((IOCON->PIO[1][15] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO115_FUNC_ALT6)                     /* Selects pin function.: PORT115 (pin A11) is configured as EMC_CKE(0) */
      | IOCON_PIO_DIGIMODE(PIO115_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][16] = ((IOCON->PIO[1][16] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO116_FUNC_ALT6)                     /* Selects pin function.: PORT116 (pin B7) is configured as EMC_A(10) */
      | IOCON_PIO_DIGIMODE(PIO116_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][19] = ((IOCON->PIO[1][19] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO119_FUNC_ALT6)                     /* Selects pin function.: PORT119 (pin L1) is configured as EMC_D(8) */
      | IOCON_PIO_DIGIMODE(PIO119_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][20] = ((IOCON->PIO[1][20] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO120_FUNC_ALT6)                     /* Selects pin function.: PORT120 (pin M1) is configured as EMC_D(9) */
      | IOCON_PIO_DIGIMODE(PIO120_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][21] = ((IOCON->PIO[1][21] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO121_FUNC_ALT6)                     /* Selects pin function.: PORT121 (pin N8) is configured as EMC_D(10) */
      | IOCON_PIO_DIGIMODE(PIO121_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][22] = ((IOCON->PIO[1][22] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO122_FUNC_ALT6)                     /* Selects pin function.: PORT122 (pin P11) is configured as EMC_CKE(1) */
      | IOCON_PIO_DIGIMODE(PIO122_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][23] = ((IOCON->PIO[1][23] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO123_FUNC_ALT6)                     /* Selects pin function.: PORT123 (pin M10) is configured as EMC_A(11) */
      | IOCON_PIO_DIGIMODE(PIO123_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][25] = ((IOCON->PIO[1][25] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO125_FUNC_ALT6)                     /* Selects pin function.: PORT125 (pin M12) is configured as EMC_A(13) */
      | IOCON_PIO_DIGIMODE(PIO125_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][26] = ((IOCON->PIO[1][26] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO126_FUNC_ALT6)                     /* Selects pin function.: PORT126 (pin J10) is configured as EMC_A(8) */
      | IOCON_PIO_DIGIMODE(PIO126_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][27] = ((IOCON->PIO[1][27] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO127_FUNC_ALT6)                     /* Selects pin function.: PORT127 (pin F10) is configured as EMC_A(9) */
      | IOCON_PIO_DIGIMODE(PIO127_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][28] = ((IOCON->PIO[1][28] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO128_FUNC_ALT6)                     /* Selects pin function.: PORT128 (pin E12) is configured as EMC_D(12) */
      | IOCON_PIO_DIGIMODE(PIO128_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][29] = ((IOCON->PIO[1][29] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO129_FUNC_ALT6)                     /* Selects pin function.: PORT129 (pin C11) is configured as EMC_D(13) */
      | IOCON_PIO_DIGIMODE(PIO129_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][30] = ((IOCON->PIO[1][30] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO130_FUNC_ALT6)                     /* Selects pin function.: PORT130 (pin A8) is configured as EMC_D(14) */
      | IOCON_PIO_DIGIMODE(PIO130_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][31] = ((IOCON->PIO[1][31] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO131_FUNC_ALT6)                     /* Selects pin function.: PORT131 (pin C5) is configured as EMC_D(15) */
      | IOCON_PIO_DIGIMODE(PIO131_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][4] = ((IOCON->PIO[1][4] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO14_FUNC_ALT6)                      /* Selects pin function.: PORT14 (pin D4) is configured as EMC_D(11) */
      | IOCON_PIO_DIGIMODE(PIO14_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][5] = ((IOCON->PIO[1][5] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO15_FUNC_ALT6)                      /* Selects pin function.: PORT15 (pin E4) is configured as EMC_A(4) */
      | IOCON_PIO_DIGIMODE(PIO15_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][6] = ((IOCON->PIO[1][6] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO16_FUNC_ALT6)                      /* Selects pin function.: PORT16 (pin G4) is configured as EMC_A(5) */
      | IOCON_PIO_DIGIMODE(PIO16_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][7] = ((IOCON->PIO[1][7] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO17_FUNC_ALT6)                      /* Selects pin function.: PORT17 (pin N1) is configured as EMC_A(6) */
      | IOCON_PIO_DIGIMODE(PIO17_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][8] = ((IOCON->PIO[1][8] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO18_FUNC_ALT6)                      /* Selects pin function.: PORT18 (pin P8) is configured as EMC_A(7) */
      | IOCON_PIO_DIGIMODE(PIO18_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][9] = ((IOCON->PIO[1][9] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO19_FUNC_ALT6)                      /* Selects pin function.: PORT19 (pin K6) is configured as EMC_CASN */
      | IOCON_PIO_DIGIMODE(PIO19_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][25] = ((IOCON->PIO[3][25] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO325_FUNC_ALT6)                     /* Selects pin function.: PORT325 (pin P9) is configured as EMC_A(14) */
      | IOCON_PIO_DIGIMODE(PIO325_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSBPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: H3, peripheral: USBHSH, signal: USB_DP, pin_signal: USB1_DP}
  - {pin_num: H2, peripheral: USBHSH, signal: USB_DM, pin_signal: USB1_DM}
  - {pin_num: G2, peripheral: USBHSH, signal: USB_VBUS, pin_signal: USB1_VBUS}
  - {pin_num: G1, peripheral: USBHSH, signal: USB_IDVALUE, pin_signal: USB1_ID}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitUSBPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitUSBPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
}


#define PIO010_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO010_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO011_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO011_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */
#define PIO012_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO012_FUNC_ALT6              0x06u   /*!< Selects pin function.: Alternative connection 6. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSWDPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M3, peripheral: SWD, signal: SWDIO, pin_signal: PIO0_12/FC3_TXD_SCL_MISO/FREQME_GPIO_CLK_B/SCT0_GPI7/SWDIO/ADC0_2}
  - {pin_num: L3, peripheral: SWD, signal: SWCLK, pin_signal: PIO0_11/FC6_RXD_SDA_MOSI_DATA/CTIMER2_MAT2/FREQME_GPIO_CLK_A/SWCLK/ADC0_1}
  - {pin_num: P2, peripheral: SWD, signal: SWO, pin_signal: PIO0_10/FC6_SCK/CTIMER2_CAP2/CTIMER2_MAT0/FC1_TXD_SCL_MISO/SWO/ADC0_0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSWDPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSWDPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][10] = ((IOCON->PIO[0][10] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO010_FUNC_ALT6)                     /* Selects pin function.: PORT010 (pin P2) is configured as SWO */
      | IOCON_PIO_DIGIMODE(PIO010_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][11] = ((IOCON->PIO[0][11] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO011_FUNC_ALT6)                     /* Selects pin function.: PORT011 (pin L3) is configured as SWCLK */
      | IOCON_PIO_DIGIMODE(PIO011_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][12] = ((IOCON->PIO[0][12] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO012_FUNC_ALT6)                     /* Selects pin function.: PORT012 (pin M3) is configured as SWDIO */
      | IOCON_PIO_DIGIMODE(PIO012_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO211_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO211_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO213_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO213_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO214_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO214_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO215_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO215_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO216_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO216_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO221_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO221_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO222_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO222_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO223_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO223_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO224_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO224_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO225_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO225_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO228_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO228_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO229_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO229_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO230_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO230_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO231_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO231_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO30_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO30_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO31_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO31_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO320_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO320_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO321_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO321_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO322_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO322_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO330_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO330_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO33_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO33_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO35_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO35_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO36_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO36_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO37_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO37_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO38_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO38_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO39_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO39_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO416_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO416_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLCDPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: K3, peripheral: LCD, signal: LCD_PWR, pin_signal: PIO2_11/LCD_PWR/SD_VOLT(0)/FC5_SCK}
  - {pin_num: L7, peripheral: LCD, signal: LCD_FP, pin_signal: PIO2_14/LCD_FP/USB0_FRAME/USB0_PORTPWRN/CTIMER0_MAT2/FC5_CTS_SDA_SSEL0}
  - {pin_num: P7, peripheral: LCD, signal: LCD_DCLK, pin_signal: PIO2_13/LCD_DCLK/SD_VOLT(2)/FC5_TXD_SCL_MISO}
  - {pin_num: L8, peripheral: LCD, signal: LCD_LP, pin_signal: PIO2_16/LCD_LP/USB1_FRAME/USB1_PORTPWRN/CTIMER1_MAT3/FC8_SCK}
  - {pin_num: M8, peripheral: LCD, signal: LCD_AC, pin_signal: PIO2_15/LCD_AC/USB0_UP_LED/USB0_OVERCURRENTN/CTIMER0_MAT3/FC5_RTS_SCL_SSEL1}
  - {pin_num: K10, peripheral: LCD, signal: 'LCD_VD, 4', pin_signal: PIO2_22/LCD_VD(4)/SCT0_OUT7/CTIMER2_CAP0}
  - {pin_num: L10, peripheral: LCD, signal: 'LCD_VD, 3', pin_signal: PIO2_21/LCD_VD(3)/FC3_CTS_SDA_SSEL0/MCLK/CTIMER3_MAT3}
  - {pin_num: G11, peripheral: LCD, signal: 'LCD_VD, 11', pin_signal: PIO2_29/LCD_VD(11)/FC7_RTS_SCL_SSEL1/FC8_TXD_SCL_MISO/CTIMER2_CAP3/CLKOUT}
  - {pin_num: J11, peripheral: LCD, signal: 'LCD_VD, 7', pin_signal: PIO2_25/LCD_VD(7)/USB0_VBUS}
  - {pin_num: F12, peripheral: LCD, signal: 'LCD_VD, 12', pin_signal: PIO2_30/LCD_VD(12)/CTIMER2_MAT2}
  - {pin_num: G13, peripheral: LCD, signal: 'LCD_VD, 10', pin_signal: PIO2_28/LCD_VD(10)/FC7_CTS_SDA_SSEL0/CTIMER2_CAP2}
  - {pin_num: D14, peripheral: LCD, signal: 'LCD_VD, 13', pin_signal: PIO2_31/LCD_VD(13)}
  - {pin_num: K14, peripheral: LCD, signal: 'LCD_VD, 6', pin_signal: PIO2_24/LCD_VD(6)/SCT0_OUT9}
  - {pin_num: M14, peripheral: LCD, signal: 'LCD_VD, 5', pin_signal: PIO2_23/LCD_VD(5)/SCT0_OUT8}
  - {pin_num: D12, peripheral: LCD, signal: 'LCD_VD, 14', pin_signal: PIO3_0/LCD_VD(14)/PDM0_CLK/CTIMER1_MAT0}
  - {pin_num: D11, peripheral: LCD, signal: 'LCD_VD, 15', pin_signal: PIO3_1/LCD_VD(15)/PDM0_DATA/CTIMER1_MAT1}
  - {pin_num: B10, peripheral: LCD, signal: 'LCD_VD, 19', pin_signal: PIO3_5/LCD_VD(19)/FC8_RTS_SCL_SSEL1/CTIMER4_MAT1}
  - {pin_num: C9, peripheral: LCD, signal: 'LCD_VD, 20', pin_signal: PIO3_6/LCD_VD(20)/LCD_VD(0)/CTIMER4_MAT2}
  - {pin_num: B8, peripheral: LCD, signal: 'LCD_VD, 21', pin_signal: PIO3_7/LCD_VD(21)/LCD_VD(1)/CTIMER4_CAP2}
  - {pin_num: A7, peripheral: LCD, signal: 'LCD_VD, 22', pin_signal: PIO3_8/LCD_VD(22)/LCD_VD(2)/CTIMER4_CAP3}
  - {pin_num: C7, peripheral: LCD, signal: 'LCD_VD, 23', pin_signal: PIO3_9/LCD_VD(23)/LCD_VD(3)/CTIMER0_CAP2}
  - {pin_num: A13, peripheral: GPIO, signal: 'PIO3, 3', pin_signal: PIO3_3/LCD_VD(17)/FC9_TXD_SCL_MISO}
  - {pin_num: N2, peripheral: FLEXCOMM9, signal: SCK, pin_signal: PIO3_20/FC9_SCK/SD_CARD_INT_N/CLKOUT/SCT0_OUT7}
  - {pin_num: P5, peripheral: FLEXCOMM9, signal: RXD_SDA_MOSI, pin_signal: PIO3_21/FC9_RXD_SDA_MOSI/SD_BACKEND_PWR/CTIMER4_MAT3/UTICK_CAP2/ADC0_9}
  - {pin_num: N5, peripheral: FLEXCOMM9, signal: TXD_SCL_MISO, pin_signal: PIO3_22/FC9_TXD_SCL_MISO/ADC0_10}
  - {pin_num: K13, peripheral: FLEXCOMM9, signal: CTS_SDA_SSEL0, pin_signal: PIO3_30/FC9_CTS_SDA_SSEL0/SCT0_OUT4/FC4_SSEL2/EMC_A(19)}
  - {pin_num: C4, peripheral: GPIO, signal: 'PIO4, 16', pin_signal: PIO4_16/ENET_MDIO/CTIMER4_MAT3/FC9_TXD_SCL_MISO}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLCDPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLCDPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[2][11] = ((IOCON->PIO[2][11] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO211_FUNC_ALT1)                     /* Selects pin function.: PORT211 (pin K3) is configured as LCD_PWR */
      | IOCON_PIO_DIGIMODE(PIO211_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][13] = ((IOCON->PIO[2][13] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO213_FUNC_ALT1)                     /* Selects pin function.: PORT213 (pin P7) is configured as LCD_DCLK */
      | IOCON_PIO_DIGIMODE(PIO213_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][14] = ((IOCON->PIO[2][14] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO214_FUNC_ALT1)                     /* Selects pin function.: PORT214 (pin L7) is configured as LCD_FP */
      | IOCON_PIO_DIGIMODE(PIO214_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][15] = ((IOCON->PIO[2][15] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO215_FUNC_ALT1)                     /* Selects pin function.: PORT215 (pin M8) is configured as LCD_AC */
      | IOCON_PIO_DIGIMODE(PIO215_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][16] = ((IOCON->PIO[2][16] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO216_FUNC_ALT1)                     /* Selects pin function.: PORT216 (pin L8) is configured as LCD_LP */
      | IOCON_PIO_DIGIMODE(PIO216_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][21] = ((IOCON->PIO[2][21] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO221_FUNC_ALT1)                     /* Selects pin function.: PORT221 (pin L10) is configured as LCD_VD(3) */
      | IOCON_PIO_DIGIMODE(PIO221_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][22] = ((IOCON->PIO[2][22] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO222_FUNC_ALT1)                     /* Selects pin function.: PORT222 (pin K10) is configured as LCD_VD(4) */
      | IOCON_PIO_DIGIMODE(PIO222_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][23] = ((IOCON->PIO[2][23] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO223_FUNC_ALT1)                     /* Selects pin function.: PORT223 (pin M14) is configured as LCD_VD(5) */
      | IOCON_PIO_DIGIMODE(PIO223_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][24] = ((IOCON->PIO[2][24] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO224_FUNC_ALT1)                     /* Selects pin function.: PORT224 (pin K14) is configured as LCD_VD(6) */
      | IOCON_PIO_DIGIMODE(PIO224_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][25] = ((IOCON->PIO[2][25] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO225_FUNC_ALT1)                     /* Selects pin function.: PORT225 (pin J11) is configured as LCD_VD(7) */
      | IOCON_PIO_DIGIMODE(PIO225_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][28] = ((IOCON->PIO[2][28] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO228_FUNC_ALT1)                     /* Selects pin function.: PORT228 (pin G13) is configured as LCD_VD(10) */
      | IOCON_PIO_DIGIMODE(PIO228_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][29] = ((IOCON->PIO[2][29] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO229_FUNC_ALT1)                     /* Selects pin function.: PORT229 (pin G11) is configured as LCD_VD(11) */
      | IOCON_PIO_DIGIMODE(PIO229_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][30] = ((IOCON->PIO[2][30] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO230_FUNC_ALT1)                     /* Selects pin function.: PORT230 (pin F12) is configured as LCD_VD(12) */
      | IOCON_PIO_DIGIMODE(PIO230_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][31] = ((IOCON->PIO[2][31] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO231_FUNC_ALT1)                     /* Selects pin function.: PORT231 (pin D14) is configured as LCD_VD(13) */
      | IOCON_PIO_DIGIMODE(PIO231_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][0] = ((IOCON->PIO[3][0] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO30_FUNC_ALT1)                      /* Selects pin function.: PORT30 (pin D12) is configured as LCD_VD(14) */
      | IOCON_PIO_DIGIMODE(PIO30_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][1] = ((IOCON->PIO[3][1] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO31_FUNC_ALT1)                      /* Selects pin function.: PORT31 (pin D11) is configured as LCD_VD(15) */
      | IOCON_PIO_DIGIMODE(PIO31_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][20] = ((IOCON->PIO[3][20] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO320_FUNC_ALT1)                     /* Selects pin function.: PORT320 (pin N2) is configured as FC9_SCK */
      | IOCON_PIO_DIGIMODE(PIO320_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][21] = ((IOCON->PIO[3][21] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO321_FUNC_ALT1)                     /* Selects pin function.: PORT321 (pin P5) is configured as FC9_RXD_SDA_MOSI */
      | IOCON_PIO_DIGIMODE(PIO321_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][22] = ((IOCON->PIO[3][22] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO322_FUNC_ALT1)                     /* Selects pin function.: PORT322 (pin N5) is configured as FC9_TXD_SCL_MISO */
      | IOCON_PIO_DIGIMODE(PIO322_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][3] = ((IOCON->PIO[3][3] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO33_FUNC_ALT0)                      /* Selects pin function.: PORT33 (pin A13) is configured as PIO3_3 */
      | IOCON_PIO_DIGIMODE(PIO33_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][30] = ((IOCON->PIO[3][30] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO330_FUNC_ALT1)                     /* Selects pin function.: PORT330 (pin K13) is configured as FC9_CTS_SDA_SSEL0 */
      | IOCON_PIO_DIGIMODE(PIO330_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][5] = ((IOCON->PIO[3][5] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO35_FUNC_ALT1)                      /* Selects pin function.: PORT35 (pin B10) is configured as LCD_VD(19) */
      | IOCON_PIO_DIGIMODE(PIO35_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][6] = ((IOCON->PIO[3][6] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO36_FUNC_ALT1)                      /* Selects pin function.: PORT36 (pin C9) is configured as LCD_VD(20) */
      | IOCON_PIO_DIGIMODE(PIO36_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][7] = ((IOCON->PIO[3][7] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO37_FUNC_ALT1)                      /* Selects pin function.: PORT37 (pin B8) is configured as LCD_VD(21) */
      | IOCON_PIO_DIGIMODE(PIO37_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][8] = ((IOCON->PIO[3][8] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO38_FUNC_ALT1)                      /* Selects pin function.: PORT38 (pin A7) is configured as LCD_VD(22) */
      | IOCON_PIO_DIGIMODE(PIO38_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][9] = ((IOCON->PIO[3][9] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO39_FUNC_ALT1)                      /* Selects pin function.: PORT39 (pin C7) is configured as LCD_VD(23) */
      | IOCON_PIO_DIGIMODE(PIO39_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[4][16] = ((IOCON->PIO[4][16] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO416_FUNC_ALT0)                     /* Selects pin function.: PORT416 (pin C4) is configured as PIO4_16 */
      | IOCON_PIO_DIGIMODE(PIO416_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO12_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO12_FUNC_ALT5               0x05u   /*!< Selects pin function.: Alternative connection 5. */
#define PIO13_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO13_FUNC_ALT5               0x05u   /*!< Selects pin function.: Alternative connection 5. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitAudioPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: L14, peripheral: DMIC0, signal: 'CLK, 1', pin_signal: PIO1_2/CAN0_TD/CTIMER0_MAT3/SCT0_GPI6/PDM1_CLK/USB1_PORTPWRN}
  - {pin_num: J13, peripheral: DMIC0, signal: 'DATA, 1', pin_signal: PIO1_3/CAN0_RD/SCT0_OUT4/PDM1_DATA/USB0_PORTPWRN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitAudioPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitAudioPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[1][2] = ((IOCON->PIO[1][2] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO12_FUNC_ALT5)                      /* Selects pin function.: PORT12 (pin L14) is configured as PDM1_CLK */
      | IOCON_PIO_DIGIMODE(PIO12_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][3] = ((IOCON->PIO[1][3] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO13_FUNC_ALT5)                      /* Selects pin function.: PORT13 (pin J13) is configured as PDM1_DATA */
      | IOCON_PIO_DIGIMODE(PIO13_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO00_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO00_FUNC_ALT4               0x04u   /*!< Selects pin function.: Alternative connection 4. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitIrDAPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: D6, peripheral: SCT0, signal: 'IN, 0', pin_signal: PIO0_0/CAN1_RD/FC3_SCK/CTIMER0_MAT0/SCT0_GPI0/PDM0_CLK}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitIrDAPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitIrDAPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][0] = ((IOCON->PIO[0][0] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO00_FUNC_ALT4)                      /* Selects pin function.: PORT00 (pin D6) is configured as SCT0_GPI0 */
      | IOCON_PIO_DIGIMODE(PIO00_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO01_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO01_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO022_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO022_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO311_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO311_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO42_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO42_FUNC_ALT2               0x02u   /*!< Selects pin function.: Alternative connection 2. */
#define PIO43_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO43_FUNC_ALT2               0x02u   /*!< Selects pin function.: Alternative connection 2. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitKeyboardPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: A1, peripheral: GPIO, signal: 'PIO0, 1', pin_signal: PIO0_1/CAN1_TD/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_GPI1/PDM0_DATA}
  - {pin_num: B12, peripheral: GPIO, signal: 'PIO0, 22', pin_signal: PIO0_22/FC6_TXD_SCL_MISO_WS/UTICK_CAP1/CTIMER3_CAP3/SCT0_OUT3/USB0_VBUS}
  - {pin_num: B2, peripheral: GPIO, signal: 'PIO3, 11', pin_signal: PIO3_11/MCLK/FC0_SCK/FC1_SCK/TRACEDATA(3)}
  - {pin_num: F14, peripheral: FLEXCOMM6, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO4_2/FC6_RXD_SDA_MOSI_DATA/SCT0_GPI3/EMC_CSN(3)}
  - {pin_num: F13, peripheral: FLEXCOMM6, signal: TXD_SCL_MISO_WS, pin_signal: PIO4_3/FC6_TXD_SCL_MISO_WS/CTIMER0_CAP3/SCT0_GPI4/EMC_DYCSN(2)}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitKeyboardPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitKeyboardPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][1] = ((IOCON->PIO[0][1] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO01_FUNC_ALT0)                      /* Selects pin function.: PORT01 (pin A1) is configured as PIO0_1 */
      | IOCON_PIO_DIGIMODE(PIO01_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][22] = ((IOCON->PIO[0][22] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO022_FUNC_ALT0)                     /* Selects pin function.: PORT022 (pin B12) is configured as PIO0_22 */
      | IOCON_PIO_DIGIMODE(PIO022_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][11] = ((IOCON->PIO[3][11] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO311_FUNC_ALT0)                     /* Selects pin function.: PORT311 (pin B2) is configured as PIO3_11 */
      | IOCON_PIO_DIGIMODE(PIO311_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[4][2] = ((IOCON->PIO[4][2] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO42_FUNC_ALT2)                      /* Selects pin function.: PORT42 (pin F14) is configured as FC6_RXD_SDA_MOSI_DATA */
      | IOCON_PIO_DIGIMODE(PIO42_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[4][3] = ((IOCON->PIO[4][3] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO43_FUNC_ALT2)                      /* Selects pin function.: PORT43 (pin F13) is configured as FC6_TXD_SCL_MISO_WS */
      | IOCON_PIO_DIGIMODE(PIO43_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO010_DIGIMODE_ANALOG        0x00u   /*!< Select Analog/Digital mode.: Analog mode. */
#define PIO010_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO016_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO016_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO10_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO10_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO118_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO118_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO42_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO42_FUNC_ALT2               0x02u   /*!< Selects pin function.: Alternative connection 2. */
#define PIO43_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO43_FUNC_ALT2               0x02u   /*!< Selects pin function.: Alternative connection 2. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitChargePins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M4, peripheral: GPIO, signal: 'PIO0, 16', pin_signal: PIO0_16/FC4_TXD_SCL_MISO/CLKOUT/CTIMER1_CAP0/EMC_CSN(0)/ENET_TXD0/ADC0_4}
  - {pin_num: N3, peripheral: GPIO, signal: 'PIO1, 0', pin_signal: PIO1_0/FC0_RTS_SCL_SSEL1/SD_D(3)/CTIMER0_CAP2/SCT0_GPI4/TRACECLK/ADC0_6}
  - {pin_num: D1, peripheral: GPIO, signal: 'PIO1, 18', pin_signal: PIO1_18/FC8_TXD_SCL_MISO/SCT0_OUT5/CAN1_RD/EMC_BLSN(1)}
  - {pin_num: F14, peripheral: FLEXCOMM6, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO4_2/FC6_RXD_SDA_MOSI_DATA/SCT0_GPI3/EMC_CSN(3)}
  - {pin_num: F13, peripheral: FLEXCOMM6, signal: TXD_SCL_MISO_WS, pin_signal: PIO4_3/FC6_TXD_SCL_MISO_WS/CTIMER0_CAP3/SCT0_GPI4/EMC_DYCSN(2)}
  - {pin_num: P2, peripheral: ADC0, signal: 'CH, 0', pin_signal: PIO0_10/FC6_SCK/CTIMER2_CAP2/CTIMER2_MAT0/FC1_TXD_SCL_MISO/SWO/ADC0_0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitChargePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitChargePins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][10] = ((IOCON->PIO[0][10] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO010_FUNC_ALT0)                     /* Selects pin function.: PORT010 (pin P2) is configured as ADC0_0 */
      | IOCON_PIO_DIGIMODE(PIO010_DIGIMODE_ANALOG)           /* Select Analog/Digital mode.: Analog mode. */
    );
  IOCON->PIO[0][16] = ((IOCON->PIO[0][16] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO016_FUNC_ALT0)                     /* Selects pin function.: PORT016 (pin M4) is configured as PIO0_16 */
      | IOCON_PIO_DIGIMODE(PIO016_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][0] = ((IOCON->PIO[1][0] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO10_FUNC_ALT0)                      /* Selects pin function.: PORT10 (pin N3) is configured as PIO1_0 */
      | IOCON_PIO_DIGIMODE(PIO10_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][18] = ((IOCON->PIO[1][18] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO118_FUNC_ALT0)                     /* Selects pin function.: PORT118 (pin D1) is configured as PIO1_18 */
      | IOCON_PIO_DIGIMODE(PIO118_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[4][2] = ((IOCON->PIO[4][2] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO42_FUNC_ALT2)                      /* Selects pin function.: PORT42 (pin F14) is configured as FC6_RXD_SDA_MOSI_DATA */
      | IOCON_PIO_DIGIMODE(PIO42_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[4][3] = ((IOCON->PIO[4][3] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO43_FUNC_ALT2)                      /* Selects pin function.: PORT43 (pin F13) is configured as FC6_TXD_SCL_MISO_WS */
      | IOCON_PIO_DIGIMODE(PIO43_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO017_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO017_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO029_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO029_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO030_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO030_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO11_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO11_FUNC_ALT1               0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO124_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO124_FUNC_ALT5              0x05u   /*!< Selects pin function.: Alternative connection 5. */
#define PIO219_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO219_FUNC_ALT2              0x02u   /*!< Selects pin function.: Alternative connection 2. */
#define PIO226_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO226_FUNC_ALT3              0x03u   /*!< Selects pin function.: Alternative connection 3. */
#define PIO312_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO312_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitWiFiPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E14, peripheral: GPIO, signal: 'PIO0, 17', pin_signal: PIO0_17/FC4_SSEL2/SD_CARD_DET_N/SCT0_GPI7/SCT0_OUT0/EMC_OEN/ENET_TXD1}
  - {pin_num: B13, peripheral: GPIO, signal: 'PIO0, 29', pin_signal: PIO0_29/FC0_RXD_SDA_MOSI/CTIMER2_MAT3/SCT0_OUT8/TRACEDATA(2)}
  - {pin_num: A2, peripheral: GPIO, signal: 'PIO0, 30', pin_signal: PIO0_30/FC0_TXD_SCL_MISO/CTIMER0_MAT0/SCT0_OUT9/TRACEDATA(1)}
  - {pin_num: K12, peripheral: FLEXCOMM3, signal: RXD_SDA_MOSI, pin_signal: PIO1_1/FC3_RXD_SDA_MOSI/CTIMER0_CAP3/SCT0_GPI5/USB1_OVERCURRENTN}
  - {pin_num: N14, peripheral: FLEXCOMM3, signal: SSEL3, pin_signal: PIO1_24/FC2_RXD_SDA_MOSI/SCT0_OUT1/FC3_SSEL3/EMC_A(12)}
  - {pin_num: P12, peripheral: FLEXCOMM3, signal: TXD_SCL_MISO, pin_signal: PIO2_19/LCD_VD(1)/FC3_TXD_SCL_MISO/FC7_RXD_SDA_MOSI_DATA/CTIMER3_MAT1}
  - {pin_num: H11, peripheral: FLEXCOMM3, signal: SCK, pin_signal: PIO2_26/LCD_VD(8)/FC3_SCK/CTIMER2_CAP1}
  - {pin_num: L2, peripheral: GPIO, signal: 'PIO3, 12', pin_signal: PIO3_12/SCT0_OUT8/CTIMER3_CAP0/CLKOUT/EMC_CLK(1)/TRACECLK}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitWiFiPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitWiFiPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][17] = ((IOCON->PIO[0][17] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO017_FUNC_ALT0)                     /* Selects pin function.: PORT017 (pin E14) is configured as PIO0_17 */
      | IOCON_PIO_DIGIMODE(PIO017_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][29] = ((IOCON->PIO[0][29] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO029_FUNC_ALT0)                     /* Selects pin function.: PORT029 (pin B13) is configured as PIO0_29 */
      | IOCON_PIO_DIGIMODE(PIO029_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[0][30] = ((IOCON->PIO[0][30] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO030_FUNC_ALT0)                     /* Selects pin function.: PORT030 (pin A2) is configured as PIO0_30 */
      | IOCON_PIO_DIGIMODE(PIO030_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][1] = ((IOCON->PIO[1][1] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO11_FUNC_ALT1)                      /* Selects pin function.: PORT11 (pin K12) is configured as FC3_RXD_SDA_MOSI */
      | IOCON_PIO_DIGIMODE(PIO11_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[1][24] = ((IOCON->PIO[1][24] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO124_FUNC_ALT5)                     /* Selects pin function.: PORT124 (pin N14) is configured as FC3_SSEL3 */
      | IOCON_PIO_DIGIMODE(PIO124_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][19] = ((IOCON->PIO[2][19] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO219_FUNC_ALT2)                     /* Selects pin function.: PORT219 (pin P12) is configured as FC3_TXD_SCL_MISO */
      | IOCON_PIO_DIGIMODE(PIO219_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][26] = ((IOCON->PIO[2][26] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO226_FUNC_ALT3)                     /* Selects pin function.: PORT226 (pin H11) is configured as FC3_SCK */
      | IOCON_PIO_DIGIMODE(PIO226_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][12] = ((IOCON->PIO[3][12] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO312_FUNC_ALT0)                     /* Selects pin function.: PORT312 (pin L2) is configured as PIO3_12 */
      | IOCON_PIO_DIGIMODE(PIO312_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO031_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO031_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO314_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO314_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO315_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO315_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO316_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO316_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO317_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO317_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO318_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO318_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO319_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO319_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO326_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO326_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO327_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO327_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO329_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO329_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBlePins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M5, peripheral: GPIO, signal: 'PIO0, 31', pin_signal: PIO0_31/FC0_CTS_SDA_SSEL0/SD_D(2)/CTIMER0_MAT1/SCT0_OUT3/TRACEDATA(0)/ADC0_5}
  - {pin_num: E3, peripheral: GPIO, signal: 'PIO3, 14', pin_signal: PIO3_14/SCT0_OUT4/FC9_RTS_SCL_SSEL1/CTIMER3_MAT1/TRACEDATA(2)}
  - {pin_num: E1, peripheral: FLEXCOMM8, signal: RXD_SDA_MOSI, pin_signal: PIO3_16/FC8_RXD_SDA_MOSI/SD_D(4)}
  - {pin_num: K1, peripheral: FLEXCOMM8, signal: TXD_SCL_MISO, pin_signal: PIO3_17/FC8_TXD_SCL_MISO/SD_D(5)}
  - {pin_num: J3, peripheral: GPIO, signal: 'PIO3, 19', pin_signal: PIO3_19/FC8_RTS_SCL_SSEL1/SD_D(7)/CTIMER4_MAT1/CAN0_RD/SCT0_OUT6}
  - {pin_num: K5, peripheral: GPIO, signal: 'PIO3, 26', pin_signal: PIO3_26/SCT0_OUT0/FC4_RXD_SDA_MOSI/EMC_A(15)}
  - {pin_num: P14, peripheral: GPIO, signal: 'PIO3, 27', pin_signal: PIO3_27/SCT0_OUT1/FC4_TXD_SCL_MISO/EMC_A(16)}
  - {pin_num: L13, peripheral: GPIO, signal: 'PIO3, 29', pin_signal: PIO3_29/SCT0_OUT3/FC4_RTS_SCL_SSEL1/EMC_A(18)}
  - {pin_num: D2, peripheral: GPIO, signal: 'PIO3, 15', pin_signal: PIO3_15/FC8_SCK/SD_WR_PRT}
  - {pin_num: M6, peripheral: GPIO, signal: 'PIO3, 18', pin_signal: PIO3_18/FC8_CTS_SDA_SSEL0/SD_D(6)/CTIMER4_MAT0/CAN0_TD/SCT0_OUT5}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitBlePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitBlePins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[0][31] = ((IOCON->PIO[0][31] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO031_FUNC_ALT0)                     /* Selects pin function.: PORT031 (pin M5) is configured as PIO0_31 */
      | IOCON_PIO_DIGIMODE(PIO031_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][14] = ((IOCON->PIO[3][14] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO314_FUNC_ALT0)                     /* Selects pin function.: PORT314 (pin E3) is configured as PIO3_14 */
      | IOCON_PIO_DIGIMODE(PIO314_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][15] = ((IOCON->PIO[3][15] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO315_FUNC_ALT0)                     /* Selects pin function.: PORT315 (pin D2) is configured as PIO3_15 */
      | IOCON_PIO_DIGIMODE(PIO315_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][16] = ((IOCON->PIO[3][16] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO316_FUNC_ALT1)                     /* Selects pin function.: PORT316 (pin E1) is configured as FC8_RXD_SDA_MOSI */
      | IOCON_PIO_DIGIMODE(PIO316_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][17] = ((IOCON->PIO[3][17] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO317_FUNC_ALT1)                     /* Selects pin function.: PORT317 (pin K1) is configured as FC8_TXD_SCL_MISO */
      | IOCON_PIO_DIGIMODE(PIO317_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][18] = ((IOCON->PIO[3][18] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO318_FUNC_ALT0)                     /* Selects pin function.: PORT318 (pin M6) is configured as PIO3_18 */
      | IOCON_PIO_DIGIMODE(PIO318_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][19] = ((IOCON->PIO[3][19] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO319_FUNC_ALT0)                     /* Selects pin function.: PORT319 (pin J3) is configured as PIO3_19 */
      | IOCON_PIO_DIGIMODE(PIO319_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][26] = ((IOCON->PIO[3][26] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO326_FUNC_ALT0)                     /* Selects pin function.: PORT326 (pin K5) is configured as PIO3_26 */
      | IOCON_PIO_DIGIMODE(PIO326_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][27] = ((IOCON->PIO[3][27] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO327_FUNC_ALT0)                     /* Selects pin function.: PORT327 (pin P14) is configured as PIO3_27 */
      | IOCON_PIO_DIGIMODE(PIO327_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][29] = ((IOCON->PIO[3][29] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO329_FUNC_ALT0)                     /* Selects pin function.: PORT329 (pin L13) is configured as PIO3_29 */
      | IOCON_PIO_DIGIMODE(PIO329_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO117_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO117_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO227_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO227_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO323_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO323_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */
#define PIO324_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO324_FUNC_ALT1              0x01u   /*!< Selects pin function.: Alternative connection 1. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitTouchpanelPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: N12, peripheral: GPIO, signal: 'PIO1, 17', pin_signal: PIO1_17/ENET_MDIO/FC8_RXD_SDA_MOSI/SCT0_OUT4/CAN1_TD/EMC_BLSN(0)}
  - {pin_num: H14, peripheral: GPIO, signal: 'PIO2, 27', pin_signal: PIO2_27/LCD_VD(9)/FC9_SCK/FC3_SSEL2}
  - {pin_num: C2, peripheral: FLEXCOMM2, signal: CTS_SDA_SSEL0, pin_signal: PIO3_23/FC2_CTS_SDA_SSEL0/UTICK_CAP3}
  - {pin_num: E2, peripheral: FLEXCOMM2, signal: RTS_SCL_SSEL1, pin_signal: PIO3_24/FC2_RTS_SCL_SSEL1/CTIMER4_CAP0/USB0_VBUS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitTouchpanelPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitTouchpanelPins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[1][17] = ((IOCON->PIO[1][17] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO117_FUNC_ALT0)                     /* Selects pin function.: PORT117 (pin N12) is configured as PIO1_17 */
      | IOCON_PIO_DIGIMODE(PIO117_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][27] = ((IOCON->PIO[2][27] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO227_FUNC_ALT0)                     /* Selects pin function.: PORT227 (pin H14) is configured as PIO2_27 */
      | IOCON_PIO_DIGIMODE(PIO227_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][23] = ((IOCON->PIO[3][23] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO323_FUNC_ALT1)                     /* Selects pin function.: PORT323 (pin C2) is configured as FC2_CTS_SDA_SSEL0 */
      | IOCON_PIO_DIGIMODE(PIO323_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][24] = ((IOCON->PIO[3][24] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO324_FUNC_ALT1)                     /* Selects pin function.: PORT324 (pin E2) is configured as FC2_RTS_SCL_SSEL1 */
      | IOCON_PIO_DIGIMODE(PIO324_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
}


#define PIO210_DIGIMODE_DIGITAL       0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO210_FUNC_ALT0              0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO22_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO22_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */
#define PIO23_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO23_FUNC_ALT3               0x03u   /*!< Selects pin function.: Alternative connection 3. */
#define PIO24_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO24_FUNC_ALT3               0x03u   /*!< Selects pin function.: Alternative connection 3. */
#define PIO25_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO25_FUNC_ALT3               0x03u   /*!< Selects pin function.: Alternative connection 3. */
#define PIO26_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO26_FUNC_ALT3               0x03u   /*!< Selects pin function.: Alternative connection 3. */
#define PIO32_DIGIMODE_DIGITAL        0x01u   /*!< Select Analog/Digital mode.: Digital mode. */
#define PIO32_FUNC_ALT0               0x00u   /*!< Selects pin function.: Alternative connection 0. */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitZigbeePins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: C3, peripheral: GPIO, signal: 'PIO2, 2', pin_signal: PIO2_2/ENET_CRS/FC3_SSEL3/SCT0_OUT6/CTIMER1_MAT1}
  - {pin_num: B1, peripheral: FLEXCOMM1, signal: RXD_SDA_MOSI, pin_signal: PIO2_3/ENET_TXD2/SD_CLK/FC1_RXD_SDA_MOSI/CTIMER2_MAT0}
  - {pin_num: D3, peripheral: FLEXCOMM1, signal: TXD_SCL_MISO, pin_signal: PIO2_4/ENET_TXD3/SD_CMD/FC1_TXD_SCL_MISO/CTIMER2_MAT1}
  - {pin_num: C1, peripheral: FLEXCOMM1, signal: CTS_SDA_SSEL0, pin_signal: PIO2_5/ENET_TX_ER/SD_POW_EN/FC1_CTS_SDA_SSEL0/CTIMER1_MAT2}
  - {pin_num: F3, peripheral: FLEXCOMM1, signal: RTS_SCL_SSEL1, pin_signal: PIO2_6/ENET_TX_CLK/SD_D(0)/FC1_RTS_SCL_SSEL1/CTIMER0_CAP0}
  - {pin_num: P1, peripheral: GPIO, signal: 'PIO2, 10', pin_signal: PIO2_10/ENET_RX_ER/SD_CARD_DET_N}
  - {pin_num: C10, peripheral: GPIO, signal: 'PIO3, 2', pin_signal: PIO3_2/LCD_VD(16)/FC9_RXD_SDA_MOSI/CTIMER1_MAT2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitZigbeePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitZigbeePins(void) { /* Function assigned for the Core #0 (ARM Cortex-M4) */
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  IOCON->PIO[2][10] = ((IOCON->PIO[2][10] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO210_FUNC_ALT0)                     /* Selects pin function.: PORT210 (pin P1) is configured as PIO2_10 */
      | IOCON_PIO_DIGIMODE(PIO210_DIGIMODE_DIGITAL)          /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][2] = ((IOCON->PIO[2][2] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO22_FUNC_ALT0)                      /* Selects pin function.: PORT22 (pin C3) is configured as PIO2_2 */
      | IOCON_PIO_DIGIMODE(PIO22_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][3] = ((IOCON->PIO[2][3] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO23_FUNC_ALT3)                      /* Selects pin function.: PORT23 (pin B1) is configured as FC1_RXD_SDA_MOSI */
      | IOCON_PIO_DIGIMODE(PIO23_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][4] = ((IOCON->PIO[2][4] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO24_FUNC_ALT3)                      /* Selects pin function.: PORT24 (pin D3) is configured as FC1_TXD_SCL_MISO */
      | IOCON_PIO_DIGIMODE(PIO24_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][5] = ((IOCON->PIO[2][5] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO25_FUNC_ALT3)                      /* Selects pin function.: PORT25 (pin C1) is configured as FC1_CTS_SDA_SSEL0 */
      | IOCON_PIO_DIGIMODE(PIO25_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[2][6] = ((IOCON->PIO[2][6] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO26_FUNC_ALT3)                      /* Selects pin function.: PORT26 (pin F3) is configured as FC1_RTS_SCL_SSEL1 */
      | IOCON_PIO_DIGIMODE(PIO26_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
  IOCON->PIO[3][2] = ((IOCON->PIO[3][2] &
    (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))      /* Mask bits to zero which are setting */
      | IOCON_PIO_FUNC(PIO32_FUNC_ALT0)                      /* Selects pin function.: PORT32 (pin C10) is configured as PIO3_2 */
      | IOCON_PIO_DIGIMODE(PIO32_DIGIMODE_DIGITAL)           /* Select Analog/Digital mode.: Digital mode. */
    );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
