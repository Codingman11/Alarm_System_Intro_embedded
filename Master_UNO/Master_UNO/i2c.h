/*
 * i2c.h
 *
 * Created: 13.3.2024 14.05.36
 *  Author: jesse
 */ 


#ifndef I2C_H_
#define I2C_H_

//Defining the twi status
#define TWI_START_TRANSMIT 0x08
#define TWI_SLA_W_ACK 0x18
#define TWI_SLA_W_NACK 0x20
#define TWI_SLA_R_ACK 0x40
#define TWI_SLA_R_NACK 0x48
#define TWI_DATA_T_ACK 0x28
#define TWI_DATA_T_NACK 0x30

#include <avr/io.h>

void I2C_init();
uint8_t I2C_start_write(char slave_write_add);
uint8_t I2C_start_read(char slave_read_add);
uint8_t I2C_write(char data);
char I2C_read_ack();
char I2C_read_nack();
void I2C_stop();



#endif /* I2C_H_ */