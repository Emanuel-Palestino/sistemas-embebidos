int contador;
// Tabla de valores
uint8_t display[] = {
	0b11000000,
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10011000};

void setup()
{
	// CONFIGURACIÓN I/O

	// Establece A1 y A2 como entradas
	DDRC = 0x00;
	// Establece PB0, PD7 y PD4 como salidas
	DDRB = 0x01;
	DDRD = 0x90;

	// Inicializa contador
	contador = 0;
	mostrarNumero();
}

void loop()
{
	// MANIPULAR EL CONTADOR

	// Si se presiona el boton A1
	if (!(PINC & 0x02))
	{
		contador = (contador < 9) ? contador + 1 : 0;
		// Muestra el número en el display
		mostrarNumero();
	}
	// Si se presiona el boton A2
	if (!(PINC & 0x04))
	{
		contador = (contador > 0) ? contador - 1 : 9;
		// Muestra el número en el display
		mostrarNumero();
	}

	delay(200);
}

void mostrarNumero()
{
	// Datos de 7 segmentos del display
	uint8_t auxiliar = display[contador];
	for (int i = 0; i < 8; i++)
	{
		// Dato
		if (auxiliar & 0x80)
			PORTB = 0x01;
		else
			PORTB = 0x00;

		// reloj SHCP Alto
		PORTD = PORTD | 0b10000000;
		// reloj SHCP Bajo
		PORTD = PORTD & 0b01111111;

		// Corrimiento
		auxiliar <<= 1;
	}

	// Datos de los displays
	uint8_t auxiliar2 = 0x01;
	for (int i = 0; i < 8; i++)
	{
		// Dato
		if (auxiliar2 & 0x80)
			PORTB = 0x01;
		else
			PORTB = 0x00;

		// reloj SHCP Alto
		PORTD = PORTD | 0b10000000;
		// reloj SHCP Bajo
		PORTD = PORTD & 0b01111111;

		// Corrimiento
		auxiliar2 <<= 1;
	}

	// reloj STCP
	PORTD = PORTD | 0b00010000;
	PORTD = PORTD & 0b11101111;
}
