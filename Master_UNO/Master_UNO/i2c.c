/*
 * i2c.c
 *
 * Created: 13.3.2024 14.05.23
 *  Author: jesse
 */ 

 #include "i2c.h"
 //I2C init

 void I2C_init() {
	TWSR = 0x00;
	TWBR = 0x03;
 }

 //I2C write start
 uint8_t I2C_start_write(char slave_write_add) {
	uint8_t twi_status;
	TWCR = (1 <<TWSTA) | (1 <<TWEN) | (1 << TWINT);
	while (! (TWCR & (1 << TWINT)));
	twi_status = TWSR & 0xF8;
	if (twi_status != 0x08) {
		return 0;
	}
	TWDR = slave_write_add;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	twi_status = TWSR & 0xF8;
	if (twi_status == 0x18) {
		return 1;
	}
	if (twi_status == 0x20) {
		return 2;
	}		

	return 3; // SLA+W failed 
 }

 //I2C  read start
 uint8_t I2C_start_read(char slave_read_add) {
	uint8_t twi_status;
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	twi_status = TWSR & 0xF8;
	if (twi_status != TWI_START_TRANSMIT) {
		return 0;
	}
	TWCR = slave_read_add;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));

	twi_status = TWSR & 0xF8;
	if (twi_status == TWI_SLA_R_ACK) {
		return 1;
	} else if (twi_status == TWI_SLA_R_NACK) {
		return 2;
	}

	return 3; 
 }
 //I2C write

 uint8_t I2C_write(char data) {
	uint8_t twi_status;
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	twi_status = TWSR & 0xF8;
	if (twi_status == 0x28) {
		return 0;
	}
	if (twi_status == 0x30) {
		return 1;
	} 

	return 2; //Data transmission failed
		
 }
 //I2C ack read

 char I2C_read_ack() {
	TWCR = (1 << TWEN) | (1 < TWINT) | (1 < TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
 }

 char I2C_read_nack() {
	TWCR = (1 << TWEN) | (1 < TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
 }


 //I2C stop
 void I2C_stop() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	while (TWCR &(1 << TWSTO));
 }

 //I2C command write
