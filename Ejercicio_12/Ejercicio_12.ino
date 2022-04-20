// Programa por medio del cual debe iniciar encendido el LED conectado en PD2 y co el botón 
// A1 el LED encendido debe desplazarse de PD2 a PD5, mientras que con el botón A2 el desplazamiento debe ser de PD5 a PD2.
// Al llegar a un extremo la salida permanecerá sin cambios hasta que se presione el botón contrario al que llevó al LED encendido a ese extremo.

uint8_t conta = 0;
uint8_t tabla[] = {0x38, 0x34, 0x2C, 0x1C};

ISR(PCINT1_vect) {
	if (!(PINC & 0x02) && conta < 3) {
		conta++;
		PORTB = tabla[conta];
	}

	if (!(PINC & 0x04) && conta > 0) {
		conta--;
		PORTB = tabla[conta];
	}
}

void setup()
{
	DDRC = 0x00;	// Entrada
	DDRB = 0xFF;	// Salida

	PCMSK1 = 0x06; 	// Máscara para PC1 y PC2
	PCICR = 0x02;	// Habilita PCINT1

	PORTB = 0x38;	// Inicializa el primer led
}

void loop()
{
	
}