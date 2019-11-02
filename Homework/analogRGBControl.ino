const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;
const int bluePin = 9;
const int greenPin = 10;
const int redPin = 11;
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0; 
int ledValue1 = 0;
int ledValue2 = 0;
int ledValue3 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(potPin3, INPUT);
  pinMode(bluePin, OUTPUT); 
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  setColor();
}

void setColor() {
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);
  ledValue1 = potValue1 / 4;
  ledValue2 = potValue2 / 4;
  ledValue3 = potValue3 / 4;
  analogWrite(bluePin, ledValue1);
  analogWrite(greenPin, ledValue2); 
  analogWrite(redPin, ledValue3);
  Serial.println(ledValue3);
  Serial.println("\t");
  Serial.println(ledValue2);
  Serial.println("\t");
  Serial.println(ledValue1);  
}
