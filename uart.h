/*
 ************************************************************
 * UART - 
 * 	Communication API over UART
 ************************************************************
 */

#ifndef __UART__
#define __UART__
// intialize transmit/receive for 1200 baud 2 stop bits 8 data bits 
void uart_9600();

// recieve  single character over serial port
unsigned char rx_byte(void);

// non-blocking USART_receive implementation
unsigned char rx_byteNB(void);

// transmit a single character over serial port
void tx_byte(unsigned char data);

// converts integer to string, appends \r and \n transmits over serial
void tx_inttext(int num);

#endif //__UART__
