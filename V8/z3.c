#include <LiquidCrystal.h>

#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

#define MAX_BROJ_KOCKICA	3

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int stanje;
int taster;
unsigned char dozvola;
int broj_kockica_prvi_igrac;
int broj_kockica_drugi_igrac;
int broj_na_ekranu;
int rez_prvi_igrac[MAX_BROJ_KOCKICA];
int rez_drugi_igrac[MAX_BROJ_KOCKICA];
int pozicija_kockice;
int temp;
int gubi_prvi;
int gubi_drugi;

void setup() {
	lcd.begin(16, 2);
	Serial.begin(9600);
	stanje = 0;
	dozvola = 1;
	broj_kockica_prvi_igrac = 2;
	broj_na_ekranu = 0;
	pozicija_kockice = 0;
	gubi_prvi = 0;
	gubi_drugi = 0;
}

void loop() {
	switch(stanje)
	{
	// Pocetno stanje - prvi igrac bira broj kockica
	case 0: 
		taster = readButton();
		if(taster == UP && dozvola)
		{
			dozvola = 0; 
			if(broj_kockica_prvi_igrac < MAX_BROJ_KOCKICA) broj_kockica_prvi_igrac++;
		}

		if(taster == DOWN && dozvola)
		{
			dozvola = 0; 
			if(broj_kockica_prvi_igrac > 2) broj_kockica_prvi_igrac--;
		}

		if(taster == SELECT && dozvola)
		{
			dozvola = 0; 
			stanje = 1;
			broj_na_ekranu = 0;
			lcd.setCursor(2, 0);
			pozicija_kockice = 0;
			broj_kockica_drugi_igrac = broj_kockica_prvi_igrac - 1;
		}

		if(taster == 0) dozvola = 1;

		lcd.setCursor(0, 0);
		lcd.print(broj_kockica_prvi_igrac);
	break;


	// Drugo stanje - izvlacenje kockica prvog igraca
	case 1:
		taster = readButton();
		if(pozicija_kockice < broj_kockica_prvi_igrac)
		{
			lcd.setCursor(pozicija_kockice * 2 + 2, 0);
			lcd.print(broj_na_ekranu);
			delay(100);

			if(taster == SELECT && dozvola)
			{
			dozvola = 0; 
			rez_prvi_igrac[pozicija_kockice] = broj_na_ekranu;
			pozicija_kockice++;
			}

			broj_na_ekranu++;
			if(broj_na_ekranu == 7) broj_na_ekranu = 1;

			if(taster == 0) dozvola = 1;   
		}
		else 
		{
			stanje = 2;
		}
	break;


	// Ispis broj kockica drugog igraca
	case 2:
		lcd.setCursor(0, 1);
		lcd.print(broj_kockica_drugi_igrac);
		broj_na_ekranu = 0;
		pozicija_kockice = 0;
		stanje = 3;
	break;

	// Cetvrto stanje - ivlacenje kockica drugog igraca
	case 3:
		taster = readButton();
		if(pozicija_kockice < broj_kockica_drugi_igrac)
		{
			lcd.setCursor(pozicija_kockice * 2 + 2, 1);
			lcd.print(broj_na_ekranu);
			delay(100);

			if(taster == SELECT && dozvola)
			{
				dozvola = 0; 
				rez_drugi_igrac[pozicija_kockice] = broj_na_ekranu;
				pozicija_kockice++;
			}

			broj_na_ekranu++;
			if(broj_na_ekranu == 7) broj_na_ekranu = 1;

			if(taster == 0) dozvola = 1;   
		}
		else 
		{
			stanje = 4;
			gubi_prvi = 0;
			gubi_drugi = 0;
		}
	break;


	// Sortiraj rezultate
	case 4:
	// Prvi igrac
		for(int i = 0; i < broj_kockica_prvi_igrac; i++)
		{
			for(int j = i+1; j < broj_kockica_prvi_igrac - i + 1; j++)
			{
				if(rez_prvi_igrac[i] < rez_prvi_igrac[j]) 
				{
					temp = rez_prvi_igrac[i];
					rez_prvi_igrac[i] = rez_prvi_igrac[j];
					rez_prvi_igrac[j] = temp;
				}
			}
		}

		// Drugi igrac
		for(int i = 0; i < broj_kockica_drugi_igrac; i++)
		{
			for(int j = i+1; j < broj_kockica_drugi_igrac - i + 1; j++)
			{
				if(rez_drugi_igrac[i] < rez_drugi_igrac[j]) 
				{
					temp = rez_drugi_igrac[i];
					rez_drugi_igrac[i] = rez_drugi_igrac[j];
					rez_drugi_igrac[j] = temp;
				}
			}
		}

		lcd.clear();
		for(int i = 0; i < broj_kockica_prvi_igrac; i++)
		{
			lcd.setCursor(i*2, 0);
			lcd.print(rez_prvi_igrac[i]);
		}

		for(int i = 0; i < broj_kockica_drugi_igrac; i++)
		{
			lcd.setCursor(i*2, 1);
			lcd.print(rez_drugi_igrac[i]);
		}

		stanje = 5;
	break;

	// Poredjenje rezultata
	case 5:
		for(int i = 0; i < broj_kockica_drugi_igrac; i++)
		{
			if(rez_prvi_igrac[i] > rez_drugi_igrac[i]) gubi_drugi++;
			else gubi_prvi++;
		}

		lcd.setCursor(broj_kockica_prvi_igrac * 2, 0);
		lcd.print(gubi_prvi);
		lcd.setCursor(broj_kockica_prvi_igrac * 2, 1);
		lcd.print(gubi_drugi);

		stanje = 6;
	break;

	case 6:
		taster = readButton();
		if(taster == SELECT && dozvola)
		{
			stanje = 0;
			dozvola = 0;
          	lcd.clear();
		}
		if(taster == 0) dozvola = 1;
	break;

	default:
		lcd.clear();
		lcd.print("ERROR");
		delay(1000);
	break;
	}
  
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