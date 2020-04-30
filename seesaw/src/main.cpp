#include <Arduino.h> // add the Arduino library
#include <Servo.h> // add the Servo library

int dialPin (A1); // speed control varistor pin
int dialVal (0); // speed control value
int stopPin (4); // stop button pin
int stopVal (0); // stop button value
int startPin (5); //start button pin
int startVal (0); //start button value
int limitPinOne (6); //limit switch pin
int limitValOne (0); //limit switch one value
int limitPinTwo (7); //other limit switch
int limitValTwo (0); //limit switch two's value
int servoPos (0); //a value to track the current position of the servo

Servo theServo; //defining the name of the servo using the Servo.h library

void setup()
{ 
  Serial.begin (9600); //turn on serial output
  

  theServo.attach(3); //tell the program what physical pin the servo control is attached to

  pinMode (dialPin,INPUT); //set the dial pin as an input
  pinMode (stopPin,INPUT_PULLUP); //set the stop pin as an input with the pullup resistors on
  digitalWrite (stopPin,HIGH); //set the stop pin to a high state
  pinMode (startPin,INPUT_PULLUP); //set the start pin as an input with pullups on
  digitalWrite (startPin,HIGH); //set the start pin high
  pinMode (limitPinOne,INPUT_PULLUP); //set the first limit switch as input with pullups on
  digitalWrite (limitPinOne,HIGH); //set the pin high
}

void loop()
{
  dialVal = analogRead(dialPin);
  startVal = digitalRead (startPin);
  stopVal = digitalRead(stopPin);

  Serial.println (startVal);
}