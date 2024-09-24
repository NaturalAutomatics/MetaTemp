/*
 * Arduino Uno MetaTemp Prototype
 * Testing Dual Peltier elements  + L298N Driver
 * 
 * Created by Alex Noyanov June 25th 2022 
 * 
 * Connection Guide:
 * 
 * L298N Driver | Arduino 
 * 
 * ENA          | 10
 * IN 1         | 5
 * IN 2         | 4
 * IN 3         | 3
 * IN 4         | 2
 * ENB          | 11
 * 
 */

// Connections:
int leftOne = 2;
int leftTwo = 3;

int rightOne = 4;
int rightTwo = 5;

 void coolRight(){
  digitalWrite(rightOne,HIGH);
  digitalWrite(rightTwo,LOW);
 }

void coolLeft(){
  digitalWrite(leftOne,HIGH);
  digitalWrite(leftTwo,LOW);
}

void heatRight(){
  digitalWrite(rightOne,LOW);
  digitalWrite(rightTwo,HIGH);
}

void heatLeft(){
  digitalWrite(leftOne,LOW);
  digitalWrite(leftTwo,HIGH);
}

void offAll(){
  digitalWrite(leftOne, LOW);
  digitalWrite(leftTwo, LOW);
  digitalWrite(rightOne, LOW);
  digitalWrite(rightTwo, LOW);
}
 

void setup() {
  // put your setup code here, to run once:
  pinMode(leftOne, OUTPUT);
  pinMode(leftTwo, OUTPUT);
  pinMode(rightOne, OUTPUT);
  pinMode(rightTwo, OUTPUT);  
  offAll();
}
void loop() {
  // put your main code here, to run repeatedly:
  coolLeft();
  coolRight();
  delay(100);
  offAll();
  delay(100);

}
