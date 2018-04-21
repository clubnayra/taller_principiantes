// pines a utilizar
// trigger: señal de disparo del ultrasonico
// echo: pulso devuelto por el ultrasonico
//       con tiempo proporcional a la distancia medida
int trig = 2;
int echo = 3;

// algunas variables que nos seran utiles
unsigned int pulso, distancia;

void setup() {
  // put your setup code here, to run once:
  // configuramos el puerto serial
  Serial.begin(9600);

  // configuramos los pines 
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // nos aseguramos que el pulso de disparo inicie en bajo
  digitalWrite(trig, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  // generamos el pulso, este debe ser de 10us como minimo
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // leemos e pulso que nos devuelve el ultrasonico
  // y lo convertimos a cm
  pulso = pulseIn(echo, HIGH);
  distancia = pulse / 58;

  // mandamos la distancia medida en cm por el puerto serial
  Serial.println(distancia);

  // esperamos un tiempo para evitar recibir
  // un posible eco en la siguiente medida
  delay(100);
}
