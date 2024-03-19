/*
 * usart.h
 *
 * Created: 13.3.2024 14.05.59
 *  Author: jesse
 */ 


#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

void USART_init(unsigned int ubrr);
int USART_transmit(char data, FILE *stream);
int USART_receive(FILE *stream);



#endif /* USART_H_ */