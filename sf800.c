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

static int flwtimerof_count = 0;

// ********************************************************
void start_flwtimer () {
	// External clock on falling  edge, noise cancelling
	TCCR0A = 0;
	// Clock on T1 (PD6) on falling edge
	TCCR0B |= (1 << CS00) | (1 << CS02);

	// No interrupts
	TIMSK0 |= (1 << TOIE0);
	}

// ********************************************************
void stop_flwtimer () {
	TCCR0B &= ~(1 << CS00) & ~(1 << CS01) & ~(1 << CS02);
	}

// ********************************************************
ISR (TIMER0_OVF_vect) {
	if (flwtimerof_count++ == 46)
		tx_text("Overflow...");
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
void clear_flwcount () {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		TCNT1 = 0;
		}
	}

// ********************************************************
unsigned int get_flwcount () {
	unsigned int tcnt1 = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		tcnt1 = TCNT1;
		}

	return tcnt1;
	}
