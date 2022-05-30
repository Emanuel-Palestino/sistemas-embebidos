// TWI - Ejemplo 2
#include<TWI.h>

uint8_t escribe_RAM(uint8_t datos[], uint8_t n, uint8_t dir) {
	uint8_t edo;
	edo = TWI_Inicio();
	if (edo != 0x01) return 0x00;

	edo = TWI_EscByte(0x50 << 1);
	if (edo != 0x01) {
		TWI_Paro();
		return 0x00;
	}

	if(TWI_EscByte(dir) != 0x01) {
		TWI_Paro();
		return 0x00;
	}

	for(uint8_t i = 0; i < n; i++) {
		if (TWI_EscByte(datos[i]) != 0x01) {
			TWI_Paro();
			return 0x00;
		}
	}

	TWI_Paro();
	return 0x01;
}
uint8_t lee_RAM(uint8_t datos[], uint8_t n, uint8_t dir) {
	uint8_t edo;
	edo = TWI_Inicio();
	if (edo != 0x01) return 0x00;

	// Direción del esclavo
	edo = TWI_EscByte(0x50 << 1);
	if (edo != 0x01) {
		TWI_Paro();
		return 0x00;
	}

	// Dirección de Acceso
	if(TWI_EscByte(dir) != 0x01) {
		TWI_Paro();
		return 0x00;
	}

	// Inicio Repetido
	if (TWI_Inicio() != 0x01) {
		TWI_Paro();
		return 0x00;
	}

	// Dirección del esclavo para leer
	edo = TWI_EscByte(0x50 << 1) | 0x01;	// SLA + R
	if (edo != 0x01) {
		TWI_Paro();
		return 0x00;
	}

	// Lee los n-1 datos
	for(uint8_t i = 0; i < n - 1; i++) {
		edo = TWI_LeeByte(&datos[i], 1);
		if (edo != 0x01) {
			TWI_Paro();
			return 0x00;
		}
	}

	// Lee el último dato
	TWI_LeeByte(&datos[n - 1], 0);
	TWI_Paro();
	return 0x01;
}

void setup() {

}

void loop() {}