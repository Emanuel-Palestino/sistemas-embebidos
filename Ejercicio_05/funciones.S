#include "avr/io.h"

.global conf_IO
conf_IO:
	clr R18
	out _SFR_IO_ADDR(DDRC), R18		// Entrada
	out _SFR_IO_ADDR(DDRB), R18
	ser R19
	out _SFR_IO_ADDR(PORTC), R19		// Pull-Up
	out _SFR_IO_ADDR(PORTB), R19
	out _SFR_IO_ADDR(DDRD), R19		// Salida
	ret

.global suma
suma:
	//in R20, _SFR_IO_ADDR(PINC)
	//andi R20, 0x0F
	//in R21, _SFR_IO_ADDR(PINB)
	//andi R21, 0x0F
	add R24, R22					// Recibimos los argumentos
	out _SFR_IO_ADDR(PORTD), R24
	ret
