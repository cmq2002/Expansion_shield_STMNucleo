///*
// * button.c
// *
// *  Created on: Oct 12, 2022
// *      Author: binch
// */
//

#include "button.h"
int KeyReg0[NO_OF_BUTTON] = {[0 ... NO_OF_BUTTON -1] = NORMAL_STATE};
int KeyReg1[NO_OF_BUTTON] = {[0 ... NO_OF_BUTTON -1] = NORMAL_STATE};
int KeyReg2[NO_OF_BUTTON] = {[0 ... NO_OF_BUTTON -1] = NORMAL_STATE};
int KeyReg3[NO_OF_BUTTON] = {[0 ... NO_OF_BUTTON -1] = NORMAL_STATE};

int TimeOutForKeyPress[NO_OF_BUTTON] =  { [0 ... NO_OF_BUTTON -1] = 500};
int button_flag[NO_OF_BUTTON] = { [0 ... NO_OF_BUTTON -1] = 0};


void subKeyProcess(int i){
	//TODO
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
	button_flag[i] = 1;
}

void getKeyInput(uint16_t i){
  KeyReg2[i] = KeyReg1[i];
  KeyReg1[i] = KeyReg0[i];
  if (i == 0){
	  KeyReg0[i] = HAL_GPIO_ReadPin(Button0_GPIO_Port, Button0_Pin);
  }
  else if (i == 1){
	  KeyReg0[i] = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
  }
  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
    if (KeyReg2[i] != KeyReg3[i]){
      KeyReg3[i] = KeyReg2[i];

      if (KeyReg3[i] == PRESSED_STATE){
        TimeOutForKeyPress[i] = 500;
        subKeyProcess(i);
      }
    }else{
       TimeOutForKeyPress[i] --;
        if (TimeOutForKeyPress[i] == 0){
          KeyReg3[i] = NORMAL_STATE;
        }
    }
  }
}

