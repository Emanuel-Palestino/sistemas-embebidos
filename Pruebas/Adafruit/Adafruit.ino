#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void setup() {
	Serial.begin(9600);
	tcs.begin();
}

void loop() {
	float R, G, B;
	tcs.getRGB(&R, &G, &B);
	Serial.println(String(R) + "," + String(G) + "," + String(B));
	delay(1000);
}