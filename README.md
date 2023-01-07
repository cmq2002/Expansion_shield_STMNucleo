# Expansion shield for STM Nucleo Development Board - HCMUT Logic Design Project

## General Information:
- Development Board: STM32 Nucleo-64 with STM32F103RBT6 MCU.
- Major components: DHT-20 sensor and LCD 16x2.
- Purpose: Measuring temperature and humidity then display the information using the LCD.

## About the Project layout:
- The Altium_Designer folder includes Schematic and PCB layout of the Expansion Shield for STM Nucleo.
- The STM32 folder consists of the program for the shield's operation.
- The Documents folder holds all manual, datasheet for devices and components.

## About the System's Behavior:
- Initially, the shield will print out greeting message. After that, it immediately take the measurements every 3 seconds.
- UART communication is used to control the operation. The command !C# will stop the measurement instantly for observing and whenever, the command !R# is received the system will run normally again.
- The state when receiving !C# command is maintained in 10 seconds, after than the system will be automatically back to measurement. However, in within 10 seconds, if users enter !R# system will instatnly changing to automatic state without waiting for time out.  
