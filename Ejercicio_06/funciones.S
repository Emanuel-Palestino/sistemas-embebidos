#include<avr/io.h>

.global delay_500ms
delay_500ms:
	LDI R20, 32
s3:
	LDI R19, 250
s2:
	LDI R18, 250
s1:
	DEC R18
	NOP
	BRNE s1

	DEC R19
	BRNE s2

	DEC R20
	BRNE s3

	RET