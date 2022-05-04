// Ejemplo 7 creo xd

void setup()
{
	DDRB = 0x06;	// Salidas en PB1 y PB2

	// Configración Timer 1 PWM
	ICR1 = 39999;	// Valor máximo
	TCCR1A = 0xA2;	// Modo 14
	TCCR1B = 0x1A;	// Preescala de 8
	TCCR1C = 0x00;

}

void loop()
{
	OCR1A = 1799;	// 0°
	OCR1B = 4199;	// 180°
	delay(200);

	OCR1A = 2999;	// 90°
	OCR1B = 2999;	// 90°
	delay(200);

	OCR1A = 4199;	// 180°
	OCR1B = 1799;	// 0°
	delay(200);

	OCR1A = 2999;	// 90°
	OCR1B = 2999;	// 90°
	delay(200);
}
