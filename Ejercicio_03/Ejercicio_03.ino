void setup()
{
	// put your setup code here, to run once:
	pinMode(A1, INPUT);
	pinMode(10, OUTPUT);
}

void loop()
{
	// put your main code here, to run repeatedly:
	if (digitalRead(A1) == LOW)
		digitalWrite(10, LOW);
	else
		digitalWrite(10, HIGH);
	delay(300);
}
