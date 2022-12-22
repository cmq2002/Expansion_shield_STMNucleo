/*
 * fsm_automatic.h
 *
 *  Created on: Dec 22, 2022
 *      Author: acer
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include <stdio.h>
#include "i2c-lcd.h"
#include "dht20.h"
#include "software_timer.h"

#define INIT 0
#define READ 1

extern uint16_t value_x10[2];
extern char temp[10],humid[10];

void init_reading(void);

void fsm_run(void);

#endif /* INC_FSM_AUTOMATIC_H_ */
