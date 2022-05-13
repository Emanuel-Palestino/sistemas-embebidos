// ADC - Ejercicio 3
// Muestre el valor digital generado por el ptenciómetro conectado en A0 en los 4 displays de 7 segmentos del shield multifunción.
// Utilice el temporizador 1 con ayuda del preescalador, para actualizar la información cada medio segundo.

#include <Displays_MFS.h>

uint16_t valor = 0;
void setup()
{
	// configuración I/O
	DDRC = 0x00;	// Entrada del potenciometro
	initDisplay();

	// Configurar el timer 1 (interrumpe cada medio segundo)
	TCCR1A = 0x00;
	TCCR1B = 0x0C;
	TIMSK1 = 0x02;
	OCR1A = 31249;

	// Configuración del ADC
	ADMUX = 0x40;	// Vref en Aref y canal 0		(0x60 para obtener el resultado en 8 bits)
	ADCSRA = 0xCF;	// Habilita ADC e inicia conversión
	DIDR0 = 0x01;
}

ISR(TIMER1_COMPA_vect) {
	ADCSRA |= 1 << ADSC;
}

ISR(ADC_vect) {
	valor = ADCW;
	// Para mostrar el porcentaje
	// valor = (ADCH * 100) / 255;
}

void loop()
{
	WriteInteger(valor);
}