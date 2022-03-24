int contador;
// Tabla de valores
char display[][17] = {
	"1100000000000001",
	"1111100100000001",
	"1010010000000001",
	"1011000000000001",
	"1001100100000001",
	"1001001000000001",
	"1000001000000001",
	"1111100000000001",
	"1000000000000001",
	"1001100000000001"};

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
	// Datos
	for (int i = 0; i < 16; i++)
	{
		// Dato
		PORTB = display[contador][i];
		// SHCP Alto
		PORTD = PORTD | 0b10000000;

		// SHCP Bajo
		PORTD = PORTD & 0b01111111;
	}
	// STCP
	PORTD = PORTD | 0b00010000;
	PORTD = PORTD & 0b11101111;
}
