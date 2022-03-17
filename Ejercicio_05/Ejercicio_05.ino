extern "C" void conf_IO();
extern "C" void suma(uint8_t a, uint8_t b);

void setup()
{
	conf_IO();
}

void loop()
{
	uint8_t x, y;
	x = PINC;
	x = x & 0x0F;
	y = PINB;
	y = y & 0x0F;
	suma(x, y);
	delay(200);
}
