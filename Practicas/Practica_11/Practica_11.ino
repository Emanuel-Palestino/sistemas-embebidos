#include <TWI.h>
#include <Displays_MFS.h>

#define RTC 0x68

void setup() {
	DDRC = 0x00;
	DDRD = 0x00;  // Dato. Entrada de selección.

	TWI_Config();
	initDisplays();
  	WriteDigit(3, 0b10001100);

	// escribir(0x00, 0x00); // segundos
	// escribir(0x55, 0x01); // minutos
	escribir(0x20, 0x02); // horas
	// escribir(0x02, 0x03); // dia (semana)
	// escribir(0x07, 0x04); // dia (mes)
	// escribir(0x06, 0x05); // mes
	// escribir(0x22, 0x06); // año

	// Serial.begin(9600);
}

void loop() {
	uint8_t dato, valor;

	lee(&dato, 0x01);
	// Serial.print("Min: ");
	// Serial.println(dato, HEX);

	valor = dato;

	lee(&dato, 0x02);
	// Serial.print("Hor: ");
	// Serial.println(dato, HEX);

	WriteInteger(dato * 100 + valor);
	

	// Serial.println("");

	// delay(1000);
}

uint8_t lee(uint8_t *dato, uint8_t dir)
{
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;

	edo = TWI_EscByte(RTC << 1); // Maestro Transmisor
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}
	
	edo = TWI_EscByte(dir); // Escribe dirección de acceso
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}

	edo = TWI_Inicio(); // Inicio repetido
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte((RTC << 1) | 0x01); // Maestro Receptor
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}

	edo = TWI_LeeByte(dato, 0); // Lee con nAck

	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}
	TWI_Paro();

	return 1;
}

uint8_t escribir(uint8_t dato, uint8_t dir)
{
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;

	edo = TWI_EscByte(RTC << 1); // Maestro Transmisor
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte(dir); // Escribe dirección de acceso
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}

	edo = TWI_EscByte(dato);
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}

	TWI_Paro(); // Condición de Paro

	return 1;
}
