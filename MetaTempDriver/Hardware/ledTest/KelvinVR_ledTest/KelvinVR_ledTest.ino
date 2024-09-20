
int buzzer = 37;
int greenLed = 10;
int redLed = 11;
int ledPlus = 9;
int ledMinus = 8;

int pinsOutput[] = {buzzer,greenLed, redLed,ledPlus, ledMinus};

// Values for methods:
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void blinkLed(int ledPin){
  digitalWrite(ledPin,HIGH);
  delay(1000);
  digitalWrite(ledPin,LOW);
  delay(1000);
}

void fadeEffect(int led) {
   // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void ledOn(){
  digitalWrite(ledPlus,HIGH);
  digitalWrite(ledMinus,LOW);
}

void ledOff() {
  digitalWrite(ledPlus,LOW);
}

void blinkFront(int delayTime){
  digitalWrite(ledPlus,HIGH);
  delay(delayTime);
  digitalWrite(ledPlus,LOW);
  delay(delayTime);
}

void fullPinSetup(){
  for(int i = 0; i < sizeof(pinsOutput); i++){
    pinMode(pinsOutput[i],OUTPUT);
  }
}

void setup() {
  // put your setup code here, to run once:
  fullPinSetup();
  //blinkFrontLed(greenLed);
}

void loop() {
  // put your main code here, to run repeatedly:
//  blinkLed(greenLed);
//  delay(100);
//  blinkLed(redLed);
//  blinkFront(100);
//fadeEffect(ledPlus);
fadeEffect(greenLed);
fadeEffect(ledPlus);
}
