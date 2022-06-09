// Ejemplo 2 - Contador UP/DOWN en LCD.
// Considerar un máximo de 100 eventos

#include <LCD.h>
uint8_t conta = 0;

void setup() {
	DDRC = 0xFF;	// LCD
	DDRD = 0x00;	// Botones
	PORTD = 0x0C;	// Pull-up
	LCD_init();
	LCD_write_cad((uint8_t *) "    Eventos:          000", 25);

	EICRA = 0x0A;	// INT0 INT1 por flanco de bajada
	EIMSK = 0x03;	// Habilita INT0 e INT1
}

ISR(INT0_vect) {
	uint8_t U, D, C;

	conta = (conta > 0) ? conta - 1 : 100;
	U = conta % 10;
	D = (conta / 10) % 10;
	C = (conta / 100);

	LCD_cursor(0x16);
	LCD_write_data(C + 0x30);
	LCD_write_data(D + 0x30);
	LCD_write_data(U + 0x30);
}

ISR(INT1_vect) {
	uint8_t U, D, C;
	conta = (conta < 100) ? conta + 1 : 0;

	U = conta % 10;
	D = (conta / 10) % 10;
	C = (conta / 100);

	LCD_cursor(0x16);
	LCD_write_data(C + 0x30);
	LCD_write_data(D + 0x30);
	LCD_write_data(U + 0x30);
}

void loop() {}