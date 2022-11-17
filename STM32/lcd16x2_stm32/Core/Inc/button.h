/*
 * button.h
 *
 *  Created on: Oct 12, 2022
 *      Author: binch
 */



#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#define NO_OF_BUTTON 	3

#define NORMAL_STATE SET
#define PRESSED_STATE RESET


extern int button_flag[NO_OF_BUTTON];

void getKeyInput(uint16_t);

#endif /* INC_BUTTON_H_ */
