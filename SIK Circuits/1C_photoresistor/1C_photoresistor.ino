/*
 Photoresistor program for SIK circuit 1C
*/

int photoresistor = 0;              //this variable will hold a value based on the brightness of the ambient light
const int threshold = 700;                //if the photoresistor reading is below this value the the light will turn on

void setup()
{
  Serial.begin(9600);               //start a serial connection with the computer

  pinMode(13, OUTPUT);              //set pin 13 as an output that can be set to HIGH or LOW
}

void loop()
{
  //read the brightness of the ambient light
  photoresistor = analogRead(A0);   //set photoresistor to a number between 0 and 1023 based on how bright the ambient light is
  Serial.println(photoresistor);    //print the value of photoresistor in the serial monitor on the computer

  digitalWrite(13, photoresistor < threshold); //photoresistor < threshold is returns true or false, which is interpreted as 1 or 0 by digitalWrite

  delay(100);               
}

