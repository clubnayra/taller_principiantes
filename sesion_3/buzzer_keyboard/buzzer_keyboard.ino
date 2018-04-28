#include "pitches.h"

uint8_t pulsador = 2;
uint8_t buzzer = 3;
uint8_t contador = 0;

uint16_t const the_simpsons[] = {
  NOTE_C6, NOTE_E6, NOTE_FS6, NOTE_A6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_A5, NOTE_FS5, \
  NOTE_FS5, NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_G5, NOTE_AS5, NOTE_C6, \
  NOTE_C6, NOTE_C6, NOTE_C6
};

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsador, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(pulsador) == HIGH);
  tone(buzzer, the_simpsons[contador]);
  delay(200);
  while(digitalRead(pulsador) == LOW);
  noTone(buzzer);
  contador++;
  if (contador > 20) {
    contador = 0;
  }
  delay(200);
}
