void setup()
{
	// put your setup code here, to run once:
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	digitalWrite(12, HIGH);
	digitalWrite(11, HIGH);
	digitalWrite(10, HIGH);
}

void loop()
{
	// put your main code here, to run repeatedly:
	delay(100);
	digitalWrite(13, HIGH);
	digitalWrite(12, LOW);
	delay(100);
	digitalWrite(12, HIGH);
	digitalWrite(11, LOW);
	delay(100);
	digitalWrite(11, HIGH);
	digitalWrite(10, LOW);
	delay(100);
	digitalWrite(10, HIGH);
	digitalWrite(11, LOW);
	delay(100);
	digitalWrite(11, HIGH);
	digitalWrite(12, LOW);
	delay(100);
	digitalWrite(12, HIGH);
	digitalWrite(13, LOW);
}
