/*
 * uart_reading.h
 *
 *  Created on: Dec 22, 2022
 *      Author: acer
 */

#ifndef INC_UART_READING_H_
#define INC_UART_READING_H_

#include <string.h>
#include <stdio.h>
#include "main.h"
#include "dht20.h"
#include "i2c-lcd.h"
#include "software_timer.h"

#define INIT_UART 0

#define READING 1

#define STOP 2

#define isRST 7

#define isCAP 8

#define AUTO 9

#define WAIT 10

#define MAX_BUFFER_SIZE 50

#define MAX_CMD_SIZE 3

extern uint8_t buffer_byte;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

void cmd_parser_fsm();

void uart_control_fsm();

void Scan_Addr();

#endif /* INC_UART_READING_H_ */
