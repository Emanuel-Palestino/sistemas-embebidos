// ADC - Ejercicio 1
// El shield multifunción contiene un potenciómetro de 10Kohhms conectado en A0. Realice un programa que digitalice la entreada analógica y, 
// dependiendo de su valor, encienda uno de los LED's del mismo shield, dividiendo el rango de conversión en 4 niveles.
void setup()
{
	// Configuración I/O
	DDRC = 0x00;	// Entrada
	DDRB = 0x3C;	// Salida
	PORTB = 0x3C;	// LED's apagados

	// Configuración del ADC
	ADMUX = 0x40;
	ADCSRA = 0xEF;	// Habilita interrupción, preescalado de 128 y carrera libre
	ADCSRB = 0x00;	// Carrera libre (Cuando termina una conversión, continua con la siguiente).
	DIDR0 = 0x01;	// Selecciona canal 0
}

ISR(ADC_vect) {
	int16_t aux;
	aux = ADCW;
	if (aux < 256)
		PORTB = 0x1C;
	else if (aux < 512)
		PORTB = 0x2C;
	else if (aux < 768)
		PORTB = 0x34;
	else
		PORTB = 0x38;

	// Inicia conversión
	//ADCSRA |= 1 << ADSC;	// Por la carrera libre, ya no necesitamos iniciar manualmente.
}

void loop()
{
	
}