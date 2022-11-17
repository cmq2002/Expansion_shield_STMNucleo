/*
 * fsm_manual.c
 *
 *  Created on: Oct 12, 2022
 *      Author: binch
 */

#include "fsm_manual.h"

void fsm_manual_run(){
	switch (status){
	case MAN_RED:
		//TODO
		HAL_GPIO_TogglePin(LED3_00_GPIO_Port, LED3_00_Pin);
		if(timer1_flag == 1){
			timer1_flag = 0;
			status = AUTO_RED;
			setTimer1(5000);
		}
		break;
	case MAN_YELLOW:
		//TODO
		break;
	case MAN_GREEN:
		break;
	}
}

