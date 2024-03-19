/*
 * i2c.h
 *
 * Created: 8.3.2024 0.13.08
 *  Author: jesse
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>

#define SLAVE_READ 0
#define SLAVE_WRITE 1
#define SLAVE_GENERAL 2

#define MASTER_STOP 1
#define MASTER_ACK_RECEIVED 0
#define MASTER_NACK_RECEIVED 2
#define MASTER_LAST_BYTE_RECEIVED 3
#define MASTER_ERROR 4

void I2C_init_slave(char slave_address);
uint8_t I2C_listen_from_master();
uint8_t I2C_receive_from_master();
uint8_t I2C_transmit_to_master_ACK(uint8_t data);
uint8_t I2C_transmit_to_master_NACK(uint8_t data);

#endif /* I2C_H_ */