int led = 2;
int buttonPin = 7;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for half a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for half a second
  }
}
