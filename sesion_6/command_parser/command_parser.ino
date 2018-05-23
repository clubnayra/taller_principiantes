#define MAX_CMD_SIZE 30
String cmd; // string en el que se guardara todo el comando
char c; // caracter auxiliar para manejar las lecturas del puerto serial
uint8_t cmd_complete; // bandera para indicar el fin de lectura en cmd
uint8_t i; // variable auxiliar
int8_t index; // posicion en la que se encuentra el delimitador
int8_t last_index; // posicion en la que se encuentra el anterior delimitador

#define MAX_COMANDO_SIZE 10
String comando; // nombre del comando reconocido

#define MAX_ARGS 3
String argumentos[MAX_ARGS]; // argumentos del comando reconocidos 

// asigna una cadena vacia a todos los elementos del array argumentos
// llamado siempre antes de reconocer un nuevo comando
void clearArgumentos(void) {
  for(i = 0; i < MAX_ARGS; i++) {
    argumentos[i] = "";
  }
}

void setup() {
  // put your setup code here, to run once:
  // configuramos el puerto serial a una velocidad de 115200 buadios
  Serial.begin(115200);
  // esperamos a que se abra un puerto
  while(!Serial);

  // reservamos con un espacio lo suficientemente grande para evitar la fragmentacion de memoria
  // cmd.reserve(MAX_CMD_SIZE);
  
  cmd = "";
  cmd_complete = 0;
  
  // comando.reserve(MAX_COMANDO_SIZE);
  
  clearArgumentos();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // comenzamos a recibir un comando
  while(Serial.available() > 0) { // Serial.available() retorna -1 si no se esta recibiendo nada por el puerto serial.
    c = Serial.read(); // almacenamos momentanemente el caracter recibido en el puerto serial
    switch(c) {
      // utilizamos \r y \n como caracteres que indican el fin del comando
      case '\r':
      case '\n':
        if (cmd != "") { // verificamos que hayamos recibido por lo menos algo (sin esto da errores cuando recibimos ambos \r y \n)
          cmd_complete = 1;
        }
        break;
      default:
        cmd += c; // añadimos el carcter leido al comando
        break;
    }
    if(cmd_complete) { // procesamos el comando
      cmd_complete = 0; // reseteamos la bandera
      cmd.trim(); // quitamos espacios en blanco sobrantes
      cmd += ' '; // requerido para detectar el ultimo argumento
      Serial.println(cmd);
      index = cmd.indexOf(' '); // buscamos el primer delimitador (un espacio en blanco para este ejemplo)
      if(index > 0) {
        comando = cmd.substring(0, index);  // todo lo que esta desde el inicio de cmd hasta el primer delimitador es
                                            // el nombre del comando
        Serial.print("comando: ");
        Serial.println(comando);
        i = 0;
        while(i < MAX_ARGS) {
          last_index = index + 1;  //nuestra siguiente busqueda debe comenzar despues del delimitador
          index = cmd.indexOf(' ', last_index); // buscamos el siguiente delimitador
          if(index > 0) {
            argumentos[i] = cmd.substring(last_index, index); // la cadena encerrada entre last_index e index es un argumento
            Serial.print("argumento ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(argumentos[i]);
            i++;
          }
          else {  // si no se encuentran mas argumentos, salimos del while
            i = MAX_ARGS;
          }
        }
      }

      // limpiamos el comando recibido, el nombre y los argumentos
      cmd = "";
      comando = "";
      clearArgumentos();
    }
  }
}
