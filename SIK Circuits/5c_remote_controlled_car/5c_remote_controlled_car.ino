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


int switch_pin = 7;             //switch to turn the robot on and off

int speed;       
char direction; 

void setup() {
  //motor control
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);   
  Serial.setTimeout(100);
  Serial.println("Enter motor speed, from 1-9.  Use WASD for control"); 
  speed= 0;
  direction = ' ';
}

void loop() {
  
  if (Serial.available() > 0) {         //if the user has entered something in the serial monitor
    char input = char(Serial.read());  
    //check for speed input
    if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6' || input == '7' || input == '8' || input == '9'){
      speed = int(input-'0')*25;
      Serial.println("Speed change");
    }
    //check for direction
    if (input == 'w' || input == 'a' || input == 's' || input == 'd' || input == ' '){
     direction = input;
     Serial.println("Direction change");
    }
    Serial.print("Motor Speed: ");      
    Serial.println(speed);
    Serial.print("Direction: ");  
    Serial.println(direction);
  }
  
  if (digitalRead(7) == 1) { 

    if (direction == 'w'){
      spin_motor_right(speed);
      spin_motor_left(speed);
    }
    if (direction == 's'){
      spin_motor_right(-speed);
      spin_motor_left(-speed);
    }
    if (direction == 'a'){
      spin_motor_right(speed);
      spin_motor_left(-speed);
    }
    if (direction == 'd'){
      spin_motor_right(-speed);
      spin_motor_left(speed);
    }
    if (direction == ' '){
      spin_motor_right(0);
      spin_motor_left(0);
    }
    
  } else {                              //if the switch is off...
    spin_motor_right(0);  
    spin_motor_left(0);                 //turn the motor off
  }
  delay(100);
  
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