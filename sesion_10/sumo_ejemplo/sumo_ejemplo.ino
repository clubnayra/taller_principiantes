#include "TB6612FNG.h"
#include "FSME.h"

// pines a conectar pra los sensores
// actualmente solo estan implementados los sensores de linea y el pulsador
enum SENSORES_PINS {
  LINEA_DER = 2,
  LINEA_IZQ = 3,
  PULSADOR = 4,
};

// pines a utilizar para el driver de motores
// declarado para el driver tb6612fng, sin embargo se puede utilizar con otros
// similares como el l298 dejando sin conectar el pin STD_BY
enum TB6612FNG_PINS {
  PWM_DER = 6,
  IN1_DER = 7,
  IN2_DER = 8,
  PWM_IZQ = 9,
  IN1_IZQ = 10,
  IN2_IZQ = 11,
  STD_BY = 12,
};
TB6612FNG motor_der=TB6612FNG(PWM_DER,IN1_DER,IN2_DER,STD_BY);
TB6612FNG motor_izq=TB6612FNG(PWM_IZQ,IN1_IZQ,IN2_IZQ,STD_BY);

// estados de la maquina de estados
// implementado solo la primera parte del diagrama (parte superior)
// no se implementa el estado de rutina de inicio (estado "inicio" en el diagrama)
enum ESTADOS {
  ESPERA,
  ESP_5S, // estado "5 s" en el diagrama
  NORMAL,
  ATRAS,
  GIRO,

  ESTADOS_MAX
};
Transition *espera_trans[1];
Transition *esp5s_trans[1];
Transition *normal_trans[1];
Transition *atras_trans[1];
Transition *giro_trans[1];

State sumo_states[ESTADOS_MAX];

FSME sumo;

// eventos
uint8_t esPulsadorPresionado (void); // pulsador
uint8_t estaFuera (void); // borde
uint8_t estaDentro (void); // no borde

// prototipos para las acciones de cada estado
void esperaLoop (void);
void esp5sLoop (void);
void normalLoop (void); // implementar en esta accion las rutinas de ataque, busqueda y evasion
void atrasLoop (void);
void giroLoop (void);

void setup() {
  // put your setup code here, to run once:

  // cofiguracion de pines
  motor_der.Setup();
  motor_izq.Setup();

  pinMode(LINEA_DER, INPUT_PULLUP);
  pinMode(LINEA_IZQ, INPUT_PULLUP);
  pinMode(PULSADOR, INPUT_PULLUP);

  // configuracion de la maquina de estados
  espera_trans[0] = new EvnTransition(esPulsadorPresionado, ESP_5S);
  esp5s_trans[0] = new TimeTransition(5000, NORMAL);
  normal_trans[0] = new EvnTransition(estaFuera, ATRAS);
  atras_trans[0] = new EvnTransition(estaDentro, GIRO);
  giro_trans[0] = new TimeTransition(1000, NORMAL);

  sumo_states[ESPERA].setState(esperaLoop, espera_trans, 1);
  sumo_states[ESP_5S].setState(esp5sLoop, esp5s_trans, 1);
  sumo_states[NORMAL].setState(normalLoop, normal_trans, 1);
  sumo_states[ATRAS].setState(atrasLoop, atras_trans, 1);
  sumo_states[GIRO].setState(giroLoop, giro_trans, 1);

  sumo.setStates(sumo_states, ESTADOS_MAX);
  sumo.setInitialState(ESPERA);

  // coniguracion puerto serial
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  sumo.run();
}

// implementacion de los eventos
uint8_t esPulsadorPresionado (void) {
  if (digitalRead(PULSADOR) == LOW) return 1;
  else return 0;
}
uint8_t estaFuera (void) {
  if ((digitalRead(LINEA_IZQ) == LOW) || (digitalRead(LINEA_DER) == LOW)) return 1;
  else return 0;
}
uint8_t estaDentro (void) {
  if ((digitalRead(LINEA_IZQ) == LOW) || (digitalRead(LINEA_DER) == LOW)) return 0;
  else return 1;
}

// implementacion de las acciones
void esperaLoop (void) {
  if (sumo.isStateChanged()) {
    Serial.println(F("Estado espera, presione el pulsador para iniciar"));
    motor_der.Brake(); // frenar los motores
    motor_izq.Brake();
  }
}
void esp5sLoop (void) {
  if (sumo.isStateChanged()) {
    Serial.println(F("Estado espera 5 segundos, esperando"));
  }
}
void normalLoop (void) {
  if (sumo.isStateChanged()) {
    Serial.println(F("Estado normal"));
  }
  // implementar rutinas de busqueda, ataque y evasion
  motor_der.Move(255); // los valores de TB6612FNG::Move(int16_t velocity) pueden variar de -255 a 255
  motor_izq.Move(255);
}
void atrasLoop (void) {
  if (sumo.isStateChanged()) {
    Serial.println(F("Estado atras, retrocediendo"));
    motor_der.Move(-255);
    motor_izq.Move(-255);
  }
}
void giroLoop (void) {
  if (sumo.isStateChanged()) {
    Serial.println(F("Estado giro, girando"));
    motor_der.Move(-255);
    motor_izq.Move(255);
  }
}

