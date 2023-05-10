#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  

char lcd_input[32];

int button = 7;

extern "C" char* __brkval;
extern "C" char* __malloc_;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear(); 
  Serial.begin(9600); 
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  
  Serial.println("BEGIN PROGRAM");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Loading");
  //create map
  int game_map_lower[100];
  int game_map_upper[100];
  int up;
  bool jump = true;
  bool win_check = false;
  int count;
  unsigned long time;
  bool button_mem = false;

  game_map_lower[0]=0;
  game_map_lower[1]=0;
  game_map_lower[2]=0;
  game_map_lower[3]=0;
  
  //init upper level as all blocks
  for (int i=0;i<100;i++){
    game_map_upper[i] = 1;
  }
  //set up bottom level
  for (int i=3;i<100;i++){
    up = 0;
    if (count > 5){
      up = int(random(2));
      if (up == 1){
        //set uppper level to be clear for 2 spaces on each side of lower level block
        for (int j=-2;j<3;j++){
          game_map_upper[i-j]=0;
        }
        count = 0;
      }
    }
    game_map_lower[i]=up;
    count ++;
    delay(50);
    if (i%20 == 0){
      lcd.setCursor(6 + i/20, 0);
      lcd.print(".");
    }
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("BEGIN");
  delay(1000);
  lcd.clear();
  
  //iterate through map
  for (int i=0;i<84;i++){

    time = millis();
    while (millis()-time<1000){
      if (digitalRead(button)==0){
        if (button_mem == false){
          jump = !jump;
          Serial.print("Jump ");
          Serial.println(int(jump));
        }

        button_mem = true;
      }
      else if (digitalRead(button)==1){button_mem = false;}
      
    }
    
    //render subsection of map to lcd
    for (int j=0;j<16;j++){
      
      lcd.setCursor(j, 1);
      if (game_map_lower[i+j] == 0){lcd.write(" ");}
      else {lcd.write(255);}
      
      lcd.setCursor(j, 0);
      if (game_map_upper[i+j] == 0){lcd.write(" ");}
      else {lcd.write(255);}
    }
    //render player
    lcd.setCursor(4, int(jump));
    lcd.print("*");
  
    //check if player hits block
    if ((game_map_lower[i+4] == 1 && jump == 1) || (game_map_upper[i+4]==1 && jump == 0)){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game over!");
      delay(5000);
      break;
    }
    
    //check win
    if (i==80){win_check = true;}
  }
  if (win_check == true){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You Win!");
    delay(5000);
  }
  delay(1000);
  print_memory_usage();
}

void print_memory_usage() {
  int free_memory;
  if((int)__brkval == 0)
    free_memory = ((int)&free_memory) - ((int)__malloc_heap_start);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);
  Serial.print("Free memory: ");
  Serial.println(free_memory);
}