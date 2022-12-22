/*
 * dht20.h
 *
 *  Created on: Dec 22, 2022
 *      Author: acer
 */

#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include <stdio.h>
#include "main.h"
#include "i2c-lcd.h"
#include "software_timer.h"

#define INIT 0
#define READ 1

extern uint16_t value_x10[2];
extern char temp[20],humid[20];

void dht20_init(void);

void dht20_reset(uint8_t);

void dht20_read(uint16_t*);

void dht20_start(void);

void init_reading(void);

void fsm_run(void);

#endif /* INC_DHT20_H_ */
