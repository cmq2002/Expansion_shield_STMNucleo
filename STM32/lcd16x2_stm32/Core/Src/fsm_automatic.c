/*
 * fsm_automatic.c
 *
 *  Created on: Oct 5, 2022
 *      Author: binch
 */

#include "global.h"
#include "software_timer.h"
#include "fsm_automatic.h"

void fsm_automatic_run() {
	switch (status) {
	case INIT:
		status = AUTO_RED;
		setTimer1(500);
		break;
	case AUTO_RED:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
//		if (timer1_flag == 1) {
//			status = AUTO_GREEN;
//			setTimer1(300);
//		}
		if (button_flag[0] == 1) {
			button_flag[0] = 0;
			status = AUTO_GREEN;
			setTimer1(500);
		}
		if (button_flag[1] == 1) {
			button_flag[1] = 0;
			status = AUTO_YELLOW;
			setTimer1(500);
		}
		break;
	case AUTO_GREEN:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
		if (timer1_flag == 1) {
			status = AUTO_YELLOW;
			setTimer1(200);
		}
		if (button_flag[0] == 1) {
			button_flag[0] = 0;
			status = AUTO_YELLOW;
			setTimer1(5000);
		}
		if (button_flag[1] == 1) {
			button_flag[1] = 0;
			status = AUTO_RED;
			setTimer1(500);
		}
		break;
	case AUTO_YELLOW:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		if (timer1_flag == 1) {
			status = AUTO_RED;
			setTimer1(500);
		}
		if (button_flag[0] == 1) {
			button_flag[0] = 0;
			status = AUTO_RED;
			setTimer1(5000);
		}
		if (button_flag[1] == 1) {
			button_flag[1] = 0;
			status = AUTO_GREEN;
			setTimer1(500);
		}
		break;
	}
}

