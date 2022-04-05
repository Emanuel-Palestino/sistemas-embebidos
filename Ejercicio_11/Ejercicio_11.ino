// Ejercicio: Control simple
// Se pretende mantener la temperatura de un horno en una temperatura de referencia.

ISR(INT0_vect) {
	PORTB = 0x00;	// Apaga
}

ISR(INT1_vect) {
	PORTB = 0x01;	// Enciende
}

void setup() {
	DDRD = 0x00;	// Entrada
	DDRB = 0x01;	// Salida

	EICRA = 0x0F;	// Se activan con flanco de subida
	EIMSK = 0x03;	// Habilita int0/int1
	
	PORTB = 0x00;
	if(PIND & 0x08)
		PORTB = 0x01;
}

void loop() {
}