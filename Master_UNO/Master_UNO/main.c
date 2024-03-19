/*
 * Master_UNO.c
 *
 * Created: 11.3.2024 17.10.41
 * Author : jesse
 */ 

#define F_CPU 16000000UL
#define FOSC 16000000UL
#define BAUD 9600 
#define MYBBR (FOSC/16/BAUD-1) // for i2c
#define SLAVE_ADDRESS 0x30

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>
//importing necessary header files
#include "i2c.h"
#include "lcd.h"
#include "usart.h"


FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);

typedef enum {
	IDLE, HANDLE_KEYPAD, KEYPAD_TIMEOUT, READ_MOTION, START_ALARM, STOP_ALARM, WRONG_PASSWORD,
	TOO_LONG_PASSWORD, FAIL
}STATE;

int main(void)
{
    USART_init(MYBBR);
	lcd_init(LCD_DISP_ON);

	stdout = &uart_output;
	stdin = &uart_input;
	
	STATE g_State = IDLE;
	lcd_clrscr();
	lcd_puts("Detecting...");
	//unsigned char twi_send_data[20] = "Master to slave\n";
	//char test_char_array[16];
	//uint8_t twi_status = 0;
	uint8_t motion_sensed;
	uint8_t twi_status;
	//Slave address 
	
	/* Replace with your application code */
    while (1) 
    {

		switch(g_State) {
			case IDLE:
				g_State = READ_MOTION;
				break;
			case START_ALARM:
				break;
			case STOP_ALARM:
				break;
			case HANDLE_KEYPAD:
				break;
			case READ_MOTION:
				twi_status = I2C_start_read(SLAVE_ADDRESS);
				if (twi_status == 0) {
					printf("ERROR");
					break;
				} else {
					printf("YES");
				}
				//twi_status = I2C_read_start(SLAVE_ADDRESS);
				//if (twi_status != TWI_ACK_RECEIVED) {
					//g_State = FAIL;
					//break;
				//}
				//motion_sensed = I2C_read_ack();
				//if (motion_sensed == 'y') {
					//g_State = FAIL;
					//break;
				//}
				//I2C_read_nack();
				//I2C_stop();
//
				//if (motion_sensed == 1){
					//g_State = START_ALARM;
					//break;
				//}
				break;
			case KEYPAD_TIMEOUT:
				break;
			case WRONG_PASSWORD:
				break;
			case TOO_LONG_PASSWORD:
				break;
			case FAIL:
				break;
			default:
				break;
		}
		//TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
//
		//while (!(TWCR & (1 << TWINT))){
			//;
		//}
//
		//twi_status = (TWSR & 0xF8);
//
		//itoa(twi_status, test_char_array, 16);
		//printf(test_char_array);
		//printf(" ");
		//
		//TWDR = SLAVE_ADDRESS;
//
		//TWCR = (1 << TWINT) | (1 << TWEN);
//
		//while (!(TWCR & (1 << TWINT))) {
			//;
		//}
	//
		//twi_status = (TWSR & 0xF8);
		//itoa(twi_status, test_char_array, 16);
		//printf(test_char_array);
		//printf(" ");
//
		////transmite data to slave
		//for (int8_t twi_data_index = 0; twi_data_index < sizeof(twi_send_data); twi_data_index++) {
			//TWDR = twi_send_data[twi_data_index];
//
			//TWCR = (1 << TWINT) | (1 << TWEN);
//
			//while (!(TWCR & (1 << TWINT))) {
				//;
			//}
//
			//twi_status = (TWSR & 0xF8);
            //itoa(twi_status, test_char_array, 16);
            //printf(test_char_array);
            //printf(" ");
		//}
//
		////stop
//
		//TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
//
		//_delay_ms(1000);
	}

	return 0;
}

