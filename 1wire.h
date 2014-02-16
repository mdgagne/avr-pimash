/*
 ************************************************************
 * PiMash - 
 * 	DS19B20 interface API
 * 	Adapted from Peter Dennegger's (danni@specs.de) 
 * 	1-Wire Example
 ************************************************************
 */
#ifndef __ONEWIRE__
#define __ONEWIRE__
// Initialize IO register and data direction
void init_1wire ();

// Starts a temp conversion
unsigned int start_convert ();

// Reads the temp from a 1-probe bus, checks CRC
// Returns -1 on failure
unsigned int get_temp ();
#endif // __ONEWIRE__
