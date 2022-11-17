/*
 * software_timer.c
 *
 *  Created on: Sep 25, 2022
 *      Author: binch
 */

#include "software_timer.h"
#include "global.h"

#define TIMER_CYCLE	10

int timer0_counter = 0;
int timer0_flag = 0;

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

void setTimer0(int duration) {
	timer0_counter = duration/ TIMER_CYCLE;
	timer0_flag = 0;
}

void setTimer1(int duration){
	timer1_counter = duration/ TIMER_CYCLE;
	timer1_flag = 0;
}

void setTimer2(int duration){
	timer2_counter = duration/ TIMER_CYCLE;
	timer2_flag = 0;
}
void timerRun(){
	if(timer0_counter > 0){
			timer0_counter--;
			if(timer0_counter <= 0){
				timer0_flag = 1;
			}
		}

	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}

	if(timer2_counter > 0){
				timer2_counter--;
				if(timer2_counter <= 0){
					timer2_flag = 1;
				}
			}
}
