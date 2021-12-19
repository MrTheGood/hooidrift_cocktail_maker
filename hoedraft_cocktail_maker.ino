
const int BUTTON_UP = 2;
const int BUTTON_DOWN = 3;
const int BUTTON_SELECT = 4;


void setup() {
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_SELECT, INPUT);

  // Selection LEDs
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}


int index = 0;
bool isButtonUpPressed = false;


void loop() {
  digitalWrite(index + 5, LOW);

  
  int buttonUpValue = digitalRead(BUTTON_UP);

  if (buttonUpValue == HIGH) {
    if (!isButtonUpPressed) {
      isButtonUpPressed = true;
      index = (index + 1) % 5;
    }
  } else isButtonUpPressed = false;
  


  digitalWrite(index + 5, HIGH);
  delay(20);
}
