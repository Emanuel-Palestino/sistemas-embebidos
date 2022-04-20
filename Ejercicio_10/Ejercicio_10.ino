// Ejemplo 2: Contador de eventos
// El puerto B se incrementará cada vez que se presiona el botón 1 y tendrá un decremento al presionar al botón 2.
// Deberá contar de 0 a 9, pasando de 9 a 0 (UP) ó de 0 a 9 (DOWN)

uint8_t contador = 0;

ISR(INT0_vect) {
	contador = (contador < 9) ? contador + 1 : 0;
	PORTB = contador;
}

ISR(INT1_vect) {
	contador = (contador > 0) ? contador - 1 : 9;
	PORTB = contador;
}

void setup() {
	// Configuración I/O
	DDRD = 0x00;	// Entrada
	PORTD = 0x0C;	// Pull-up para el PD2 y PD3
	DDRB = 0xFF;	// Salida

	// Configuración INT0/INT1
	EICRA = 0x0A;	// Configurando INT0 y INT1 para que reaccione a flanco de bajada
	EIMSK = 0x03;	// Habilita INT0 y INT1
}

void loop() {
	
}