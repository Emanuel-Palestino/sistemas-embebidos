// Realice una rutina en ensamblador para un delay de medio segundo

extern "C" void delay_500ms();

void setup()
{
	DDRB = 0x04;	// PB2 como salida
}

void loop()
{
	PINB = 0x04;	// Conmuta PB2
	delay_500ms();
}
