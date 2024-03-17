byte led[4] = {2, 3, 4, 5};
byte button[4] = {6, 7, 8, 9};
byte seq[100] = {};
byte seq_length = 0;
bool buttonPressed = false;

void setup() {
  for (byte i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
    pinMode(button[i], INPUT);
  }
  randomSeed(analogRead(0));

  seq[seq_length] = random(0, 4);
  digitalWrite(led[seq[seq_length]], HIGH);
  delay(1000);
  digitalWrite(led[seq[seq_length]], LOW);

  waitForButtonPress(seq[0]);
  if (buttonPressed == false) {
    return;
  }
}

void loop() {
  for (byte i = 0; i < seq_length; i++) {
    displayAndCheckButton(seq[i]);
    if (buttonPressed == false) {
      return;
    }
    seq[seq_length] = random(0, 4);
    seq_length++;
    delay(1000);
  }
}

void displayAndCheckButton(byte ledIndex) {
  digitalWrite(led[ledIndex], HIGH);
  delay(1000);
  digitalWrite(led[ledIndex], LOW);
  waitForButtonPress(ledIndex);
}

void waitForButtonPress(byte ledIndex) {
  unsigned long startTime = millis();
  unsigned long timeout = 5000;

  while (true) {
    if (digitalRead(button[ledIndex]) == HIGH) {
      buttonPressed = true;
      seq_length++;
      return;
    }
    if (millis() - startTime >= timeout) {
      buttonPressed = false;
      return;
    }
  }
}