#ifndef __ONEWIRE__
#define __ONEWIRE__

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


// DS18B20 Communication API
// NOTE: Assumes a single DS19B20 is on the bus and it is powered with external Vcc

// Sends reset pulse and waits for presence pulse from DS19B20
bool initCom ();

// Issues a convert command to all DS19B20s on the bus
bool startConvert ();

// Reads the first 3 bytes of the scratchpad in 
// order to get the Th and Tl from the DS18B20
unsigned short getTemp ();

#endif // __ONEWIRE__
