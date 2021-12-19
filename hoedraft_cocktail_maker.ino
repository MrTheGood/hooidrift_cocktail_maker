//    Copyright 2021 MrTheGood
// 
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

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
        makeTemplateCocktail();
        break;
      case 1: 
        makeTemplateCocktail();
        break;
      case 2: 
        makeTemplateCocktail();
        break;
      case 3: 
        makeTemplateCocktail();
        break;
      case 4: 
        makeHooidriftSpecialCocktail();
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
  const long flashInterval = 1000;

  
  static unsigned long previousTime = 0;
  static bool isSelectedLampOn = false;

  
  unsigned long now = millis();
  
  if (isSelectedLampOn) digitalWrite(index + INDEX_OFFSET, HIGH);
  else digitalWrite(index + INDEX_OFFSET, LOW);

  if (now - previousTime > flashInterval) {
    isSelectedLampOn = !isSelectedLampOn;
  }
}


void makeTemplateCocktail() {
  const unsigned int durationBottleOne = 500;
  const unsigned int durationBottleTwo = 500;
  const unsigned int durationBottleThree = 1750;
  const unsigned int durationBottleFour = 250;
  
  if (cocktailDuration == 0) {
    cocktailDuration = durationBottleOne + durationBottleTwo + durationBottleThree + durationBottleFour;
  }
  unsigned long now = millis();


  unsigned int duration = durationBottleOne;
  if (now - startTime > duration) digitalWrite(10, LOW);
  else digitalWrite(10, HIGH);

  if (now - startTime < duration || now - startTime > duration + durationBottleTwo) digitalWrite(11, LOW);
  else digitalWrite(11, HIGH);
  duration += durationBottleTwo;

  if (now - startTime < duration || now - startTime > duration + durationBottleThree) digitalWrite(12, LOW);
  else digitalWrite(12, HIGH);
  duration += durationBottleThree;

  if (now - startTime < duration || now - startTime > duration + durationBottleFour) digitalWrite(13, LOW);
  else digitalWrite(13, HIGH);
  duration += durationBottleFour;

  
  if (now - startTime > cocktailDuration) {
    stopMakingCocktails();
  }
}


void makeHooidriftSpecialCocktail() {
  static unsigned int bottleCount = 0;
  static int bottleDurations[4] = {0,0,0,0};
  
  if (cocktailDuration == 0) {
    bottleCount = random(1, 5);

    for (int i = 0; i < bottleCount; i++) {
      unsigned int selectedBottle = random(0, 4);
      while (bottleDurations[selectedBottle] != 0) {
        selectedBottle = random(0, 4);
      }

     
      int duration = random(500, 2500);
      bottleDurations[selectedBottle] = duration;
      cocktailDuration += duration;
    }
  }
  unsigned long now = millis();

  int duration = 0;
  for (int i = 0; i < 4; i++) {
    if (now - startTime < duration || now - startTime > duration + bottleDurations[i]) digitalWrite(i+10, LOW);
    else digitalWrite(i+10, HIGH);
    duration += bottleDurations[i];
  }

  
  if (now - startTime > cocktailDuration) {
    stopMakingCocktails();
    for (int i = 0; i < 4; i++)
      bottleDurations[i] = 0;
  }
}

void stopMakingCocktails() {
  cocktailDuration = 0;
  isMakingCocktail = false;
  startTime = 0;
}
