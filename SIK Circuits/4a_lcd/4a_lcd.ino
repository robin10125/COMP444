#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#include <string.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  

char lcd_input[32];

extern "C" char* __brkval;
extern "C" char* __malloc_;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear(); 
  Serial.begin(9600); 
}

void loop() {
  
  Serial.println("BEGIN PROGRAM");
  Serial.println("Enter text");
  for (int i=0;i<32;i++){
    lcd_input[i]=' ';
  }

  get_input(lcd_input);
 
  for (int i=0;i<32;i++){
    lcd.setCursor(i%16, int(i>=16));
    lcd.write(lcd_input[i]);
  }

  print_memory_usage();
}
void get_input(char *lcd_input){
  String input;
  bool check = false;
  while (check == false){
    if (Serial.available()) { // check if there is incoming data
        input = Serial.readString(); 
        check = true;
        Serial.println(input);
    }
  }
  input.replace("\n", "");
  
  for (int i=0;i<min(input.length(),32);i++){
    lcd_input[i]=input[i];
  }

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
