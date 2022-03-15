int cont;

void setup()
{
	// put your setup code here, to run once:
/* 	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(10, OUTPUT);
	cont = 0;
	digitalWrite(13, LOW);
	digitalWrite(12, HIGH);
	digitalWrite(11, HIGH);
	digitalWrite(10, HIGH); */

	DDRC = 0x00;
	DDRB = 0x3C;

	PORTB = 0x1C;
}

void loop()
{
	// put your main code here, to run repeatedly:
	//if (digitalRead(A1) == LOW)
	if (!(PINC & 0x02))
		cont = (cont < 3) ? cont + 1 : 0;
	//if (digitalRead(A2) == LOW)
	if (!(PINC & 0x04))
		cont = (cont > 0) ? cont - 1 : 3;

	switch(cont) {
		case 0:
			PORTB = 0x1C;
			break;
		case 1:
			PORTB = 0x2C;
			break;
		case 2:
			PORTB = 0x34;
			break;
		case 3:
			PORTB = 0x38;
			break;
	}
	
/* 	switch (cont)
	{
	case 0:
		digitalWrite(13, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(10, HIGH);
		break;
	case 1:
		digitalWrite(13, HIGH);
		digitalWrite(12, LOW);
		digitalWrite(11, HIGH);
		digitalWrite(10, HIGH);
		break;
	case 2:
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(11, LOW);
		digitalWrite(10, HIGH);
		break;
	case 3:
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(10, LOW);
		break;
	} */
	delay(300);
}
