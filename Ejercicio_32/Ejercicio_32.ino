// Ejercicio 2 - Salida a 7 seg
// Utilizando la función anterior, escriba un programa que revise un teclado matricial y coloque el valor
// de la tecla presionada en un display de 7 segmentos.
uint8_t tabla[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void setup() {
	DDRB = 0x0F;	// Renglones
	DDRC = 0x00;	// Columnas
	PORTC = 0x0F;	// Pull-up
	DDRD = 0xFF;	// Display
}

void loop() {
	uint8_t temp;
	temp = teclado();
	if (temp != 0xFF)
		PORTD = tabla[temp];
	delay(300);
}

uint8_t teclado() {
	uint8_t sondeo[] = {0x0E, 0x0D, 0x0B, 0x07};
	uint8_t i, aux;

	for (i = 0; i < 4; i++) {
		PORTB = sondeo[i];
		asm("NOP");
		aux = PINC & 0x0F;
		if (aux != 0x0F) {
			switch(aux) {
				//	val = 4 * renglon + columna
				case 0x0E: return 4 * i + 0;
				case 0x0D: return 4 * i + 1;
				case 0x0B: return 4 * i + 2;
				case 0x07: return 4 * i + 3;
			}
		}
	}

	return 0xFF;
}