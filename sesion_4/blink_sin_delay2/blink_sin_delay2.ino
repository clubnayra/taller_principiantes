uint8_t led = 13;
uint8_t led2 = 5;

uint8_t estado_led = LOW;
uint8_t medio_periodo = 250; // periodo en ms
uint32_t ultimo_cambio;
uint32_t tiempo_actual;

uint8_t estado_led2 = LOW;
uint8_t medio_periodo2 = 100; // periodo en ms
uint32_t ultimo_cambio2;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led, estado_led);
  digitalWrite(led2, estado_led2);
  ultimo_cambio = millis();
  ultimo_cambio2 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  tiempo_actual = millis();
  if (tiempo_actual - ultimo_cambio >= medio_periodo) {
    estado_led = !estado_led;
    digitalWrite(led, estado_led);
    ultimo_cambio = tiempo_actual;
  }

  if (tiempo_actual - ultimo_cambio2 >= medio_periodo2) {
    estado_led2 = !estado_led2;
    digitalWrite(led2, estado_led2);
    ultimo_cambio2 = tiempo_actual;
  }
}

