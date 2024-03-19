/*
 * Slave_MEGA.c
 *
 * Created: 11.3.2024 17.11.16
 * Author : jesse
 */ 
#define F_CPU 16000000UL
#define FOSC 16000000UL
#define BAUD 9600
#define MYUBBR (FOSC/16/BAUD-1)

#define SLAVE_ADDRESS 0x20
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>
//importing necessary header files
#include "i2c.h"
#include "usart.h"

volatile uint8_t motionSensed = 0;
FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);

typedef enum 
{
	IDLE, READKEYPAD, READMOTIONSENSOR, FAULT
}
STATE;

STATE g_STATE = IDLE;

int main(void)
{
	USART_init(MYUBBR);

	stdout = &uart_output;
	stdin = &uart_input;

	char twi_receive_data[20];
	char test_char_array[16]; // 16-bit array, assumes that the int given is 16-bits
	uint8_t twi_index = 0;
	uint8_t twi_status = 0;

	TWAR = SLAVE_ADDRESS;

	//initialize TWI slave
	TWCR |= (1 << TWEA) | (1 << TWEN);
	TWCR &= ~(1 << TWSTA) & ~(1 << TWSTO);

	DDRE &= ~(1 << PE4);
	uint8_t motionState = 0;
    /* Replace with your application code */
    while (1) 
    {

		switch(g_STATE) {
			case IDLE:
				break; 
			case READKEYPAD:
				break;
			case READMOTIONSENSOR:
				break;
			default:
				g_STATE = FAULT;
				break;
		}
		motionState = (PINE & (1 << PE4));
		if (motionState != 0){
			printf("motion sensed");
		} else if (motionState == 0){
			printf("motion not checked");
		} else {
			printf("fault");
		}
		_delay_ms(3000);
		
		
		//while (!(TWCR & (1 << TWINT))) {
			//;
		//}
//
		//twi_status = (TWSR & 0xF8);
//
		//TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
//
		//while (!(TWCR & (1 << TWINT))) {
			//;
		//}
//
		//twi_status = (TWSR & 0xF8);
		//// if status indicates that previous response was either slave address or general call and ACK was returned
		//// store the data register value to twi_receive_data
		//if((twi_status == 0x80) || (twi_status == 0x90)) {
			//
			//twi_receive_data[twi_index] = TWDR;
			//twi_index++;
		//} else if ((twi_status == 0x88) || (twi_status == 0x98)) {
		//// if status indicates that previous response was either slave address or general call and NOT ACK was returned
		//// store the data register value to twi_receive_data
			//twi_receive_data[twi_index] = TWDR;
			//twi_index++;
		//} else if ((twi_status == 0xA0)) {
			//// Stop condition or repeated start was received
			//// Clear interrupt flag
			//TWCR |= (1 << TWINT);
		//}
//
		//if (20 <= twi_index) {
			//printf(twi_receive_data);
			//twi_index = 0;
		//}
    }

	return 0;
}


 void motion_check() {

	 uint8_t motionState = (PINE & (1 << PE4));
	 if (motionState && motionSensed != 1) {
		motionSensed = 1;
		printf("Motion checked");
	 }
 }


