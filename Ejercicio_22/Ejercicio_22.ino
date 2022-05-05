// ADC - Ejercicio 2
void setup()
{
	DDRC = 0x00;
	DDRB = 0x08;

	TCCR2A = 0xC3;	// Modo (3) PWM Rápido e invertido
	TCCR2B = 0x07;	// Preescala de 1024

	ADMUX = 0x60;	// Canal 0, Vref en Avcc y alineación a la izquierda
	ADCSRA = 0xCF;	// Hab. ADC, inicia conversión, con Interrupción. Se podría usar carrera libre también
	DIDR0 = 0x01;	// Sin buffer digital en ADC0
}

ISR(ADC_vect) {
	OCR2A = ADCH;	// define el ancho
	ADCSRA |= 1 << ADSC;	// inicia conversión
}

void loop()
{
	
}