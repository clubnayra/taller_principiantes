/**
 * blink_configurable.
 * este ejemplo hace uso de la clase CommandParser para modificar su frecuencia y ciclo de trabajo
 * se utilian dos comandos:
 *  - frec valor_de_frecuencia
 *  - duty valor_de_ciclo_de_trabajo
 * donde valor_de_* es un numero positivo ya sea real o entero
 * el comando es psado a traves del puerto serial
 * se reconoce tanto \r como \n como el final del comando
 * ejemplos de uso:
 *    frec 0.5
 *    duty 50
 *    frec 100
 *    duty 33.33
 */

#include "CommandParser.h"

unsigned int delay_on, delay_off; // tiempo de encendido y apagado del led, calculado en funcion a frec y duty
unsigned int last_transition, current; // timestamps
uint8_t state; // el estado del led: 0 = apagado, 1 = encendido
float duty = 50.0; // el porcentaje de tiempo en el que el led estara encendido, en %
float frec = 1.0; // la frecuencia a la que parpadeara el led, en Hz

// nuestro reconocedor de comandos
CommandParser cmd;

// esta funcion calcula los valores de delay_on y delay_off en base a los valores de frec y duty
void updateTiming() {
  if (frec > 0 && duty >= 0 && duty <= 100) { // verificamos que los valores sean correctos
    delay_on = (unsigned int)(10.0 * duty / frec);
    delay_off = (unsigned int)(10.0 * (100.0 - duty) / frec);
  }
}

// funcion para el comando frec
// recibe un solo argumento, el valor de la frecuencia en Hz expresado como numero real
void changeFrec(String *args) {
  float aux;
  if (args[0] != ""){ // verificamos que el argumento este presente
    aux = args[0].toFloat(); // arg[0] es un string, lo convertimos a float, si no es posible retorna 0.00
    if (aux > 0) { // verificamos que sea un valor valido
      frec = aux; // actualizamos los valores
      updateTiming();
    }
  }
}

// funcion para el comando duty
// recibe un solo argumento, el valor del ciclo de trabajo en % expresado como numero real
void changeDuty(String *args) {
  float aux;
  if (args[0] != ""){
    aux = args[0].toFloat();
    if (aux >= 0 && aux <= 100) {
      duty = aux;
      updateTiming();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  state = 1;

  cmd.setDelimiter(' '); // utilizamos un espacio en blanco (' ') como delimitador

  // adicion de comandos:
  // los comandos se añaden con el metodo: CommandParser::addCommand(str, action);
  // donde:
  // -str: un String o cadena de caracteres que identifican al nombre del comando
  // -action: la funcion que se ejecutara cuando se reconozca el comando, esta funcion
  //  debe ser de la forma void action(String *args);
  //  donde args es un array de String en el que se pasaran los argumentos que se reconozcan
  cmd.addCommand("frec", changeFrec);
  cmd.addCommand("duty", changeDuty);

  last_transition = millis();
  updateTiming();
}

void loop() {
  // put your main code here, to run repeatedly:

  // se debe llamar esta funcion periodicamente para que se reciban los comandos
  cmd.run();

  // parpadeamos el led
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
