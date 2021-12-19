
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


signed int index = 0;
unsigned long startTime = 0;
bool isMakingCocktail = false;


void loop() {
  
  if (isMakingCocktail) makeCocktail();
  else selection();

  delay(20);
}


void selection() {
  static bool isButtonUpPressed = false;
  static bool isButtonDownPressed = false;
  static bool isButtonSelectPressed = false;

  
  digitalWrite(index + 5, LOW);
  
  
  int buttonUpValue = digitalRead(BUTTON_UP);
  if (buttonUpValue == HIGH) {
    if (!isButtonUpPressed) {
      isButtonUpPressed = true;
      index = (index + 1) % 5;
    }
  } else isButtonUpPressed = false;
  
  
  int buttonDownValue = digitalRead(BUTTON_DOWN);
  if (buttonDownValue == HIGH) {
    if (!isButtonDownPressed) {
      isButtonDownPressed = true;
      index--;
      if (index < 0) index = 4;
    }
  } else isButtonDownPressed = false;
  
  
  int buttonSelectValue = digitalRead(BUTTON_SELECT);
  if (buttonSelectValue == HIGH) {
    if (!isButtonSelectPressed) {
      isButtonSelectPressed = true;
      isMakingCocktail = true;
      startTime = millis();
    }
  } else isButtonSelectPressed = false;
  
  
  digitalWrite(index + 5, HIGH);
}


void makeCocktail() {
  const long flashInterval = 250;
  const long cocktailDuration = 2500;

  
  static unsigned long previousTime = 0;
  static bool isSelectedLampOn = false;

  
  unsigned long now = millis();
  
  if (isSelectedLampOn) digitalWrite(index + 5, HIGH);
  else digitalWrite(index + 5, LOW);

  if (now - previousTime > flashInterval) {
    isSelectedLampOn = !isSelectedLampOn;
  }
  
  if (now - startTime > cocktailDuration) {
    isMakingCocktail = false;
    startTime = 0;
  }
}
