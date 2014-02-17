/*
 ************************************************************
 * PiMash - 
 * 	Microcontroller component of the raspberry-pi 
 * 	based RIMS controller
 ************************************************************
 */
#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>
#include "sf800.h"
#include "uart.h"

// SF800 k factor is 5600 pulse/liter. To report in liter/min:
// pulses/sec * 1/5600 liter/pulses * 60 sec/min = liter/min
#define K_FACTOR 60.0f / 5600.0f

// timer variables
int flwtimerof_count = 0;
int flwcount =0;

// ********************************************************
void start_flwtimer () {
	TCNT0 = 0;
	// External clock on falling  edge, noise cancelling
	TCCR0A = 0;
	// Clock on T1 (PD6) on falling edge
	TCCR0B |= (1 << CS02) | (1 << CS00);

	// No interrupts
	TIMSK0 |= (1 << TOIE0);
	}

// ********************************************************
void stop_flwtimer () {
	TCCR0B &= ~(1 << CS00) & ~(1 << CS01) & ~(1 << CS02);
	}

// ********************************************************
ISR (TIMER0_OVF_vect) {
	// Capture pulses every 1 second and reset counter 1
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (flwtimerof_count++ == 46) {
			flwtimerof_count = 0;
			flwcount = TCNT1;
			TCNT1 = 0;
			}
		}
	}

// ********************************************************
void init_sf800 () {
	PORTD  = 0;
	DDRD &= ~(1 << PD6);

	// External clock on falling  edge, noise cancelling
	TCCR1A = 0;
	// Clock on T1 (PD6) on falling edge
	TCCR1B |= (1 << CS11) | (1 << CS12);
	TCCR1C = 0;

	// No interrupts
	TIMSK1 = 0;
	}

// ********************************************************
double get_flwrate () {
	double flowrate = flwcount;
	flowrate *= K_FACTOR;
	return flowrate;
	}
