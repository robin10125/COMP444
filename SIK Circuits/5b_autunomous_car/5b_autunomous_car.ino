/*
This program borrows heavily from SIK Circuit 5a MotorBasics from the SIK handbook
*/

//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;  
const int BIN1 = 8;           //control pin 1 on the motor driver for the right motor
const int BIN2 = 9;                      //control pin 2 on the motor driver for the right motor
const int PWMA = 11;  
const int PWMB = 10;          //speed control pin on the motor driver for the right motor

const int trig = 6;
const int echo = 5;

int switch_pin = 7;             //switch to turn the robot on and off

unsigned long time;
float distance;
void setup() {
  //motor control
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //distance reader
  pinMode(trig, OUTPUT);  
  pinMode(echo, INPUT); 

  Serial.println("Enter motor speed, from 1-9.  Use WASD for control"); 
}

void loop() {
  
  distance = get_distance();
  if (digitalRead(7) == 1) { 
    if (distance < 25){
      time = millis();
      while (millis()-time < 1000){
        spin_motor_right(-200);
        spin_motor_left(-200);
        Serial.println("Back");
      }
      time = millis();
      while (millis()-time < 2000){
        spin_motor_right(-200);
        spin_motor_left(200);
      }
    }
    else{
      spin_motor_right(200);
      spin_motor_left(200);
    }
    
  } else {                              //if the switch is off...
    spin_motor_right(0);  
    spin_motor_left(0);                 //turn the motor off
  }
  delay(100);
  
}
float get_distance(){

  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  float echo_time = pulseIn(echo, HIGH); //length in microseconds of pulse, reads how long it takes for echo to read HIGH
  //sound travels 0.0343 cm/microsecond.  (2 times the ) Distance = vt, so 0.0343 * echo_time.  
  //this distance is to the reflection point and back, so it is further divided by 2 to get the distance of the reflection point
  //0.0343 / 2 is 0.01715
  return echo_time * 0.01715; 
}
//spinMotor function taken from SIK Circuit 5a MotorBasics
void spin_motor_right(int motor_speed)                       //function for driving the right motor
{
  if (motor_speed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motor_speed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motor_speed));                 //now that the motor direction is set, drive it at the entered speed
}

void spin_motor_left(int motor_speed)                       //function for driving the left motor
{
  if (motor_speed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motor_speed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motor_speed));                 //now that the motor direction is set, drive it at the entered speed
}