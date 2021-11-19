/**
\file uart.h

University of Colorado Boulder <br>
ECEN 5803 Mastering Embedded System Architecture <br>

Function prototypes for the UART 
*/

#ifndef __UART_H__
#define __UART_H__

void uart_init();
void uart_printf(const char * format, ... );

#endif