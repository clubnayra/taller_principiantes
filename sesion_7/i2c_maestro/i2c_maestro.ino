#include <Wire.h>

// direccion del dispositivo esclavo
#define SLA_ADDRESS 8

// variables en las que se guardaran los valores leidos
uint16_t pot1;  // valor del potenciometro 1
uint16_t pot2;  // valor del potenciometro 2
uint8_t aux;    // numero de bytes recividos

// tipos de errores que reconoce la libreria Wire
enum error_enum {
  SUCCESS,    // sin errores
  BUFF_OVF,   // los datos a transmitir no entran en el buffer
  N_ADDRESS,  // se recibio nack al enviar la direccion
  N_DATA,     // se recibio nack al enviar un dato
};

// variable en la que se gurdara el error recibido
uint8_t error;

// registros disponibles en el dispositivo esclavo
enum datos {
  FREC,   // frecuencia de muestreo en Hz
  POT1_H, // los 8 bits mas significtivos del potenciometro 1
  POT1_L, // los 8 bits menos significtivos del potenciometro 1
  POT2_H, // los 8 bits mas significtivos del potenciometro 2
  POT2_L, // los 8 bits menos significtivos del potenciometro 2
};

void setup() {
  // put your setup code here, to run once:

  // configurmos el puerto serial
  // solo con fines de debug
  Serial.begin(115200);
  while(!Serial);

  // configuramos el puerto i2c
  Wire.begin();           // iniciamos como maestro
  Wire.setClock(400000);  // frecuencia del clock = 400 kHz
}

void loop() {
  // put your main code here, to run repeatedly:

  // comenzamos la transaccion de lectura del potenciometro 1
  Serial.println("solicitando potenciometro 1...");
  // antes de recivir datos debemos apuntar al registro que queremos leer
  // esto se hace escribiendo solo un byte, con la direccion del registro que queremos leer
  Wire.beginTransmission(SLA_ADDRESS);  // iniciamos la transmision al esclavo (escritura)
  Wire.write((uint8_t)POT1_H);          // apuntamos al primer byte del potenciometro 1
  error = Wire.endTransmission();       // terminamos la transmision

  // leemos solo si la transmision fue exitosa
  switch (error) {
    case SUCCESS:
      Serial.println("solicitando lectura, 2 bytes...");
      aux = Wire.requestFrom(SLA_ADDRESS, 2); // solicitamos una lecture de datos
                                              // mandamos nack despues de 2 bytes
      if (aux == 2) { // verificamos que la lectura fue exitosa
        pot1 = Wire.read() * 256; // leemos el byte mas significativo
        pot1 += Wire.read();      // leemos el byte menos significativo
        Serial.print("leido: ");
        Serial.println(pot1);
      }
      else {
        Serial.println("error al solicitar lectura...");
      }
      break;
    case BUFF_OVF:
      Serial.println("demasiados datos para transmitir...");
      break;
    case N_ADDRESS:
      Serial.print("ningun esclavo con la direccion ");
      Serial.println(SLA_ADDRESS);
      break;
    case N_DATA:
      Serial.println("fallo al transmitir los datos, nack");
      break;
    default:
      Serial.println("fallo al transmitir, error desconocido...");
      break;
  }

  delay(1000);
}
