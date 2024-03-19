/*
 * i2c.c
 *
 * Created: 7.3.2024 20.33.25
 *  Author: jesse
 * Source: Atmel-2549-8-bit-AVR-Microcontroller-ATmega640-1280-1281-2560-2561_datasheet.pdf, pp. 244-258
 */ 

 #include "i2c.h"
 /***********************************************************************/
 /*	@brief		Initialize I2C connection								*/
 /*																		*/
 /*	@param		none													*/
 /*	@return		none													*/
 /*	                                                                    */
 /***********************************************************************/

 void I2C_init_slave(char slave_addr) {
	TWAR = slave_addr;
	TWCR |= (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
 }

 /***********************************************************************/
 /*	@brief		Listening from master I2C								*/
 /*																		*/
 /*	@param		none													*/
 /*	@return		SLAVE_READ or SLAVE_WRITE or SLAVE_GENERAL													*/
 /*	                                                                    */
 /***********************************************************************/

 uint8_t I2C_listen_from_master() {
	uint8_t twi_status;
	
	
	while (1) {
		
		while(!(TWCR & (1 << TWINT))){
			;
		}
		twi_status = (TWSR & 0xF8);

		if ((twi_status == 0x60) || (twi_status == 0x68)) {
			return SLAVE_READ;
		}
		else if (twi_status == 0xA8 || (twi_status == 0xB0)) {
			return SLAVE_WRITE;
		}
		else if (twi_status == 0x70 || (twi_status == 0x78)) {
			
			return SLAVE_GENERAL;
		} 
	}
 }


  /***********************************************************************/
  /*	@brief		Reading data from master							 */
  /*																	 */
  /*	@param		none												 */
  /*	@return		TWDR as data										 */
  /*				MASTER_STOP - Master responds with stop signal		 */													
  /*	            MASTER_ERROR  - Something error happened			 */
  /***********************************************************************/

 uint8_t I2C_receive_from_master() {
	uint8_t twi_status;
	
		
	while (1) {
		twi_status = (TWSR & 0xF8);
		while(!(TWCR & (1 << TWINT))){
			;
		}

		if ((twi_status == 0x80) || (twi_status == 0x90)) {
			return TWDR;
		} 
		else if (twi_status == 0x88 || (twi_status == 0x98)) {
			return TWDR;
		}
		else if (twi_status == 0xA0) {
			TWCR |= (1 << TWINT);
			return MASTER_STOP;
		} else {
			return MASTER_ERROR;
		}
	}
 }

 
 /***********************************************************************/
 /*	@brief		Transmit the byte to the master with ACK				*/
 /*																		*/
 /*	@param		uint8_t data											*/
 /*	@return		TWDR as data											*/
 /*				MASTER_STOP - Master responds with stop signal			*/
 /*	            MASTER_ERROR  - Something error happened				*/
 /***********************************************************************/

 uint8_t I2C_transmit_to_master_ACK(uint8_t data) {
	
	uint8_t twi_status;
	TWDR = data;
	// "clear" TWINT and generate ACK (TWEA)
	TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))){;}
	twi_status = (TWSR & 0xF8);

	if (twi_status == 0xA0) {
		return MASTER_STOP;
	} else if (twi_status == 0xB8) {
		return MASTER_ACK_RECEIVED;
	} else if (twi_status == 0xC0) {
		TWCR |= (1 << TWINT);
		return MASTER_NACK_RECEIVED;
	} else if (twi_status == 0xC8) {
		return MASTER_LAST_BYTE_RECEIVED;
	} else {
		return MASTER_ERROR;
	}

 }

 
 /***********************************************************************/
 /*	@brief		Transmite the byte to the master with NACK				*/
 /*																		*/
 /*	@param		none													*/
 /*	@return		TWDR as data											*/
 /*				MASTER_STOP - Master responds with stop signal			*/
 /*	            MASTER_ERROR  - Something error happened				*/
 /***********************************************************************/

 uint8_t I2C_transmit_to_master_NACK(uint8_t data) {
	
	uint8_t twi_status;
	TWDR = data;
	TWCR |= (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT))) {;}
	
	twi_status = (TWSR & 0xF8);
	if (twi_status == 0xA0) {
		return MASTER_STOP;
	} else if (twi_status == 0xB8) {
		return MASTER_ACK_RECEIVED;
	} else if (twi_status == 0xC0) {
		TWCR |= (1 << TWINT);
		return MASTER_NACK_RECEIVED;
	} else if (twi_status == 0xC8) {
		return MASTER_LAST_BYTE_RECEIVED;
	} else {
		return MASTER_ERROR;
	}
 }

