// Realice un decodificador de binario a 7 segmentos, utilizando un arreglo de constantes en memoria Flash USANDO ENSAMBLADOR

extern "C" void conf_IO();
extern "C" void decodifica();

void setup()
{
	conf_IO();
}

void loop()
{
	decodifica();
	delay(300);
}