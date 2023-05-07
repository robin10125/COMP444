/*
Program 2B Trumpet
*/
int speakerPin = 12; 

int yellow_button = 5;
int red_button = 4;
int green_button = 3;
int blue_button = 2;
//frequencies is {e4,g4,a4,b4,c4,d4}
int frequencies[] = {330,392,440,494,524,588};

void setup()
{
  pinMode(speakerPin, OUTPUT);    //set the output pin for the speaker
  pinMode(yellow_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);
  pinMode(blue_button, INPUT_PULLUP);
  
  Serial.begin(9600);   
}

void loop() {
   if (digitalRead(yellow_button) == LOW && digitalRead(blue_button) == HIGH){tone(speakerPin,frequencies[0],100);}
   else if (digitalRead(red_button) == LOW && digitalRead(blue_button) == HIGH){tone(speakerPin,frequencies[1],100);}
   else if (digitalRead(green_button) == LOW && digitalRead(blue_button) == HIGH){tone(speakerPin,frequencies[2],100);}

   else if (digitalRead(yellow_button) == LOW && digitalRead(blue_button) == LOW){tone(speakerPin,frequencies[3],100);}
   else if (digitalRead(red_button) == LOW && digitalRead(blue_button) == LOW){tone(speakerPin,frequencies[4],100);}
   else if (digitalRead(green_button) == LOW && digitalRead(blue_button) == LOW){tone(speakerPin,frequencies[5],100);}
  //delay(100);
   
}
