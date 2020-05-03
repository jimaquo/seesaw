#include <Arduino.h> // add the Arduino library
#include <Servo.h> // add the Servo library

//Global values that can be seen by the entire program
int dialPin (A1); // speed control varistor pin
int dialVal (0); //analog vlaue of the varister between 0 and 1023
int stopPin (4); // stop button pin
int stopVal (0); // stop button value
int startPin (5); //start button pin
int startVal (0); //start button value
int limitPinOne (6); //limit switch pin
int limitValOne (0);
int limitPinTwo (7); //other limit switch
int limitValTwo (0);

//A class created to control the speed of the servo without cluttering the loop or using delay.
class servoControl
{
  Servo servo;              // the servo
  
  int pos; // current servo position 
  int increment; // increment to move for each interval
  unsigned int updateInterval; // the value used to determine how often the script updates the servo pos
  unsigned long lastUpdate; // last update of servo pos (millis)
  
  public: //parts of the class that the rest of the script can see
    
  servoControl(int interval) //class function that allows us to set the speed of the servoControl class
  {
    updateInterval = interval;
    increment = 1;
  }
  void attach(int pin) //class function so we can attach more servos with less code later.
  {
    servo.attach (pin); //tells the code to expect the pin number of the servo
  }
  
//a function timer using the millis function so we don't have to use delays and hold up the system
// otherwise the inputs won't work while the seesaw is going.
  void Update() 
  {
    if((millis() - lastUpdate) > updateInterval)  // compares time minus last update to the update interval
    {
        pos += increment; //add position of servo plus the increment value we want the servo to rotate
        servo.write(pos); //send the new position to the servo
        lastUpdate = millis(); //sets the lastUpdate value to the current millis clock
        if (limitValOne == LOW) // if the servo is at one limit or the other...
        {
        increment = -increment;// ...reverse direction
        }   
        if (limitValTwo == LOW) // if the servo is at one limit or the other...
        {
        increment = -increment;// ...reverse direction
        } 
    }    
  }
};

servoControl seesaw(dialVal/5); //make a new object called seesaw based on the servoControl class

void setup()
{ 
  seesaw.attach(3); //tell the code that the servo object called seesaw is hooked up to pin 3
  Serial.begin (9600); //turn on serial output for testing
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

void readButtons()
{
  startVal = digitalRead (startPin); //checks if the start button is pushed
  stopVal = digitalRead(stopPin); //Checks if the stop button is pushed
  dialVal = analogRead(dialPin); //checks the dial value between 0 and 1023      
  limitValOne = digitalRead (limitPinOne); //checks if a limit is reached
  limitValTwo = digitalRead (limitPinTwo);
}

void loop()
{
  readButtons();
  seesaw.Update(); //tells the seesaw object to run the update function
  Serial.println (dialVal);
}
