// Genere un tono de 400 Hz (aproximandamente) en PD6 para una respuesta automática, mientras se mantenga presionado un botón conectado en PC0.
// Para la revisión del botón se pueden emplear interrupciones por cambios en PC0
// T = 1/400Hz = 2.5ms = 2500us
// 1250us/62.5ns(Tiempo del micro) = 20000
// 20000/256 = 78.125 (cabe en 8bits)

void setup()
{
	// config I/O
	DDRC = 0x00;		// Botón
	DDRD = 0x40;		// Salida en PD
	// config PCINT2
	// camios en PC0

	// config Timer 0
	// modo ctc
	// preescala de 256
	// con respuesta automática
	// inicia sin reloj
}

ISR(int2) {
	if (pc0 == 0) {
		// reloj al timer
	} else {
		// timer 0 sin reloj
	}
}

void loop()
{
	
}