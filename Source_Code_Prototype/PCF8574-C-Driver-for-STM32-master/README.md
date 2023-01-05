# PCF8574 C Driver for STM32

## How to use? 
You have to use a CubeMX generator(with HAL Libraries).

0) Set in a pcf8574.c amount of used I/0 expanders
1) Set an address for each expander using pcf8574_setaddr(number_of_expander, address_of_expander) - number of first expander is 0! As address use only decimal numbers - pcf8574_setaddr(0, 66) **example values**
2) When You have to set HIGH or LOW a certain pin on specified expander, you can use this - pcf8574_write(number_of_expander, number_of_pin(0 to 7), state(0 or 1), (1 if we want to send a i2c command now, 0 if else))
3) Have FUN!
 
