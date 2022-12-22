/*
 * fsm_automatic.c
 *
 *  Created on: Dec 22, 2022
 *      Author: acer
*/
#include "fsm_automatic.h"

uint16_t value_x10[2] = {0, 0};
char temp[10], humid[10];
int status = INIT;

void init_reading(void){
	dht20_init();
	dht20_read(value_x10);
}

void fsm_run(void){
	switch(status){
		case INIT:
			setTimer1(1);
			status = READ;
			break;
		case READ:
			if (timer1_flag == 1){
				dht20_read(value_x10);
				//11011111 is degree character (manual)
				sprintf(temp," %d.%d%cC",value_x10[1]/10,value_x10[1]%10 ,0b11011111);
				sprintf(humid," %01d.%d%%",value_x10[0]/10,value_x10[0]%10);
				setTimer1(100);
			}
			break;
		default:
			break;
	}
	lcd_show_value();
}
