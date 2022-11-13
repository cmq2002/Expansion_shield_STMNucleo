/*
 * app_i2c.c
 *
 *  Created on: Dec 14, 2019
 *      Author: VAIO
 */

#include "main.h"


#define I2C_ADDRESS        0x30F

/* I2C SPEEDCLOCK define to max value: 400 KHz on STM32F1xx*/
#define I2C_SPEEDCLOCK   400000
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;


void I2C_Init(void){
	/*##-1- Configure the I2C peripheral ######################################*/
	  I2cHandle.Instance             = I2C1;
	  I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;
	  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;
	  I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
	  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	  I2cHandle.Init.OwnAddress2     = 0xFF;
	  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

	  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }
}


