#include <TWI.h>
#include <Displays_MFS.h>

#define RTC 0x68

uint8_t estado = 1, estado_usart = 1, cont = 0;
char buffer[9];

void setup() {
	DDRC = 0x00;	// A1 entrada
	DDRD = 0x00; 	// Dato. Entrada de selección.

	PCMSK1 = 0x02; 	// Máscara para PC1
	PCICR = 0x02;	// Habilita PCINT1

	// Configuración USART
	UBRR0 = 103;
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;

	TWI_Config();
	initDisplays();

	// escribir(0x00, 0x00); // segundos
	// escribir(0x11, 0x01); // minutos
	// escribir(0x19, 0x02); // horas
	// escribir(0x03, 0x03); // dia (semana)
	// escribir(0x08, 0x04); // dia (mes)
	// escribir(0x06, 0x05); // mes
	// escribir(0x22, 0x06); // año

}

ISR(PCINT1_vect) {
	// Si se presiona el boton A1
	if (!(PINC & 0x02)) {
		estado = (estado < 3) ? estado + 1: 1;
	}
}

ISR(USART_RX_vect) {
	uint8_t segundos, minutos, horas, anyo, mes, dia, aux;
	aux = UDR0;

	switch (estado_usart) {
		case 1:
			if (aux == 'H' || aux == 'h') {
				lee(&segundos, 0x00);
				lee(&minutos, 0x01);
				lee(&horas, 0x02);
				sprintf(buffer, "%02d:%02d:%02d", bcd_a_decimal(horas),
					bcd_a_decimal(minutos), bcd_a_decimal(segundos));
				envia_cadena(buffer);
			}

			else if (aux == 'F' || aux == 'f') {
				lee(&dia, 0x04);
				lee(&mes, 0x05);
				lee(&anyo, 0x06);
				sprintf(buffer, "%02d/%02d/%02d", bcd_a_decimal(dia),
					bcd_a_decimal(mes), bcd_a_decimal(anyo));
				envia_cadena(buffer);
			}

			else if (aux == 'T' || aux == 't')
				estado_usart = 4;
			
			else if (aux == 'D' || aux == 'd')
				estado_usart = 5;
			
			else
				envia_cadena("Comando no definido");
			
			break;

		case 4:
			if (cont < 5) {
				buffer[cont] = aux;
				cont++;
			} else {
				buffer[cont] = aux;
				cont = 0;

				horas = (buffer[0] - 48) * 10 + (buffer[1] - 48);
				minutos = (buffer[2] - 48) * 10 + (buffer[3] - 48);
				segundos = (buffer[4] - 48) * 10 + (buffer[5] - 48);

				escribir(dec_a_bcd(segundos), 0x00);	// segundos
				escribir(dec_a_bcd(minutos), 0x01);		// minutos
				escribir(dec_a_bcd(horas), 0x02); 		// horas

				estado_usart = 1;
			}
			break;

		case 5:
			if (cont < 5) {
				buffer[cont] = aux;
				cont++;
			} else {
				buffer[cont] = aux;
				cont = 0;

				dia = (buffer[0] - 48) * 10 + (buffer[1] - 48);
				mes = (buffer[2] - 48) * 10 + (buffer[3] - 48);
				anyo = (buffer[4] - 48) * 10 + (buffer[5] - 48);

				escribir(dec_a_bcd(dia), 0x04);		// dia
				escribir(dec_a_bcd(mes), 0x05);		// mes
				escribir(dec_a_bcd(anyo), 0x06); 	// año

				estado_usart = 1;
			}
			break;
	}
}

void loop() {
	uint8_t segundos, minutos, horas, mes, dia;

	switch (estado) {
		case 1:
			lee(&minutos, 0x01);
			lee(&horas, 0x02);
			WriteInteger(bcd_a_decimal(horas) * 100 + bcd_a_decimal(minutos));
			break;
		case 2:
			lee(&segundos, 0x00);
			WriteInteger(bcd_a_decimal(segundos));
			break;
		case 3:
			lee(&dia, 0x04);
			lee(&mes, 0x05);
			WriteInteger(bcd_a_decimal(dia) * 100 + bcd_a_decimal(mes));
			break;
	}
}

uint8_t lee(uint8_t *minutos, uint8_t dir) {
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;

	edo = TWI_EscByte(RTC << 1); // Maestro Transmisor
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

	edo = TWI_EscByte((RTC << 1) | 0x01); // Maestro Receptor
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_LeeByte(minutos, 0); // Lee con nAck

	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	TWI_Paro();

	return 1;
}

uint8_t escribir(uint8_t minutos, uint8_t dir) {
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;

	edo = TWI_EscByte(RTC << 1); // Maestro Transmisor
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte(dir); // Escribe dirección de acceso
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte(minutos);
	if (edo != 0x01) {
		TWI_Paro();

		return 0;
	}

	TWI_Paro(); // Condición de Paro

	return 1;
}


uint8_t bcd_a_decimal(uint8_t bcd) {
	return (bcd / 16 * 10) + (bcd % 16);
}

uint8_t dec_a_bcd(uint8_t decimal) {
	return (decimal / 10 * 16) + (decimal % 10);
}

void envia_cadena(char *cad) {
	uint8_t c, i = 0;

	c = cad[0];
	while (c != 0x00){
		while (!(UCSR0A & 1 << UDRE0))
			; // Asegura buffer vacío
		UDR0 = c;
		i = i + 1;
		c = cad[i];
	}

	while (!(UCSR0A & 1 << UDRE0))
		; // Asegura buffer vacío
	UDR0 = 0x0D;
	while (!(UCSR0A & 1 << UDRE0))
		; // Asegura buffer vacío
	UDR0 = 0x0A;
}