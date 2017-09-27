/*
 * remoter_powermanage.h
 *
 *  Created on: 2017年8月16日
 *      Author: xuke
 */

#ifndef REMOTER_POWERMANAGE_H_
#define REMOTER_POWERMANAGE_H_

#include "remoter_base.h"
#include "fsl_i2c.h"
#include "fsl_adc.h"
#include "fsl_power.h"
#include "timers.h"
#include <stdlib.h>
#include <math.h>
#include "remoter_message.h"
#include "remoter_main.h"

#define I2C_MASTER_BASE RMT_PM_I2C_BASE
#define I2C_MASTER_CLOCK_FREQUENCY RMT_PM_I2C_CLK_FREQ
#define CHG_I2C_MASTER_SLAVE_ADDR_7BIT RMT_PM_I2C_CHG_SLAVE_ADDR
#define FG_I2C_MASTER_SLAVE_ADDR_7BIT RMT_PM_I2C_FG_SLAVE_ADDR
#define I2C_BAUDRATE RMT_PM_I2C_BAUDRATE

#define PM_CLOCK_FLEXCOMM		RMT_PM_CLOCK_FLEXCOMM
#define PM_CLOCK_GPIO			RMT_PM_CLOCK_GPIO
#define PM_EN_GPIO_PORT			RMT_PM_EN_GPIO_PORT
#define PM_EN_GPIO_PIN			RMT_PM_EN_GPIO_PIN

#define BIT(nr) 	(1<<(nr))
#define _PM_MASK(BITS, POS) \
		((unsigned char)(((1 << (BITS)) - 1) << (POS)))
#define PM_MASK(LEFT, RIGHT) \
		_PM_MASK((LEFT) - (RIGHT) + 1, RIGHT)

#define CHG_TASK_PRIO		configMAX_PRIORITIES - 3
#define CHG_STK_SIZE 		configMINIMAL_STACK_SIZE + 110
#define FG_TASK_PRIO		configMAX_PRIORITIES - 3
#define FG_STK_SIZE 		configMINIMAL_STACK_SIZE + 110

#define PM_SW_TIMER_PERIOD_MS (9000U/portTICK_PERIOD_MS)

/* Charger */
#define SMALL_CHG_CURRENT 		100U
#define MIDDLE_CHG_CURRENT 		500U
#define BIG_CHG_CURRENT 		800U

#define CHG_MAX_REGS 			6U

#define CHG_REG00_STA_CTL 		0x00
#define CHG_REG01_CTL 			0x01
#define CHG_REG02_CTL_BVR 		0x02
#define CHG_REG03_VERSION 		0x03
#define CHG_REG04_CURRENT 		0x04
#define CHG_REG05_ADPT_IIN 		0x05
#define CHG_REG06_SAFETY 		0x06

#define REG00_OTG_STATUS 		BIT(7)
#define REG00_CHG_STATUS 		PM_MASK(5,4)
#define REG00_CHG_FAULT 		PM_MASK(2,0)
#define CHG_STATUS_OPT 			4U

#define REG01_IIN_SET_BIT 		PM_MASK(7,6)
#define REG01_ITRM_EN_BIT 		BIT(3)
#define REG01_CHG_EN_BIT 		BIT(2)
#define SET_USB100_VAL 			0U
#define SET_USB500_VAL 			1U
#define SET_USB800_VAL 			2U

#define REG04_CHG_RESET 		BIT(7)
#define REG04_ICHG_REF_BIT 		PM_MASK(6,4)
#define REG04_ITRM_REF_BIT 		PM_MASK(2,0)
#define REG04_ITRM_REF_VAL 		2U

#define REG06_MAX_CHG_CURRENT 	PM_MASK(7,4)
#define REG06_MAX_CHG_VLT 		PM_MASK(3,0)
#define REG06_MAX_CURRENT_VAL 	2U //(A = (37.4+6.8n)/R, so n=(AR-37.4)/6.8 )
#define REG06_MAX_VLT_VAL 		8U //((4350 + 20 - 1 - 4200)/20)
/* eof Charger */

/* FG */
#define FG_MAX_REGS 			0x0A

#define FG_REG00_VERSION 		0x00
//#define FG_REG01_CTL 			0x01
#define FG_REG02_VOLT_HIGH 		0x02
#define FG_REG03_VOLT_LOW 		0x03
#define FG_REG04_SOC_HIGH 		0x04
#define FG_REG05_SOC_LOW 		0x05
#define FG_REG06_ALRT_HIGH 		0x06
#define FG_REG07_ALRT_LOW 		0x07
#define FG_REG08_CONFIG 		0x08
#define FG_REG0A_MODE 			0x0A
#define REG_BATINFO 			0x10

#define REG08_CFG_UFG_BIT 		BIT(1)
#define REG08_CFG_THD_BITS 		PM_MASK(7,3)
#define REG08_CFG_THD_SET 		1U

#define REG0A_MODE_SLEEP 		PM_MASK(7,6)
#define REG0A_MODE_RESTART 		PM_MASK(3,0)


#define REG00_OTG_STATUS1 		BIT(7)
#define REG00_CHG_STATUS1 		PM_MASK(5,4)
#define REG00_CHG_FAULT1 		PM_MASK(2,0)
#define CHG_STATUS_OPT1 			4U

#define SIZE_BATINFO    64
static unsigned char config_info[SIZE_BATINFO] = {
	0x16, 0xF0, 0x69, 0x68, 0x65, 0x62, 0x60, 0x58,
	0x69, 0x51, 0x57, 0x5A, 0x51, 0x44, 0x3D, 0x33,
	0x2E, 0x25, 0x20, 0x1D, 0x26, 0x33, 0x43, 0x48,
	0x17, 0x5C, 0x0B, 0x85, 0x29, 0x49, 0x59, 0x65,
	0x7A, 0x78, 0x72, 0x77, 0x43, 0x1C, 0x5F, 0x39,
	0x18, 0x3A, 0x52, 0x87, 0x8F, 0x91, 0x94, 0x52,
	0x82, 0x8C, 0x92, 0x96, 0xFF, 0x93, 0xB3, 0xCB,
	0x2F, 0x7D, 0x72, 0xA5, 0xB5, 0xC1, 0x2C, 0xCB,
};
/* eof FG */

/* ADC */
#define DEMO_ADC_BASE RMT_PM_ADC_BASE
#define DEMO_ADC_SAMPLE_CHANNEL_NUMBER RMT_PM_ADC_SAMPLE_CHANNEL

static adc_result_info_t gAdcResultInfoStruct;
adc_result_info_t *volatile gAdcResultInfoPtr = &gAdcResultInfoStruct;
volatile bool gAdcConvSeqAIntFlag;

int temp_volt_table[][2] =
{
		{-20, 2878},
		{-19, 2859},
		{-18, 2841},
		{-17, 2821},
		{-16, 2801},
		{-15, 2781},
		{-14, 2760},
		{-13, 2739},
		{-12, 2717},
		{-11, 2694},
		{-10, 2671},
		{-9 , 2647},
		{-8 , 2623},
		{-7 , 2598},
		{-6 , 2573},
		{-5 , 2548},
		{-4 , 2522},
		{-3 , 2495},
		{-2 , 2468},
		{-1 , 2441},
		{0  , 2413},
		{1  , 2385},
		{2  , 2356},
		{3  , 2328},
		{4 , 2298},
		{5  , 2269},
		{6  , 2239},
		{7  , 2209},
		{8  , 2179},
		{9  , 2148},
		{10 , 2118},
		{11 , 2087},
		{12 , 2056},
		{13 , 2025},
		{14 , 1993},
		{15 , 1962},
		{16 , 1931},
		{17 , 1899},
		{18 , 1868},
		{19 , 1836},
		{20 , 1805},
		{21 , 1774},
		{22 , 1743},
		{23 , 1711},
		{24 , 1680},
		{25 , 1650},
		{26 , 1619},
		{27 , 1588},
		{28 , 1558},
		{29 , 1528},
		{30 , 1498},
		{31 , 1468},
		{32 , 1439},
		{33 , 1410},
		{34 , 1381},
		{35 , 1352},
		{36 , 1324},
		{37 , 1296},
		{38 , 1269},
		{39 , 1242},
		{40 , 1215},
		{41 , 1189},
		{42 , 1163},
		{43, 1137},
		{44, 1112},
		{45, 1087},
		{46, 1063},
		{47 , 1039},
		{48 , 1015},
		{49 , 992 },
		{50 , 969 },
		{51 , 947 },
		{52 , 925 },
		{53 , 903 },
		{54 , 882 },
		{55 , 861 },
		{56 , 841 },
		{57 , 821 },
		{58 , 802 },
		{59 , 783 },
		{60 , 764 },
		{61 , 746 },
		{62 , 728 },
		{63 , 711 },
		{64 , 694 },
		{65 , 678 },
		{66 , 661 },
		{67 , 646 },
		{68 , 630 },
		{69 , 615 },
		{70 , 601 },
		{71 , 586 },
		{72 , 572 },
		{73 , 559 },
		{74 , 545 },
		{75 , 532 },
		{76 , 519 },
		{77 , 507 },
		{78 , 495 },
		{79 , 483 },
		{80 , 471 },
};
/* eof ADC */

/* For Tasks */
#define DEFAULT_BATT_TEMPERATURE 	240U
#define DEFAULT_BATT_CAPACITY 		50U
#define DEFAULT_BATT_VOLTAGE 		3700U
#define TEMP_HIGH_DELAY_MS 			2000U
#define TEMP_COMMCOM_DELAY_MS 		4000U

typedef struct _pm_handle {
    I2C_Type *base;
    i2c_master_transfer_t xfer;
} pm_handle_t;
/* eof Tasks */

enum charging_status {
	CHG_READY,
	CHG_IN_PROGRESS,
	CHG_DONE,
	CHG_FAULT,
	MAX_CHGING_STATUS,
};

#endif /* REMOTER_POWERMANAGE_H_ */
