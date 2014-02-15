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
	PORTC = 0;
	DDRC = 0;

	// Init the probe
	if (0 == init_probe ())
		tx_text ("probe init SUCCESS");
	else
		tx_text ("probe init FAIL");

	// Read and report the temp every 1 second	
	while (1) {
		start_convert ();
		_delay_ms (1000);
		unsigned int temp = get_temp ();
		
		if (temp)
			tx_inttext (temp);
		else
			tx_text ("failed");
		}
	
    return (0);
	}
