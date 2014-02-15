/*
 ************************************************************
 * PiMash - 
 * 	DS19B20 interface API
 ************************************************************
 */
#include <avr/io.h>
#include <util/atomic.h>
#include <util/delay.h>
#include "1wire.h"


#ifndef T_PIN
#define T_PIN	PC0
#define T_IN	PINC
#define T_OUT	PORTC
#define T_DDR	DDRC
#define OUT 1
#define IN 0
#define ON 1
#define OFF 0
#endif

static void  SETPIN(unsigned char on) {
	if (on) 
		T_OUT |= (1<<T_PIN);
	else
		T_OUT &= ~(1<<T_PIN);
	}

static void SETDIR(unsigned char out) {
	if (out)
		T_DDR |= (1<<T_PIN);
	else
		T_DDR &= ~(1<<T_PIN);
	}


// ********************************************************
// Returns 0  if a presence ack is received
unsigned char initProbe () {
	unsigned char err = 1;

	// Set as output, drive low for 480 us
	SETPIN (OFF); 
	SETDIR (OUT);
	_delay_us (480);

	// Set as input, wait at least 60 us and check the input state
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		SETDIR(IN);	
		_delay_us (70);
		err = T_IN & (1 << T_PIN);
		}
	
	// Wait another 480 - 70 us, line should be high by pull-up resistor
	_delay_us (480 - 70);
	if (0 == (T_IN & (1 << T_PIN))) {
		err = 1;
		}
	
	return err;
	}
