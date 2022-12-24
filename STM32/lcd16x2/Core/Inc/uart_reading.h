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

#define MAX_BUFFER_SIZE 30

#define IDLE 0
#define CMD_WAITING 1
#define CMD_READ_R 2
#define CMD_READ_C 3
//#define CMD_WAITING_O 2
//#define CMD_WAITING_OK 3
//#define CMD_WAITING_R 4
//#define CMD_WAITING_RS 5
//#define CMD_WAITING_RST 6

#define isRST 7
#define isCAP 8
#define AUTO 9

extern uint8_t buffer_byte;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern int index_buffer;
extern int buffer_flag;


void cmd_parser_fsm();

void uart_control_fsm();

void Scan_Addr();

#endif /* INC_UART_READING_H_ */
