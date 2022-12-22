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

//globally use
uint8_t buffer_byte;
uint8_t buffer[MAX_BUFFER_SIZE];
int index_buffer = 0;
int buffer_flag = 0;
int isRST = 0;
int isOK = 0;

//Locally use
int cmdParserStatus = IDLE;
int cmd_index = 0;

void cmd_parser_fsm()
{
	switch (cmdParserStatus)
	{
	case IDLE:
		if (buffer[cmd_index] == '!')
		{
			cmdParserStatus = CMD_WAITING;
		}
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
	case CMD_WAITING:
		if (buffer[cmd_index] == 'O')
		{
			cmdParserStatus = CMD_WAITING_O;
		}
		else if (buffer[cmd_index] == 'R')
		{
			cmdParserStatus = CMD_WAITING_R;
		}
		else cmdParserStatus = IDLE;
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
//-----------------------------------------------------
	case CMD_WAITING_O:
		if (buffer[cmd_index] == 'K')
		{
			cmdParserStatus = CMD_WAITING_OK;
		}
		else cmdParserStatus = IDLE;
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
	case CMD_WAITING_OK:
		if (buffer[cmd_index] == '#')
		{
			isOK = 1;
			cmdParserStatus = IDLE;
		}
		else cmdParserStatus = IDLE;
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
//-----------------------------------------------------
	case CMD_WAITING_R:
		if (buffer[cmd_index] == 'S')
		{
			cmdParserStatus = CMD_WAITING_RS;
		}
		else cmdParserStatus = IDLE;
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
	case CMD_WAITING_RS:
		if (buffer[cmd_index] == 'T')
		{
			cmdParserStatus = CMD_WAITING_RST;
		}
		else cmdParserStatus = IDLE;
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
	case CMD_WAITING_RST:
		if (buffer[cmd_index] == '#')
		{
			isRST = 1;
			setTimer2(1);
			cmdParserStatus = IDLE;
		}
		else cmdParserStatus = IDLE;
		cmd_index++;
		if (buffer_flag == 0)
		{
			index_buffer = 0;
			cmd_index = 0;
		}
		break;
//-----------------------------------------------------
	default:
		break;
	}
}

void uart_comms_fsm()
{
	if (isRST == 1)
	{
		if (timer2_flag == 1){
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			setTimer2(100);
		}
		fsm_run();
	}
	if (isOK == 1)
	{
		isOK = 0;
		isRST = 0;
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

