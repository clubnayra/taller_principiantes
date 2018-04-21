// resistencia usada en el circuito
#define SER_RES 100000

// valores del ntc (varia de ntc a ntc)
#define NOM_TEMP 25+273.15
#define NOM_RES 50000
#define B 4057

// pines a utilizar
int ntc = A0;

// algunas variables que nos seran utiles
unsigned int value;
float res, temp;

float getRes(uint16_t adc, uint32_t serRes) {
  float res = serRes/(1023.0/adc - 1.0);
  return res;
}

float getTemp(float res) {
  float temp = 1.0/(1.0/(NOM_TEMP) + log(res/NOM_RES)/B);
  return temp;
}

void setup() {
  // put your setup code here, to run once:
  // configuramos el puerto serial
  Serial.begin(9600);

  // configuramos los pines 
  pinMode(ntc, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // leemos el valor del adc en el ntc
  value = analogRead(ntc);

  // calculamos la temperatura
  res = getRes(value, SER_RES);
  temp = getTemp(res) - 273.15 ;

  // mandamos la temperatura medida en C por el puerto serial
  Serial.println(temp);

  // esperamos un tiempo
  delay(100);
}
