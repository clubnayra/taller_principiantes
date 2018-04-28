uint8_t dir1 = 7;
uint8_t dir2 = 8;
uint8_t pwm_pin = 9;

uint8_t pot = A0;

int16_t vel = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  vel = analogRead(pot) / 2 - 256;
  if (vel < 0) {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    vel = -vel - 1;
  }
  else {
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, LOW);
  }
  analogWrite(pwm_pin, vel);
}
