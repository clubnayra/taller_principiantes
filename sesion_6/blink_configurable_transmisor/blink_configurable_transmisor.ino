/**
 * blink_configurable_transmisor.
 * 
 * ejercicio realizado en el taller
 * 
 * transmite los comandos para cambiar la frecuencia y ciclo de trabajo
 * del ejemplo blink_configurable.
 * 
 * hardware extra:
 *  - un potenciometro en la entrada analogica A0, con el valor leido de
 *    este potenciometro se calculara el valor de la frecuencia a enviar
 *  - un potenciometro en la entrada analogica A1, con el valor leido de
 *    este potenciometro se calculara el valor del ciclo de trabajo a enviar
 *    
 * conexion serial:
 * la conexion debe ser cruzada, es decir el pin tx del transmisor debe
 * ser conectado al pin rx del receptor y viceversa
 * 
 */

uint8_t pot_frec = A0;
uint8_t pot_duty = A1;

float frec;
float duty;

void setup() {
  // put your setup code here, to run once:

  // iniciamos el puerto serial
  Serial.begin(115200);
  while(!Serial);

}

void loop() {
  // put your main code here, to run repeatedly:

  // llemos los valores de los potenciometros y los mapeamos a valores adecuados usando la regla de tres
  frec = analogRead(pot_frec) * 9.9 / 1023 + 0.1; // remapeamos el valor del potenciometro de 0-1023 a 0.1-10.0
  duty = analogRead(pot_duty) * 100.0 / 1023; // remapeamos el valor del potenciometro de 0-1023 a 0.0-100.0

  // comando de frecuencia
  Serial.print("frec ");
  Serial.println(frec);

  //comando de ciclo de trabajo
  Serial.print("duty ");
  Serial.println(duty);

  delay(500);
}
