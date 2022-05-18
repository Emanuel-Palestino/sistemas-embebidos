// Comunicación Serial - Ejercicio 3 - Envío y Recepción de enteros
// Realice un programa para la tarjeta Arduino Uno que reciba dos enteros.
// Cada entero será una secuencia de caracteres ASCII terminada con un caracter no numérico.
// El MCU debe sumar los enteros y regresear el resultado.
// Configure para que la comunicación se realice a 9600 bps.
// Para simular se puede ocupar el mismo proyecto proteus del ejercicio 25

uint8_t estado = 0;
uint16_t n1 = 0, n2 = 0, suma;

void setup() {
	// Configuración I/O
	DDRD = 0x02;	// TxD como salida y RxD como entrada

	// Configuración USART0 (interrupción por recepción)
	UBRR0 = 103;	// Para 9600
	UCSR0A = 0x00;	// Normal Asíncrono
	UCSR0B = 0x98;	// Habilita Rx y Tx con interrupción por Rx
	UCSR0C = 0x06;	// Datos de 8 bits
}

ISR(USART_RX_vect) {
	uint8_t dato;
	dato = UDR0;
	if (estado == 0) {
		if (dato >= 0x30 && dato <= 0x39) {
			n1 *= 10;
			n1 += (dato - 0x30);
		} else {
			estado = 1;
		}
	} else {
		if (dato >= 0x30 && dato <= 0x39) {
			n2 *= 10;
			n2 += (dato - 0x30);
		} else {
			suma = n1 + n2;
			envia_numero(n1);
			envia_cadena(" + ");
			envia_numero(n2);
			envia_cadena(" = ");
			envia_numero(suma);

			estado = 0;
			n1 = n2 = 0;
		}
	}
}

void envia_numero(int16_t numero) {
	char algo[10];
	sprintf(algo, "%d", numero);
	envia_cadena(algo);
}

void envia_numero2(uint16_t numero) {
	uint8_t aux;
	if (numero >= 10)
		envia_numero2(numero / 10);
	aux = numero % 10;
	while(!(UCSR0A & 1 << UDRE0));
	UDR0 = aux + 0x30;
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

void loop() {
	
}