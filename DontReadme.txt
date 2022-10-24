2 chân SCL(serial clock)/SDA (serial data) giao tiếp I2C dùng 2 pins PB8-PB9 (D14/D15)
chân LED: PB10 (D6)

Chỉ sài hàng ray của adruino (Giống shield của thầy).


chân SCL/SDA treo trên VCC (pull-up), cấu hình GPIO dạng (input/output)? Open-drain *(Không phải analog).
First, MCU send data to DHT20(truy vấn cảm biến), Then it responds data to MCU

reference:
https://www.bluedot.space/tutorials/how-many-devices-can-you-connect-on-i2c-bus/
https://drive.google.com/file/d/1EUze00NjyJdFRy9nF8QQxjB7dwrBWjGl/view
https://khuenguyencreator.com/lap-trinh-stm32-voi-dht11-theo-chuan-1-wire/
https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
