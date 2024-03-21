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
#include "keypad.h"
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
	KEYPAD_Init();
	I2C_init_slave(SLAVE_ADDRESS);
	stdout = &uart_output;
	stdin = &uart_input;


	DDRE &= ~(1 << PE4);
	uint8_t motionState = 0;
	uint8_t key;
	uint8_t count = 0;
	uint8_t count2 = 0;
	uint8_t ack_status;
    /* Replace with your application code */
    while (1) 
    {
//
		//switch(I2C_listen_from_master()) {
			//case SLAVE_READ:
				//printf("SLA+W received and ACK returned\n");
				//do {
					//count = I2C_receive_from_master();
					//printf("Count: %d\n", count);
				//} while (count != -1);
				//_delay_ms(5000);
				//break;
			//case 1:
				//printf("SLA+R received and ACK returned\n");
				//do {
					//ack_status = I2C_transmit_to_master(count2);
					//printf("Count 2: %d\n", count2);
					//count2++;
				//} while (ack_status == 0);
				//_delay_ms(5000);
				//break;
			//case 2:
				//printf("General call received & ack returned\n");
				//break;
				//
		//}

		
		//switch(g_STATE) {
			//case IDLE:
				//switch(I2C_listen_from_master()) {
					//case SLAVE_READ:
						//printf("SLA+W get\n");
						//break;
					//case SLAVE_WRITE:
						//I2C_transmit_to_master("y");
						//break;
				//}
				//break;
			//case READKEYPAD:
				//switch (I2C_listen_from_master()) {
					//case SLAVE_WRITE:
						//do {
							//key = KEYPAD_GetKey();
							//ack_status = I2C_transmit_to_master(key);
						//} while (ack_status == 0);
						//g_STATE = IDLE;
						//break;
					//case SLAVE_READ:
						//g_STATE = FAULT;
				//}
				//break;
			//case READMOTIONSENSOR:
				//switch (I2C_listen_from_master()) {
					//case SLAVE_WRITE:
						//motionState = (PINE & (1 << PE4));
						//if (motionState != 0) {
							//motionSensed = 1;
						//do {
							//ack_status = I2C_transmit_to_master(motionState);
						//} while (ack_status == 0);
						//motionSensed = 0;
						//g_STATE = IDLE;
						//break;
				//}
				//break;
			//default:
				//g_STATE = FAULT;
				//break;
		//}
		//motionState = (PINE & (1 << PE4));
		//if (motionState != 0){
			//printf("motion sensed");
		//} else if (motionState == 0){
			//printf("motion not checked");
		//} else {
			//printf("fault");
		//}
		
		_delay_ms(100);
		
		
		//motionState = (PINE & (1 << PE4));
		//if (motionState != 0) {
		//motionSensed = 1;
		//do {
		//twi_status = I2C_transmit_to_master_ACK(motionState);
		//} while (twi_status == MASTER_ACK_RECEIVED);
		//
		//if (twi_status == MASTER_ACK_RECEIVED) {
		//key  = KEYPAD_GetKey();
		//printf("%c\r\n", (char)key);
		//}
		//}
    }

	return 0;
}



