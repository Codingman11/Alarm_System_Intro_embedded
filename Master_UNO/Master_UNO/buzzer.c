/*
 * buzzer.c
 *
 * Created: 13.3.2024 16.08.54
 *  Author: jesse
 */ 

 #include "main.h"
 #include "buzzer.h"
 #include <avr/io.h>
 #include <avr/interrupt.h>
ISR(TIMER1_COMPA_vect) {
	PORTB ^= (1 << PB3);
}

void init_buzzer() {
	
	//resetting timer/counter
	TCCR1A = 0;
	TCCR1B = 0;

	TCCR1A |= (1 << COM1A0);
	TCCR1B |= (1 << CS12) | (1 << WGM10);

	OCR1A = F_CPU/32/2/64 - 1;
}

void start_buzz() {
	TIMSK1 |= (1 << OCIE1A);
}

void stop_buzz() {
	TIMSK1 &= ~(1 << OCIE1A);

	PORTB &= ~(1 << PB3);
}
