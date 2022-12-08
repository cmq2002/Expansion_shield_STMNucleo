/*
 * DHT20_reading.h
 *
 *  Created on: Nov 21, 2022
 *      Author: acer
 */

#ifndef INC_DHT20_READING_H_
#define INC_DHT20_READING_H_

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 30
#define SPACE ' '

extern uint8_t buffer_byte;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern int dht20_flag;

extern int temperature;
extern int humidity;

void DHT20_READING_CALLBACK();

void DHT20_DATA_PROCESSING();
// This function will take out value from the buffer
// Make it ready for display on the lcd

#endif /* INC_DHT20_READING_H_ */
