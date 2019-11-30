#include <LiquidCrystal.h>
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
const int RS = 12;
const int enable = 11;
const int pinX = A0;
const int pinY = A1;
const int pinSW = 8;
const int minThreshold = 250;
const int maxThreshold = 900;
unsigned long startMillis = 0;
unsigned long currentMillis = 0;
int miniPeriod = 5000;
int period = 5000;

int menu = 1;
int xValue = 0;
int yValue = 0;
bool joyMoved = false;

int startingLevelValue = 0;
int currentLevelValue = 1;
int startingHighScore = 0;
bool timer = false; 

LiquidCrystal lcd(RS, enable, D4, D5, D6, D7);

void updateMenu() { 
  switch(menu) {
    case 0: 
      menu = 1;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Block Breaker");
      lcd.setCursor(3,1);
      lcd.print("START GAME");
      break;
    case 2: 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Block Breaker");
      lcd.setCursor(3,1);
      lcd.print("HIGH SCORE");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Block Breaker");
      lcd.setCursor(4,1);
      lcd.print("SETTINGS");
      break;
    case 4: 
      menu = 3;
      break;
  }
}

void executeAction() {
  switch(menu) {
    case 1:
      startGame();
      timer = true; // added this for millis(10 sec) in Start Game 
      startMillis = millis();
      break;
    case 2:
      highScore();      
      break;
    case 3:
      settings();
      break;
   }
}

void startGame() {
  startMillis = millis();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lives:3");
  lcd.setCursor(8,0);
  lcd.print("Level:");
  lcd.print(startingLevelValue);
  lcd.setCursor(0,1);
  lcd.print("Score:"); 
  lcd.print(startingLevelValue * 3);
  delay(10000);
}

void highScore() {
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("High Score: ");
  lcd.setCursor(1,1);
  lcd.print("ALEX");
  lcd.setCursor(10,1);
  lcd.print(startingHighScore); 
  delay(6000);
}

void settings() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Start Level: ");
  lcd.print(startingLevelValue);
  lcd.setCursor(0,1);
  lcd.print("Name:ALEX"); 
  delay(6000);

}

void GameOver() { 
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Congrats!");
  lcd.setCursor(0,1);
  lcd.print("Press btn->quit");

}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(pinSW, INPUT_PULLUP);
  updateMenu();

}

void loop() {
  // put your main code here, to run repeatedly:
   xValue = analogRead(pinX);
   yValue = analogRead(pinY);
   
   currentMillis = millis();
  
  if(xValue < minThreshold && joyMoved == false){
    menu--;
    updateMenu();
    delay(100);
    joyMoved = true;
  
  }
  
  if(xValue > maxThreshold && joyMoved == false){
    menu++;
    updateMenu();
    delay(100);
    joyMoved = true;
  
  }

  if(xValue > minThreshold && xValue < maxThreshold) {
    joyMoved = false; 
  }
    
  if(!digitalRead(pinSW)) { 
     executeAction();
     updateMenu();
     delay(100);
  
  }
  
  if(timer == true) {  
    if(currentMillis - startMillis >= miniPeriod) {
      startingLevelValue += 1; 
      currentMillis = millis();
    
    }
    if(startMillis - currentMillis >= period) { 
      GameOver();
        if(!digitalRead(pinSW)) {
          menu = 2;
          updateMenu();
        
        }
      }
    timer = false;
    }                      

}
