#include <avr/io.h>

.global conf_IO
conf_IO:
	clr R18
	out _SFR_IO_ADDR(DDRC), R18			// Entrada
	ser R19
	out _SFR_IO_ADDR(PORTC), R19		// Pull up
	out _SFR_IO_ADDR(DDRD), R19			// Salida
	ret

.global decodifica
decodifica:
	in R19, _SFR_IO_ADDR(PINC)
	andi R19, 0x0F						// Número a decodificar
	ldi R30, lo8(tabla)					// Z apunta a la tabla
	ldi R31, hi8(tabla)
	add R30, R19
	brcc salto1
	inc R31
salto1:
	lpm R18, Z
	out _SFR_IO_ADDR(PORTD), R18
	ret


tabla:
	.byte 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71