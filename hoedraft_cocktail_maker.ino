




void setup() {

  // Selection LEDs
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

int index = 0;
void loop() {
  digitalWrite(index, LOW);
  
  index = (index + 1) % 5 + 5;

  digitalWrite(index, HIGH);
  
  delay(100);
}
