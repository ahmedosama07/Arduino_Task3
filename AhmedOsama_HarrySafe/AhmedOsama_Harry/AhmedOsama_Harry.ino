/*
 * I assumed that the sensor returns 1 if black line is detected
*/

// defining ir sensor pins
#define ir_left_pin 2
#define ir_mid_pin 3
#define ir_right_pin 4

// declaring variables to store sensors readings
int ir_left;
int ir_mid;
int ir_right;

// number of times to reach an empty end
int empty = 0;


void setup() {
  // setting pin modes
  pinMode(ir_left_pin, INPUT);
  pinMode(ir_mid_pin, INPUT);
  pinMode(ir_right_pin, INPUT);
}

void loop() {
  // reading the sensors
  ir_left = digitalRead(ir_left_pin);
  ir_mid = digitalRead(ir_mid_pin);
  ir_right = digitalRead(ir_right_pin);

  // moving forward while the middle(front) sensor reads a black line
  while(ir_mid == 1)
  {
    moveForward();

    // handling the case if moved on the same way twice
    if(ir_right == 0 && ir_left == 1 && (empty == 2 || empty == 3))
    {
      rotate90left();
    }
  }

  // rotate right if reaches to a corner and only right side sensor reads a black line
  if(ir_right == 1 && ir_left == 0)
  {
    rotate90right();
  }

  // rotate left if reaches to a corner and only left side sensor reads a black line
  else if(ir_right == 0 && ir_left == 1)
  {
    rotate90left();
  }

  // rotate 180 degrees if reaches an empty end and count this end
  else if(ir_right == 0 && ir_left == 0)
  {
    rotate90right();
    rotate90right();

    empty++;
  }

  // if middle(front) side sensor reads nothing but the other two sensors read a black line the robot rotates to right
  else if(ir_right == 1 && ir_left == 1)
  {
    rotate90right();
  }
}

void moveForward(){}
void moveBackward(){}
void rotate90right(){}
void rotate90left(){}
