
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
bool isButtonDownPressed = false;
bool isButtonSelectPressed = false;

bool isMakingCocktail = false;
int tmp = 0;


void loop() {

  if (isMakingCocktail) {
    if (tmp % 2 == 0) digitalWrite(index + 5, HIGH);
    else digitalWrite(index + 5, LOW);
    tmp++;

    if (tmp >= 500) {
      tmp = 0;
      isMakingCocktail = false;
    }
  } else {
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
        index = (index - 1) % 5;
        if (index == -1) index = 4;
      }
    } else isButtonDownPressed = false;
  
    
    int buttonSelectValue = digitalRead(BUTTON_SELECT);
    if (buttonSelectValue == HIGH) {
      if (!isButtonSelectPressed) {
        isButtonSelectPressed = true;
        isMakingCocktail = true;
      }
    } else isButtonSelectPressed = false;

    
    digitalWrite(index + 5, HIGH);
  }



  delay(20);
}
