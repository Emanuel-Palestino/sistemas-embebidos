// Ejemplo 1 - LCD

#include <LCD.h>

void setup() {
	DDRC = 0xFF;	// Salida
	LCD_init();
	LCD_write_cad((uint8_t *) "SISTEMAS EMBEBIDOS", 20);
}

void loop() {}