/*
 ************************************************************
 * PiMash - 
 * 	Microcontroller component of the raspberry-pi 
 * 	based RIMS controller
 ************************************************************
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>	
#include <stdlib.h>
#include <util/delay.h>

#include "uart.h"

// intialize data direction and call other intialization functions  	
static void ioinit (void) {
	uart_115200 ();		
	}

// intialize input capture
//void IC_init(void);

// FIXME
// Need to:
//	1) Read temperature sensors
//	2) Use PID to adjust PV "On" pulse width
//	3) Read SF800 Flow Meter
//	4) Look for SP and Kp, Ki, Kd parameters from UART
int main (void) {
	ioinit();

	while (1) {
		_delay_ms(1000);
		tx_byte('t');
		tx_byte('e');
		tx_byte('s');
		tx_byte('t');
		tx_byte('\r');
		tx_byte('\n');
		}

	
    return (0);
	}
