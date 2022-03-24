// Realice un decodificador de binario a 7 segmentos, utilizando un arreglo de constantes en memoria Flash

uint8_t tabla[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void setup()
{
	DDRC = 0x00;
	PORTC = 0xFF;
	DDRC = 0xFF;
}

void loop()
{
	uint8_t x;
	x = PINC & 0x0F;
	PORTD = tabla[x];
	delay(300);
}