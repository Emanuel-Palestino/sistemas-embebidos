#include <Displays_MFS.h>

uint8_t actual;
uint8_t x = 0, y = 0;

void setup(){
  DDRC = 0x00;      // Entradas A4, A5

  // Configuración de Timer 1
  TCCR1A = 0x00;    // Modo CTC
  TCCR1B = 0x0B;    // Inicia con preescalor de 64
  TCCR1C = 0x00;
  OCR1A = 37499;    // Valor Máximo
  TIMSK1 = 0x02;    // Habilita interrupción

  ADMUX = 0x64;     // Canal 4, Vref en Avcc y alineación a la izquierda
  ADCSRA = 0xCF;    // Hab. ADC, inicia prendido, con interrupción, sin carrera libre
  DIDR0 = 0x30;     // Sin buffer digital en ADC4, ADC5
  actual = 0x64;    // Entrada actual

  initDisplays();
}

ISR(TIMER1_COMPA_vect){
  actual ^= 0x01;       // Conmuta entre A4 y A5
  ADMUX = actual;       // Actualiza ADMUX
  ADCSRA |= 1 << ADSC;  // Inicia conversión
}

ISR(ADC_vect){
  uint8_t aux = ADCH;     // Obtiene valor del ADC
  aux = (aux * 99) / 255; // Mapea coordenadas entre 0 y 99

  if (actual == 0x64){    // Sí es la coordenada X
    x = aux;
  } else {
    y = aux;
  }
}

void loop(){
  WriteInteger(x * 100 + y);
}
