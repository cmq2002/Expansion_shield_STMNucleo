/*
 * uart_reading.c
 *
 *  Created on: Dec 22, 2022
 *      Author: acer
 */


/*
 * fsm.c
 *
 *  Created on: Nov 20, 2022
 *      Author: PC
 */
#include "uart_reading.h"

extern UART_HandleTypeDef huart2;

extern I2C_HandleTypeDef hi2c1;

//Globally use in main to take input
uint8_t buffer_byte;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

//Locally use in uart_reading
uint8_t cmdParserStatus = INIT_UART;
uint8_t cmd_data[MAX_CMD_SIZE];
uint8_t cmd_index = 0;
uint8_t cmd_flag = INIT_UART;

int isCmdEqualToRST(uint8_t str[]){
	int flag = 0;
	if (str[0] == 'R') flag = 1;
	else flag = 0;
	return flag;
}

int isCmdEqualToCAP(uint8_t str[]){
	int flag = 0;
	if (str[0] == 'C') flag = 1;
	else flag = 0;
	return flag;
}

void cmd_parser_fsm(){
	switch(cmdParserStatus){
		case INIT_UART:
			if (buffer_byte == '!') cmdParserStatus = READING;
			break;
		case READING:
			if (buffer_byte != '!' && buffer_byte != '#'){
				cmd_data[cmd_index] = buffer_byte;
				cmd_index++;
			}
			else if (buffer_byte == '!'){
				cmdParserStatus = READING;
			}
			else if (buffer_byte == '#'){
				cmdParserStatus = STOP;
				cmd_index = 0;
			}
			break;
		case STOP:
			if (isCmdEqualToRST(cmd_data)==1) cmd_flag = isRST;
			else if (isCmdEqualToCAP(cmd_data)==1) cmd_flag = isCAP;
			else return;
			cmdParserStatus = INIT_UART;
			break;
		default:
			break;
	}
}

void uart_control_fsm()
{
	switch (cmd_flag){
		case INIT_UART:
			cmd_flag = AUTO;
			setTimer2(1);
			break;
		case AUTO:
			if (timer2_flag == 1){
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
				setTimer2(300);
			}
			reading_fsm_run();
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
			break;
		case isCAP:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
			setTimer4(1000);
			cmd_flag = WAIT;
			break;
		case WAIT:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
			if (timer4_flag == 1) cmd_flag = INIT_UART;
			break;
		case isRST:
			cmd_flag = INIT_UART;
			break;
		default:
			break;
	}
}

void Scan_Addr() {
    char info[] = "\r\n\r\nScanning I2C bus...\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)info, strlen(info), HAL_MAX_DELAY);

    HAL_StatusTypeDef res;
    for(uint16_t i = 0; i < 128; i++) {
        res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10);
        if(res == HAL_OK) {
            char msg[64];
            snprintf(msg, sizeof(msg), "0x%02X", i);
            HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        } else {
            HAL_UART_Transmit(&huart2, (uint8_t*)".", 1, HAL_MAX_DELAY);
        }
    }
}

