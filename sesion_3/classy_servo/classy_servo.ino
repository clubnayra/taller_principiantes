#include <Servo.h>

/**
 *  Una clase para controlar servos. 
 *  En esta clase se presenta una forma mas elaborada de controlar
 *  servomotores, permite controlr la velocidad a la que se desea que
 *  el servomotor gire en grados/segundo.
 */
class MyServo {
private:
  int8_t increment;
  uint16_t interval;
  uint8_t pos;
  Servo my_servo;

public:
  MyServo(void) {
    this->increment = 1;
    this->interval = 1;
    this->pos = 0;
  }

  void attach(uint8_t pin) {
    this->my_servo.attach(pin);
    this->my_servo.write(pos);
  }

  void detach(void) {
    this->my_servo.detach();
  }

  void setCurrentPos(uint8_t pos) {
    this->pos = pos;
    this->my_servo.write(pos);
  }

  /**
   * metodo para mover el servomotor a un determinado angulo y a una 
   * determinada velocidad.
   * @param final_pos: un uint8_t que indica el angulo al que se desea
   *                   move el servomotor, debe estar entre 0-180 grados.
   * @param vel: un uint16_t que indica la velocidad a la que se desea
   *             girar el servomotor, debe estar entre 1-1000 grados/segundo.
   */
  void move(uint8_t final_pos, uint16_t vel) {
    // verificamos que los parametros esten en un rango adecuado
    if (vel > 1000) {
      vel = 1000;
    }
    if (vel < 1) {
      vel = 1;
    }
    if (final_pos > 180) {
      final_pos = 180;
    }

    // valor del delay necesario para conseguir la velocidad
    this->interval = (uint16_t)(1000.0 / vel + 0.5);

    // sentido de giro
    this->increment = 1;
    if (final_pos < this->pos) {
      this->increment *= -1;
    }

    // giro
    while (this->pos != final_pos) {
      this->pos += this->increment;
      this->my_servo.write(this->pos);
      delay(this->interval);
    }
  }
};

MyServo myservo;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.move(180, 60);
  delay(500);
  myservo.move(0, 60);
  delay(500);
}
