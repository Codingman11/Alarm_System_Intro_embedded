/*
 * usart.c
 *
 * Created: 13.3.2024 14.05.49
 *  Author: jesse
 */ 

#include "usart.h"
void USART_init(unsigned int ubrr) {

	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//enabling receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* set frame format: 8 data, 2 stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

int USART_transmit(char data, FILE *stream) {
	  
	while (!(UCSR0A & (1 << UDRE0))) {
		  
	}
	UDR0 = data;
	return 0;

}

int USART_receive(FILE *stream) {

	while (!(UCSR0A & (1 << UDRE0))){
		  
	}
	return UDR0;
}
