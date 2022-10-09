2 chân SCL(serial clock)/SDA (serial data) dùng 2 pins PB8-PB9 (D14/D15)

DHT11 chân data treo trên VCC (pull-up), cấu hình GPIO dạng (input/output)? Open-drain *(Không phải analog).
First, MCU send data to DHT11 (truy vấn cảm biến), Then it responds data to MCU

reference:
https://drive.google.com/file/d/1EUze00NjyJdFRy9nF8QQxjB7dwrBWjGl/view
https://khuenguyencreator.com/lap-trinh-stm32-voi-dht11-theo-chuan-1-wire/
https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf