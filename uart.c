/*
 ************************************************************
 * PiMash - 
 * 	Communication API over UART
 ************************************************************
 */
#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

// *************************************************************
void uart_115200 () {
	#define BAUD 115200
	#include <util/setbaud.h>

	// set baud rate
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
   	UCSR0A |= (1 << U2X0);
	#else	
   	UCSR0A &= ~(1 << U2X0);
   	#endif

	// enable transmit and receive
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// set frame format to 8 data bits 2 stop bits
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);	
	}

// *************************************************************
unsigned char rx_byteNB(void) {
	// wait for data to be received
	if(UCSR0A & (1 << RXC0))	
		return UDR0;
	else
		return '\0';
	}

// *************************************************************
unsigned char rx_byte(void) {
	// wait for data to be received
	while( !(UCSR0A & (1 << RXC0)))
		{}
	
	return '\0';
	}

// *************************************************************
void tx_byte(unsigned char data) {
	// wait for empty transmit register
	while( !(UCSR0A & (1 << UDRE0)) )
		{}

	// put the data into output buffer
	UDR0 = data;
	}

// *************************************************************
void tx_inttext(int num) {
	int i ;
	char string[7];
	
	if(num !=0) {
		for(i = 4;i >=0; i--) {
			string[i] = num % 10 + '0';
			num /= 10;
			}
	
		// send character string
		for(i=0;i<=4;i++)
			tx_byte(string[i]);
		
			tx_byte('\r');
			tx_byte('\n');
		}
	}
