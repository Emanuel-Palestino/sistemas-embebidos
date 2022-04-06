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
  ldi R19, 8
ciclo1:
  //andi R18, 0x80
  sbrc R18, 7
  out _SFR_IO_ADDR(PORTB), R21
  out _SFR_IO_ADDR(PORTB), R20
  out _SFR_IO_ADDR(PORTD), R18
  ret

tabla:
 .byte  0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000
