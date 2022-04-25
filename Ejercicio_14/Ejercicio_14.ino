// Genere un tono de 400 Hz (aproximandamente) en PD6 para una respuesta automática, mientras se mantenga presionado un botón conectado en PC0.
// Para la revisión del botón se pueden emplear interrupciones por cambios en PC0
// T = 1/400Hz = 2.5ms = 2500us
// 1250us/62.5ns(Tiempo del micro) = 20000
// 20000/256 = 78.125 (cabe en 8bits)

void setup()
{
	// Config I/O
	DDRC = 0x00;		// Botón
	DDRD = 0x40;		// Salida en PD6
	// Config PCINT1
	// 	camios en PC0
	PORTC = 0x01; 		// Pull-up en PC0
	PCMSK1 = 0x01;		// Máscara para PC0
	PCICR = 0x02;		// Habilita PCINT1

	// Config Timer 0
	// 	modo ctc
	// 	preescala de 256
	// 	con respuesta automática
	// 	inicia sin reloj
	OCR0A = 78;			// Valor de comparación
	TCCR0A = 0x42;		// Modo CTC con respuesta automática
	TCCR0B = 0x00;		// Uso del reloj sin preescalador
}

ISR(PCINT1_vect) {
	if (!(PINC & 0x01)) {
		// preescalado de 256 al timer
		TCCR0B = 0x08;
	} else {
		// sin preescalado al timer
		TCCR0B = 0x00;
	}
}

void loop()
{
	
}