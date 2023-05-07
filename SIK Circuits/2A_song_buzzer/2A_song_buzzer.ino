/*
Program 2A Buzzer
*/
int speakerPin = 12; 
int num_notes = 35;
// Index 0 of each subbarry is the note, 0->c3, 1->d3, ... 11->g4, and index 1 is the # of beats
int music_sequence[num_notes][2] = {
  {1,1},{5,2},{5,3},
  {3,1}, {4,1},{5,1},{4,3},
  {3,2},{4,1},{5,1},{4,1},{3,1},
  {2,1},{1,2},{2,1},{0,2},
  {1,1},{3,1},{5,1},{4,1},{3,1},{4,1},
  {3,1},{1,2},{2,1},{0,2},
  {1,1},{3,1},{2,1},{4,1},{5,1},{3,1},
  {1,1},{1,2},{17,3}
};
//frequencies corresponds to g2,a3,b3,c3#,d3,e3,f3,g3,a4,b4,c4,d4,e4,f4,g4
int frequencies[] = {98, 110, 124, 139,147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};
int frequency;
int beats;
int length;

void setup()
{
  pinMode(speakerPin, OUTPUT);    //set the output pin for the speaker
  length = 500;
  Serial.begin(9600);   
}

void loop() {
  Serial.println("Begin song!");
  // put your main code here, to run repeatedly:
  for (int i=0; i<num_notes; i++){
    beats = music_sequence[i][1];
    frequency = frequencies[music_sequence[i][0]];
    Serial.println(frequency);
    tone(speakerPin, frequency, beats * length);
    delay(beats*length+50);
    
  }
}
