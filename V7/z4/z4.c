#include <LiquidCrystal.h>

#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned char dozvola;
byte jacina;
int taster;
  
void setup() {
 // initialize display
 lcd.begin(16, 2);
 pinMode(10, OUTPUT);
 
 dozvola = 1;
 jacina = 0;
}

void loop() {
 taster = readButton();
 if(taster == UP && dozvola)
 {
   dozvola = 0;
   if(jacina > 255 - 25) jacina = 255;
   else jacina += 25;
 }
  
 if(taster == DOWN && dozvola)
 {
   dozvola = 0;
   if(jacina < 25) jacina = 0;
   else jacina -= 25;
 }
  
 if(taster == 0) dozvola = 1;
  
 // Set background light
 analogWrite(10, jacina);
 
 // Write value on display
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(jacina);
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
