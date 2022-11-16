/*
 * app_i2c_lcd.c
 *
 *  Created on: Jun 8, 2020
 *      Author: Nguyet
 */


#include <app_i2c_lcd.h>
#include "main.h"
#include <math.h>
extern I2C_HandleTypeDef I2cHandle;;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 				66 // change this according to ur setup

#define PCF8574_SLAVE_ADDRESS 			66 ///< PCF8574 Default I2C Slave Address


#define	LCD_COLUMN 						16
#define	LCD_LINE						2
// commands
#define LCD_CLEARDISPLAY 				0x01
#define LCD_RETURNHOME 					0x02
#define LCD_ENTRYMODESET 				0x04
#define LCD_DISPLAYCONTROL 				0x08
#define LCD_CURSORSHIFT 				0x10
#define LCD_FUNCTIONSET 				0x20
#define LCD_SETCGRAMADDR 				0x40
#define LCD_SETDDRAMADDR 				0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 					0x00
#define LCD_ENTRYLEFT 					0x02
#define LCD_ENTRYSHIFTINCREMENT 		0x01
#define LCD_ENTRYSHIFTDECREMENT 		0x00

// flags for display on/off control
#define LCD_DISPLAYON 					0x04
#define LCD_DISPLAYOFF 					0x00
#define LCD_CURSORON 					0x02
#define LCD_CURSOROFF 					0x00
#define LCD_BLINKON 					0x01
#define LCD_BLINKOFF 					0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 				0x08
#define LCD_CURSORMOVE 					0x00
#define LCD_MOVERIGHT 					0x04
#define LCD_MOVELEFT 					0x00

// flags for function set
#define LCD_8BITMODE 					0x10
#define LCD_4BITMODE 					0x00
#define LCD_2LINE 						0x08
#define LCD_1LINE 						0x00
#define LCD_5x10DOTS 					0x04
#define LCD_5x8DOTS 					0x00

// pin/port bit
#define DB4  							0b00000001 // P0 : DB4 bit
#define DB5  							0b00000010 // P1 : DB5 bit
#define DB6  							0b00000100 // P2 : DB6 bit
#define DB7  							0b00001000 // P3 : DB7 bit
#define EN 								0b00010000 // P4 : Enable bit
#define RW 								0b00100000 // P5 : R/W bit
#define RS 								0b01000000 // P6 : RS bit
#define BL 								0b10000000 // P7 : BACKLIGHT bit

void FaBoLCD_PCF8574(uint8_t addr);
void init(void);
void begin(uint8_t cols, uint8_t rows, uint8_t charsize);

void clear();
void home();

void noDisplay();
void display();
void noBlink();
void blink();
void noCursor();
void cursor();
void scrollDisplayLeft();
void scrollDisplayRight();
void leftToRight();
void rightToLeft();
void autoscroll();
void noAutoscroll();

void setRowOffsets(int row1, int row2, int row3, int row4);
void createChar(uint8_t, uint8_t[]);
void setCursor(uint8_t, uint8_t);
uint8_t write(uint8_t);
void command(uint8_t);
void send(uint8_t, uint8_t);
void write4bits(uint8_t);
void write8bits(uint8_t);
void pulseEnable(uint8_t);
void writeI2c(uint8_t);

uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;

uint8_t _numlines;
uint8_t _row_offsets[4];

uint8_t _i2caddr;
uint8_t _backlight;


void LCD_Testing(void){

	uint8_t initData[1] = {0xaa};
	HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)66, (uint8_t *) initData, 1, 0xffff);
	HAL_Delay(100);
}

void FaBoLCD_PCF8574(uint8_t addr)
{
  _i2caddr = addr;
  _backlight = BL;
  uint8_t initData[1] = {0x80};
  HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)0x42, (uint8_t *) initData, 1, 0xffff);
  HAL_Delay(100);
  init();
  begin(LCD_COLUMN, LCD_LINE, LCD_5x8DOTS);
}

/**
 @brief init
*/
void init()
{
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
}

/**
 @brief brgin
*/
void begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
  if (lines > 1) {
	_displayfunction |= LCD_2LINE;
  }
  _numlines = lines;

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
	_displayfunction |= LCD_5x10DOTS;
  }

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  HAL_Delay(50);
  // Now we pull both RS and R/W low to begin commands
  writeI2c(0x00);

  // this is according to the hitachi HD44780 datasheet
  // figure 24, pg 46

  // we start in 8bit mode, try to set 4 bit mode
  write4bits(DB4|DB5);
  HAL_Delay(5); // wait min 4.1ms

  // second try
  write4bits(DB4|DB5);
  HAL_Delay(5); // wait min 4.1ms

  // third go!
  write4bits(DB4|DB5);
  HAL_Delay(2);

  // finally, set to 4-bit interface
  write4bits(DB5);

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}

/**
 @brief setRowOffsets
*/
void setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

/********** high level commands, for the user! */

/**
 @brief clear
*/
void clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  HAL_Delay(2);  // this command takes a long time!
}

/**
 @brief home
*/
void home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  HAL_Delay(2);  // this command takes a long time!
}

/**
 @brief setCursor
*/
void setCursor(uint8_t col, uint8_t row)
{
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
	row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
	row = _numlines - 1;    // we count rows starting w/0
  }

  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

/**
 @brief Turn the display off (quickly)
*/
void noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/**
 @brief Turn the display on (quickly)
*/
void display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/**
 @brief Turns the underline cursor off
*/
void noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/**
 @brief Turns the underline cursor on
*/
void cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/**
 @brief Turn off the blinking cursor
*/
void noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/**
 @brief Turn on the blinking cursor
*/
void blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/**
 @brief These commands scroll the display without changing the RAM
*/
void scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

/**
 @brief These commands scroll the display without changing the RAM
*/
void scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

/**
 @brief This is for text that flows Left to Right
*/
void leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

/**
 @brief This is for text that flows Right to Left
*/
void rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

/**
 @brief This will 'right justify' text from the cursor
*/
void autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

/**
 @brief This will 'left justify' text from the cursor
*/
void noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

/**
 @brief Allows us to fill the first 8 CGRAM locations with custom characters
*/
void createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
	write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

/**
 @brief command
*/
inline void command(uint8_t value) {
  send(value, 0);
}

/**
 @brief write
*/
inline uint8_t write(uint8_t value) {
  send(value, RS);
  return 1; // assume sucess
}

/************ low level data pushing commands **********/

/**
 @brief write either command or data, 4-bit
*/
void send(uint8_t value, uint8_t mode) {
  uint8_t Hbit = (value >> 4) & 0x0F;
  uint8_t Lbit = value & 0x0F;
  write4bits(Hbit|mode);
  write4bits(Lbit|mode);
}

/**
 @brief pulseEnable
*/
void pulseEnable(uint8_t value) {
  writeI2c(value & ~EN); // EN LOW
  HAL_Delay(1);
  writeI2c(value|EN);    // EN HIGH
  HAL_Delay(1);  // enable pulse must be >450ns
  writeI2c(value & ~EN); // EN LOW
  HAL_Delay(1); // commands need > 37us to settle
}

/**
 @brief write4bits
*/
void write4bits(uint8_t value) {
  writeI2c(value);
  pulseEnable(value);
}

/**
 @brief writeI2c
*/
void writeI2c(uint8_t data) {
  uint8_t data_t[1];
  data_t[0] = data|_backlight;
  HAL_I2C_Master_Transmit (&I2cHandle, (uint16_t)_i2caddr,(uint8_t *) data_t, 1, 0xFFFF);
}
























//////////////////////////////////////////////////////////////////////////


void Lcd_Initialization (void)
{
	FaBoLCD_PCF8574(SLAVE_ADDRESS_LCD);
}

void Lcd_Send_Cmd (char cmd)
{
	command(cmd);
}

void Lcd_Send_Data (char data)
{
	write(data);
}



void Lcd_Send_String (char *str)
{
	while (*str) Lcd_Send_Data (*str++);
}

void Lcd_Clear_Display (void)
{
	Lcd_Send_Cmd (0x01); //clear display
}

void Lcd_Goto_XY (int row, int col)
{
	setCursor(col, row);
}


void Show_Box_ID(uint16_t bID){

	char strBoxID[16];
	sprintf(strBoxID, "Box ID: %d", bID);

	Lcd_Goto_XY(0, 0);
	Lcd_Send_String((char*)strBoxID);
}

void Show_KWH(uint32_t ws){
	char strTotalKWH[16];
	uint32_t kwh;
//	kwh = ws/1000;
	kwh = round((double)ws/(3600*1000));

	sprintf(strTotalKWH, "Total: %ld kWh", kwh);

	Lcd_Goto_XY(1, 0);
	Lcd_Send_String((char*)strTotalKWH);
}
