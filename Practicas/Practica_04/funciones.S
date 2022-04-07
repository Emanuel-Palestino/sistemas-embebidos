#include <avr/io.h>

.global conf_IO
conf_IO:
  clr R18
  out _SFR_IO_ADDR(DDRC), R18     // Entrada (A1, A2)
  ldi R19, 0x01
  out _SFR_IO_ADDR(DDRB), R19     // Salida PB0
  ldi R19, 0x90
  out _SFR_IO_ADDR(DDRD), R19     // Salida (PD7, PD4)
  ret

.global evalua_botones
evalua_botones:
  sbic _SFR_IO_ADDR(PINC), 1	// if (!(PINC & 0x02))
  jmp boton2					// else
  cpi R24, 9					// si
  brlo menor					// operador ternario
  ldi R24, 0
  ret
menor:
  inc R24
  ret
  
boton2:							
  sbic _SFR_IO_ADDR(PINC), 2	// if (!(PINC & 0x04))
  jmp salir						// else
  cpi R24, 0					// si
  breq iguales					// operador ternario
  dec R24
  ret
iguales:
  ldi R24, 9   
salir:
  ret


.global mostrar
mostrar:
  ldi R30, lo8(tabla)         // Z apunta a la tabla
  ldi R31, hi8(tabla)
  clr R20					// 0
  ser R21					// 1
  add R30, R24
  brcc salto1
  inc R31
salto1:
  lpm R18, Z						// auxiliar
  ldi R19, 8						// i

ciclo1:								// datos display
  mov R23, R18
  andi R23, 0x80					// if (auxiliar & 0x80)
  breq bitochoNo
  out _SFR_IO_ADDR(PORTB), R21		// PORTB = 0x01;
  jmp fin_cond1
bitochoNo:							// else
  out _SFR_IO_ADDR(PORTB), R20		// PORTB = 0x00;
fin_cond1:
  in R22, _SFR_IO_ADDR(PORTD)		//PORTD = PORTD | 0b10000000;
  ori R22, 0b10000000
  out _SFR_IO_ADDR(PORTD), R22
  in R22, _SFR_IO_ADDR(PORTD)		//PORTD = PORTD & 0b01111111;
  andi R22, 0b01111111
  out _SFR_IO_ADDR(PORTD), R22
  lsl R18							//auxiliar <<= 1;
  dec R19
  cpi R19, 0
  brne ciclo1

  ldi R18, 0x01						// auxiliar2
  ldi R19, 8						// i
ciclo2:
  mov R23, R18
  andi R23, 0x80					// if (auxiliar2 & 0x80)
  breq bitochoNo2
  out _SFR_IO_ADDR(PORTB), R21		// PORTB = 0x01;
  jmp fin_cond2
bitochoNo2:							// else
  out _SFR_IO_ADDR(PORTB), R20		// PORTB = 0x00;
fin_cond2:
  in R22, _SFR_IO_ADDR(PORTD)		//PORTD = PORTD | 0b10000000;
  ori R22, 0b10000000
  out _SFR_IO_ADDR(PORTD), R22
  in R22, _SFR_IO_ADDR(PORTD)		//PORTD = PORTD & 0b01111111;
  andi R22, 0b01111111
  out _SFR_IO_ADDR(PORTD), R22
  lsl R18							//auxiliar2 <<= 1;
  dec R19
  cpi R19, 0
  brne ciclo2

  in R22, _SFR_IO_ADDR(PORTD)		//PORTD = PORTD | 0b00010000;
  ori R22, 0b00010000
  out _SFR_IO_ADDR(PORTD), R22
  in R22, _SFR_IO_ADDR(PORTD)		//PORTD = PORTD & 0b11101111;
  andi R22, 0b11101111
  out _SFR_IO_ADDR(PORTD), R22

  ret

tabla:
 .byte  0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000
