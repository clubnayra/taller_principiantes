#define MAX_CMD_SIZE 30
String cmd;
char c;
uint8_t cmd_complete, i;
int8_t index, last_index;

#define MAX_COMANDO_SIZE 10
String comando;

#define MAX_ARGS 3
String argumentos[MAX_ARGS];

void clearArgumentos(void) {
  for(i = 0; i < MAX_ARGS; i++) {
    argumentos[i] = "";
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  // cmd.reserve(MAX_CMD_SIZE);
  cmd = "";
  cmd_complete = 0;
  // comando.reserve(MAX_COMANDO_SIZE);
  clearArgumentos();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0) {
    c = Serial.read();
    switch(c) {
      case '\r':
      case '\n':
        cmd_complete = 1;
        break;
      default:
        cmd += c;
        break;
    }
    if(cmd_complete) {
      cmd_complete = 0;
      cmd.trim();
      Serial.println(cmd);
      index = cmd.indexOf(' ');
      if(index > 0) {
        comando = cmd.substring(0, index);
        comando.trim();
        Serial.println(comando);
        i = 0;
        while(index > 0) {
          last_index = index;
          index = cmd.indexOf(' ', index);
          argumentos[i] = cmd.substring(last_index, index);
          Serial.println(argumentos[i]);
          argumentos[i].trim();
          i++;
          if(i == MAX_ARGS) {
            continue;
          }
        }
      }
      /*Serial.println("Comando: " + comando);
      for(i = 0; i < MAX_ARGS; i++) {
        Serial.println("Argumento " + (i + (": " + argumentos[i])));
      }*/
      
      cmd = "";
      clearArgumentos();
    }
  }
}
