/*
 * app_i2c_lcd.h
 *
 *  Created on: Nov 13, 2022
 *      Author: acer
 */

#ifndef INC_APP_I2C_LCD_H_
#define INC_APP_I2C_LCD_H_

#include "main.h"

void Lcd_Initialization (void);

void Lcd_Send_Cmd (char cmd);

void Lcd_Send_Data (char data);

void Lcd_Send_String (char *str);

void Lcd_Clear_Display (void);

void Lcd_Goto_XY (int row, int col);

#endif /* INC_APP_I2C_LCD_H_ */
