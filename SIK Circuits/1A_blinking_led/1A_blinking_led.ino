/*
Blinking LED Program
*/


bool light; //light determines whether light is on or off

void setup() {
  //set the button pins as inputs
  pinMode(13, OUTPUT);
  light = true; //set to true at start
}

void loop() {
light = !light; //alternate light between true and false
digitalWrite(13, light); //digitalWrite interprets true the same as HIGH and false the same as LOW
delay(1000);
}


