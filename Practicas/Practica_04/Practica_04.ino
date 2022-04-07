uint8_t contador, n_conta;

extern "C" void conf_IO();
extern "C" void mostrar(uint8_t valor);
extern "C" uint8_t evalua_botones(uint8_t actual);

void setup()
{
	// CONFIGURACIÓN I/O
  conf_IO();

	// Inicializa contador
	contador = 0;
	mostrar(contador);
}

void loop() {
	n_conta = evalua_botones(contador);
	if(contador != n_conta) {
		mostrar(n_conta);
		contador = n_conta;
	}
	delay(200);
}
