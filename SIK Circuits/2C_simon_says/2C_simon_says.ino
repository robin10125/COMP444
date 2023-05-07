/*
Program 2C Simon Says
*/
int speakerPin = 12; 

int yellow_button = 8;
//int yellow_light = 9;
int red_button = 6;
//int red_light = 7;
int green_button = 4;
//int green_light = 5;
int blue_button = 2;
//int blue_light = 3;

//blue,green,red,yellow
int led_pins[4] = {3,5,7,9};

//frequencies corresponds to g2,a3,b3,c3,d3,e3,f3,g3,a4,b4,c4,d4,e4,f4,g4
int frequencies[] = {98, 110, 124, 131,147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};
int button_frequencies[] = {349, 392, 440, 494};

int lose_sequence[3][2]{
  {2,1},{1,1},{0,5}
};
int begin_sequence[3][2]{
  {12,1},{14,1},{16,1}
};
int win_sequence[7][2]{
  {4,1},{6,1},{4,1},{6,1},{4,1},{6,1},{8,3}
};

int song_sequence[9][2]{
  {0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,2},
};
int sequence[10];
int val;
bool game_start;
bool check;
unsigned long start_time = 0;
int time_limit=10000;

void setup()
{
  pinMode(speakerPin, OUTPUT);    //set the output pin for the speaker
  
  pinMode(yellow_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);
  pinMode(blue_button, INPUT_PULLUP);
  
  pinMode(yellow_button, OUTPUT);
  pinMode(red_button, OUTPUT);
  pinMode(green_button, OUTPUT);
  pinMode(blue_button, OUTPUT);
  
  Serial.begin(9600);   
}

void loop() {
  Begin:
  Serial.println("BEGIN PROGRAM");
  game_start = false;
  tone(speakerPin,262,1000);
  while (game_start == false){
    digitalWrite(led_pins[0], HIGH);
    digitalWrite(led_pins[1], HIGH);
    digitalWrite(led_pins[2], HIGH);
    digitalWrite(led_pins[3], HIGH);
    if ( digitalRead(red_button) == LOW || digitalRead(blue_button) == LOW || digitalRead(green_button) == LOW || digitalRead(yellow_button) == LOW ){
      game_start = true;
      digitalWrite(led_pins[0], LOW);
      digitalWrite(led_pins[1], LOW);
      digitalWrite(led_pins[2], LOW);
      digitalWrite(led_pins[3], LOW);
      delay(1000);
    }
    delay(100);
    
  }
  Serial.println("BEGIN GAME!");
  //begin game sound
  play_song();
  delay(1000);
  //iterate through rounds
  for (int i=0;i<10;i++){
    Serial.print("BEGIN ROUND: ");
    Serial.println(i);
    play_begin();
    delay(1000);
    //generate sequence
    for (int j=0;j<i+1;j++){
      val = rand() % 4;
      Serial.print("LIGHT: ");
      Serial.println(val);
      sequence[j]=val;
      digitalWrite(led_pins[val], HIGH);
      tone(speakerPin, button_frequencies[val], 1000);
      delay(1000);
      digitalWrite(led_pins[val], LOW);
      delay(500);
    }
    digitalWrite(led_pins[0], HIGH);
    digitalWrite(led_pins[1], HIGH);
    digitalWrite(led_pins[2], HIGH);
    digitalWrite(led_pins[3], HIGH);
    delay(250);
    digitalWrite(led_pins[0], LOW);
    digitalWrite(led_pins[1], LOW);
    digitalWrite(led_pins[2], LOW);
    digitalWrite(led_pins[3], LOW);
    
    start_time = millis(); 
    Serial.print("Start time: ");
    Serial.println(start_time);
  
    for (int j=0;j<i+1;j++){
      //Serial.print("Sequence index: ");
      //Serial.println(j);
      //wait for button to be pressed
      check = false;
      while (!check) {
        
        if (digitalRead(red_button) != HIGH || digitalRead(blue_button) != HIGH || digitalRead(green_button) != HIGH || digitalRead(yellow_button) != HIGH){check = true;}
        //check if any wrong buttons are pressed
        if ( 
            (digitalRead(blue_button)==0 && sequence[j]!=0) ||
            (digitalRead(green_button)==0 && sequence[j]!=1) ||
            (digitalRead(red_button)==0 && sequence[j]!=2) ||
            (digitalRead(yellow_button)==0 && sequence[j]!=3) ||
            millis() - start_time > time_limit 
          ){
          play_lose();
          delay(1000);
          Serial.println(millis() - start_time);
          Serial.println("END OF GAME, RESTARTING");
          goto Begin; 
          }
      }
      digitalWrite(led_pins[0], digitalRead(blue_button)==0);
      digitalWrite(led_pins[1], digitalRead(green_button)==0);
      digitalWrite(led_pins[2], digitalRead(red_button)==0);
      digitalWrite(led_pins[3], digitalRead(yellow_button)==0);
      tone(speakerPin,494,100);
      delay(500);
      digitalWrite(led_pins[0], LOW);
      digitalWrite(led_pins[1], LOW);
      digitalWrite(led_pins[2], LOW);
      digitalWrite(led_pins[3], LOW);
    }
    digitalWrite(led_pins[0], HIGH);
    digitalWrite(led_pins[1], HIGH);
    digitalWrite(led_pins[2], HIGH);
    digitalWrite(led_pins[3], HIGH);
    delay(1000);
    digitalWrite(led_pins[0], LOW);
    digitalWrite(led_pins[1], LOW);
    digitalWrite(led_pins[2], LOW);
    digitalWrite(led_pins[3], LOW);
  }
  Serial.println("YOU WIN");
  play_win();
}

void play_begin(){
  for (int i=0; i<3; i++){
    tone(speakerPin, frequencies[begin_sequence[i][0]], begin_sequence[i][1] * 250);
    delay(begin_sequence[i][1]*250+50);
  }
}
void play_lose(){
  for (int i=0; i<3; i++){
    tone(speakerPin,  frequencies[lose_sequence[i][0]], lose_sequence[i][1] * 250);
    delay(lose_sequence[i][1]*250+50);
  }
}
void play_win(){
  for (int i=0; i<7; i++){
    tone(speakerPin, frequencies[win_sequence[i][0]], win_sequence[i][1] * 250);
    delay(win_sequence[i][1]*250+50);
  }
}

void play_song(){
  for (int i=0; i<3; i++){
    tone(speakerPin, frequencies[song_sequence[i][0]], song_sequence[i][1] * 250);
    delay(song_sequence[i][1]*250+50);
  }
}