uint8_t segundos;
uint8_t minutos;
uint8_t encendido = 0x0C;
uint8_t apagado = 0x08;
// Tabla de valores
uint8_t numeros[] = {
	0b11000000,
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10011000
  };

ISR(PCINT1_vect) {
	// Si se presiona el boton A1 pausa/inicio
	if (!(PINC & 0x02))
	{
    //pausar timer, deshabilita otros dos botones
    //TCCR1B = (TCCR1B == apagado) ? encendido : apagado;
    if(TCCR1B == apagado) {
      TCCR1B = encendido;
      PORTB &= 0b11011111;
    } else {
      TCCR1B = apagado;
      PORTB |= 0x20;
    }
	}
	// Si se presiona el boton A2 incrementar
	if (!(PINC & 0x04) && TCCR1B == apagado)
	{ 
    if(segundos < 59 & minutos < 10){
      segundos ++;
    }
    else {
      if (minutos < 10){
        minutos ++;
        segundos = 0;
      }
      else {
        minutos = 0;
        segundos = 0;
      }
    }
	}
	// Si se presiona el boton A3 decrementar
	if (!(PINC & 0x08) && TCCR1B == apagado)
	{
    if(segundos > 0){
      segundos --;
    }
    else {
      if (minutos > 0){
        minutos --;
        segundos = 59;
      }
      else {
        minutos = 10;
        segundos = 0;
      }
    }
	}
}
void setup()
{
    Serial.begin(9600);
	// CONFIGURACIÓN I/O

	// Establece A1, A2 y A3 como entradas
	DDRC = 0x00;
	// Establece PB0, PD7 y PD4 como salidas
	DDRB = 0x21;
	DDRD = 0x90;

  PCMSK1 = 0x0E; 	// Máscara para PC1, PC2 y PC3
	PCICR = 0x02;	// Habilita PCINT1

  // Configuración de Timer 1


    /*TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
    Serial.println(TCCR1A, HEX);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS12);
    Serial.println(TCCR1B, HEX);
    TIMSK1 = _BV(OCIE1A);
    Serial.println(TIMSK1, HEX);*/
 
	/*TCCR1A = ;		// Modo CTC
	TCCR1B = 0x08;		// Inicia sin reloj
	TCCR1C = 0x00;
  TIMSK1 = 0x02;*/
  
  TCCR1A = 0b00000000;
  TCCR1B = apagado;
  TCCR1C = 0;
  TIMSK1 = 0x02;
  OCR1A = 62499;    // Valor Máximo
  // Inicializa reloj en 0
  PORTB |= 0x20;
  segundos = 0;
  minutos = 0;
	mostrar(0,1);


}

ISR(TIMER1_COMPA_vect){

  if(segundos > 0){
      segundos --;
    } else {
      if (minutos > 0){
        minutos --;
        segundos = 59;
      }
      else {
        TCCR1B = apagado;
        PORTB |= 0x20;
      }
    }
}

void loop()
{
  uint8_t unidad;
  uint8_t aux=segundos;
    unidad= aux % 10;
    aux= aux/10;
    mostrar(unidad, 8);
    delay(5);

    unidad= aux % 10;
    aux= aux/10;
    mostrar(unidad, 4);
    delay(5);

    aux=minutos;
    unidad= aux % 10;
    aux= aux/10;
    mostrar(unidad, 2);
    delay(5);

    unidad= aux % 10;
    aux= aux/10;
    mostrar(unidad, 1);
    delay(5);
}

void mostrar(uint8_t dato, uint8_t display)
{
	// Datos de 7 segmentos del display
	uint8_t auxiliar = numeros[dato];
  if(display==2)
    auxiliar &= 0x7f;
	for (int i = 0; i < 8; i++)
	{
		// Dato
		if (auxiliar & 0x80)
			PORTB |= 0x01;
		else
			PORTB &= 0xFE;

		// reloj SHCP Alto
		PORTD = PORTD | 0b10000000;
		// reloj SHCP Bajo
		PORTD = PORTD & 0b01111111;

		// Corrimiento
		auxiliar <<= 1;
	}

	// Datos de los displays
	uint8_t auxiliar2 = display;
	for (int i = 0; i < 8; i++)
	{
		// Dato
		if (auxiliar2 & 0x80)
      PORTB |= 0x01;
    else
      PORTB &= 0xFE;

		// reloj SHCP Alto
		PORTD = PORTD | 0b10000000;
		// reloj SHCP Bajo
		PORTD = PORTD & 0b01111111;

		// Corrimiento
		auxiliar2 <<= 1;
	}

	// reloj STCP
	PORTD = PORTD | 0b00010000;
	PORTD = PORTD & 0b11101111;
}
uint8_t potencia(uint8_t base, uint8_t mipow)
{
    if(mipow==0)
     return 1;
    uint8_t resultado = base;
    while (mipow > 1)
    {
        resultado = resultado * base;
        mipow --;
    }
    return resultado;
}
