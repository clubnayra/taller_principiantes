#include "Motors.h"

uint8_t trig_izq = A0;
uint8_t echo_izq = A1;
float dist_izq;

uint8_t trig_der = A4;
uint8_t echo_der = A5;
float dist_der;

uint32_t ultimo_tiempo;

Motors motors( 10, // stdby pin
                9, // pwm motor izquierdo
                8, // pin 1 para el control del sentido del motor izquierdo
                7, // pin 2 para el control del sentido del motor izquierdo
                6, // pwm motor derecho
                5, // pin 1 para el control del sentido del motor derecho
                4);// pin 2 para el control del sentido del motor derecho

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  //while(!Serial);

  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  motors.start();

  // sensor izquierdo
  pinMode(trig_izq, OUTPUT);
  pinMode(echo_izq, INPUT);

  // sensor derecho
  pinMode(trig_der, OUTPUT);
  pinMode(trig_der, INPUT);

  digitalWrite(trig_izq, LOW);
  digitalWrite(trig_der, LOW);
  
  ultimo_tiempo = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

  while (millis() - ultimo_tiempo < 60);
  
  digitalWrite(trig_izq, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_izq, LOW);
  ultimo_tiempo = millis();
  dist_izq = pulseIn(echo_izq, HIGH) / 58.0;
  Serial.println(dist_izq);

  while (millis() - ultimo_tiempo < 60);
  
  digitalWrite(trig_der, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_der, LOW);
  ultimo_tiempo = millis();
  dist_der = pulseIn(echo_der, HIGH) / 58.0;
  Serial.println(dist_der);

  if (dist_izq > 10 && dist_der > 10) {
    motors.drive(128, 128);
    Serial.println("adelante");
  }
  else if (dist_izq <= 10 && dist_der <= 10) {
    motors.drive(128, -128);
    Serial.println("atras");
  }
  else if (dist_izq > 10 && dist_der <= 10) {
    motors.drive(0, 128);
    Serial.println("izquierda");
  }
  else if (dist_izq <= 10 && dist_der > 10) {
    motors.drive(128, 0);
    Serial.println("derecha");
  }
  
  delay(100);

  motors.drive(0, 0);
  motors.brake();
}
