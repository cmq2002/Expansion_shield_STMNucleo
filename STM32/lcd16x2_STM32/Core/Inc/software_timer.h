/*
 * software_timer.h
 *
 *  Created on: Sep 25, 2022
 *      Author: binch
 */
#include "main.h"
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;

void setTimer0(int);
void setTimer1(int);
void setTimer2(int);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
