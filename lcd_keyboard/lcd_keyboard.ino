/*
  SparkFun Inventor’s Kit
  Circuit 4A-HelloWorld

  The LCD will display the words "Hello World" and show how many seconds have passed since
  the RedBoard was last reset.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#include <string.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

string text;
char helper;
char lower_letter_array[] = 'abcdefghijklmnopqrstuvwxyx';
char symbol_array[] = " '.,-!\"?()[]{}:;@$&/\\%#+=*|^_<>";
char number_array[] = "0123456789"
int* arrays = {lower_letter_array, upper_letter_array, symbol_array, number_array};
const int yellow_button = 2;
const int green_button = 3;
const int red_button = 4;

int l_interator;
int s_iterator;
int n_iterator;
int case_interator;
int symbols[4] = {0,0,0};
int indexes[4] = {26,31,10};

void setup() {
  helper = 'a';
  text = '';
  char* display;
  l_interator=0;
  s_iterator=0;
  n_iterator=0;
  case_interator=0;
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
}

void loop() {

  if (digitalRead(yellow_button) == LOW) {
    case_iterator += 1;
    case iterator = case_iterator%4;
    symbols[1]=0;
    symbols[2]=0;
    }
  else if (digitalRead(red_button) == LOW) {
    symbols[case_iterator] = (symbols[case_iterator] + 1) % indexes[case_iterator];
    helper = arrays[case_iterator][symbols[case_iterator]]
    if {case_iterator == 1}{helper = helper - a + A}
  }

  else if (digitalRead(green_button) == LOW) {
    text += helper;
    symbols[1] = 0;
    symbols[2] = 0;
    }
  lcd.setCursor(0, 0);
  lcd.print(helper);
  
  lcd.setCursor(0, 1); 
  if( text.length() <= 16){lcd.print(text); }
  else{lcd.print(text.substr(text.length()-16,16));}
       
}
