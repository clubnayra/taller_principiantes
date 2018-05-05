#include <TimerOne.h>

uint8_t led = 13;

uint8_t estado_led = LOW;
uint32_t medio_periodo = 250000; // periodo en us

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Timer1.initialize(medio_periodo);
  Timer1.attachInterrupt(blink_led);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void blink_led (void) {
  estado_led = !estado_led;
  digitalWrite(led, estado_led);
}

