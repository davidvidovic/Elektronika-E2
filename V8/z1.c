#include <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned char dozvola;
unsigned char rec_gen;
int taster;
int duzina;
int korisnik_duzina;
char rec_displej[8];
char rec_korisnik[8];


void setup() {
	lcd.begin(16, 2);
	Serial.begin(9600);
	randomSeed(analogRead(0));
	dozvola = 1;
	generisi_rec();
}

void loop() {
	taster = readButton();
	if(taster == SELECT && dozvola)
	{
		dozvola = 0;
		generisi_rec();
	}
	if(taster == 0) dozvola = 1;

	// Ako je rec jos neobradjena, udji u petlju i cekaj poruku sa serijske komunikacije
	if(rec_gen == 1)
	{
		while(Serial.available() == 0);
		delay(100);
		korisnik_duzina = Serial.available();
		Serial.readBytes(rec_korisnik, korisnik_duzina);
		rec_korisnik[korisnik_duzina] = 0;

		lcd.setCursor(0, 1);
		if(proveri_rec()) lcd.print("ECCE HOMO");
		else lcd.print("BOT");

		// Resetuj fleg da je rec obradjena i da treba da se generise nova pritiskom na SELECT
		rec_gen = 0;
	}
}

void generisi_rec()
{
	// Postavi fleg da je generisana nova rec koja jos nije resena (nije bilo unosa za nju)
	rec_gen = 1;

	duzina = random(5, 9);
	
	for(int i = 0; i < duzina; i++)
	{
		int karakter = random(0, 3);
		switch(karakter)
		{
		  	// Veliko slovo
			case 0: 
		  		rec_displej[i] = random(65, 91);
		  	break;
		  
		  	// Malo slovo
			case 1: 
		  		rec_displej[i] = random(97, 123);
		  	break;
		  
		  	// Broj
			case 2: 
		  		rec_displej[i] = random(48, 58);
		  	break;
		  
		  	default: break;
		}
  }
    
    rec_displej[duzina] = 0;
    lcd.clear();
    lcd.print(rec_displej);
}


int proveri_rec()
{
	if(duzina != korisnik_duzina) return 0;

	for(int i = 0; i < duzina; i++)
	{
	 	if(rec_displej[i] != rec_korisnik[i]) return 0; 
	}

	return 1;
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
