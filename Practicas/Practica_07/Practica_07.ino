#include <Displays_MFS.h>

uint8_t ancho = 125;
uint8_t porcentaje = 50;

void setup(){ 
	// config. I/O
	DDRC = 0x00;
	DDRB = 0x08;  // Salida en PB3

	// config. PCINT1
	PCMSK1 = 0x0E; // Máscara para PC1
	PCICR = 0x02;  // Habilita PCINT1

	// config. Timer 2 para PWM
	TCCR2A = 0xC3;	// Modo 3, Modo invertido
	TCCR2B = 0x07;	// Preescalado de 1024
  
  OCR2A = 125;    // Valor inicial (%)

  initDisplays();
}

ISR(PCINT1_vect) {

  // Para incrementar
	if(!(PINC & 0x02)) {
		ancho = (ancho < 250) ? ancho + 25 : 0;
    porcentaje = (porcentaje < 100) ? porcentaje + 10 : 0;
		OCR2A = ancho;
	}

  // Para decrementar
  if(!(PINC & 0x04)) {
    ancho = (ancho > 0) ? ancho - 25 : 250;
    porcentaje = (porcentaje > 0) ? porcentaje - 10 : 100;
    OCR2A = ancho;
  }
  
}

void loop(){
	WriteInteger(porcentaje);
}
