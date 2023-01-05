/*
 * pcf8574.c
         Library used to control a PCF8574 I/O expander by I2C bus - no support for reading ports yet...
 	 	 Biblioteka służąca do obsługi przy użyciu I2C ekspanderów opartych na PCF8574
 *
 *  Created on: 26.05.2019
 *      Author: ng
 */
#include "main.h"
I2C_HandleTypeDef hi2c1;


#define EXP_NUM 2

	char str[10];
	uint8_t pcf8574_addr[EXP_NUM];
	uint8_t port_state[EXP_NUM];
	uint8_t txdata[EXP_NUM];
	int i;
	int b = 0;

	char int_pow(char base, char exp)
	{
	    char result = 1;
	    while (exp)
	    {
	        if (exp & 1)
	           result *= base;
	        exp /= 2;
	        base *= base;
	    }
	    return result;
	}

void pcf8574_init(uint8_t exp_num, uint8_t exp_addr){
	pcf8574_addr[exp_num]=exp_addr;
	for(i=0;i=2;i++){
		port_state[EXP_NUM]=0b00000000;
	}

}

void pcf8574_setaddr(int exp_num, int addr){
	pcf8574_addr[exp_num]=addr;
}

void pcf8574_write(int exp_num, int port_num, int port_state, int send_cmd){

	uint8_t number=int_pow(2, port_num);

	uint8_t number_negated =  ~number;

	if(port_num<=7 || port_num>=0){
		if(port_state == 1){
			port_state[exp_num] = port_state[exp_num] | number;
			txdata[exp_num] = port_state[exp_num];

		}
		if(port_state == 0){
			port_state[exp_num] = port_state[exp_num] & number_negated;
			txdata[exp_num] = port_state[exp_num];

		}

	}

	if(send_cmd==1){
		uint8_t addr_send[1];
		uint8_t port_state_send[1];
		port_state_send[0] = txdata[exp_num];
		addr_send[0] = pcf8574_addr[exp_num];
		uint8_t addr[1];
		addr[0] = addr_send[0];
		uint8_t tx[1];
		uint8_t txdata = port_state_send[0];
		tx[0]= txdata;
		HAL_I2C_Master_Transmit(&hi2c1,addr[0],tx,1,100);
		//HAL_I2C_Master_Transmit_DMA(&hi2c1, addr[0], tx, 1);

		//HAL_I2C_Master_Transmit(&hi2c1,pcf8574_addr[exp_num],tx,1,100);
	}
}
