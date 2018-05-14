#include <Servo.h>
#include <FSME.h> // libreria para utilizar la maquina de estados finita
#include "ButtonCount.h" // archivo extra en el que se implementa los contadores de pulsos

// declaramos nuestro actuador, en este caso
// es el servo que actuara como cerradura
Servo cerradura;

// definimos en un enum los estados de la maquina
// de estados finita, solo con el fin de que el codigo
// sea mas facil de entender y leer
enum {
  espera, // espera = 0
  s_1,    // s_1 = 1
  s_11,   // s_11 = 2
  s_110,  // s_110 = 3
  s_1101, // s_1101 = 4
};

// declaramos el array de estados
State estados[5];

// declaramos las transiciones (array de punteros a transiciones).
// debemos declarar un array por cada estado y el largo de cada
// array debe ser igual al numero de transitiones en ese estado.
Transition *espera_t[2];  // e.g. array de transiciones para el estado espera, con 2 transicion
Transition *s_1_t[2];
Transition *s_11_t[2];    // noten que antes del nombre de la variable hay un *
Transition *s_110_t[2];   // lo que indica que se trata de un puntero.
Transition *s_1101_t[2];

// declaramos la maquina de estados finita
FSME caja_fuerte;

// funcion para detectar un evento:
// para las transiciones tipo EvnTransition se requiere de una funcion que
// le indique a la maquina de estados cuando se debe realizar esa transicion.
// en este caso necesitamos una funcion que nos indique cuando se pulso el
// digito 0 (pulsador 0), esta funcion debe retornar un uint8_t o char.
// esta funcion no debe tomar ningun parametro
uint8_t pulsado_0(void) {
  if (get_pulses_0() >= 1) {  // la funcion get_pulses_0() nos retorna el numero de veces que
                              // se pulso el digito 0, implementado en ButtonCount.h
    clear_pulses_0();  // si se pulso el digito 0 limpiamos el contador de pulsos 
    Serial.println("pulsado 0");
    return 1; // esta funcion deber retornar 1 para indicar que se debe realizar esta transicion
  }
  else {
    return 0; // si retorna 0 la transicion no se realizara
  }
}

// lo mismo que la anterior funcion, pero esta vez para el digito 1 (pulsador 1)
uint8_t pulsado_1(void) {
  if (get_pulses_1() >= 1) {
    Serial.println("pulsado 1");
    clear_pulses_1();
    return 1;
  }
  else {
    return 0;
  }
}

// funcion para realizar una accion:
// este tipo de funciones son las que se ejecutan reiteradamente
// mientras se permanezca en el estado en el que esta asociada
// la funcion, esta funcion no toma ningun parametro
// ni retorna nada.
// en este caso se trata de la accion de cerrar la caja fuerte.
void cerrar(void) {
  // con el metodo FSME::isStateChanged() detectamos si acaba
  // de ocurrir un cambio de estado, y si lo combinamos con
  // el condicional if, podemos utilizarlo para correr
  // codigo una sola vez, seria el equivalente al setup()
  // de un sketch normal en arduino
  if (caja_fuerte.isStateChanged()) {
    Serial.println("cerrar"); // solo se ejecutara una vez
  }

  // todo lo que este fuera de el anterior if se ejecutara
  // reiteradamente, similar al loop() de un sketch normal en arduino
  cerradura.write(90);
}

// funcion para realizar la accion de abrir la caja fuerte
void abrir(void) {
  if (caja_fuerte.isStateChanged()) {
    Serial.println("abrir");
  }
  
  cerradura.write(0);
}

// funcion que no hace nada, lastimosamente todos los estados
// requieren de una accion a relizar, en este caso a los estados
// que no realizan ninguna accion los vincularemos a esta accion 
void noHacerNada(void) {
  return;
}

void setup() {
  // put your setup code here, to run once:
  
  // inicializacion del servomotor
  cerradura.attach(9);
  cerradura.write(0);

  // inicializacion de transiciones:
  // al tratarse de punteros los inicializamos con el prefijo new
  // podemos tener dos tipos de transiciones:
  // EvnTransition, que son transiciones dependientes de eventos.
  // TimeTrnsition, que son transiciones dependientes de tiempos.
  // en este ejemplo solo se usaran ransiciones tipo EvnTransition
  // estas transiciones requieren de dos parametros:
  // Event (pulsado_1): es la funcion para detectar un evento, ya vista antes
  // NextState (s_1): es el siguiente estado al que se pasara si se realiza la transicion
  espera_t[0] = new EvnTransition(pulsado_1, s_1);    // 1ra transicion para el estado espera
  espera_t[1] = new EvnTransition(pulsado_0, espera); // 2da transicion para el estado espera

  s_1_t[0] = new EvnTransition(pulsado_1, s_11);    // 1ra transicion para el estado s_1
  s_1_t[1] = new EvnTransition(pulsado_0, espera);  // 2da transicion para el estado s_1

  s_11_t[0] = new EvnTransition(pulsado_0, s_110);  // llenamos las transiciones de acuerdo
  s_11_t[1] = new EvnTransition(pulsado_1, s_1);    // a nuestro diagrama de estados

  s_110_t[0] = new EvnTransition(pulsado_1, s_1101);
  s_110_t[1] = new EvnTransition(pulsado_0, espera);

  s_1101_t[0] = new EvnTransition(pulsado_1, espera);
  s_1101_t[1] = new EvnTransition(pulsado_0, espera);

  // inicilizacion de estados:
  // a diferencia de las transiciones, en los estados ya no trabajamos
  // con punteros, por lo que los inicializamos con el metodo:
  // - State::setState(Action, Trans, TransNO)
  // donde:
  // - Action: es la funcion para realizar una accion, ya vista antes
  // - Trans: es el array (de punteros) a transiciones para ese estado
  // - TransNO: el numero de transiciones
  estados[espera].setState(cerrar, espera_t, 2);
  estados[s_1].setState(noHacerNada, s_1_t, 2);
  estados[s_11].setState(noHacerNada, s_11_t, 2);
  estados[s_110].setState(noHacerNada, s_110_t, 2);
  estados[s_1101].setState(abrir, s_1101_t, 2);

  // inicializacion de la maquina de estados finita:
  // inicializamos en dos partes:
  // primero añadimos los estados con el metodo:
  // - FSME::setStates(States, StatesNO)
  // donde:
  // - States: es el array de estados que conforman la maquina de estados
  // - StatesNO: es el numero de estados
  caja_fuerte.setStates(estados, 5);
  // despues indicamos cual es el estado de inicio con el metodo:
  // - FSME::setInitialState(CurrentState)
  // donde:
  // - CurrentState: el estado inicial
  caja_fuerte.setInitialState(espera);
  
  pulsador0_setup();
  pulsador1_setup();

  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // ejecucion de la maquina de estados finita:
  // para poner en marcha la maquina de estados finita
  // utilizamos el metodo FSME::run()
  // lo debemos llamar constantemente, por lo que debe ir dentro de loop()
  // y no es aconsejable utilizar la funcion delay() del arduino.
  caja_fuerte.run();

  // contadores de pulsos
  pulsos_0.run();
  pulsos_1.run();
}
