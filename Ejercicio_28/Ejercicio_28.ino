// Ejemplo 2 - Manejo de un DAC
// Para evaluar el comportamiento del DAC, realice un programa que digitalice una entrada analógica
// y utilice el valor digital para enviarlo al DAC a través de la interfaz SPI.
// El estado del interruptor debe determinar el valor del bit GA' para establecer la ganacia.

void setup() {
	// Config I/O
	DDRC = 0x00;	// Entrada para el ADC
	DDRD = 0x00;	// Entrada para el botón
	PORTD = 0x01;	// Pull-up para el botón
	DDRB = 0x2C;	// Interfaz SPI
	PORTB = 0x04;	// Esclavo inactivo

	// Config interfaz SPI
	SPCR = 0x50;	// SPI como maestro, modo 0. (Envía primero al MSB)
	SPSR = 0x01;	// fosc/2

	// Config ADC
	ADMUX = 0x40;
	ADCSRA = 0xCF;
	DIDR0 = 0x01;


}

ISR(ADC_vect) {
	uint16_t dato;
	uint8_t temp;

	// Prepara el dato a enviar
	dato = ADCW << 2;
	dato |= 0x1003;   
	if (PINC & 0x01)
		dato |= 0x2000;

	// Habilita al esclavo
	PORTB &= 0xFB;

	// Envía el byte alto
	SPDR = dato >> 8;
	while(!(SPSR & 1 << SPIF));
	temp = SPDR;

	// Envía el byte bajo
	SPDR = dato;
	while(!(SPSR & 1 << SPIF));
	temp = SPDR;

	// Deshabilita el esclavo
	PORTB |= 0x04;

	// Inicia nueva conversión
	ADCSRA |= 1 << ADSC;
}

void loop() {}