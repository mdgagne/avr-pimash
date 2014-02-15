/*
 ************************************************************
 * PiMash - 
 * 	DS19B20 interface API
 ************************************************************
 */
#ifndef __ONEWIRE__
#define __ONEWIRE__
// Initialize the probe
unsigned char init_probe ();

// Starts a temp conversion
void start_convert ();

// Reads Th and Tl from a single DS18B20
unsigned int get_temp ();
#endif // __ONEWIRE__
