// Genere una señal PWM rápida con salida en modo No Invertido, donde el ancho del pulso esté determinado por el valor del puerto B.
// Para el valor máximo del temporizador conseidere que en la tarjeta Arduino solo quedan 6 bits disponibles en el puerto B.
// Utilice un factor de preescala de 64 y calcule la frecuencia de la señal de la salida.

// El modo de operación 7. Este modo tiene como máximo un valor de registro.
//Como vamos a ocupar OCR0A para el valor máximo, utilizamos OCR0B para tomar lo que tengamos del PB

// T = 64 x 64 x 62.5ns = 2.56 x10-4 = 256us. F = 3.906KHz

void setup()
{
	//config I/O
	DDRB = 0x00;		// Entrada
	PORTB = 0xFF;		// Pull-up
	DDRD = 0x20;		// Salida en PD5

	// config Timer
	OCR0A = 63;			// Máximo para PWM
	TCCR0A = 0x23;		// Configurando modo 7, no invertido
	TCCR0B = 0x0B;		// Preescala de 64
}

void loop()
{
	OCR0B = PINB & 0x3F;
	delay(100);
}