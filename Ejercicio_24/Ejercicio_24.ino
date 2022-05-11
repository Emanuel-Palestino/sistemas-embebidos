// Comunicación Serial - Ejercicio 1 - Programa ECO
// Escriba un programa EXO que transmita cualquier caracter 

void setup()
{
	// Configuración I/O
	DDRD = 0x02;	// RXD es entrada y TXD salida

	// Configuración USART0
	UBRR0 = 207;	// Para 4800 bps
	UCSR0A = 0x00; 	// Asíncrono Normal
	UCSR0B = 0x98;	// Habilita Tx y Rx con interrupción por Rx
	UCSR0C = 0x06;	// Datos de 8 bits, sin paridad y 1 bit de paro
}

ISR(USART_RX_vect) {
	uint8_t aux;
	aux = UDR0;
	while(!(UCSR0A & 1 << UDRE0));	// Asegura buffer vacío
	UDR0 = aux;
}

void loop()
{
	
}
