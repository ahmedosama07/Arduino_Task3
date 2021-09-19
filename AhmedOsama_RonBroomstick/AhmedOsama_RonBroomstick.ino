// Wire library for I2C 
#include <Wire.h>

// IMU Address
#define IMU_ADDRESS 0x68

// Led pin
#define REDLED 13

// Itterations for error calculations
const uint32_t ITTERATIONS = 3000;

// Offsets
int32_t x_gyro_offset = 0;
int32_t y_gyro_offset = 0;

// Declarintg pitch and roll
int16_t roll;
int16_t pitch;

// Declaring time variables to calculate the angle from the angular velocity
uint32_t elapsed_time;
uint32_t current_time;
uint32_t previous_time;

void setup() {
  // Setting pinMode
  pinMode(REDLED, OUTPUT);
  
  // Initialization
  setIMU_Register(0x6B, 0x00);

  // Gyroscope Configuration
  // FSR = 500
  setIMU_Register(0x1B,0x08);

  //Calibration
  calibrateIMU(ITTERATIONS);
}

void loop() {
  // Calculating time
  previous_time = current_time;
  current_time = millis();
  elapsed_time = (current_time - previous_time) / 1000;
  
  // Reading Sensors
  int16_t x_gyro = readIMU_2Bytes(0x43);
  int16_t y_gyro = readIMU_2Bytes(0x45);

  // Scaling Values
  // Angular velocity in degrees per second
  x_gyro = ((x_gyro * 500) / 32767) + x_gyro_offset;
  y_gyro = ((y_gyro * 500) / 32767) + y_gyro_offset;

  // pitch and roll angles
  roll = x_gyro * elapsed_time;
  pitch = y_gyro * elapsed_time;

  // blinking the led while one of the two angles at least exceeds 60 degrees
  while(roll > 60 || pitch > 60)
  {
    digitalWrite(REDLED, HIGH);
    delay(10);
    digitalWrite(REDLED, LOW);
  }

  delay(10);
}

// Interfacing IMU
void setIMU_Register(uint8_t reg, uint8_t val)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

// Read 1 byte
uint8_t readIMU_1Byte(uint8_t reg)
{
  uint8_t data = 0;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 1);
  while(Wire.available() < 1);
  data = Wire.read();
  return data;
}

// Read 2 byte
uint16_t readIMU_2Bytes(uint8_t reg)
{
  uint16_t data = 0;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 2);
  while(Wire.available() < 2);
  data = Wire.read() << 8 | Wire.read();
  return data;
}

// Calibration
void calibrateIMU(uint32_t ITTERATIONS)
{
  for(uint32_t i = 0; i < ITTERATIONS; i++)
  {
    x_gyro_offset += readIMU_2Bytes(0x43);
    y_gyro_offset += readIMU_2Bytes(0x45);
  }

  x_gyro_offset /= ITTERATIONS;
  y_gyro_offset /= ITTERATIONS;
}
