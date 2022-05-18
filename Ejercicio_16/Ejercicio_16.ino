// 4. Configure la tarjeta Arduion para que genere un tono de 500 Hz, mientras se mantenga presionado un botón concectado en PC0.
// Uilice respuesta automática del temporizador, por lo que el tono se va a generar en OC1A (PB1).
// Para detectar los eventos en el botón, haga uso de las interrupciones por cambios en las terminales.

ISR(PCINT1_vect) {
  if (!(PINC & 0x01)) {
    TCCR1B = 0x09;  // Reloj al timer 1
  } else {
    TCCR1B = 0x08;  // Quitando reloj al timer 1
  }
}

void setup()
{
	DDRC = 0x00;		// Entrada (PC0)
	PORTC = 0x01;		// PUll-up en PC0
	DDRB = 0x02;		// PB1 como salida

	// Configuración de la PC INT1
	PCMSK1 = 0x01;		// Máscara para PC0
	PCICR = 0x02;		// Habilita PCINT1

	// Configuración de Timer 1
	OCR1A = 15999;		// Valor Máximo
	TCCR1A = 0x40;		// Modo CTC con respuesta automática
	TCCR1B = 0x08;		// Inicia sin reloj
	TCCR1C = 0x00;

}

void loop()
{
	
}
