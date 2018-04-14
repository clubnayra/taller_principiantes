/*
  pulsador

  enciende y apaga el led conectado al pin digital 2
  cuando se presiona el pulsador conectado al pin digital 7.

  el circuito se muestra en la imagen pulsador sin pullup.

*/

const int pulsador = 7;     // the number of the pushbutton pin
const int led = 2;      // the number of the LED pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(buttonPin) == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
