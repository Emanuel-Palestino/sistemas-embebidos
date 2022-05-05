// Empleando PWM, controle la intensidad del LED conectado en PB2, manjenado 5 niveles. Con el botón A1 se hará el cambio de intensidad,
// la cual será modificada con incrementos de un 20% cada vez que el botón es presionado. (Al encender el sistema, el LED debe estar apagado).
// Para una adecuada operación del LED, configure para que la señal PWM tenga unn frecuencia de 100Hz.

//#include <Displays_MFS.h>

uint8_t ancho = 75;

void setup()
{
  Serial.begin(9600);
  
	// config. I/O
	DDRC = 0x00;
	DDRB = 0x08;  // Salida en PB3
  DDRD = 0x08;  // Salida en PD3

	// config. PCINT1
	PCMSK1 = 0x0E; // Máscara para PC1
	PCICR = 0x02;  // Habilita PCINT1

	// config. Timer 2 para PWM
	TCCR2A = 0x33;	// Modo 7, Modo invertido
	TCCR2B = 0x0F;	// Preescalado de 1024
  
  OCR2A = 150;
    OCR2B = 75;  
}

ISR(PCINT1_vect) {


  
	if(!(PINC & 0x02)) {
		ancho = (ancho < 150) ? ancho + 15 : 0;
		OCR2B = ancho;
      Serial.println(PB3, HEX);
	}

  if(!(PINC & 0x04)) {
    ancho = (ancho > 0) ? ancho - 15 : 150;
    OCR2B = ancho;
  }
  
}

void loop()
{
	
}
