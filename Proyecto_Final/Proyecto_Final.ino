#include <TWI.h>

#define RGB_SENSOR 0x29

void setup() {
	DDRC = 0x00;	// A1 entrada
	DDRD = 0x00; 	// Dato. Entrada de selección.

	PCMSK1 = 0x02; 	// Máscara para PC1
	PCICR = 0x02;	// Habilita PCINT1

	// Configuración USART
	// UBRR0 = 103;
	// UCSR0A = 0x00;
	// UCSR0B = 0x98;
	// UCSR0C = 0x06;

	TWI_Config();
	Serial.begin(9600);

	uint8_t dato[2], edo;

	// edo = lee(&dato, 0x92);
	// Serial.println("Dato: " + String(dato) + "Edo: " + String(edo));

	// Inicialización del sensor
	escribir(0, 0x81);	// maxima sensibilidad
	escribir(0, 0x8F);	// ganancia en 1
	escribir(3, 0x80);	// habilita ADC y activa el sensor




}


// ISR(USART_RX_vect) {
// 	uint8_t aux;
// 	aux = UDR0;

// }

void loop() {
	uint16_t r, g, b;
	getRGB(&r, &g, &b);

	Serial.println(String(r) + "," + String(g) + "," + String(b));

	delay(500);
}

uint8_t lee(uint8_t *dato, uint8_t dir) {
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;

	edo = TWI_EscByte(RGB_SENSOR << 1); // Maestro Transmisor
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}
	
	edo = TWI_EscByte(dir); // Escribe dirección de acceso
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_Inicio(); // Inicio repetido
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte((RGB_SENSOR << 1) | 0x01); // Maestro Receptor
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

/////////////////////////////
	edo = TWI_LeeByte(&dato[0], 1); // Lee con Ack

	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_LeeByte(&dato[1], 0); // Lee con nAck

	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	TWI_Paro();

	return 1;
}

uint8_t escribir(uint8_t dato, uint8_t dir) {
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;

	edo = TWI_EscByte(RGB_SENSOR << 1); // Maestro Transmisor
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte(dir); // Escribe dirección de acceso
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte(dato);
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	TWI_Paro(); // Condición de Paro

	return 1;
}

void getRGB(uint16_t *r, uint16_t *g, uint16_t *b) {
	uint8_t datos[2];
	float val1, val2, val3;
	uint32_t clear;

	lee(datos, 0x94);
	clear = (datos[1] << 8) | datos[0];

	lee(datos, 0x96);
	*r = (datos[1] << 8) | datos[0];

	lee(datos, 0x98);
	*g = (datos[1] << 8) | datos[0];

	lee(datos, 0x9A);
	*b = (datos[1] << 8) | datos[0];

	// Serial.print("Clear: " + String(clear) + ", UNO: ");
  	// Serial.println(String(*r) + "," + String(*g) + "," + String(*b));


	if (clear == 0) {
		*r = *g = *b = 0;
		return;
	}

	val1 = (float)*r / clear * 255.0;
	val2 = (float)*g / clear * 255.0;
	val3 = (float)*b / clear * 255.0;

	if (val1 > 255)
		val1 = 255;

	if (val2 > 255)
		val2 = 255;

	if (val3 > 255)
		val3 = 255;

	*r = (uint16_t)val1;
	*g = (uint16_t)val2;
	*b = (uint16_t)val3;
  
}

// void envia_cadena(char *cad) {
// 	uint8_t c, i = 0;

// 	c = cad[0];
// 	while (c != 0x00){
// 		while (!(UCSR0A & 1 << UDRE0))
// 			; // Asegura buffer vacío
// 		UDR0 = c;
// 		i = i + 1;
// 		c = cad[i];
// 	}

// 	while (!(UCSR0A & 1 << UDRE0))
// 		; // Asegura buffer vacío
// 	UDR0 = 0x0D;
// 	while (!(UCSR0A & 1 << UDRE0))
// 		; // Asegura buffer vacío
// 	UDR0 = 0x0A;
// }
