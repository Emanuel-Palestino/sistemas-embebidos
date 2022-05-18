#include <Displays_MFS.h>

uint8_t actual;
uint8_t x = 0, y = 0;

void setup()
{
  DDRC = 0x00;

  // Configuración de Timer 1
  TCCR1A = 0x00;    // Modo CTC
  TCCR1B = 0x0B;    // Inicia sin reloj
  TCCR1C = 0x00;
  OCR1A = 37499;    // Valor Máximo
  TIMSK1 = 0x02;

  ADMUX = 0x60;     // Canal 0, Vref en Avcc y alineación a la izquierda
  ADCSRA = 0x8F;    // Hab. ADC, inicia apagado, con Interrupción, sin carrera libre
  DIDR0 = 0x10;     // Sin buffer digital en ADC4
  actual = 0x10;

  Serial.begin(9600);

  initDisplays();
}

ISR(TIMER1_COMPA_vect){
  actual ^= 0x30;
  DIDR0 = actual;
  ADCSRA |= 1 << ADSC;  // inicia conversión
}

ISR(ADC_vect){
  uint8_t aux = ADCH;
  aux = (aux * 255) / 99;

  Serial.println(ADCH);

  if (actual == 0x10){
    x = aux;
  } else {
    y = aux;
  }
}

void loop(){
  WriteInteger(x * 100 + y);
}
