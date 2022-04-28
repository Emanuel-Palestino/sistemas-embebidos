// Empleando PWM, controle la intensidad del LED conectado en PB2, manjenado 5 niveles. Con el botón A1 se hará el cambio de intensidad,
// la cual será modificada con incrementos de un 20% cada vez que el botón es presionado. (Al encender el sistema, el LED debe estar apagado).
// Para una adecuada operación del LED, configure para que la señal PWM tenga unn frecuencia de 100Hz.

uint16_t ancho = 0;

void setup()
{
	// config. I/O
	DDRC = 0x00;
	DDRB = 0x04;  // Salida en PB2

	// config. PCINT1
	PCMSK1 = 0x02; // Máscara para PC1
	PCICR = 0x02;  // Habilita PCINT1

	// config. Timer 1 para PWM
	OCR1A = 20000;	// Valor máximo
	OCR1B = 0;		// Inicia Apagado
	TCCR1A = 0x33;	// Modo 15, Modo invertido
	TCCR1B = 0x1A;	// Preescalado de 8
	TCCR1C = 0x00;
}

ISR(PCINT1_vect) {
	if(!(PINC & 0x02)) {
		ancho = (ancho < 20000) ? ancho + 4000 : 0;
		OCR1B = ancho;
	}
}

void loop()
{
	
}