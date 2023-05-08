/*SIK circuit 3A, servo motor*/
#include <Servo.h>

Servo my_servo;
int potentiometer;
int servo_val;

void setup() {
  // put your setup code here, to run once:
  my_servo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  potentiometer = analogRead(A0);
  
  servo_val = map(potentiometer, 0, 1023, 20, 160);
  my_servo.write(servo_val);
}
