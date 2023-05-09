#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  

float temperature;

extern "C" char* __brkval;
extern "C" char* __malloc_;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  lcd.begin(16, 2);
  lcd.clear(); 
  Serial.begin(9600); 
}

void loop() {
  lcd.clear();
  temperature = ( (analogRead(A0) * 0.004882813) - 0.5) * 100;
  Serial.println(temperature);
  lcd.setCursor(0,0);
  lcd.print("|18 |22 |26 |30 ");
  for (int i=18;i<min(34,round(temperature)+1);i++){
    lcd.setCursor(i-18,1);
    lcd.write(255);
  }
  round(2.4);
  //lcd.print(temperature);
  print_memory_usage();
  delay(1000);
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