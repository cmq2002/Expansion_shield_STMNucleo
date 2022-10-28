2 chân SCL(serial clock)/SDA (serial data) giao tiếp I2C dùng 2 pins PB8-PB9 (D14/D15)
chân LED: PB10 (D6)

Chỉ sài hàng ray của adruino (Giống shield của thầy).

chân SCL/SDA treo trên VCC (pull-up) (R = 1k-4.7k), cấu hình GPIO dạng Open-drain *(Không phải analog).
First, MCU send data to DHT20(truy vấn cảm biến), Then it responds data to MCU

Kết nối 1 master nhiều slave

LCD I2C PCF8574

STM32

- Address 
	DHT20	:	0x38
	LCD	:	0x27 (A0,A1,A2 no res = 1) =>	Max 8 devices LCDs (0x20->0x27)
- Clockspeed
	CLK 	:	100000 (Standard mode : 100kb/s)	

- Data Send: 
	Looking for
	1. HAL_I2C_Master_Transmit()

	 

reference:
https://khuenguyencreator.com/giao-thuc-i2c-lap-trinh-stm32-voi-rtc-ds3231/
https://www.bluedot.space/tutorials/how-many-devices-can-you-connect-on-i2c-bus/
https://drive.google.com/file/d/1EUze00NjyJdFRy9nF8QQxjB7dwrBWjGl/view
https://khuenguyencreator.com/lap-trinh-stm32-voi-dht11-theo-chuan-1-wire/
https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
https://tapit.vn/giao-tiep-stm32f103c8t6-voi-lcd-16x2-thong-qua-module-i2c/
