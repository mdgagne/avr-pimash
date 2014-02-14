#ifndef __ONEWIRE__
#define __ONEWIRE__

// DS18B20 supported Commands
#define SKIPROM     0xCC
#define CONVERT     0x44
#define WRITESCH    0x4E
#define READSCH     0xBE
#define CPYSCH      0x48

// DS18B20 Not-yet supported Commands
//#define SEARCHROM   0xf0
//#define READROM     0x33
//#define MATCHROM    0x55
//#define RECALLE2    0xB8
//#define READPWR     0xB4
//#define ALMSEARCH   0xEC

// DS18B20 Communication API
// NOTE: Assumes a single DS19B20 is on the bus and it is powered with external Vcc
void initCom ();
void sendCommand (char cmd);


#endif // __ONEWIRE__
