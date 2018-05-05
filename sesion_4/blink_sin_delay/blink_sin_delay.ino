uint8_t led = 13;

uint8_t estado_led = LOW;
uint8_t medio_periodo = 250;
uint32_t ultimo_cambio;
uint32_t tiempo_actual;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  digitalWrite(led, estado_led);
  ultimo_cambio = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  tiempo_actual = millis();
  if (tiempo_actual - ultimo_cambio >= medio_periodo) {
    estado_led = !estado_led;
    digitalWrite(estado_led);
    ultimo_cambio = tiempo_actual;
  }
}

