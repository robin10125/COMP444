/**/
float echo_time;
float distance;
const int trig = 11;
const int echo = 12;
const int red = 3;
const int green =5;
const int blue = 6;
int index;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);  
  pinMode(echo, INPUT);    

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  echo_time = pulseIn(echo, HIGH); //length in microseconds of pulse, reads how long it takes for echo to read HIGH
  //sound travels 0.0343 cm/microsecond.  (2 times the ) Distance = vt, so 0.0343 * echo_time.  
  //this distance is to the reflection point and back, so it is further divided by 2 to get the distance of the reflection point
  //0.0343 / 2 is 0.01715
  distance = echo_time * 0.01715; 
  Serial.println(distance);
  if (distance < 15){
    set_led(255,0,0);
  }
  else if (distance < 25){
    set_led(0,255,0);
  }
  else if (distance < 35){
    set_led(0,0,255);
  }
  else{ set_led(255,0,255);}

  delay(50);
}
void set_led(int r,int g,int b){
  analogWrite(red,r);
  analogWrite(green,g);
  analogWrite(blue,b);
}