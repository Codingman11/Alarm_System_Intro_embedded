/*
 * buzzer.h
 *
 * Created: 13.3.2024 16.08.47
 *  Author: jesse
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


void init_buzzer();
void start_buzz();
void stop_buzz();

#endif /* BUZZER_H_ */