
#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx_hal.h"
#include "dht20.h"

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear_display (void);	//clear display lcd

void lcd_goto_XY (int row, int col); //set proper location on screen

void lcd_greeting (void);

void lcd_show_value(void);
#endif /* INC_DHT20_H_ */
