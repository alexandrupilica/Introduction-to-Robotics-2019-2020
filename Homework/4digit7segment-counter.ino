const int pinSW = A2;
const int pinX = A1;
const int pinY = A0;
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;
const int noDisplays = 4;
const int noDigits = 10;

int dpState = LOW;
int swState = LOW;

bool joyMoved = false;
int xValue = 0;
int yValue = 0;
int swValue = 0;
int digit = 0;
int minThreshold = 100;
int maxThreshold = 900;
byte decimalPoint = 1;
int display = 0;
const int minDisplay = 0;
const int maxDisplay = 3;


int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG ,pinDP
};

int digits[noDisplays] = {
  pinD1, pinD2, pinD3, pinD4
};

byte digitMatrix[noDigits][segSize - 1] = {
// a b c d e f g
  {1,1,1,1,1,1,0},  //0
  {0,1,1,0,0,0,0},  //1
  {1,1,0,1,1,0,1},  //2
  {1,1,1,1,0,0,1},  //3
  {0,1,1,0,0,1,1},  //4
  {1,0,1,1,0,1,1},  //5
  {1,0,1,1,1,1,1},  //6
  {1,1,1,0,0,0,0},  //7
  {1,1,1,1,1,1,1},  //8
  {1,1,1,1,0,1,1}   //9          
};

void displayNumber(byte digit) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}

void activateDisplay() {
  for (int i = 0; i < noDisplays; i++) {
    digitalWrite(digits[i], HIGH);
    digitalWrite(digits[i], LOW);   
  }
}

void cycling(int num){
  digitalWrite(digits[num], HIGH);
  delay(250);
  digitalWrite(digits[num], LOW);
  delay(250);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noDisplays; i++) {
    pinMode(digits[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  yValue = analogRead(pinY);
  xValue = analogRead(pinX);
  swValue = digitalRead(pinSW);
  
  activateDisplay();
  cycling(display);
  
  if (swValue == HIGH) {
    digitalWrite(segments[segSize - 1], LOW);
  } else {
    digitalWrite(segments[segSize - 1], HIGH);
  }
  
  if (xValue < minThreshold && joyMoved == false) {
     if (display > minDisplay) {
        display--;
     } else {
       display = maxDisplay; 
     }
     cycling(display);
     joyMoved = true;
  }
  
  if (xValue > maxThreshold && joyMoved == false) {
      if (display < maxDisplay) {
        display++;
      } else {
        display = minDisplay;
      }
      cycling(display);
      joyMoved = true;
  }
  
  if (yValue < minThreshold && joyMoved == false) {
      if (digit > 0) {
        digit--;
      } else {
        digit = 9;
      }
      joyMoved = true;
  }
  
  if (yValue > maxThreshold && joyMoved == false) {
      if (digit < 9) {
        digit++;
      } else {
        digit = 0;
      }
      joyMoved = true;
  }

  if (yValue > minThreshold && yValue < maxThreshold) {
      joyMoved = false;
  }

  
  
  displayNumber(digit);
  delay(1);


}
