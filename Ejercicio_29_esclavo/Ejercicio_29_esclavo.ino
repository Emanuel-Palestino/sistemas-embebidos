// TWI - Ejemplo 1 - Mestro

void setup() {
	DDRB = 0x00;	// Entrada
	PORTB = 0x03;	// Pull-up
	DDRD = 0xFF;	// Salida

	uint8_t aux;
	aux = PINB & 0x03;	// Lee dirección de esclavo
	aux = (aux << 1) | 0x01;
	TWAR = aux;		// Ubica dirección con llamadas generales
	TWCR = 0x45;	// Habilita TWI con Ack e interrupciones
}

ISR(TWI_vect) {
	uint8_t estado;
	estado = TWSR & 0xF8;
	switch(estado) {
		case 0x60:
		case 0x70:
			TWCR |= 1 << TWINT;
			break;		// Limpia bandera
		case 0x80:
		case 0x90:		// Recibió un dato
			PORTD = TWDR;
			TWCR |= 1 << TWINT;
		default:		// Respuesta inesperada
			TWCR |= (1 << TWINT) | (1 << TWSTO);
	}
}

void loop() {}