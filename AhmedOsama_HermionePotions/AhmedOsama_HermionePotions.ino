//Timer Library
#include <Event.h>
#include <Timer.h>

// pins definition
#define pushButton_start 7
#define red 8
#define green 9
#define white 10

//Creating timer
Timer recipe_routine;

void setup() {
  // setting pin modes
  pinMode(pushButton_start, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(white, OUTPUT);

  // waiting for pushbutton to br pressed
  while(!digitalRead(pushButton_start));

  // turn red led on for 15 minutes
  digitalWrite(red, HIGH);
  recipe_routine.every(15 * 60000, turnoff_red, 1);

  // flash green led for 5 seconds every two minutes
  recipe_routine.every(2 * 60000, flash_green);

  // flashes white led for 10 seconds at 5 minutes and 8 minutes
  recipe_routine.every(5 * 60000, flash_white, 1);
  recipe_routine.every(8 * 60000, flash_white, 1);
}  

void loop() {
  // update timer
  recipe_routine.update();
}

// flash green led for 5 seconds
void flash_green()
{
  digitalWrite(green, HIGH);
  delay(5000);
  digitalWrite(green, LOW);
}

// flash white led for 10 seconds
void flash_white()
{
  digitalWrite(white, HIGH);
  delay(10000);
  digitalWrite(white, LOW);
}

// turn off red led
void turnoff_red()
{
  digitalWrite(red, LOW);
}
