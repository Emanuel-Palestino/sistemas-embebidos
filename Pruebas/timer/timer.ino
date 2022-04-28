uint8_t segundos;
uint8_t minutos;
uint8_t encendido = _BV(WGM13) | _BV(WGM12) | _BV(CS12);
uint8_t apagado = 0x18;
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
    TCCR1B = (TCCR1B == apagado) ? encendido : apagado;
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
    // Establece A1, A2 y A3 como entradas
  DDRC = 0x00;
  // Establece PB0, PD7 y PD4 como salidas
  DDRB = 0x01;
  DDRD = 0x90;

  PCMSK1 = 0x0E;  // Máscara para PC1, PC2 y PC3
  PCICR = 0x02; // Habilita PCINT1

 
    //timer 1 setup
    //  WGM15, prescaler /256
    //  connect OC1B to pinTick
    //  enable the OC1A interrupt
    TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS12);
    TIMSK1 = _BV(OCIE1A);
    
    //with a /256 prescaler, timer 1 ticks at 62.5kHz
    //1-second is thus 62500 ticks or 0xF424
     OCR1A = 0xF424;

      segundos = 0;
  minutos = 0;

    
}//setup

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
    
}//loop

ISR( TIMER1_COMPA_vect )
{

      if(segundos > 0){
      segundos --;
    } else {
      if (minutos > 0){
        minutos --;
        segundos = 59;
      }
      else {
        TCCR1B = apagado;
      }
    }
    
}//ISR


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
      PORTB = 0x01;
    else
      PORTB = 0x00;

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
      PORTB = 0x01;
    else
      PORTB = 0x00;

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
