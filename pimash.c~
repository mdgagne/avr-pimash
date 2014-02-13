/*
 ************************************************************
 * PiMash - 
 * 	Microcontroller component of the raspberry-pi 
 * 	based RIMS controller
 ************************************************************
 */

#define F_CPU 12000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>	
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#define FOSC 12000000
#define BAUD 1200
#define UBRR FOSC/16/BAUD-1

// intialize data direction and call other intialization functions  	
void ioinit (void);

// intialize transmit/receive for 1200 baud 2 stop bits 8 data bits 
void USART_init(unsigned int ubrr);

// intialize input capture
void IC_init(void);

// recieve  single character over serial port
unsigned char  USART_receive(void);

// non-blocking USART_receive implementation
unsigned char  USART_receiveNB(void);

// transmit a single character over serial port
void USART_transmit(unsigned char data);

// converts integer to string, appends \r and \n transmits over serial
void inttostring(int num);

// checks to see if and 'i' or 'd' is received, increase decrease PWM accordingly
void checkserial(void);

// FIXME
// Need to:
//	1) Read temperature sensors
//	2) Use PID to adjust PV "On" pulse width
//	3) Read SF800 Flow Meter
//	4) Look for SP and Kp, Ki, Kd parameters from UART
int main (void) {
	ioinit();	
    return (0);
	}

void ioinit (void) {	
	}

unsigned char  USART_receiveNB(void) {
	// wait for data to be received
	//if(UCSRA & (1 << RXC))	
	//return UDR;
	//else
	return '\0';
	}

unsigned char  USART_receive(void) {
	// wait for data to be received
	//while( !(UCSRA & (1 << RXC))){}
	return '\0';
	}

void USART_transmit(unsigned char data) {
	// wait for empty transmit register
	//while( !(UCSRA & (1 << UDRE)) ){}

	// put the data into output buffer
	//UDR = data;
	}

void inttostring(int num) {
	int i ;
	char string[7];
	
	if(num !=0) {
		for(i = 4;i >=0; i--) {
			string[i] = num % 10 + '0';
			num /= 10;
			}
	
		// send character string
		for(i=0;i<=4;i++)
			USART_transmit(string[i]);
		
			USART_transmit('\r');
			USART_transmit('\n');
		}
	}



