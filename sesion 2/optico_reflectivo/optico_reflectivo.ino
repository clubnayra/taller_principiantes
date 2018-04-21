// pines a utilizar
int tcrt = A0;

// algunas variables que nos seran utiles
unsigned int line;
float volt;

void setup() {
  // put your setup code here, to run once:
  // configuramos el puerto serial
  Serial.begin(9600);

  // configuramos los pines 
  pinMode(tcrt, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // leemos el valor del adc en el pin conectado al sensor
  line = analogRead(tcrt);

  // lo convertimos a voltaje
  volt = line * 5.0 / 1024;

  // mandamos el voltaje medido en el sensor
  Serial.println(volt);

  // esperamos un tiempo
  delay(100);
}
