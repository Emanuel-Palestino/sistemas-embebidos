int cont;

void setup(){

  // Entradas/Salidas
  DDRC = 0x00;    // Establece como entrada A1, A2
  DDRB = 0x3C;    // Establece como salida D1(13), D2(12), D3(11), D4(10)
	
  // Lee el dato almacenado en la EEPROM
  cont = EEPROM_read(0x0);

  // Verifica que lo leído sea válido
  // (que esté entre los valores permitidos)
  if (cont < 0 || cont > 15){
    cont = 1;  
  }

  // Inicializa LEDs
  establece_LEDS();

}

void loop(){

  // Aumentar el contador
  if (!(PINC & 0x02))   // Sí el botón presionado es A1
    cont = (cont < 15) ? cont + 1 : 0;

  // Decrementar el contador
  if (!(PINC & 0x04))   // Sí el botón presionado es A2
    cont = (cont > 0) ? cont - 1 : 15;

  // Muestra cont
  establece_LEDS();

  // Guarda valor de cont
  EEPROM_write(cont, 0x0);

  delay(200);
 
}

// Función que maneja los LEDs
void establece_LEDS(){

  // Encienda o apaga los LEDs según el valor de cont
  switch (cont){
    case 0:
      PORTB = 0x3C;   // 0011 1100
      break;
    case 1:
      PORTB = 0x1C;   // 0001 1100
      break;
    case 2:
      PORTB = 0x2C;   // 0010 1100
      break;
    case 3:
      PORTB = 0x0C;   // 0000 1100
      break;
    case 4:
      PORTB = 0x34;   // 0011 0100
      break;
    case 5:
      PORTB = 0x14;   // 0001 0100
      break;
    case 6:
      PORTB = 0x24;   // 0010 0100
      break;
    case 7:
      PORTB = 0x04;   // 0000 0100
      break;
    case 8:
      PORTB = 0x38;   // 0011 1000
      break;
    case 9:
      PORTB = 0x18;   // 0001 1000
      break;
    case 10:
      PORTB = 0x28;   // 0010 1000
      break;
    case 11:
      PORTB = 0x08;   // 0000 1000
      break;
    case 12:
      PORTB = 0x30;   // 0011 0000
      break;
    case 13:
      PORTB = 0x10;   // 0001 0000
      break;
    case 14:
      PORTB = 0x20;   // 0010 0000
      break;
    case 15:
      PORTB = 0x00;   // 0000 0000
      break;
  }
  
}

// Función para guardar un dato en la EEPROM
// en la dirección dada
void EEPROM_write(uint8_t dato, uint8_t dir){

  // Asegura que no haya escritura en proceso
  while (EECR & 1 << EEPE);

  // Establece la dirección
  EEAR = dir;

  // Guarda el dato
  EEDR = dato;

  // Pone en alto habilitador maestro
  EECR |= (1 << EEMPE);

  // Inicia escritura;
  EECR |= (1 << EEPE);

}

// Función para leer un dato de la EEPROM
// en la dirección dada
uint8_t EEPROM_read(uint8_t dir){

  // Asegura que no hay una escritura en proceso
  while (EECR & 1 << EEPE);

  // Establece dirección
  EEAR = dir;

  // Inicia lectura
  EECR |= (1 << EERE);

  // Regresa el dato leído
  return EEDR;

}
