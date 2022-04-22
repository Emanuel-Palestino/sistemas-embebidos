// Timers Ejemplo 1: Escriba una secuencia de instrucciones para generar una señal de 50KHz. Es igual a 160 ciclos de reloj normales (16MHz)
// a) Genere la señal en PD0, por lo que no podrá usar una respuesta automática.

ISR(TIMER0_COMPA_vect) {
	PIND = 0x01;
}

void setup() {
	DDRD = 0x01;	// Salida
	OCR0A = 159;	// Valor para comparación
	TCCR0A = 0x02;	// Modo CTC
	TCCR0B = 0x01;	// Uso de reloj sin pre-escalador
	TIMSK0 = 0x02;	// Interrupción por coincidencia con el comparador A.
}

void loop() {
	
}