/*
 * remoter_touchpanel.h
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#ifndef REMOTER_TOUCHPANEL_H_
#define REMOTER_TOUCHPANEL_H_

#include "remoter_base.h"
#include "fsl_i2c.h"
#include "fsl_touch_ft5406.h"

#define TP_I2C_MASTER		RMT_TP_I2C_BASE
#define TP_I2C_MASTER_CLOCK_FREQUENCY		RMT_TP_I2C_CLK_FREQ
#define TP_I2C_MASTER_SLAVE_ADDR_7BIT		RMT_TP_I2C_CHG_SLAVE_ADDR
#define TP_I2C_BAUDRATE		RMT_TP_I2C_BAUDRATE

#define TP_CLOCK_GPIO		RMT_TP_CLOCK_GPIO
#define TP_CLOCK_FLEXCOMM		RMT_TP_CLOCK_FLEXCOMM

#define TP_RESET_GPIO_PORT		RMT_TP_RESET_GPIO_PORT
#define TP_RESET_GPIO_PIN		RMT_TP_RESET_GPIO_PIN

#endif /* REMOTER_TOUCHPANEL_H_ */
