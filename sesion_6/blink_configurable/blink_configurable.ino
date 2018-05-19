#include "CommandParser.h"

unsigned int delay_on, delay_off;
unsigned int last_transition, current;
uint8_t state;
float duty = 50.0;
float frec = 1.0;

CommandParser cmd;

void updateTiming() {
  delay_on = (unsigned int)(10.0 * duty / frec);
  delay_off = (unsigned int)(10.0 * (100.0 - duty) / frec);
}

void changeFrec(String *args) {
  frec = args[0].toFloat();
  updateTiming();
}

void changeDuty(String *args) {
  duty = args[0].toFloat();
  updateTiming();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  state = 1;
  
  cmd.setDelimiter(' ');
  cmd.addCommand("frec", changeFrec);
  cmd.addCommand("duty", changeDuty);

  last_transition = millis();
  updateTiming();
}

void loop() {
  // put your main code here, to run repeatedly:
  cmd.run();
  current = millis();
  if ((state == 1) && (current - last_transition >= delay_on)) {
    digitalWrite(13, LOW);
    state = 0;
    last_transition = current;
  }
  if ((state == 0) && (current - last_transition >= delay_off)) {
    digitalWrite(13, HIGH);
    state = 1;
    last_transition = current;
  }
}
