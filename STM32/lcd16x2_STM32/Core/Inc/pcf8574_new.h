/*
 * pcf8574_new.h
 *
 *  Created on: Nov 18, 2022
 *      Author: binch
 */

#ifndef INC_PCF8574_NEW_H_
#define INC_PCF8574_NEW_H_

void pcf8574_init(uint8_t exp_num, uint8_t exp_addr);
void pcf8574_setaddr(int exp_num, int addr);
void pcf8574_write(int exp_num, int port_num, int port_state, int send_cmd);

#endif /* INC_PCF8574_NEW_H_ */
