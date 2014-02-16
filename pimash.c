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
#include <stdio.h>
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
	char str[30];


	// Read and report the temp	
	while (1) {
		tx_text ("Reading temp");
		if (0 != start_convert ()) {
			tx_text ("Failed to start conversion");
			_delay_ms (1000);
			continue;
			}

		_delay_ms (1000);	
		unsigned int temp = get_temp ();
		
		tx_text("temp:");
		if (temp) {
			sprintf (str, "%04X hex", temp);
			tx_text(str);
			sprintf (str, "%4d.%01d c\n", temp >> 4, (temp << 12) / 6553);
			tx_text(str);
			}
		else
			tx_text ("failed");	
		}
	
    return (0);
	}
