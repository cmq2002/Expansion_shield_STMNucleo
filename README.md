# Expansion shield for STM Nucleo

## General Information:
- Major components: DHT-20 sensor and LCD 16x2
- Purpose: Measuring temperature and humidity then print out using the LCD.
- Project layout:
  - The Altiutm Designer folder includes Schematic and PCB layout of the Expansion Shield for STM Nucleo.
  - The STM32 folder consists of the program to control this shield.
  - The Proteus foler contains the simulation of the shield.

## Geneal Idea:
- 2 chân SCL(serial clock)/SDA (serial data) giao tiếp I2C dùng 2 pins PB8-PB9 (D14/D15)

- chân LED: PA1 (A1)

- Chỉ sài hàng ray của adruino (Giống shield của thầy).

- chân SCL/SDA treo trên VCC (pull-up), cấu hình GPIO dạng (input/output)? Open-drain *(Không phải analog).

- First, MCU send data to DHT20(truy vấn cảm biến), Then it responds data to MCU

- LCD I2C PCF8574

- STM32
  - looking for HAL_I2C_Master_Transmit()

  - Address 
  	- DHT20	:	0x38
	-  LCD	:	0x27 (A0,A1,A2 no res = 1) =>	Max 8 devices LCDs (0x20->0x27)
  - Clockspeed
	-  CLK 	:	100000 (100kHz)	

  - LCD
	- Implement function:
	- Ex:
	- LCD_Init(): bla bla, move cursor to home and set data address 0
	- LCD_Send_Data():include send the header. 4 parts in the data send x+y+z+t
	- LCD_Send_Cmd():	work same with send data()
	- LCD_Goto_XY (int row, int col): move the cursor to xy
		    
## About the STM32 Project:
- Configuring the .ioc:
  - GPIO: For the Led 
  - I2C1: For communication with the PCF8574 extension || By default: SCL -> PB8, SDA -> PB9
  - RCC: Generate external crystal clock
  - SYS: For STLink V2 Debuger
  - TIM2 - NVIC: Invoke timer interrupt
- The project using external crystal to generate 72Mhz clock
- To invoke the timer interrupt every 10ms, setting must be as follow:
  - Prescaler = 7199
  - Counter = 99
  
## About the Proteus Simulation:
- Since the process of making custom board takes a long time, at the beginning of the project we will use Proteus for simulation instead to test the correctness of the program and also optimizing it.

- Later on, when the board is available we will run on real hardwares.
		
## Reference:
- https://tapit.vn/giao-tiep-stm32f103c8t6-voi-lcd-16x2-thong-qua-module-i2c/
- https://www.bluedot.space/tutorials/how-many-devices-can-you-connect-on-i2c-bus/
- https://drive.google.com/file/d/1EUze00NjyJdFRy9nF8QQxjB7dwrBWjGl/view (For microbit IoTs)
- https://khuenguyencreator.com/lap-trinh-stm32-voi-dht11-theo-chuan-1-wire/
- https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
- https://controllerstech.com/i2c-lcd-in-stm32/
- https://controllerstech.blogspot.com/2017/07/i2c-in-stm32.html
