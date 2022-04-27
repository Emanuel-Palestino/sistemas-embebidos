// Timers Ejemplo 1: Escriba una secuencia de instrucciones para generar una señal de 50KHz. Es igual a 160 ciclos de reloj normales (16MHz)
// b) Genere la salida en PD6 (OC0A), configurando una respuesta automática

void setup() {
	DDRD = 0x40;	// Salida en PD6
	OCR0A = 159;	// Valor para comparación
	TCCR0A = 0x42;	// Modo CTC
	TCCR0B = 0x01;	// Uso de reloj sin pre-escalador
}

void loop() {
	
}