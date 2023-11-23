#include <LiquidCrystal.h>

#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

#define MAX_LEN	10

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int pozicija_kursora;
char karakter;
int taster;
unsigned char dozvola;
int duzina_reklame;

void setup() {
	lcd.begin(16, 2);

	pozicija_kursora = 0;
	karakter = 32;
	dozvola = 1;
	duzina_reklame = 1;
}

void loop() {
	taster = readButton();
	if(taster == UP && dozvola)
	{
		dozvola = 0;
		karakter++;
		if(karakter == 33) karakter = 65;
		if(karakter == 91) karakter = 97;
		if(karakter == 123) karakter = 48;
		if(karakter == 58) karakter = 65;
	}

	if(taster == DOWN && dozvola)
	{
		dozvola = 0;
		karakter--;
		if(karakter == 31) karakter = 57;
		if(karakter == 47) karakter = 122;
		if(karakter == 96) karakter = 90;
		if(karakter == 64) karakter = 32;
	}

	if(taster == RIGHT && dozvola)
	{
		dozvola = 0;
		if(pozicija_kursora < MAX_LEN) 
		{  
			pozicija_kursora++;
			duzina_reklame++;
			lcd.setCursor(pozicija_kursora, 0);
			karakter = 32;
		}
	}

	if(taster == LEFT && dozvola)
	{
		dozvola = 0;
		if(pozicija_kursora > 0) pozicija_kursora--;
		lcd.setCursor(pozicija_kursora, 0);
		karakter = 32;
	}

	if(taster == SELECT && dozvola)
	{
		lcd.noCursor();
		dozvola = 0;
		for(int i = 0; i < duzina_reklame; i++)
		{
			lcd.scrollDisplayLeft();
			delay(300);  
		}
		
		// Reset sve
		pozicija_kursora = 0;
		karakter = 32;
		dozvola = 1;
		duzina_reklame = 1;
		lcd.clear();
		lcd.cursor();
	}
	
	if(taster == 0) dozvola = 1;

	lcd.setCursor(pozicija_kursora,0);
	lcd.cursor();
	lcd.print(karakter);
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
