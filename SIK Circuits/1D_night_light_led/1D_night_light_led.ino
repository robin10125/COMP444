/*
 Night light LED program
*/

int photoresistor;  
int potentiometer;            
const int threshold = 550; 

int RedPin = 9;
int GreenPin = 10;
int BluePin = 11;
//color_array corresponds to {red, orange, yellow, green, cyan, blue, magenta}
int color_array[7][3] = {{100,0,0},{100,50,0},{100,100,0},{0,100,0},{0,100,100},{0,0,100},{100,0,100}} ;
//colour_index corresponds to the color in colour_array, and is calculated by the potentiometer reading
int color_index;
void setup()
{
  Serial.begin(9600);               //start a serial connection with the computer
  int photoresistor = 0;  
  int potentiometer = 0;   
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);             
}
void loop()
{
  //read the brightness of the ambient light
  photoresistor = analogRead(A0);
  potentiometer = analogRead(A1);

  Serial.println(photoresistor);    //print the value of photoresistor in the serial monitor on the computer
  Serial.println(potentiometer);

  if (photoresistor < threshold){
    
    //fit potentiometer value to [0,6] -> divide by 147 to fit to [0-6.95918...) 
    //Arduino will only take the integer value of this, so the result will be: integers in range [0,6]
    //this allows the potentiometer value to index the colour_array
    color_index = potentiometer/147;
    analogWrite(RedPin, color_array[color_index][0]);
    analogWrite(GreenPin, color_array[color_index][1]);
    analogWrite(BluePin, color_array[color_index][2]);

  }
  else{
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 0);
  }

  delay(100);               
}
