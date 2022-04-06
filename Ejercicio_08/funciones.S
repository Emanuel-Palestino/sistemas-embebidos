#include "avr/io.h"

.global MEF
MEF:
	LDI R30, lo8(tabla)
	LDI R31, hi8(tabla)		// Z apunta a la dirección de la tabla
	LSR R31					// Se divide entre 2, haciendo un acarreo teniendo en cuenta el acarreo
	ROR R30
	ADD R30, R24			// A Z le sumamos el número de estado
	BRCC no_carry			// Esto es para considerar el acarreo en la suma de 8 bits
	INC R31
no_carry:
	IJMP					// Se salt al caso correspondiente

tabla:
	RJMP caso_0
	RJMP caso_1
	RJMP caso_2
	RJMP caso_3

caso_0:
	LDI R18, 0x00
	OUT _SFR_IO_ADDR(PORTB), R18
	SBIS _SFR_IO_ADDR(PINC), 1
	RET
	LDI R24, 0x01
	RET

caso_1:
	LDI R18, 0x04
	OUT _SFR_IO_ADDR(PORTB), R18
	SBIC _SFR_IO_ADDR(PINC), 2		// if(TA == 0)
	LDI R24, 0x02					// estado = 2
	SBIS _SFR_IO_ADDR(PINC), 1		// else if(SP == 1)
	LDI R24, 0x03					// estado = 3
	RET

caso_2:
	LDI R18, 0x00
	OUT _SFR_IO_ADDR(PORTB), R18
	SBIS _SFR_IO_ADDR(PINC), 1
	LDI R24, 0x03
	RET

caso_3:
	LDI R18, 0x08
	OUT _SFR_IO_ADDR(PORTB), R18
	SBIC _SFR_IO_ADDR(PINC), 1
	LDI R24, 0x01
	SBIC _SFR_IO_ADDR(PINC), 3
	LDI R24, 0x00
	RET