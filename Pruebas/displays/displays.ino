#define L 4 // puerto de comunicación
#define C 7 // puerto para reloj
#define D 8 // puerto de datos
const byte MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
const byte POSICION[] = {0xF1, 0xF2, 0xF4, 0xF8};
void setup()
{
	pinMode(L, OUTPUT);
	pinMode(C, OUTPUT);
	pinMode(D, OUTPUT);
}
void loop()
{
	Escribe(3, 0);
	Escribe(2, 1);
	Escribe(1, 2);
	Escribe(0, 3);
}

void Escribe(byte Segmento, byte Valor)
{
	digitalWrite(L, LOW);
	shiftOut(D, C, MSBFIRST, MAP[Valor]);
	shiftOut(D, C, MSBFIRST, POSICION[Segmento]);
	digitalWrite(L, HIGH);
}