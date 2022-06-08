#define dir_MEM 0x50
#include <TWI.h>

uint8_t Edo = 0, total;
uint16_t dir;
uint8_t datos[64], i;

uint8_t escribe_RAM(uint8_t datos[], uint8_t n, uint8_t dir);
uint8_t lee_RAM(uint8_t datos[], uint8_t n, uint8_t dir);
void envia_cadena(uint8_t *cad);

ISR(USART_RX_vect)
{
	uint8_t aux;
	aux = UDR0;
	switch (Edo)
	{
	// Edo = 0: Recibe comando
	case 0:
		dir = 0;
		if (aux == 'R' || aux == 'r')
			Edo = 1;
		else if (aux == 'W' || aux == 'w')
			Edo = 3;
		else
			envia_cadena((uint8_t *)"Comando no definido");
		break;
	// Edo = 1: Recibe dirección de lectura
	case 1:
		if (aux >= 0x30 && aux <= 0x39)
			dir = dir * 10 + (aux - 0x30);
		else
		{
			if (dir > 255)
			{
				envia_cadena((uint8_t *)"Direccion fuera de rango");
				Edo = 0;
			}
			else
			{
				total = 0;
				Edo = 2;
			}
		}
		break;
	// Edo = 2: Recibe cantidad de datos a leer
	case 2:
		if (aux >= 0x30 && aux <= 0x39)
			total = total * 10 + (aux - 0x30);
		else
		{
			if ((dir + total) > 255)
			{
				envia_cadena((uint8_t *)"Acceso fuera de rango");
			}
			else
			{
				if (lee_RAM(datos, total, dir) == 0) // Lee de la RAM
					envia_cadena((uint8_t *)"Error al leer la SRAM");
				else
				{
					datos[total] = 0x00; // Coloca NULO
					envia_cadena(datos); // Envía por la USART
				}
			}
			Edo = 0;
		}
		break;
	// Edo = 3: Recibe dirección de escritura
	case 3:
		if (aux >= 0x30 && aux <= 0x39)
			dir = dir * 10 + (aux - 0x30);
		else
		{
			if (dir > 255)
			{
				envia_cadena((uint8_t *)"Direccion fuera de rango");
				Edo = 0;
			}
			else
			{
				i = 0;
				Edo = 4;
			}
		}
		break;
	// Edo = 1: Recibe la cadeca a escribir
	case 4:
		if (aux != '$')
		{
			datos[i] = aux;
			i = i + 1;
		}
		else
		{
			if ((dir + i) > 255)
			{
				envia_cadena((uint8_t *)"Acceso fuera de rango");
			}
			else
			{
				if (escribe_RAM(datos, i, dir) == 0)
					envia_cadena((uint8_t *)"Error al escribir en la SRAM");
				else
					envia_cadena((uint8_t *)"Escritura correcta en la SRAM");
			}
			Edo = 0;
		}
	}
}

void setup()
{
	TWI_Config();
	DDRD = 0x02; // TXD es salida
	UBRR0 = 103;
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;

	envia_cadena((uint8_t *)"Sistema Listo");
}

void loop()
{
}

uint8_t escribe_RAM(uint8_t datos[], uint8_t n, uint8_t dir)
{
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;
	edo = TWI_EscByte(dir_MEM << 1); // Maestro Transmisor
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

	for (i = 0; i < n; i++)
	{ // Escribe los datos
		edo = TWI_EscByte(datos[i]);
		if (edo != 0x01)
		{
			TWI_Paro();

			return 0;
		}
	}

	TWI_Paro(); // Condición de Paro

	return 1;
}

uint8_t lee_RAM(uint8_t datos[], uint8_t n, uint8_t dir)
{
	uint8_t edo, i;

	edo = TWI_Inicio(); // Inicio
	if (edo != 0x01)
		return 0;
	edo = TWI_EscByte(dir_MEM << 1); // Maestro Transmisor
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
	edo = TWI_EscByte((dir_MEM << 1) | 0x01); // Maestro Receptor
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}
	for (i = 0; i < n - 1; i++)
	{									 // Lee n - 1 datos
		edo = TWI_LeeByte(&datos[i], 1); // Lee con Ack
		if (edo != 0x01)
		{
			TWI_Paro();

			return 0;
		}
	}
	edo = TWI_LeeByte(&datos[i], 0); // Lee con nAck
	if (edo != 0x01)
	{
		TWI_Paro();

		return 0;
	}
	TWI_Paro();

	return 1;
}

void envia_cadena(uint8_t *cad)
{
	uint8_t c, i = 0;

	c = cad[0];
	while (c != 0x00)
	{
		while (!(UCSR0A & 1 << UDRE0))
			; // Asegura buffer vacío
		UDR0 = c;
		i = i + 1;
		c = cad[i];
	}
	while (!(UCSR0A & 1 << UDRE0))
		; // Asegura buffer vacío
	UDR0 = 0x0D;
	while (!(UCSR0A & 1 << UDRE0))
		; // Asegura buffer vacío
	UDR0 = 0x0A;
}