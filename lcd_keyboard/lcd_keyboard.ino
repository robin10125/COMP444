/*
This program allows the user to select characters with a keyboard, and print them to a lcd screen
TODO: Add memory management control code to prevent text from becoming so large that it potentially goes over memory limit
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#include <string.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

//buttons on circuit.  The integer value indicates the digital pin
int yellow_button = 2;
int green_button = 3;
int red_button = 4;


String text;  //text to be displayed
char helper_symbol;  //helper value that stores potential character selection

//the following arrays store the symbols to be used in the vocabulary of the program
char letter_array[] = "abcdefghijklmnopqrstuvwxyx";
char symbol_array[] = " '.,-!\"?()[]{}:;@$&/\\%#+=*|^_<>";
char number_array[] = "0123456789";
char* arrays[] = {letter_array, symbol_array, number_array};

int case_iterator;  //case_iterator keeps track of which set of symbols is to be used: alphabetical characters, numbers, or misc symbols
int symbols_indexor[3];  //this keeps track of the symbol being selected for each set of characters
int indexes[] = {26,31,10}; //this stores the size of each set of characters, which is used in modulo operations to loop the incrementation after reaching the size of the vocabulary

int loop_count;

void setup() {

  //set pin modes for buttons to be used as inputs
  pinMode(yellow_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);

  helper_symbol = 'a';
  text = "";
  case_iterator=0;
  for (int i=0;i<3;i++){symbols_indexor[i]=0;}
  
  lcd.begin(16, 2);
  lcd.clear(); 
  loop_count = 0;              
}

void loop() {

  //delete character if both green and red are pressed
  if (digitalRead(green_button) == LOW && digitalRead(red_button) == LOW && text.length() > 0){
    text = text.substring(0,text.length()-1);
    delay(500);
    }
  
  //increment case_iterator if yellow button is pressed
  if (digitalRead(yellow_button) == LOW) {
    case_iterator += 1;
    case_iterator = (case_iterator % 4);
    symbols_indexor[2]=0; //reset indexing value for misc symbols for convenience, since the array is sorted by approx. frequency of use
    delay(500);  //delay to prevent multiple incrementations from a single button press

    //case iterator values of 0 and 1 both index the letter array, which is stored at index 0 of arrays, 
    //so the case_incrementor values of 0 and 1 are transformed to 0 when indexing.  
    //likewise, values of 2,3 are transformed to 1,2, to match the arrays indexing ({letters,nums,symbols}), which has only 3 indexes
    //this allows for the same iterator value to be used for both upper and lower case alphabetical values
    helper_symbol = arrays[max(case_iterator-1,0)][symbols_indexor[max(case_iterator-1,0)]];
    if (case_iterator == 1){helper_symbol = toupper(helper_symbol);}
    }

  //increment symbol iterator when red button is pressed; this iterates through the symbols
  else if (digitalRead(red_button) == LOW) {
    
    //like above, case_iterator values of 0,1 are transformed to 0, and 2,3 to 1,2.  This is to make case_iterator values of both 0,1 map to the same letter_array subarray.  
    //The arrays array has 3 subarrays, so the the values must be within range [0,2].  Ie, 0,1->0 (letters), 2->1 (nums), 4->3 (misc symbols)
    symbols_indexor[max(case_iterator-1,0)] = (symbols_indexor[max(case_iterator-1,0)] + 1) % indexes[max(case_iterator-1,0)];
    helper_symbol = arrays[max(case_iterator-1,0)][symbols_indexor[max(case_iterator-1,0)]];
    if (case_iterator == 1){helper_symbol = toupper(helper_symbol);}
    delay(500);
  }

  //Add selected symbol to display text when green button is pressed
  else if (digitalRead(green_button) == LOW) {
    text += helper_symbol;

    //reset nums and misc symbols indexes to 0 for convenience
    symbols_indexor[1] = 0;
    symbols_indexor[2] = 0;
    delay(500);
    }
  
  //print text and symbol selection to the lcd screen
  lcd.setCursor(0, 0);
  lcd.print(helper_symbol);
  
  lcd.setCursor(0, 1); 
  //if text doesn't fill screen, add blinking char to indicate index of screen being written to
  if(text.length() <= 16){
    lcd.print(text);
    lcd.setCursor(text.length(),1) ;
    if (loop_count==0){
      lcd.print(" ");
      delay(200);
      }
    else{lcd.print(helper_symbol);}
    }
  //if text is greater than screen size, display only the last 16 characters of the text
  else{lcd.print(text.substring(text.length()-16,16));}
  delay(50);
  loop_count = (loop_count + 1) % 10; //keep loop_count repeating through 0-10

}
