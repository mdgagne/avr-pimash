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
#include "sf800.h"

void ioinit () {
	// Init uart
	uart_115200();

	// Init 1-wire interface registers
	init_1wire ();

	// Init the SF800 I/O registers
	init_sf800 ();
	}

// Need to:
//	2) Use PID to adjust PV "On" pulse width
//	3) Read SF800 Flow Meter
//	4) Look for SP and Kp, Ki, Kd parameters from UART
int main (void) {
	ioinit ();
	start_flwtimer ();
	sei ();

	// Every 10 second output the flow rate
	char str[16];
	while (1) {
		_delay_ms(1000);
		tx_text("flowrate (l/min):");
		sprintf (str, "%f", (double)get_flwrate ());
		tx_text(str);
		}
	
// Read and report the temp	
	//clear_flwcount ();
	//while (1) {
	//	unsigned int count = get_flwcount ();
	//	sprintf (str, "count: %u", count);
	//	tx_text (str);
	//	_delay_ms (1000);
	//	}

	//char str[30];
	//while (1) {
		//tx_text ("Reading temp");
		//if (0 != start_convert ()) {
		//	tx_text ("Failed to start conversion");
		//	_delay_ms (1000);
		//	continue;
		//	}

		//_delay_ms (1000);	
		//unsigned int temp = get_temp ();
		
		//tx_text("temp:");
		//if (temp) {
		//	sprintf (str, "%04X hex", temp);
		//	tx_text(str);
		//	sprintf (str, "%4d.%01d c\n", temp >> 4, (temp << 12) / 6553);
		//	tx_text(str);
		//	}
		//else
		//	tx_text ("failed");	
		//}
	
    return (0);
	}
