
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

  // Pumps
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}


signed int index = 0;
const signed int INDEX_OFFSET = 5;

unsigned long startTime = 0;
unsigned long cocktailDuration = 0;
bool isMakingCocktail = false;


void loop() {
  if (isMakingCocktail) {
    switch (index) {
      case 0: 
        makeHooidriftSpecialCocktail();
        break;
      case 1: 
        makeHooidriftSpecialCocktail();
        break;
      case 2: 
        makeHooidriftSpecialCocktail();
        break;
      case 3: 
        makeHooidriftSpecialCocktail();
        break;
      case 4: 
        makeFlushCocktail();
        break;
    }
    makeCocktail();
  } else selection();

  delay(20);
}


void selection() {
  static bool isButtonUpPressed = false;
  static bool isButtonDownPressed = false;
  static bool isButtonSelectPressed = false;

  
  digitalWrite(index + INDEX_OFFSET, LOW);
  
  
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
  
  
  digitalWrite(index + INDEX_OFFSET, HIGH);
}


void makeCocktail() {
  const long flashInterval = 250;

  
  static unsigned long previousTime = 0;
  static bool isSelectedLampOn = false;

  
  unsigned long now = millis();
  
  if (isSelectedLampOn) digitalWrite(index + INDEX_OFFSET, HIGH);
  else digitalWrite(index + INDEX_OFFSET, LOW);

  if (now - previousTime > flashInterval) {
    isSelectedLampOn = !isSelectedLampOn;
  }
}


void makeHooidriftSpecialCocktail() {
  if (cocktailDuration = 0) {
    cocktailDuration = 1000;
  }
  
  unsigned long now = millis();
  
  if (now - startTime > cocktailDuration) {
    stopMakingCocktails();
  }
}


void makeFlushCocktail() {
  if (cocktailDuration = 0) {
    cocktailDuration = 3000;
  }
  unsigned long now = millis();

  
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  
  if (now - startTime > cocktailDuration) {
    stopMakingCocktails();
    
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}

void stopMakingCocktails() {
  cocktailDuration = 0;
  isMakingCocktail = false;
  startTime = 0;
}
