#include <FSME.h>

uint8_t pulsador = 7;

uint8_t counter = 0;

enum {
  idle,
  det_h2l,
  wait,
  det_l2h,
  pulse
};
State states[5];
Transition *idle_t[1];
Transition *det_h2l_t[2];
Transition *wait_t[1];
Transition *det_l2h_t[2];
Transition *pulse_t[1];
FSME fsm;

uint8_t readLow(void) {
  return (digitalRead(pulsador) == LOW);
}
uint8_t readHigh(void) {
  return (digitalRead(pulsador) == HIGH);
}
void nada(void) {
  return;
}
void incCounter(void) {
  if (fsm.isStateChanged()) {
    counter++;
    Serial.println(counter);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsador, INPUT_PULLUP);

  idle_t[0] = new EvnTransition(readLow, det_h2l);
  det_h2l_t[0] = new EvnTransition(readHigh, idle);
  det_h2l_t[1] = new TimeTransition(10, wait);
  wait_t[0] = new EvnTransition(readHigh, det_l2h);
  det_l2h_t[0] = new EvnTransition(readLow, wait);
  det_l2h_t[1] = new TimeTransition(10, pulse);
  pulse_t[0] = new TimeTransition(0, idle);
  
  states[idle].setState(nada, idle_t, 1);
  states[det_h2l].setState(nada, det_h2l_t, 2);
  states[wait].setState(nada, wait_t, 1);
  states[det_l2h].setState(nada, det_l2h_t, 2);
  states[pulse].setState(incCounter, pulse_t, 1);

  fsm.setStates(states, 5);
  fsm.setInitialState(idle);

  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  fsm.run();
}
