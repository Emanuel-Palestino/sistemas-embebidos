uint8_t contador = 0, figura[8];

void setup() {

	DDRB = 0x2C;	// Interfaz SPI
	PORTB = 0x04;	// Esclavo inactivo

	// Configuración USART0 (interrupción por recepción)
	UBRR0 = 103;	// Para 9600
	UCSR0A = 0x00;	// Normal Asíncrono
	UCSR0B = 0x98;	// Habilita Rx y Tx con interrupción por Rx
	UCSR0C = 0x06;	// Datos de 8 bits

	// Config interfaz SPI
	SPCR = 0x50;	// SPI como maestro, modo 0. (Envía primero al MSB)
	SPSR = 0x01;	// fosc/2

	// Decodificador
	envia_SPI(0x09, 0x00);

	// Intensidad
	envia_SPI(0x0A, 0x07);

	// Límite
	envia_SPI(0x0B, 0x07);

	// Apagado
	envia_SPI(0x0C, 0x01);

	// Prueba
	envia_SPI(0x0F, 0x00);

	// Limpia LEDs
	limpia_leds();

	// Figura (UTM)
	envia_SPI(0x01, 0xA5);
	envia_SPI(0x02, 0xA7);
	envia_SPI(0x03, 0xA5);
	envia_SPI(0x04, 0xE5);
	envia_SPI(0x05, 0x38);
	envia_SPI(0x06, 0x10);
	envia_SPI(0x07, 0x10);
	envia_SPI(0x08, 0x10);

}

ISR(USART_RX_vect) {
	uint8_t dato;
	dato = UDR0;

	if (contador < 8){
		figura[contador] = dato;
		contador++;

		if (contador == 8) {
			envia_figura();
			contador = 0;
		}
	}
}

uint8_t envia_SPI(uint8_t reg, uint8_t value) {
	uint8_t temp;

	// Habilita al esclavo, 1111 1011
	PORTB &= 0xFB;

	// Envía el registro a modificar
	SPDR = reg;
	while(!(SPSR & 1 << SPIF));
	temp = SPDR;

	// Envía el valor
	SPDR = value;
	while(!(SPSR & 1 << SPIF));
	temp = SPDR;

	// Esclavo inactivo
	PORTB |= 0x04;

	return temp;
}

void envia_figura() {
	for (uint8_t i = 1; i <= 8; i++){
		envia_SPI(i, figura[i - 1]);
	}
}

void limpia_leds() {
	for (uint8_t i = 1; i <= 8; i++){
		envia_SPI(i, 0);
	}
}

void loop() {}
