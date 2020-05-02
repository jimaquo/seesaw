#include <Arduino.h> // add the Arduino library
#include <Servo.h> // add the Servo library

//Global values that can bee sen by the entire program
int dialPin (A1); // speed control varistor pin
float dialVal (0);
int stopPin (4); // stop button pin
int stopVal (0); // stop button value
int startPin (5); //start button pin
int startVal (0); //start button value
int limitPinOne (6); //limit switch pin
int limitValOne (0); //limit switch one value
int limitPinTwo (7); //other limit switch
int limitValTwo (0); //limit switch two's value

//A class created to control the speed of the servo without cluttering the loop.
class Sweeper
{
  Servo servo;              // the servo
  
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position
  
public: 
  Sweeper(float interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  void attach(int pin)
  {
    servo.attach (pin);
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      if ((pos >= 180) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};

Sweeper speedcontrol(dialVal/5);

void setup()
{ 
  speedcontrol.attach(3);
  Serial.begin (9600); //turn on serial output
  pinMode (dialPin,INPUT); //set the dial pin as an input
  pinMode (stopPin,INPUT_PULLUP); //set the stop pin as an input with the pullup resistors on
  digitalWrite (stopPin,HIGH); //set the stop pin to a high state
  pinMode (startPin,INPUT_PULLUP); //set the start pin as an input with pullups on
  digitalWrite (startPin,HIGH); //set the start pin high
  pinMode (limitPinOne,INPUT_PULLUP); //set the first limit switch as input with pullups on
  digitalWrite (limitPinOne,HIGH); //set the pin high
  pinMode (limitPinTwo,INPUT_PULLUP); //set second limit switch to input with pullups
  digitalWrite (limitPinTwo,HIGH); //set pin high
}



void loop()
{
  startVal = digitalRead (startPin);
  stopVal = digitalRead(stopPin);
  dialVal = analogRead(dialPin);
  limitValOne = digitalRead (limitPinOne);
  limitValTwo = digitalRead (limitPinTwo);
  speedcontrol.Update;
  Serial.println (dialVal);
}