int led = 2;
int buttonPin = 7;
int period = 100;
int buttonState;
int prevState = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != prevState) {
    period += 100;
    prevState = buttonState;
  }
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(period);                       // wait for half a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(period);                       // wait for half a second
}
