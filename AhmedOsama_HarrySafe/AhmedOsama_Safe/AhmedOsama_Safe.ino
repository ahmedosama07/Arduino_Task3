// defining pins

// encoders pins are attached to interrupt pins
#define signal_A_Encoder1 2
#define signal_B_Encoder1 3

#define signal_A_Encoder2 18
#define signal_B_Encoder2 19

#define signal_A_Encoder3 20
#define signal_B_Encoder3 21

// the green led pin
#define green_led 5

// encoders' resolution
#define resolution 512

// encoders' counters
int counter_Encoder1 = 0;
int counter_Encoder2 = 0;
int counter_Encoder3 = 0;

// angle of each encoder
int angle_Encoder1 = 0;
int angle_Encoder2 = 0;
int angle_Encoder3 = 0;

// ratio between complete revolution in degrees and the resolution of the encoders
int ratio = 360 / resolution;

void setup() {
  // setting pin modes
  pinMode(signal_A_Encoder1, INPUT_PULLUP);
  pinMode(signal_B_Encoder1, INPUT_PULLUP);
  pinMode(signal_A_Encoder2, INPUT_PULLUP);
  pinMode(signal_B_Encoder2, INPUT_PULLUP);
  pinMode(signal_A_Encoder3, INPUT_PULLUP);
  pinMode(signal_B_Encoder3, INPUT_PULLUP);

  pinMode(green_led, OUTPUT);

  // using attach interrupt for the encoders to know when their outputs change
  attachInterrupt(digitalPinToInterrupt(signal_A_Encoder1),
                  ISR_A_Encoder1,
                  CHANGE);
 attachInterrupt(digitalPinToInterrupt(signal_B_Encoder1),
                  ISR_B_Encoder1,
                  CHANGE);

 attachInterrupt(digitalPinToInterrupt(signal_A_Encoder2),
                  ISR_A_Encoder2,
                  CHANGE);
 attachInterrupt(digitalPinToInterrupt(signal_B_Encoder2),
                  ISR_B_Encoder2,
                  CHANGE);

 attachInterrupt(digitalPinToInterrupt(signal_A_Encoder3),
                  ISR_A_Encoder3,
                  CHANGE);
 attachInterrupt(digitalPinToInterrupt(signal_B_Encoder3),
                  ISR_B_Encoder3,
                  CHANGE);
}

void loop() {
  // if encoder completes complete revolution then it's counter is set to zero
  if(counter_Encoder1 == resolution || counter_Encoder1 == resolution * -1)
  {
    counter_Encoder1 = 0;
  }

  if(counter_Encoder2 == resolution || counter_Encoder2 == resolution * -1)
  {
    counter_Encoder2 = 0;
  }

  if(counter_Encoder3 == resolution || counter_Encoder3 == resolution * -1)
  {
    counter_Encoder3 = 0;
  }


  // calculating angles in degrees
  angle_Encoder1 = counter_Encoder1 * ratio;
  angle_Encoder2 = counter_Encoder2 * ratio;
  angle_Encoder3 = counter_Encoder3 * ratio;

  // calculate positive angle if it is reached through negative direction
  if(angle_Encoder1 < 0)
  {
    angle_Encoder1 = 360 - angle_Encoder1;
  }
  

  if(angle_Encoder2 < 0)
  {
    angle_Encoder2 = 360 - angle_Encoder2;
  }

  if(angle_Encoder3 < 0)
  {
    angle_Encoder3 = 360 - angle_Encoder3;
  }



  // turning on the led when requirements achieved
  if(angle_Encoder1 == 37 && angle_Encoder2 == 10 && angle_Encoder3 == 54)
  {
    digitalWrite(green_led, HIGH);
  }
}


// calculating counter for each encoder

// encoder 1
void ISR_A_Encoder1()
{
  if(digitalRead(signal_A_Encoder1) != digitalRead(signal_B_Encoder1))
  {
    counter_Encoder1 ++;
  }
  else
  {
    counter_Encoder1 --;
  }
}

void ISR_B_Encoder1()
{
  if(digitalRead(signal_A_Encoder1) <= digitalRead(signal_B_Encoder1))
  {
    counter_Encoder1 ++;
  }
  else
  {
    counter_Encoder1 --;
  }
}

/*------------------------------------------------------------------------------*/
// encoder 2
void ISR_A_Encoder2()
{
  if(digitalRead(signal_A_Encoder2) != digitalRead(signal_B_Encoder2))
  {
    counter_Encoder2 ++;
  }
  else
  {
    counter_Encoder2 --;
  }
}

void ISR_B_Encoder2()
{
  if(digitalRead(signal_A_Encoder2) <= digitalRead(signal_B_Encoder2))
  {
    counter_Encoder2 ++;
  }
  else
  {
    counter_Encoder2 --;
  }
}

/*------------------------------------------------------------------------------*/
// encoder 3
void ISR_A_Encoder3()
{
  if(digitalRead(signal_A_Encoder3) != digitalRead(signal_B_Encoder3))
  {
    counter_Encoder3 ++;
  }
  else
  {
    counter_Encoder3 --;
  }
}

void ISR_B_Encoder3()
{
  if(digitalRead(signal_A_Encoder3) <= digitalRead(signal_B_Encoder3))
  {
    counter_Encoder3 ++;
  }
  else
  {
    counter_Encoder3 --;
  }
}
