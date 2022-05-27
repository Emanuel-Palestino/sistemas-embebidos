
void setup() {
	char cadena[] = "01234567890123456789";
	uint8_t conta;

	DDRB = 0x2C;	
	DDRD = 0xFF;
	PORTB |= 0x04;

	SPCR = 0x57;	// Preescala de 128. Sin interrupcion. Modo 1.
	SPSR = 0x00;

	delay(100);
	conta = 0;
	char c;
	do {
		c = cadena[conta];
		envia_SPI(c);
		conta++;
		delay(200);
	} while (c != 0x00);

	PORTD = envia_SPI(0xFF);
	
}

uint8_t envia_SPI(char caracter) {
	uint8_t aux;

	PORTB &= 0xFB;
	SPDR = caracter;

}

void loop() {}