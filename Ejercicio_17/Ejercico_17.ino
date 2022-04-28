// Configure la tarjeta Arduino para que haga parpadear al LED conectado en PB2 del shield multifunción, 
// con una frecuencia de 1 Hz, mientras se mantenga presionado el botón A1(PC1)
// Nuevamente se hará uso de las interrupciones por cambios en las terminales para detectar los eventos en el botón.
// Pero la respuesta automática del temporizador 1 ahora será en la salida OC1B

void setup()
{
	// config. I/O
	DDRC = 0x00;
	DDRB = 0x04;	// Salida en PB2
	DDRD = 0x08;	// PD3 es salida
	PORTD = 0x08; 	// Buzzer Apagado

	// config. PCINT1
	PCMSK1 = 0x02;	// Máscara para PC1
	PCICR = 0x02;	// Habilita PCINT1

	// config. Timer 1
	ICR1 = 31249;
	OCR1B = 31249;
	TCCR1A = 0x10;	// Modo 12, Respuesta automática en OC1B
	TCCR1B = 0x18;
	TCCR1C = 0x00;
}

ISR(PCINT1_vect) {
	if(!(PINC & 0x02)) {
		TCCR1B = 0x1C;	// reloj con preescalador
		PORTD = 0x00;
	} else {
		TCCR1B = 0x18;	// sin reloj
		PORTD = 0x08;
	}
}

void loop()
{
	
}