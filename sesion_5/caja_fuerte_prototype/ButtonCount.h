#include <FSME.h>

uint8_t pulsador = 2;
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
FSME pulsos_0;

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
  if (pulsos_0.isStateChanged()) {
    counter++;
  }
}

void pulsador0_setup() {
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

  pulsos_0.setStates(states, 5);
  pulsos_0.setInitialState(idle);
}


uint8_t pulsador2 = 3;

uint8_t counter2 = 0;

State states2[5];
Transition *idle_t2[1];
Transition *det_h2l_t2[2];
Transition *wait_t2[1];
Transition *det_l2h_t2[2];
Transition *pulse_t2[1];
FSME pulsos_1;

uint8_t readLow2(void) {
  return (digitalRead(pulsador2) == LOW);
}
uint8_t readHigh2(void) {
  return (digitalRead(pulsador2) == HIGH);
}
void nada2(void) {
  return;
}
void incCounter2(void) {
  if (pulsos_1.isStateChanged()) {
    counter2++;
  }
}

void pulsador1_setup() {
  // put your setup code here, to run once:
  pinMode(pulsador2, INPUT_PULLUP);

  idle_t2[0] = new EvnTransition(readLow2, det_h2l);
  det_h2l_t2[0] = new EvnTransition(readHigh2, idle);
  det_h2l_t2[1] = new TimeTransition(10, wait);
  wait_t2[0] = new EvnTransition(readHigh2, det_l2h);
  det_l2h_t2[0] = new EvnTransition(readLow2, wait);
  det_l2h_t2[1] = new TimeTransition(10, pulse);
  pulse_t2[0] = new TimeTransition(0, idle);
  
  states2[idle].setState(nada2, idle_t2, 1);
  states2[det_h2l].setState(nada2, det_h2l_t2, 2);
  states2[wait].setState(nada2, wait_t2, 1);
  states2[det_l2h].setState(nada2, det_l2h_t2, 2);
  states2[pulse].setState(incCounter2, pulse_t2, 1);

  pulsos_1.setStates(states2, 5);
  pulsos_1.setInitialState(idle);
}

uint8_t get_pulses_0() {
  return counter;
}

uint8_t get_pulses_1() {
  return counter2;
}

void clear_pulses_0() {
  counter = 0;
}

void clear_pulses_1() {
  counter2 = 0;
}

