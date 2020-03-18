#include <Arduino.h>
#include <Servo.h>

//allocate the pins on the board
int button_up = (2); // speed up
int button_down = (3); // speed down
int button_stop = (4); // STOP, I wanna get off!!

  //make variables for the button states to be stored in
int buttonstate_up = (0);
int buttonstate_down = (0);
int buttonstate_stop = (0);
int speedstate = (0);

Servo gary; //named the servo gary... because reasons

void setup() 
{
  gary.attach (5); //gary the servo is controlled from pin 5 on the arduino using pwm (pulse width modulation)
  pinMode (2,INPUT_PULLUP); //Set the pins for the speed buttons to inputs
  pinMode (3, INPUT_PULLUP);//gary the servo is taken care of by the Servo.h
  pinMode (4,INPUT_PULLUP);
}

void loop() 
{
  buttonstate_up = digitalRead (button_up);
    if (buttonstate_up == LOW) //speed up button pushed
      speedstate++; //add one to the speedstate that gary will work from

  buttonstate_down = digitalRead (button_down);
    if (buttonstate_down == LOW) //speed down button pushed
      speedstate--; //take one off the speedstate that gary will work from

  buttonstate_stop  = digitalRead (button_stop);
    if (buttonstate_stop == LOW) //STOP button pushed
      speedstate = (0); //Resets Speed state to ZERO!

}