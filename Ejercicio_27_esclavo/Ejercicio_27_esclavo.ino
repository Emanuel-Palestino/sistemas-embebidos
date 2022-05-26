// Ejemplo 1: Arduino como Maestro y Esclavo

uint8_t conta;

void setup() {
	DDRB = 0x10;	// MISO en salida
	DDRD = 0xFF;

	SPCR = 0xC4;	// Habilita SPI en modo 1 con interrupciones
	SPSR = 0x00;

}

ISR(SPI_STC_vect) {
	uint8_t aux;
	aux = SPDR;

	if (aux != 0x00) {
		PORTD = aux;
		conta++;
	} else {
		SPDR = conta;
		conta = 0;
	}
}

void loop() {
}