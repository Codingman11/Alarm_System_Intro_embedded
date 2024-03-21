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
#define SLAVE_READ_ADDRESS 0x21
#define SLAVE_WRITE_ADDRESS 0x20

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>
//importing necessary header files
#include "i2c.h"
#include "lcd.h"
#include "usart.h"
//#include "buzzer.h"

#define	count 10
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
	I2C_init();
	
	stdout = &uart_output;
	stdin = &uart_input;
	
	STATE g_State = IDLE;

	//unsigned char twi_send_data[20] = "Master to slave\n";
	//char test_char_array[16];
	//uint8_t twi_status = 0;
	uint8_t motion_sensed;
	uint8_t twi_status;

	lcd_clrscr();
	lcd_puts("Detecting");
	//Slave address 
	

	/* Replace with your application code */
    while (1) 
    {
		switch(g_State) {
			case IDLE:
				g_State = READ_MOTION;
				break;
			case HANDLE_KEYPAD:
				break;
			case READ_MOTION:
				twi_status = I2C_start_read(SLAVE_READ_ADDRESS);
				if (twi_status != 1) {
					g_State = FAIL;
					break;
				}
				motion_sensed = I2C_read_ack();
				if (motion_sensed == 1) {
					g_State = START_ALARM;
				} else {
					g_State = IDLE;
				}
				break;
			case START_ALARM:
				buzzer_alarm();
				lcd_clrscr();
				lcd_puts("Alarm!");
				g_State = HANDLE_KEYPAD;
				break;
			case STOP_ALARM:
				stop_buzzer();
				lcd_clrscr();
				lcd_puts("Alarm is stopped");
				_delay_ms(2000);
				lcd_clrscr();
				lcd_puts("Detecting...");
				g_State = IDLE;
				break;
			case WRONG_PASSWORD:
				lcd_clrscr();
				lcd_puts("Wrong password!");
				_delay_ms(2000);
				g_State = HANDLE_KEYPAD;
				break;
			case TOO_LONG_PASSWORD:
				lcd_clrscr();
				lcd_puts("Too long pwd");
				_delay_ms(2000);
				g_State = HANDLE_KEYPAD;
				break;
			case KEYPAD_TIMEOUT:
				lcd_clrscr();
				lcd_puts("Timeout!");
				_delay_ms(2000);
				g_State = HANDLE_KEYPAD;
				break;
			case FAIL:
				I2C_stop();
				I2C_init();
				break;
				
			
		}
		
		//I2C_start_write(SLAVE_WRITE_ADDRESS);
		//_delay_ms(5);
//
		//for (uint8_t i = 0; i < count; i++) {
			//lcd_clrscr();
			//lcd_puts("Master count: ");
			//lcd_gotoxy(0,1);
			//lcd_puts(i); 
			//I2C_write(i);
			//_delay_ms(500);
		//}
//
		//I2C_start_read(SLAVE_READ_ADDRESS);
		//_delay_ms(5);
		//for (uint8_t i=0;i < count; i++)
		//{
			//if (i < count - 1){
				//printf("MASTER ACK: %d", I2C_read_ack());
				//}else {
				//printf("MASTER NACK: %d", I2C_read_nack());
			//}
			//_delay_ms(500);
		//}
		//switch(g_State) {
			//case IDLE:
				//g_State = READ_MOTION;
				//break;
			//case START_ALARM:
				//lcd_clrscr();
				//lcd_puts("Alarm!");
				//start_buzz();
				//_delay_ms(2000);
				//stop_buzz();
				//break;
			//case STOP_ALARM:
				//break;
			//case HANDLE_KEYPAD:
				//break;
			//case READ_MOTION:
				//twi_status = I2C_start_read(SLAVE_READ_ADDRESS);
				//if (twi_status != 1) {
					//g_State = FAIL;
					//break;
				//}
//
				//motion_sensed = I2C_read_ack();
				//if (motion_sensed == "y") {
					//g_State = FAIL;
					//break;
				//}
				//I2C_read_nack();
				//I2C_stop();
//
				//if (motion_sensed == 1) {
					//g_State = START_ALARM;
				//} else {
					//g_State = IDLE;
				//}
				//break;
			//case KEYPAD_TIMEOUT:
				//break;
			//case WRONG_PASSWORD:
				//break;
			//case TOO_LONG_PASSWORD:
				//break;
			//case FAIL:
				//break;
			//default:
				//break;
		//}
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


void buzzer_alarm(void) {
	// Set BUZZER_PIN as output
	DDRB |= (1 << PB3);
	
	// Generate the alarm sound
	for (int i = 0; i < 3; i++) { // Repeat the sound three times
		PORTB |= (1 << PB3); // Turn on the buzzer
		_delay_ms(200); // Keep the buzzer on for 200 milliseconds
		PORTB &= ~(1 << PB3); // Turn off the buzzer
		_delay_ms(200); // Wait for 200 milliseconds before the next iteration
	}
}

void stop_buzzer(void) {
	PORTB &= ~(1 << PB3);
}
