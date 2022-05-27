#include <Displays_MFS.h>

uint8_t actual, estado = 1;
uint16_t contador = 0;
uint8_t x[500], y[500];

uint8_t letras[] = {
  0b10001100, // P
  0b10000000, // B
  0b10100011, // o
  0b10000111, // t
  0b11000110, // C
  0b10001000, // A
  0b11000000, // D
  0b11000111, // L
  0b11101111, // i
  0b10010010, // s
  0b11100011, // v
  0b10000110, // E
  0b10101011  // n
};

void setup(){
  DDRC = 0x00;      // Entradas A4, A5
  DDRD = 0x02;      // TxD como salida y RxD como entrada

  PCMSK1 = 0x06;    // Máscara para PC1, PC2
  PCICR = 0x02;     // Habilita PCINT1

  // Configuración de Timer 1
  TCCR1A = 0x00;    // Modo CTC
  TCCR1B = 0x08;    // Inicia apagado
  TCCR1C = 0x00;
  OCR1A = 9999;     // Valor Máximo
  TIMSK1 = 0x02;    // Habilita interrupción

  ADMUX = 0x64;     // Canal 4, Vref en Avcc y alineación a la izquierda
  ADCSRA = 0x8F;    // Hab. ADC, inicia apagado, con interrupción, sin carrera libre
  DIDR0 = 0x30;     // Sin buffer digital en ADC4, ADC5
  actual = 0x64;    // Entrada actual

  // Configuración USART0 (interrupción por recepción)
  UBRR0 = 103;  // Para 9600
  UCSR0A = 0x00;  // Normal Asíncrono
  UCSR0B = 0x98;  // Habilita Rx y Tx con interrupción por Rx
  UCSR0C = 0x06;  // Datos de 8 bits

  initDisplays();
}

ISR(PCINT1_vect){
  // Si se presiona el boton A1
  if (!(PINC & 0x02)) {
    TCCR1B = 0x0A;    // Inicia con preescalor de 8
    estado = 2;
  }
  
  // Si se presiona el boton A2
  if (!(PINC & 0x04)) {
    estado = 4;
    char coordenada[20];
    for (uint16_t i = 0; i < 500; i++){
      sprintf(coordenada, "%d,%d", x[i], y[i]);
      envia_cadena(coordenada);
      while(!(UCSR0A & 1 << UDRE0));
      UDR0 = 0x0D;
      while(!(UCSR0A & 1 << UDRE0));
      UDR0 = 0x0A;
    }
    estado = 1;
  }
}

void envia_cadena(char cad[]) {
  uint8_t k = 0;
  while(cad[k] != 0) {
    while(cad[k] != 0) {
      while(!(UCSR0A & 1 << UDRE0));
      UDR0 = cad[k];
      k++;
    }
  }
}

ISR(TIMER1_COMPA_vect){  
  ADCSRA |= 1 << ADSC;  // Inicia conversión
}

ISR(ADC_vect){
  uint8_t aux = ADCH;     // Obtiene valor del ADC

  if (actual == 0x64){    // Sí es la coordenada X
    x[contador] = aux;
    actual ^= 0x01;         // Conmuta entre A4 y A5
    ADMUX = actual;         // Actualiza ADMUX
    ADCSRA |= 1 << ADSC;  // Inicia conversión
  } else {
    y[contador] = aux;
    if (contador < 499){
      contador++; 
    } else {
      contador = 0;
      TCCR1B = 0x08;      // apagar timer
      estado = 3;
    }
    actual ^= 0x01;         // Conmuta entre A4 y A5
    ADMUX = actual;         // Actualiza ADMUX
  }
}

void loop(){
  switch(estado){
    case 1:
      WriteDigit(0, letras[0]);
      WriteDigit(1, letras[1]);
      WriteDigit(2, letras[2]);
      WriteDigit(3, letras[3]);
      break;
    case 2:
      WriteDigit(0, letras[4]);
      WriteDigit(1, letras[5]);
      WriteDigit(2, letras[0]);
      WriteDigit(3, letras[3]);
      break;
    case 3:
      WriteDigit(0, letras[6]);
      WriteDigit(1, letras[7]);
      WriteDigit(2, letras[8]);
      WriteDigit(3, letras[9]);
      break;
    case 4:
      WriteDigit(0, letras[11]);
      WriteDigit(1, letras[12]);
      WriteDigit(2, letras[10]);
      WriteDigit(3, letras[8]);
      break;      
  }
}
