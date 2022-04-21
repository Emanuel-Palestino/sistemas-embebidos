uint16_t dato;
// Tabla de valores
uint8_t numeros[] = {
	0b11000000,
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10011000
  };

ISR(PCINT1_vect) {
	// Si se presiona el boton A1
	if (!(PINC & 0x02))
	{
		dato = 1000;
	}
	// Si se presiona el boton A2
	if (!(PINC & 0x04))
	{
		dato = (dato < 1000) ? dato + 1 : 0;
	}
	// Si se presiona el boton A3
	if (!(PINC & 0x08))
	{
		dato = (dato > 0) ? dato - 1 : 1000;
	}
}
void setup()
{
	// CONFIGURACIÓN I/O

	// Establece A1 y A2 como entradas
	DDRC = 0x00;
	// Establece PB0, PD7 y PD4 como salidas
	DDRB = 0x01;
	DDRD = 0x90;

  PCMSK1 = 0x0E; 	// Máscara para PC1, PC2 y PC3
	PCICR = 0x02;	// Habilita PCINT1

	// Inicializa contador
	dato = 0;
	mostrar(1,1);
}

void loop()
{
  uint8_t unidad;
  uint16_t aux=dato;
  for (int i=3;i>=0;i--){
    unidad= aux % 10;
    aux= aux/10;
    mostrar(unidad, potencia(2,i));
    delay(5);
  }
}

void mostrar(uint8_t dato, uint8_t display)
{
	// Datos de 7 segmentos del display
	uint8_t auxiliar = numeros[dato];
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
	uint8_t auxiliar2 = display;
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
uint8_t potencia(uint8_t base, uint8_t mipow)
{
    if(mipow==0)
     return 1;
    uint8_t resultado = base;
    while (mipow > 1)
    {
        resultado = resultado * base;
        mipow --;
    }
    return resultado;
}
