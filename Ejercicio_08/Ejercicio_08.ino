// Máquina de estados para una puerta automática. Utilizando Ensamblador
extern "C" uint8_t MEF(uint8_t);

uint8_t Estado;

void setup()
{
	// Configuración de puertos
	DDRC = 0x00;
	DDRB = 0xFF;
	Estado = 0;
}

void loop()
{
	Estado = MEF(Estado);
	delay(100);
}
