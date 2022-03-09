int cont;

void setup()
{
	// Definicion de entradas y salidas
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(10, OUTPUT);

	// Inicializacion
	cont = 1;
	digitalWrite(13, LOW);
	digitalWrite(12, HIGH);
	digitalWrite(11, HIGH);
	digitalWrite(10, HIGH);
}

void loop()
{
	// Aumentar el contador
	if (digitalRead(A1) == LOW)
		cont = (cont < 15) ? cont + 1 : 0;
	// Decrementar el contador
	if (digitalRead(A2) == LOW)
		cont = (cont > 0) ? cont - 1 : 15;

	// Encender o apagar LEDs según sea el caso
	switch (cont)
	{
	case 0:
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(10, HIGH);
		break;
	case 1:
		digitalWrite(13, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(10, HIGH);
		break;
	case 2:
		digitalWrite(13, HIGH);
		digitalWrite(12, LOW);
		digitalWrite(11, HIGH);
		digitalWrite(10, HIGH);
		break;
	case 3:
		digitalWrite(13, LOW);
		digitalWrite(12, LOW);
		digitalWrite(11, HIGH);
		digitalWrite(10, HIGH);
		break;
	case 4:
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(11, LOW);
		digitalWrite(10, HIGH);
		break;
	case 5:
		digitalWrite(13, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(11, LOW);
		digitalWrite(10, HIGH);
		break;
	case 6:
		digitalWrite(13, HIGH);
		digitalWrite(12, LOW);
		digitalWrite(11, LOW);
		digitalWrite(10, HIGH);
		break;
	case 7:
		digitalWrite(13, LOW);
		digitalWrite(12, LOW);
		digitalWrite(11, LOW);
		digitalWrite(10, HIGH);
		break;
	case 8:
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(10, LOW);
		break;
	case 9:
		digitalWrite(13, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(10, LOW);
		break;
	case 10:
		digitalWrite(13, HIGH);
		digitalWrite(12, LOW);
		digitalWrite(11, HIGH);
		digitalWrite(10, LOW);
		break;
	case 11:
		digitalWrite(13, LOW);
		digitalWrite(12, LOW);
		digitalWrite(11, HIGH);
		digitalWrite(10, LOW);
		break;
	case 12:
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(11, LOW);
		digitalWrite(10, LOW);
		break;
	case 13:
		digitalWrite(13, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(11, LOW);
		digitalWrite(10, LOW);
		break;
	case 14:
		digitalWrite(13, HIGH);
		digitalWrite(12, LOW);
		digitalWrite(11, LOW);
		digitalWrite(10, LOW);
		break;
	case 15:
		digitalWrite(13, LOW);
		digitalWrite(12, LOW);
		digitalWrite(11, LOW);
		digitalWrite(10, LOW);
		break;
	}

	delay(200);
}
