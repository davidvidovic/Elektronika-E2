#include <LiquidCrystal.h>

#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned char dozvola;
int kolona, vrsta;
byte taster;
  
void setup() {
 // initialize display
 lcd.begin(16, 2);
 dozvola = 1;
 kolona = 0;
 vrsta = 0;
}

void loop() {
 taster = readButton();
 if(taster == UP && dozvola)
 {
   dozvola = 0;
   if(vrsta > 0) vrsta--;
 }
  
 if(taster == DOWN && dozvola)
 {
   dozvola = 0;
   if(vrsta < 1) vrsta++;
 }
  
 if(taster == RIGHT && dozvola)
 {
   dozvola = 0;
   if(kolona < 14) kolona++; // smajl zauzima 2 karaktera
 }
  
 if(taster == LEFT && dozvola)
 {
   dozvola = 0;
   if(kolona > 0) kolona--;
 }
  
 if(taster == 0) dozvola = 1;
  
 lcd.clear();
 lcd.setCursor(kolona, vrsta);
 lcd.print(":)");
 delay(100);
}

byte readButton()
{
 int tmp = analogRead(0); //read value of Analog input 0
 //depending on voltage, we can find out which switch was pressed
 if (tmp > 635 && tmp < 645) //SELECT
 	return SELECT;
 if (tmp > 405 && tmp < 415) //LEFT
 	return LEFT;
 if (tmp > 95 && tmp < 105) //UP
 	return UP;
 if (tmp > 252 && tmp < 262) //DOWN
 	return DOWN;
 if (tmp < 5) //RIGHT
 	return RIGHT;
 return 0; //NONE
}
