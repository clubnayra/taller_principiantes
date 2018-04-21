// declaramos los pines a utilizar
int ldr = A0;
int led = 13;

//variables
unsigned int luz;
const int oscuridad = 250;

void setup() {
  // put your setup code here, to run once:
  // abrimos el puerto serial
  Serial.begin(9600);

  // configuramos los pines
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // leemos el valor sobre la resistencia
  luz = analogRead(ldr);

  // mandamos el valor leido por el puerto serial
  Serial.println(luz);

  // si hay poca luz encendemos un led
  if (luz < oscuridad) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }

  // esperamos un tiempo para apreciar
  // los valores enviados por el puerto serial
  delay(20);
}
