/*
 * remoter_powermanage.c
 *
 *  Created on: 2017年8月16日
 *      Author: xuke
 */

#include "remoter_powermanage.h"

pm_handle_t *chg_handle;
pm_handle_t *fg_handle;
TaskHandle_t PM_handler;

adc_config_t adcConfigStruct;
adc_conv_seq_config_t adcConvSeqConfigStruct;

status_t pm_i2c_write(pm_handle_t *handle, uint8_t reg, uint8_t val)
{
    status_t status;
    i2c_master_transfer_t *xfer = &(handle->xfer);

    xfer->direction = kI2C_Write;
    xfer->subaddress = reg;
    xfer->subaddressSize = 1;
    xfer->data = &val;
    xfer->dataSize = 1;
    xfer->flags = kI2C_TransferDefaultFlag;

    status = I2C_MasterTransferBlocking(handle->base, xfer);
    if(status != kStatus_Success)
    	PRINTF("%s I2C Transfer failed\r\n", __func__);

    return status;
}

status_t pm_i2c_read(pm_handle_t *handle, uint8_t reg, uint8_t *data)
{
    status_t status;
    i2c_master_transfer_t *xfer = &(handle->xfer);

    xfer->direction = kI2C_Read;
    xfer->subaddress = reg;
    xfer->subaddressSize = 1;
    xfer->data = data;
    xfer->dataSize = 1;
    xfer->flags = kI2C_TransferDefaultFlag;

    status = I2C_MasterTransferBlocking(handle->base, xfer);
    if(status != kStatus_Success)
    	PRINTF("%s I2C Transfer failed\r\n", __func__);

    return status;
}

status_t pm_update_reg_bits(pm_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t data)
{
	status_t status;
	uint8_t tmp;

	taskENTER_CRITICAL();
	status = pm_i2c_read(handle, reg, &tmp);
	if (status != kStatus_Success) {
		PRINTF("Failed: status=%d, reg=%d\n", status, reg);
		goto out;
	}

	tmp &= ~mask;
	tmp |= data & mask;

	status = pm_i2c_write(handle, reg, tmp);
	if (status != kStatus_Success) {
		PRINTF("Failed: reg=%02X, status=%d\n", reg, status);
	}

out:
	taskEXIT_CRITICAL();
	return status;
}

status_t enable_charging(bool on)
{
	if (on)
		return pm_update_reg_bits(chg_handle, CHG_REG01_CTL, REG01_CHG_EN_BIT, 0);
	else
		return pm_update_reg_bits(chg_handle, CHG_REG01_CTL, REG01_CHG_EN_BIT, REG01_CHG_EN_BIT);
}

status_t Toggle_Charger(bool bSwitch)
{
	return enable_charging(bSwitch);
}

status_t set_charging_current(uint32_t current)
{
	/* cause of the battery capacity is 1350mAh
	 * and this charge IC can only set icl to 500 ~ 1500mA
	 * So, we limited current by usb100 or usb500 or AC
	 * */
	if (0 == current) {
		PRINTF("current(%d) it's not useful, please use other API\n", current);
		return kStatus_Fail;
	} else if (current <= SMALL_CHG_CURRENT)
		return pm_update_reg_bits(chg_handle, CHG_REG01_CTL, REG01_IIN_SET_BIT, SET_USB100_VAL);
	else if (current <= MIDDLE_CHG_CURRENT)
		return pm_update_reg_bits(chg_handle, CHG_REG01_CTL, REG01_IIN_SET_BIT, SET_USB500_VAL);
	else
		return pm_update_reg_bits(chg_handle, CHG_REG01_CTL, REG01_IIN_SET_BIT, SET_USB800_VAL);
}

status_t get_charger_ic_id(uint8_t *id)
{
	status_t status;

    assert(chg_handle);
    status = pm_i2c_read(chg_handle, CHG_REG03_VERSION, id);

    return status;
}

uint8_t get_charging_status(void)
{
	//status_t status;
	uint8_t val = 0;
	uint8_t iValue = 0;

	pm_i2c_read(chg_handle, CHG_REG00_STA_CTL, &iValue);

	val = (iValue & REG00_CHG_STATUS) >> CHG_STATUS_OPT;

	//if (CHG_IN_PROGRESS == val)
		PRINTF("%s: reg val is 0x%x\n", __func__, iValue);

	return val;
}

status_t config_enable_pin(void)
{
	gpio_pin_config_t pm_config = {
	    kGPIO_DigitalOutput, 0,
	  };
	/* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
	CLOCK_AttachClk(PM_CLOCK_FLEXCOMM);

	CLOCK_EnableClock(PM_CLOCK_GPIO);

	GPIO_PinInit(GPIO, PM_EN_GPIO_PORT, PM_EN_GPIO_PIN, &pm_config);
	GPIO_WritePinOutput(GPIO, PM_EN_GPIO_PORT, PM_EN_GPIO_PIN, 0);

}

status_t charger_hw_init(void)
{
	status_t status;

    assert(chg_handle);
    status = pm_i2c_write(chg_handle, CHG_REG06_SAFETY, 0x28);
    status = pm_i2c_write(chg_handle, CHG_REG01_CTL, 0x78);
    status = pm_i2c_write(chg_handle, CHG_REG02_CTL_BVR, 0xac);
    status = pm_i2c_write(chg_handle, CHG_REG05_ADPT_IIN, 0x04);

    /* set iterm current */
    status = pm_update_reg_bits(chg_handle, CHG_REG04_CURRENT, REG04_ITRM_REF_BIT, REG04_ITRM_REF_VAL);

    /* enable iterm */
    status = pm_update_reg_bits(chg_handle, CHG_REG01_CTL, REG01_ITRM_EN_BIT, REG01_ITRM_EN_BIT);

    /* enable charging */
    status = enable_charging(true);

    PRINTF("%s: status = %d\n", __func__, status);

    return status;
}

void to_check_pm_registers(pm_handle_t *handler, int max_regs)
{
	int i;
	status_t status;
	uint8_t iValue = 0;

	for (i = 0; i <= max_regs; i++) {
		status = pm_i2c_read(handler, i, &iValue);
		PRINTF("%s: status = %d, iValue(0x0%xh) = 0x%2x\n", __func__, status, i, iValue);
	}
}

status_t Init_Charger(void)
{
	uint8_t ChgId = 0;
	status_t status;
    i2c_master_transfer_t *xfer = &(chg_handle->xfer);

    assert(chg_handle);
    memset(xfer, 0, sizeof(*xfer));
    xfer->slaveAddress = CHG_I2C_MASTER_SLAVE_ADDR_7BIT;

    config_enable_pin();

    status = get_charger_ic_id(&ChgId);
	PRINTF("Chg ID is 0x%x\r\n", ChgId);

	status = charger_hw_init();

	to_check_pm_registers(chg_handle, CHG_MAX_REGS);

	return status;
}

uint32_t get_battery_capacity(void)
{
	status_t status;
	uint8_t soc_high = 0;
	//uint8_t soc_low = 0;
	uint32_t soc;

    assert(fg_handle);
    status = pm_i2c_read(fg_handle, FG_REG04_SOC_HIGH, &soc_high);
    //status |= pm_i2c_read(fg_handle, FG_REG05_SOC_LOW, &soc_low);

    if (status != kStatus_Success) {
    	PRINTF("can't read soc from fg, return default capacity value\n");
    	soc = DEFAULT_BATT_CAPACITY;
    } else {
    	soc = soc_high;
    	PRINTF("high(%d), low(0), soc(%d)\n", soc_high, soc);
    }

    return soc;
}

uint32_t get_battery_voltage(void)
{
	status_t status;
	uint8_t volt_high = 0;
	uint8_t volt_low = 0;
	uint32_t volt;

    assert(fg_handle);
    status = pm_i2c_read(fg_handle, FG_REG02_VOLT_HIGH, &volt_high);
    status |= pm_i2c_read(fg_handle, FG_REG03_VOLT_LOW, &volt_low);

    if (status != kStatus_Success) {
    	PRINTF("can't read VOLT from fg, return default capacity value\n");
    	volt = DEFAULT_BATT_VOLTAGE;
    } else {
    	volt = (((volt_high << 8) + volt_low) * 305) / 1000;
    	PRINTF("high(%d), low(%d), volt(%d)\n", volt_high, volt_low, volt);
    }

    return volt;
}

/* This function is used to set battery parameter to registers
 * */
status_t cw2015_update_battery_info(uint8_t val)
{
	status_t status;
	uint8_t val_mode = 0;
	int i;

    assert(fg_handle);
    status = pm_i2c_read(fg_handle, FG_REG0A_MODE, &val_mode);
    if ((status != kStatus_Success) || (val_mode & REG0A_MODE_SLEEP) == REG0A_MODE_SLEEP) {
    	PRINTF("status is (%d) or mode is sleep now, return\n", status);
    	return kStatus_Fail;
    }

	/* update new battery info */
	for (i = 0; i < SIZE_BATINFO; i++) {
		status = pm_i2c_write(fg_handle, REG_BATINFO + i, config_info[i]);
		if(status != kStatus_Success)
			return status;
	}

	/* set new flag and ATHD */
	val |= REG08_CFG_UFG_BIT;
	val &= 0x07; //clear ATHD
	val |= REG08_CFG_THD_SET; //set new THD
	status = pm_i2c_write(fg_handle, FG_REG08_CONFIG, val);
	if (status != kStatus_Success)
		return status;

	/* restart IC */
	 status = pm_update_reg_bits(fg_handle, FG_REG0A_MODE, REG0A_MODE_RESTART, REG0A_MODE_RESTART);
		if (status != kStatus_Success)
			return status;
	PRINTF("now the mode reg is to set 0x*f\n");
	/* reset to default mode */
		status = pm_update_reg_bits(fg_handle, FG_REG0A_MODE, REG0A_MODE_RESTART, 0);
		if (status != kStatus_Success)
			return status;

	return status;
}

status_t get_fg_ic_id(uint8_t *id)
{
	status_t status;

    assert(fg_handle);
    status = pm_i2c_read(fg_handle, FG_REG00_VERSION, id);

    return status;
}

status_t fg_hw_init(void)
{
	int i;
	status_t status;
	uint8_t val = 0;
	uint8_t cfg_val = 0;

    assert(fg_handle);
    status = pm_update_reg_bits(fg_handle, FG_REG0A_MODE, REG0A_MODE_SLEEP, 0);

    status = pm_i2c_read(fg_handle, FG_REG08_CONFIG, &cfg_val);
    if (!(cfg_val & REG08_CFG_UFG_BIT)) {
    	PRINTF("not contain battery info, need to update battery info\n");
    	status = cw2015_update_battery_info(cfg_val);
    	if (status != kStatus_Success)
    		return status;
    } else {
    	for (i = 0; i < SIZE_BATINFO; i++) {
    		status =  pm_i2c_read(fg_handle, REG_BATINFO + i, &val);
    		if (status != kStatus_Success)
    		    	return status;
    		if (config_info[i] != val)
    			break;
    	}
    	if (i != SIZE_BATINFO) {
    		PRINTF("battery info is not match, need to update battery info\n");
        	status = cw2015_update_battery_info(cfg_val);
        	if (status != kStatus_Success)
        		return status;
    	}
    }

    PRINTF("%s: status = %d\n", __func__, status);

    return status;
}

status_t Init_FG(void)
{
	uint8_t FgId = 0;
	status_t status;
	i2c_master_transfer_t *xfer = &(fg_handle->xfer);

	assert(fg_handle);
	memset(xfer, 0, sizeof(*xfer));
	xfer->slaveAddress = FG_I2C_MASTER_SLAVE_ADDR_7BIT;

	status = get_fg_ic_id(&FgId);
	PRINTF("Fg ID is 0x%x\r\n", FgId);

	status = fg_hw_init();

	to_check_pm_registers(fg_handle, FG_MAX_REGS);

	return status;
}

/* This function is used for transform temperature by ADC.result(voltage)
 * To search result in temp_volt_table with "binary search".
 * */
int calculate_temperature(uint32_t mvolt)
{
	int table_size = sizeof(temp_volt_table)/sizeof(temp_volt_table[0]);
	int high = table_size - 1;
	int low = 0;
	int mid = 0;

	PRINTF("mvolt = %d\n", mvolt);
	if (mvolt >= temp_volt_table[0][1])
		return temp_volt_table[0][0];
	if (mvolt <= temp_volt_table[table_size - 1][1])
		return temp_volt_table[table_size - 1][0];

	/* use binary search */
	while (low < high) {
		//PRINTF("low = %d, high = %d\n", low, high);
		mid = (low + high) / 2;
		if (0 == mid)
			return temp_volt_table[1][0];
		if (mvolt > temp_volt_table[mid][1]) {
			if (mvolt < temp_volt_table[mid - 1][1])
				return temp_volt_table[mid][0];
			high = mid - 1;
		} else if (mvolt < temp_volt_table[mid][1]) {
			if (mvolt >= temp_volt_table[mid + 1][1])
				return temp_volt_table[mid + 1][0];
			low = mid + 1;
		} else
			return temp_volt_table[mid][0];
	}
	PRINTF("transform error\n");
	return DEFAULT_BATT_TEMPERATURE;
}

static void ADC_readChannel(uint32_t number, bool enable)
{
    if (enable == true)
    {
        adcConvSeqConfigStruct.channelMask |= (1 << number);
    }
    else
    {
        adcConvSeqConfigStruct.channelMask &= ~(1 << number);
    }
    ADC_SetConvSeqAConfig(DEMO_ADC_BASE, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(DEMO_ADC_BASE, true);
}

/* This function is used for to get battery temperature by ADC
 * count is used to prevent always in while()
 * */
uint32_t get_battery_temperature(void)
{
	int count = 0;
    adc_result_info_t adcResultInfoStruct;

    /* Measure the temperature sensor */
    ADC_EnableTemperatureSensor(DEMO_ADC_BASE, true);
    ADC_readChannel(DEMO_ADC_SAMPLE_CHANNEL_NUMBER,true);
    /*  trigger the converter by software. */
    ADC_DoSoftwareTriggerConvSeqA(DEMO_ADC_BASE);

    /* Wait for the converter to be done. */
    while (count < 20 && !ADC_GetChannelConversionResult(DEMO_ADC_BASE, DEMO_ADC_SAMPLE_CHANNEL_NUMBER, &adcResultInfoStruct)) {
    	count ++;
    	PRINTF("can not get adc result, count is %d\n", count);
    }
    count = 0;
    PRINTF("adcResultInfoStruct.result        = %d\r\n", adcResultInfoStruct.result);
    //PRINTF("adcResultInfoStruct.channelNumber = %d\r\n", adcResultInfoStruct.channelNumber);
    //PRINTF("adcResultInfoStruct.overrunFlag   = %d\r\n", adcResultInfoStruct.overrunFlag ? 1U : 0U);
    //PRINTF("\r\n");

    if (adcResultInfoStruct.result > 2 && adcResultInfoStruct.result < 4095)
    	return calculate_temperature((adcResultInfoStruct.result *3300) >> 12);
    else
    	return DEFAULT_BATT_TEMPERATURE;
}

/*
 * jeita work is used for to control charging current when the temperature is not normal
 * charging_disabled_flag is expression charging is disabled when it is true.
 * charging_status is expression charging is  in progress or done.
 * */
void jeita_work(uint8_t temperature, uint8_t charging_status)
{
	static bool charging_disabled_flag;
	static bool current_is_limited_now;

	if ((temperature >= 50) && (charging_status == CHG_IN_PROGRESS)) {
		Toggle_Charger(false); //disable charging
		charging_disabled_flag = 1;
	} else if ((temperature >= 45) && (charging_status == CHG_IN_PROGRESS) && (!current_is_limited_now)) {
		set_charging_current(SMALL_CHG_CURRENT);
		current_is_limited_now = true;
	} else if ((temperature <= 48) && charging_disabled_flag) {
		Toggle_Charger(true); // enable charging
		charging_disabled_flag = 0;
	} else if ((temperature < 45) && current_is_limited_now) {
		set_charging_current(BIG_CHG_CURRENT);//set to the common current
		current_is_limited_now = false;
	}
}

void PowerManage_Task(void *pvParameters)
{
	uint8_t charging_status = 0;
	uint32_t capacity, volt;
	uint32_t temperature = DEFAULT_BATT_TEMPERATURE;
	static int last_capacity;
	static uint8_t last_charging_status;
	static int last_temperature  = DEFAULT_BATT_TEMPERATURE;
	static bool msg_changed_flag;
	struct remote_message msg_send = {0};

	PRINTF("%s\n", __func__);

    vTaskDelay(1000);	// xuke @ 20170923	To wait for GUI task running.
	PM_handler = xTaskGetCurrentTaskHandle();
    while(1) {
    	taskENTER_CRITICAL();

    	/* read all status & value */
    	volt = get_battery_voltage();

    	capacity = get_battery_capacity();
		if (capacity != last_capacity) {
			last_capacity = capacity;
			msg_changed_flag = true;
		}

    	charging_status = get_charging_status();
    	if (last_charging_status != charging_status) {
    		msg_changed_flag = true;
    		last_charging_status = charging_status;
    	}

		temperature = get_battery_temperature();
		if (abs(temperature - last_temperature) > 10) {
			last_temperature = temperature;
			msg_changed_flag = true;
		}

		PRINTF("%s, temp is %d, capacity is %d, volt is %d, change_flag is %d\n", __func__, temperature, capacity, volt, msg_changed_flag);

		/* Send status & value to HAL */
		if (msg_changed_flag) {
			msg_send.task_src = TASK_PM;
			msg_send.task_dst = TASK_GUI_SVC;
			msg_send.msg.msg_pm.capacity = last_capacity;
			//msg_send.msg.msg_pm.batt_temperature = last_temperature;
			msg_send.msg.msg_pm.charging_status = charging_status;

			Message_Send(&msg_send);
			msg_changed_flag = false;
			PRINTF("%s, send the change\n", __func__);
		}

		/* Limited charging current by temperature */
		if (CHG_IN_PROGRESS == last_charging_status) {
//			jeita_work(last_temperature, last_charging_status);		// TODO
		}

		taskEXIT_CRITICAL();
		//vTaskDelay(1000);
		//xTimerChangePeriod();
		vTaskSuspend(PM_handler);
    }

}

static void PmSwTimerCallback(TimerHandle_t xTimer)
{
    //PRINTF("%s: resume pm task.\r\n", __func__);
	vTaskResume(PM_handler);
}

static void ADC_ClockPower_Configuration(void)
{
    /* SYSCON power. */
    POWER_DisablePD(kPDRUNCFG_PD_VDDA);    /* Power on VDDA. */
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);    /* Power on the ADC converter. */
    POWER_DisablePD(kPDRUNCFG_PD_VD2_ANA); /* Power on the analog power supply. */
    POWER_DisablePD(kPDRUNCFG_PD_VREFP);   /* Power on the reference voltage source. */
    POWER_DisablePD(kPDRUNCFG_PD_TS);      /* Power on the temperature sensor. */

    /* Enable the clock. */
    //CLOCK_AttachClk(kFRO12M_to_MAIN_CLK);

    /* CLOCK_AttachClk(kMAIN_CLK_to_ADC_CLK); */
    /* Sync clock source is not used. Using sync clock source and would be divided by 2.
     * The divider would be set when configuring the converter.
     */

    CLOCK_EnableClock(kCLOCK_Adc0); /* SYSCON->AHBCLKCTRL[0] |= SYSCON_AHBCLKCTRL_ADC0_MASK; */
}

/*
 * Configure the ADC as normal converter in polling mode.
 */
void ADC_Configuration(void)
{

    /* Configure the converter. */
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */
    adcConfigStruct.clockDividerNumber = 1;                /* The divider for sync clock is 2. */
    adcConfigStruct.resolution = kADC_Resolution12bit;
    adcConfigStruct.enableBypassCalibration = false;
    adcConfigStruct.sampleTimeNumber = 0U;
    ADC_Init(DEMO_ADC_BASE, &adcConfigStruct);

    /* Use the temperature sensor input to channel 0. */
    //ADC_EnableTemperatureSensor(DEMO_ADC_BASE, true);

    /* Enable channel 0's conversion in Sequence A. */
    adcConvSeqConfigStruct.channelMask = (1U << 3); /* Includes channel 0. */
    adcConvSeqConfigStruct.triggerMask = 0U;
    adcConvSeqConfigStruct.triggerPolarity = kADC_TriggerPolarityNegativeEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode = kADC_InterruptForEachSequence;
    ADC_SetConvSeqAConfig(DEMO_ADC_BASE, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(DEMO_ADC_BASE, true); /* Enable the conversion sequence A. */
}

status_t Temp_ADC_Init(void)
{
    /* Enable the power and clock for ADC. */
    ADC_ClockPower_Configuration();

    /* Calibration. */
    if (ADC_DoSelfCalibration(DEMO_ADC_BASE)) {
        PRINTF("ADC_DoSelfCalibration() Done.\r\n");
    } else {
        PRINTF("ADC_DoSelfCalibration() Failed.\r\n");
    }

    ADC_Configuration();

    /* Enable the interrupt. */
    //ADC_EnableInterrupts(DEMO_ADC_BASE, kADC_ConvSeqAInterruptEnable);
    //NVIC_EnableIRQ(DEMO_ADC_IRQ_ID);

    PRINTF("Configuration ADC Done.\r\n");

    return kStatus_Success;
}

status_t PM_I2C_Init(void)
{
    i2c_master_config_t masterConfig;

	/* attach 12 MHz clock to FLEXCOMM? */
	CLOCK_AttachClk(RMT_PM_I2C_FLEXCOMM);

    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = I2C_BAUDRATE;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(I2C_MASTER_BASE, &masterConfig, I2C_MASTER_CLOCK_FREQUENCY);

    /* alloc chg handle */
    chg_handle = ( pm_handle_t * ) pvPortMalloc( sizeof( pm_handle_t ) );
    chg_handle->base = I2C_MASTER_BASE;

    /* alloc fg handle */
    fg_handle = ( pm_handle_t * ) pvPortMalloc( sizeof( pm_handle_t ) );
    fg_handle->base = I2C_MASTER_BASE;

    return kStatus_Success;
}

int PowerManage_Init(void)
{
	status_t status = kStatus_Success;
	TimerHandle_t PmSwTimerHandle = NULL;

	//pin and init
	PRINTF("%s : Enter into PM Init\n", __func__);

	status = PM_I2C_Init();
	if (kStatus_Success != status) {
		PRINTF("%s : Init PM failed\n", __func__);
		goto err;
	}
	PRINTF("%s : Enter into PM Init1\n", __func__);

	status = Init_Charger();
	if (kStatus_Success != status) {
		PRINTF("%s : Init Charger failed\n", __func__);
		//goto err;
	}
	PRINTF("%s : Enter into PM Init2\n", __func__);

	status = Init_FG();
	if (kStatus_Success != status) {
		PRINTF("%s : Init FG failed\n", __func__);
		//goto err;
	}

	status = Temp_ADC_Init();
	if (kStatus_Success != status) {
		PRINTF("%s : Init ADC failed\n", __func__);
		goto err;
	}

    /* Create the software timer for PM */
	PmSwTimerHandle = xTimerCreate("PmTimer",          /* Text name. */
                                 PM_SW_TIMER_PERIOD_MS, /* Timer period. */
                                 pdTRUE,             /* Enable auto reload. */
                                 0,                  /* ID is not used. */
                                 PmSwTimerCallback);   /* The callback function. */
    /* Start timer. */
    xTimerStart(PmSwTimerHandle, 0);

    return 1;
err:
   	return 0;
}
