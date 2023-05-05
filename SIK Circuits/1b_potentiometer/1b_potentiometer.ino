/*
Blinking LED Program with Potentiometer
*/

bool light; //light determines whether light is on or off
int potentiometer_position; //0-1023 based off of potentiometer position
int blink_length;

void setup() {
  //set the button pins as inputs
  pinMode(13, OUTPUT);
  light = true; //set to true at start
  potentiometer_position = 1;
  blink_length = 1;
}

void loop() {
  potentiometer_position = analogRead(A0); // read potetiometer position
  blink_length = potentiometer_position / 1.023;  //normalize value to range [0,1000]
  
  light = !light; //alternate light between true and false
  
  digitalWrite(13, light); //digitalWrite interprets true the same as HIGH and false the same as LOW
  delay(blink_length);
}


