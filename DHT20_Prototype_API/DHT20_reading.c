/*
 * DHT20_reading.c
 *
 *  Created on: Nov 21, 2022
 *      Author: acer
 */

#include "DHT20_reading.h"

#define SLAVE_ADDRESS_DHT20 (0x34) // change later

extern I2C_HandleTypeDef hi2c1;


uint8_t buffer_byte = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
int dht20_flag = 0;

void DHT20_READING_CALLBACK(){
	HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDRESS_DHT20, *buffer_byte, 1, 100);
	buffer[index_buffer++] = buffer_byte;
	if (index_buffer == MAX_BUFFER_SIZE) index_buffer = 0;
	if (buffer_byte != '-'){
		dht20_flag = 1; // assume that when no value is read, dht20 sends '-' instead
		index_buffer = 0;
	}
}

void DHT20_DATA_PROCESS(){
	// here i assume that we will receive the temp first than the humid come after
	// they will be separated by a space char for instance
	if (dht20_flag == 1){
		uint8_t temp1[MAX_BUFFER_SIZE];
		uint8_t temp2[MAX_BUFFER_SIZE];
		for (int i=0; i<MAX_BUFFER_SIZE; i++){
			while (buffer[i] != ' ' && buffer[i] != '-'){
				temp1[i] = buffer[i];
			}
			continue;
			while (buffer[i] != ' ' && buffer[i] != '-'){
				temp2[i] = buffer[i];
			}
		}
		temperature = atoi(temp1);
		humidity = atoi(temp2);
	}
}
