#include <Wire.h>

// nuestra direccion como esclavo
#define ADDRESS 8

// pines en los que estan conectados los potenciometros
uint8_t pot1 = A0;
uint8_t pot2 = A1;

// variable auxiliar en la que se leera el valos de los potenciometros
uint16_t adc;

// los registros que dispondremos como esclavos
enum datos {
  FREC,   // frecuencia de muestreo en Hz
  POT1_H, // byte mas significativo del potenciometro 1
  POT1_L, // byte menos significativo del potenciometro 1
  POT2_H, // byte mas significativo del potenciometro 2
  POT2_L, // byte menos significativo del potenciometro 2

  // ultimo elemento
  NUM_DATOS
};
uint8_t buffer_datos[NUM_DATOS];

// puntero a uno de los registros que dispondremos como esclavos
uint8_t *puntero;

void setup() {
  // put your setup code here, to run once:

  // configuramos el puerto serial
  // solo con fines de debug
  Serial.begin(115200);
  while(!Serial);

  // configuramos el puerto i2c
  Wire.begin(ADDRESS);    // iniciamos como esclavo, con direccion ADDRESS
  Wire.setClock(400000);  // frecuencia del clock = 400 kHz

  // configuramos las interrupciones para solicitudes de escritura y lectura
  Wire.onReceive(solicitudEscritura); // funcion que se ejecutara en una solicitud de escritura
  Wire.onRequest(solicitudLectura);   // funcion que se ejecutara en una solicitud de lectura

  puntero = &buffer_datos[POT1_H];  // comenzamos apuntando al byte mas significativo del potenciometro 1
  buffer_datos[FREC] = 1; // seteamos la frecuencia de muestreo a 1 Hz
}

void loop() {
  // put your main code here, to run repeatedly:

  // leemos el valor del potenciometro 1
  adc = analogRead(pot1);
  // lo gurdamos en los registros correspondientes
  buffer_datos[POT1_H] = (uint8_t)((adc >> 8) & 0x00FF);
  buffer_datos[POT1_L] = (uint8_t)(adc & 0x00FF);

  // leemos el valor del potenciometro 2
  adc = analogRead(pot2);
  // lo guardamos en los registros correspondientes
  buffer_datos[POT2_H] = (uint8_t)((adc >> 8) & 0x00FF);
  buffer_datos[POT2_L] = (uint8_t)(adc & 0x00FF);

  // retrasamos lo necesario para cumplir con la frecuencia de muestreo
  delay(1000 / buffer_datos[FREC]);
}

// funcion que se ejecutara en una solicitud de escritura
// @num_datos: la cantidad de bytes en el buffer
void solicitudEscritura(int num_datos) {
  uint8_t reg;

  Serial.println("solicitud de escritura...");
  if (Wire.available()) {
    reg = Wire.read();            // leemos el primer byte
    puntero = &buffer_datos[reg]; // el primer byte siempre apunta al registro en el que se desea trabajar 
    Serial.print("apuntando al registro: ");
    Serial.println(reg);
    while (Wire.available()) {  // si hay mas datos se desea escribir en el registro que se apunto
      *puntero = Wire.read();   // escribimos en el valor del registro
      puntero++;                // apuntamos al siguiente registro
    }
  }
}

// funcion que se ejecutara en una solicitud de lectura
void solicitudLectura(void) {
  // cuando se manda una solicitud de lectura se asume que ya se apunto al registro que se desea leer
  // escribimos por defecto 2 bytes, los bytes necesarios para leer uno de los potenciometros
  Wire.write(puntero, 2);
  Serial.println("solicitud lectura...");
  Serial.print("enviado: 0x");
  Serial.print(*puntero, HEX);
  Serial.println(*(puntero + 1), HEX);
}

