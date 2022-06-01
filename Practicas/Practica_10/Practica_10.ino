uint16_t dato;


void setup() {

	DDRB = 0x2C;	// Interfaz SPI
	PORTB = 0x04;	// Esclavo inactivo

	// Config interfaz SPI
	SPCR = 0x50;	// SPI como maestro, modo 0. (Envía primero al MSB)
	SPSR = 0x01;	// fosc/2

	delay(100);


	// Deshabilita modo prueba
	dato = 0x0F00;
	envia_SPI(dato);

	// Define el número de displays a 8
	// dato = 0x0B07;
	// envia_SPI(dato);

	// for (uint16_t i = 1; i <= 8; i++){
	// 	dato = i << 4; 
	// 	envia_SPI(dato);
	// }

	// Apaga displays
	dato = 0x0C01;
	envia_SPI(dato);

	// Dato 
	// dato = 0x0107;
	// envia_SPI(dato);

	dato = 0x054F;
	envia_SPI(dato);
	
}

uint8_t envia_SPI(uint16_t dato) {
	uint8_t temp;

	// Habilita al esclavo, 1111 1011
	PORTB &= 0xFB;

	// Envía el byte alto
	SPDR = dato >> 8;
	while(!(SPSR & 1 << SPIF));
	temp = SPDR;

	// Envía el byte bajo
	SPDR = dato;
	while(!(SPSR & 1 << SPIF));
	temp = SPDR;

	// Esclavo inactivo
	PORTB = 0x04;

	delay(100);
}

void loop() {}