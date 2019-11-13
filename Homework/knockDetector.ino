const int buzzerPin = A0;
const int activeBuzzerPin = 11;
const int buttonPin = 2;
int buttonState = 0;
int buzzerValue = 0;
int activeBuzzerValue = 0;
const int threshold = 1;
//unsigned int startTime = 0;
//unsigned int currentTime = 0;
//unsigned int period = 5000;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(activeBuzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buzzerValue = analogRead(buzzerPin);
  buttonState = digitalRead(buttonPin);
  if(buzzerValue != 0)
    Serial.println(buzzerValue);
  if(buzzerValue > threshold) {
    Serial.println("knock");
    tone(activeBuzzerPin, 150);
  }
  activeBuzzerValue = !buttonState;
  digitalWrite(activeBuzzerPin, activeBuzzerValue); 
  //Serial.println(buttonState);
}
 
 
