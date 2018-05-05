uint8_t pulsador = 2;
uint8_t led = 13;

uint8_t contador = 0; // contador de pulsaciones
uint8_t contador_maximo = 0;  // record
uint8_t estado_actual;  // estados del pulsador
uint8_t estado_anterior;
uint32_t tiempo_inicio;
uint32_t tiempo = 5000; // tiempo en el que se permiten pulsaciones

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsador, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Presiona s par iniciar...\n"));
  while(Serial.read() != 's');
  Serial.println(F("Comienza a pulsar en..."));
  Serial.println(F("3..."));
  delay(1000);
  Serial.println(F("2..."));
  delay(1000);
  Serial.println(F("1...\n"));
  delay(1000);
  Serial.println(F("Comienza a pulsar!\n"));
  digitalWrite(led, HIGH);
  tiempo_inicio = millis();
  estado_anterior = digitalRead(pulsador);
  
  while(millis() - tiempo_inicio < tiempo) {
    estado_actual = digitalRead(pulsador);
    if(estado_actual == LOW && estado_anterior == HIGH) { // pulsador presionado
      contador++;
      estado_anterior = estado_actual;
      delay(10);  // para evitar lecturas de rebote
    }
    else if(estado_actual == HIGH && estado_anterior == LOW) { // pulsador suelto
      estado_anterior = estado_actual;
      delay(10);  // para evitar lecturas de rebote
    }
  }

  digitalWrite(led, LOW);
  Serial.println(F("Tiempo!\n"));

  Serial.print(F("Felicidades pulsaste "));
  Serial.print(contador);
  Serial.println(F(" veces!"));

  if(contador > contador_maximo) {  // nuevo record
    contador_maximo = contador;
    Serial.println(F("Has conseguido un nuevo record!\n"));
  }
  else {
    Serial.print(F("El actual record es de "));
    Serial.print(contador_maximo);
    Serial.println(F(" pulsaciones, sigue intentandolo...\n"));
  }
  contador = 0;
}

