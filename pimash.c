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
#include "1wire.h"

// FIXME
// Need to:
//	1) Read temperature sensors
//	2) Use PID to adjust PV "On" pulse width
//	3) Read SF800 Flow Meter
//	4) Look for SP and Kp, Ki, Kd parameters from UART
int main (void) {
	// Init uart
	uart_115200();

	// Init the probe every 5 second, report:
	// 'P': Present
	// 'Q': Non Present (Quiet)
	while (1) {
		_delay_ms(5000);
		if (initProbe ()) {
			tx_byte ('P');
			}
		else {
			tx_byte ('Q');
			}
		}
	
    return (0);
	}
