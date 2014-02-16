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

#define SF_PIN	PB0
#define SF_IN	PINB
#define SF_OUT	PORTB
#define SF_DDR	DDRB

// ********************************************************
void init_sf800 () {
	TCCR1A = 0;
	TCCR1C = 0;

	// External clock on rising edge, noise cancelling
	TCCR1B = (1 << ICNC1)|(1 << ICES1)|(1 << CS11)|(1 << CS12);
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

	
