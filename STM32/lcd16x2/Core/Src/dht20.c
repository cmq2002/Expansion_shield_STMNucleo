/*
 * dht20.c
 *
 *  Created on: Dec 21, 2022
 *      Author: binch
 */
#include "main.h"
#include "dht20.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

#define SLAVE_ADDRESS_DHT20 (0x38 << 1)

void dht20_init(void){
	uint8_t init[3];

	init[0] = 0xA8;
	init[1] = 0x00;
	init[2] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_DHT20, (uint8_t*) init, 3, 0xFF);

	HAL_Delay(10);

	init[0] = 0xBE;
	init[1] = 0x08;
	init[2] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_DHT20, (uint8_t*) init, 3, 0xFF);
	HAL_Delay(10);
}

void dht20_reset(uint8_t regis){
	//reset register

	uint8_t reset[3], reply[3];
	reset[0] = regis;
	reset[1] = 0x00;
	reset[2] = 0x00;
 	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_DHT20, (uint8_t*) reset, 3, 0xFF);
	HAL_Delay(10);

	HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDRESS_DHT20 | 0x01, (uint8_t*) reply, 3, 0xFF);
	reset[0] = 0xB0 | regis;
	reset[1] = reply[1];
	reset[2] = reply[2];
	HAL_Delay(10);

	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_DHT20, (uint8_t*) reset, 3, 0xFF);
}
void dht20_start(void){
	uint8_t status[1];
	HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDRESS_DHT20 | 0x01, (uint8_t*) status, 1, 0xFF);
	if((status[0] & 0x18) != 0x18){
		dht20_reset(0x1B);
		dht20_reset(0x1C);
		dht20_reset(0x1E);
	}

	if ((status[0] & 0x18) == 0x18){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
	}


	uint8_t trigger[1] = {0xAC};
	uint8_t data[2];
	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_DHT20, (uint8_t*) trigger, 1, 0xFF);
	HAL_Delay(80);
	data[0] = 0x33;
	data[1] = 0x00;

	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_DHT20, (uint8_t*) data, 2, 0xFF);
}

void dht20_read(uint32_t* value){
	uint8_t data[7];
	uint32_t Temper = 0, Humid = 0;
	HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDRESS_DHT20 | 0x01, (uint8_t*) data, 7, 0xFF);
	//Humid
	Humid = (Humid | data[1]) << 8;
	Humid = (Humid | data[2]) << 8;
	Humid = Humid | data[3];
	Humid = Humid >> 4;
	Humid = (Humid * 100 * 10 / 1024 / 1024)/10;
    value[0] = Humid;


	//Temperature
    Temper = (Temper | data[3]) << 8;
    Temper = (Temper | data[4]) << 8;
    Temper = Temper | data[5];
    Temper = Temper & 0xfffff;
    Temper = Temper*200/1024/1024 - 50;
	value[1] = Temper;

}
