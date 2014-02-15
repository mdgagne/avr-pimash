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

// DS18B20 supported Commands
#define SKIPROM     0xCC
#define CONVERT     0x44
#define READSCH     0xBE

// DS18B20 Not-yet supported Commands
//#define SEARCHROM   0xf0
//#define READROM     0x33
//#define MATCHROM    0x55
//#define RECALLE2    0xB8
//#define READPWR     0xB4
//#define ALMSEARCH   0xEC
//#define WRITESCH    0x4E
//#define CPYSCH      0x48

// 1-wire pin MACROS
#define T_PIN	PC0
#define T_IN	PINC
#define T_OUT	PORTC
#define T_DDR	DDRC
#define OUT 1
#define IN 0
#define ON 1
#define OFF 0

// ********************************************************
static void SETPIN(unsigned char on) {
	if (on) 
		T_OUT |= (1<<T_PIN);
	else
		T_OUT &= ~(1<<T_PIN);
	}

// ********************************************************
static void SETDIR(unsigned char out) {
	if (out)
		T_DDR |= (1<<T_PIN);
	else
		T_DDR &= ~(1<<T_PIN);
	}

// ********************************************************
static unsigned char send_bit (unsigned char bit) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		SETDIR (OUT);
		_delay_us (1);
		
		if(bit)
			SETDIR (IN);

		_delay_us (14);
	  	if((T_IN & (1 << T_PIN)) == 0 )
			bit = 0;
	  
		_delay_us (45);
		SETDIR (IN);
  		}

  	return bit;
	}

// ********************************************************
static unsigned int send_byte (unsigned char byte) {
	unsigned char i = 8;
	unsigned char j = 0;

  	do {
		j = send_bit (byte & 1);
		byte >>= 1;
		
		if(j)
		 	byte |= 0x80;
	  } while(--i);

	return byte;
	}

// ********************************************************
static unsigned int read_byte (void) {
  return send_byte(0xFF);
}

// ********************************************************
static void send_cmd (unsigned char cmd) {
	// Detect probe presense	 
	send_byte (SKIPROM);			// to all devices
	send_byte (cmd);
	}

// ********************************************************
// Returns 0  if a presence ack is received
unsigned char init_probe () {
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

// ********************************************************
void start_convert () {
	send_cmd (CONVERT);
	}

// ********************************************************
unsigned int get_temp () {
	// Issue the read command
	send_cmd (READSCH); 
	// Read in the low byte
	unsigned int temp = read_byte ();

	// Read in the high byte
	temp |= read_byte () << 8;

	// assume 12-bit (power-on state)
	return (temp <<= 3);
	}
