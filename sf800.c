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

// ********************************************************
void init_sf800 () {
	TCCR1A = 0;
	TCCR1C = 0;
	PORTD  = 0;
	DDRD = 0;

	// External clock on falling  edge, noise cancelling
	TCCR1B = (1 << CS11) | (1 << CS12);
	
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
