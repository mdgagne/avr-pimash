/*
 ************************************************************
 * PiMash - 
 * 	Microcontroller component of the raspberry-pi 
 * 	based RIMS controller
 ************************************************************
 */
#ifndef __SF800__
#define __SF800__

// Init PB0 as input capture pin used to measure flow with SF800
void init_sf800 ();
void clear_flwcount ();
unsigned int get_flwcount ();

// Start/Stop the sampling the flow rate
void start_flwtimer ();
void stop_flwtimer ();
#endif //__SF800__
