// TWI - Ejemplo 1 - Mestro
#include <TWI.h>

void setup() {
	DDRB = 0x00;  // Selección y envío
	PORTB = 0x07; // Pull-up
	DDRD = 0x00;  // Dato. Entrada de selección.
	PORTD = 0xFF; // Pull-up

	TWI_Config();
}

void loop() {
	uint8_t esclavo, dato, edo;
	if (!(PINB & 0x01)) {
		dato = PIND;
		esclavo = PINB & 0x06;
		edo = TWI_Inicio();
		if (edo == 0x01) {	// SLA + w
			edo = TWI_EscByte(esclavo);	// Dirección del esclavo
			if (edo == 0x01)
				TWI_EscByte(dato);		// Mandamos dato
			TWI_Paro();
		}
	}

	delay(300);
}