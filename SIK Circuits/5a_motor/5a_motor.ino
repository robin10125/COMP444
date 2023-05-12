/*
This program borrows heavily from SIK Circuit 5a MotorBasics from the SIK handbook
*/

//PIN VARIABLES
const int AIN1 = 13;           
const int AIN2 = 12;  
const int BIN1 = 8;          
const int BIN2 = 9;                     
const int PWMA = 11;  
const int PWMB = 10;           

int switch_pin = 7;             //switch to turn the robot on and off

int motor_speed;       

void setup() {
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  Serial.begin(9600);   
  
  Serial.println("Enter motor speed, from 0-255."); 
  motor_speed= 0;
}

void loop() {
  
  if (Serial.available() > 0) {         //if the user has entered something in the serial monitor
    int input_speed = Serial.parseInt();     //set the motor speed equal to the number in the serial message
    if (input_speed != 0){
      motor_speed = input_speed;
    }
    Serial.print("Motor Speed: ");      
    Serial.println(motor_speed);
  }
  
  if (digitalRead(7) == 1) { 
    spin_motor(motor_speed);
  } else {                              //if the switch is off...
    spin_motor(0);                   //turn the motor off
  }
  
}
//spinMotor function taken from SIK Circuit 5a MotorBasics
void spin_motor(int motor_speed)                       //function for driving the right motor
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
