#include "keyboard_aw95238.h"
#include "remoter_keypad.h"
#include "board.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"


extern keyboard_handle_t *button_handle;

status_t aw95238_i2c_read(uint8_t reg, uint8_t *data)
{
  status_t status;
  i2c_master_transfer_t *xfer = &(button_handle->xfer);
  memset(xfer, 0, sizeof(*xfer));

  xfer->slaveAddress = KEYBOARD_I2C_ADDRESS;
  xfer->direction = kI2C_Read;
  xfer->subaddress = reg;
  xfer->subaddressSize = 1;
  xfer->data = data;
  xfer->dataSize = 1;
  xfer->flags = kI2C_TransferDefaultFlag;

  status = I2C_MasterTransferBlocking(KEY_I2C_MASTER, xfer);
  if(status < 0)
    PRINTF("%s: I2C read failed...\r\n", __func__);

  return status;
}


status_t aw95238_i2c_write(uint8_t reg, uint8_t data)
{
  status_t status = 0;
  i2c_master_transfer_t *xfer = &(button_handle->xfer);
  memset(xfer, 0, sizeof(*xfer));

  xfer->slaveAddress = KEYBOARD_I2C_ADDRESS;
  xfer->direction = kI2C_Write;
  xfer->subaddress = reg;
  xfer->subaddressSize = 1;
  xfer->data = &data;
  xfer->dataSize = 1;
  xfer->flags = kI2C_TransferDefaultFlag;

  status = I2C_MasterTransferBlocking(KEY_I2C_MASTER, xfer);
  if(status < 0)
    PRINTF("%s: I2C write failed...\r\n", __func__);

  return status;
}


status_t AW95238_Init(keyboard_handle_t *handle, I2C_Type *base)
{
//    i2c_master_transfer_t *xfer = &(handle->xfer);
    status_t status = 0;
//    uint8_t mode;
    uint8_t val;

    assert(handle);
    assert(base);
    if (!handle || !base)
    {
        return kStatus_InvalidArgument;
    }
    handle->base = base;

  /*READ ID
  * this register is read only,and its value must be 0x23H
  */
  aw95238_i2c_read(AW95238_ID, &val);
  PRINTF("Read the keyboard ic id is 0x%x successfully\r\n", val);
  if(val != 0x23)
  {
    PRINTF("the id must be 0x23...\r\n");
    return -1;
  }


  /*config the port0&1 output or input
  * each bit: 1-input 0-output
  */
  aw95238_i2c_write(CONFIG_PORT0, 0x38);
  aw95238_i2c_write(CONFIG_PORT1, 0x00);

  /*config port0&1 output state*/
  aw95238_i2c_write(OUTPUT_PORT0, 0xC7);
  aw95238_i2c_write(OUTPUT_PORT1, 0x00);

  /*config for led mode*/
  aw95238_i2c_write(LED_MODE_PORT0, 0xFC);
  aw95238_i2c_write(LED_MODE_PORT1, 0xFC);

  /*set the led output under the Imax*/
  aw95238_i2c_write(LED_DIM_PORT1_1, 0x80);
  aw95238_i2c_write(LED_DIM_PORT1_0, 0x80);
  aw95238_i2c_write(LED_DIM_PORT0_1, 0x80);
  aw95238_i2c_write(LED_DIM_PORT0_0, 0x80);

  /*enable the interrupts of the aw95238
  * each bit: 0-enable 1-disable
  * only read port0 or port1 can clear corresponding interrupts
  * disable the interrupts of port1
  * enable the interrupts of port0 for bit 3,4,5
  */
  aw95238_i2c_write(INT_PORT0, 0xC7);
  aw95238_i2c_write(INT_PORT1, 0xFF);


  /* attach 12 MHz clock to FLEXCOMM6 (I2C master) */
  CLOCK_AttachClk(kFRO12M_to_FLEXCOMM6);

//  /* attach 12 MHz clock to FLEXCOMM8 (I2C slave) */
//  CLOCK_AttachClk(kFRO12M_to_FLEXCOMM8);

    return status;
}


int confirm_row(uint8_t column)
{
	uint8_t column_tmp;
  /*low the row line in order
  *OUTPUT_PORT1 0X03:1111 1111 0xFF
  *1111 0111 row 1 = 0xF7
  *1110 1111 row 2 = 0xEF
  *1101 1111 row 3 = 0xDF
  *1011 1111 row 4 = 0xBF
  *
  *pull the row line in order
  *OUTPUT_PORT1 0X03:0000 0000 0x00
  *0000 1000 row 1 = 0x08
  *0001 0000 row 2 = 0x10
  *0010 0000 row 3 = 0x20
  *0100 0000 row 4 = 0x40
  **/
	aw95238_i2c_write(OUTPUT_PORT1, 0x08);
	aw95238_i2c_read(INPUT_PORT0, &column_tmp);
	if( column_tmp != column){
		PRINTF("second read column_tmp is 0x%x\n", column_tmp);
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);
		return 1;
	}else
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);

	aw95238_i2c_write(OUTPUT_PORT1, 0x10);
	aw95238_i2c_read(INPUT_PORT0, &column_tmp);
	if( column_tmp != column){
		PRINTF("second read column_tmp is 0x%x\n", column_tmp);
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);
		return 2;
	}else
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);

	aw95238_i2c_write(OUTPUT_PORT1, 0x20);
	aw95238_i2c_read(INPUT_PORT0, &column_tmp);
	if( column_tmp != column){
		PRINTF("second read column_tmp is 0x%x\n", column_tmp);
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);
		return 3;
	}else
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);

	aw95238_i2c_write(OUTPUT_PORT1, 0x40);
	aw95238_i2c_read(INPUT_PORT0, &column_tmp);
	if( column_tmp != column){
		PRINTF("second read column_tmp is 0x%x\n", column_tmp);
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);
		return 4;
	}else
		aw95238_i2c_write(OUTPUT_PORT1, 0x00);

    return 0;
}

status_t AW95238_GetSingleButton(keyboard_handle_t *handle)
{
  status_t status = 0;
  uint8_t column;
  int row;

//	aw95238_i2c_read(INPUT_PORT0, &column);
//	PRINTF("column is 0x%x\n", column);

    if(aw95238_i2c_read(INPUT_PORT0, &column) != 0xFF)//11XX X111
    {
#if 0
      switch (column)
      {
//        case 0xF7:/*1111 0111,第1列*/
      case 0x18:
          row = confirm_row(column);
          if(row == 0)
            break;
          else
            PRINTF("the key is row = %d, column = 1\n", row);
          break;
//        case 0xEF:/*1110 1111,第2列*/
      case 0x28:
          row = confirm_row(column);
          if(row == 0)
            break;
          else
            PRINTF("the key is row = %d, column = 2\n", row);
          break;
//        case 0xDF:/*1101 1111,第3列*/
      case 0x38:
          row = confirm_row(column);
          if(row == 0)
            break;
          else
            PRINTF("the key is row = %d, column = 3\n", row);
          break;
        default:
          break;
      }
#else
	row = confirm_row(column);
	if(row == 0)
		PRINTF("wrong key happened\n");
	else
		PRINTF("the key is row = %d, column = 0x%x\n", row, column);
#endif
    }

  return status;
}
