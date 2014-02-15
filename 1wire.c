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

#define SETPIN(val) (val) ? (T_OUT |= (1<<T_PIN)) : (T_OUT &= ~(1<<T_PIN))
#define SETDIR(in)  (in) ? (T_DDR |= 1<<T_PIN) : (T_DDR &= ~(1<<T_PIN))
#endif


// ********************************************************
// Returns true if a presence ack is received
unsigned char initProbe () {
	unsigned char result = 0;
	// Set as output, drive low for 480 us
	SETPIN(1); 
	SETDIR(1);
	_delay_us (480);

	// Set as input, wait at least 60 us and check the input state
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		SETDIR(0);	
		_delay_us (70);
		result = T_IN & (1 << T_PIN);
		}

	// Wait at most another 240 - 60 us and check input state again
	// if the pin is still high we've received a presense pulse
	result = 0;
	_delay_us (240 - 70);
	result = T_IN & (1 << T_PIN);
	
	return result;
	}
