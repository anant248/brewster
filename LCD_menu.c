/*
Key Codes (in left-to-right order):

None   - 0
Select - 1
Left   - 2
Up     - 3
Down   - 4
Right  - 5

*/

#include <LiquidCrystal.h>
#include <LCD_Key.h>
#define NOKEY   -1
#define NONE     0
#define SELECT   1
#define LEFT     2
#define UP       3
#define DOWN     4
#define RIGHT    5

//lcd.setcursor(<row>,<column>)
//lcd.print(<16char/bit>)

//Pin assignments for LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
//---------------------------------------------

LCD_Key keypad;

int button = 0;
int button_wait = 500;
String keyString = "";
                 
void setup() //Runs once
{ 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Brewster");
  lcd.setCursor(0, 1);
  lcd.print("AN IGEN 330 FAIL");
  delay(3000);
  int i = 0;
  int j = 0;
  int check_count = 0;
  
  /*
  keypad.setRate(x);
  Sets the sample rate at once every x milliseconds.
  Default: 10ms
  */
  keypad.setRate(10);
  lcd.clear();
  button = keypad.getKey();
  //Setup NO KEY 
  while (button == NONE || button == NOKEY){
    lcd.setCursor(i,0);
    lcd.print("NO KEY");
    lcd.setCursor(2,1);
    lcd.print("Choose a key");
    if (j==1){
      if (i == 0){
        j = 0;
      }
      i--;
    }    
    if (j==0){
      if (i == 9){
        j = 1;
      }
      i++;
    }
    
    //Check repeatedly to reduce wait time on key recognition  50(loops)*10ms delays = 0.5s delay (+/- 20us due to code time delays)
    for (check_count = 0; check_count <= 50; check_count++){
      button = keypad.getKey();
      if (button == SELECT || button == LEFT || button == RIGHT || button == UP || button == DOWN)
        break;
      delay(10);
    }

    lcd.clear();
  }
  lcd.clear();

}

void loop()  //Loop
{ 
  button = keypad.getKey();
  if (button == SELECT){
    lcd.setCursor(0,0);
    lcd.print("BREWSTER");
    lcd.setCursor(0,1);
    lcd.print("EST. 2022");
  }
  
  //Protocol for Temperature Menu
  if (button == RIGHT){
    lcd.clear();
    button = keypad.getKey();
    //In here do any calculations necessary for the display screen. 
    while (button != SELECT && button != LEFT && button != UP && button != DOWN){
      lcd.setCursor(0,0);
      lcd.print("Temperature");
      //In here do anything that needs to be displayed on this menu screen
      button = keypad.getKey();
    }  
    if (button == SELECT || button == LEFT || button == UP || button == DOWN)
      lcd.clear();
  }

  //Protocol for pH Menu
  if (button == LEFT){
    lcd.clear();
    button = keypad.getKey();
    //In here do any calculations necessary for the display screen. 
    while (button != SELECT && button != RIGHT && button != UP && button != DOWN){
      lcd.setCursor(0,0);
      lcd.print("pH Menu");
      //In here do anything that needs to be displayed on this menu screen 
      button = keypad.getKey();
    }  
    if (button == SELECT || button == RIGHT || button == UP || button == DOWN)
      lcd.clear();
  }

  //Protocol for Progress Menu
  if (button == UP){
    lcd.clear();
    button = keypad.getKey();
    //In here do any calculations necessary for the display screen.
    while (button != SELECT && button != LEFT && button != RIGHT && button != DOWN){
      lcd.setCursor(0,0);
      lcd.print("Progress Menu");
      //In here do anything that needs to be displayed on this menu screen
      button = keypad.getKey();
    }  
    if (button == SELECT || button == LEFT || button == RIGHT || button == DOWN)
      lcd.clear();
  }

  //Protocol for Time Remaining Menu
  if (button == DOWN){
    lcd.clear();
    button = keypad.getKey();
    //In here do any calculations necessary for the display screen.
    while (button != SELECT && button != LEFT && button != RIGHT && button != UP){
      lcd.setCursor(0,0);
      lcd.print("Time Remaining");
      button = keypad.getKey();
      //In here do anything that needs to be displayed on this menu screen
    }  
    if (button == SELECT || button == LEFT || button == RIGHT || button == UP)
      lcd.clear();
  } 
}