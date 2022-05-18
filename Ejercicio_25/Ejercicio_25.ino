// Comunicación Serial - Ejercicio 2 - Envío y recepción de caracteres
// Realice un programa para la tarjeta Arduino Uno que reciba una cadena de caracteres terminada con '$',
// cuente los caracteres antes del carácter '$' y regrese la cadena y la longitud de la cadena. Considere un máximo de 99 caracteres.
// Configure para que la comunicación se realice a 9600bps

char cadena[100];
uint8_t i = 0;

void setup() {
	// Configuración I/O
	DDRD = 0x02;	// TxD como salida y RxD como entrada

	// Configuración USART0 (interrupción por recepción)
	UBRR0 = 103;	// Para 9600
	UCSR0A = 0x00;	// Normal Asíncrono
	UCSR0B = 0x98;	// Habilita Rx y Tx con interrupción por Rx
	UCSR0C = 0x06;	// Datos de 8 bits
}

void envia_cadena(char cad[]) {
  uint8_t k = 0;
  while(cad[k] != 0) {
    while(cad[k] != 0) {
      while(!(UCSR0A & 1 << UDRE0));
      UDR0 = cad[k];
      k++;
    }
  }
}

ISR(USART_RX_vect) {
	uint8_t aux;
	aux = UDR0;

	if (aux != '$') {
		cadena[i] = aux;
		i++;
	} else {
		envia_cadena("La cadena \"");
		cadena[i] = 0;	// fin de cadena
		envia_cadena(cadena);
		envia_cadena("\" tiene ");
		while(!(UCSR0A & 1 << UDRE0));
		UDR0 = (i / 10) + 48;
		while(!(UCSR0A & 1 << UDRE0));
		UDR0 = (i % 10) + 48;
		envia_cadena(" caracteres.\n");
		i = 0;
	}
}

void loop() {
	
}
