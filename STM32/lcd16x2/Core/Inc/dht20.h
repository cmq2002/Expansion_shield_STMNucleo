

#ifndef INC_DHT20_H_
#define INC_DHT20_H_

void dht20_init(void);

void dht20_reset(uint8_t);

void dht20_read(uint16_t*);

void dht20_start(void);

#endif /* INC_DHT20_H_ */
