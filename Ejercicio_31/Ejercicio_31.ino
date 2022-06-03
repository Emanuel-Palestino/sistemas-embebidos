// Ejercicio 1 - Sondeo de teclado
// Desarrolle una funnción que haga el sondeo de un teclado matricial de 4x4 y regrese el valor de la tecla presionada
//o 0xFF si no hay tecla presionada.

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