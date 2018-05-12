#include <FSME.h>
#include "ButtonCount.h"

void setup() {
  // put your setup code here, to run once:
  pulsador0_setup();
  pulsador1_setup();

  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  pulsos_0.run();
  pulsos_1.run();
  Serial.println(get_pulses_0());
  Serial.println(get_pulses_1());
  Serial.flush();
}
