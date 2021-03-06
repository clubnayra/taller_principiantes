/*
  DigitalReadSerial

  Reads a digital input on pin 7, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin 7 has a pushbutton attached to it. Give it a name:
int pushButton = 7;
int buttonState;
int prevState = LOW;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  buttonState = digitalRead(pushButton);
  if (buttonState != prevState) {
    // print out the state of the button:
    Serial.println(buttonState);
    delay(250);        // delay in between reads for stability
    prevState = buttonState;
  }
}
