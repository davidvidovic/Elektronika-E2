#include <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

enum stanja {POCETNO, PROVERA, ULAZ, POBEDA, PORAZ};

char baza_reci[20][10] = 
{
	{"konj"},
	{"david"},
	{"kralj"},
	{"tableta"},
	{"mama"},
	// 5
	{"kupus"},
	{"racunar"},
	{"simulator"},
	{"jabuka"},
	{"kristal"},
	// 10
	{"igrica"},
	{"linija"},
	{"casa"},
	{"flasa"},
	// 15
	{"mis"},
	{"olovka"},
	{"kamera"},
	{"bolnica"},
	{"dzemper"}
	// 20
};

byte taster;
int stanje;
int broj_reci;
int duzina_reci;
char rec[10];
int broj_zivota;
char ulaz_slovo;
int broj_pogodaka;
unsigned char flag;
unsigned char dozvola;
char uneta_slova[10];
int broj_unetih_slova;

void setup() 
{
	lcd.begin(16, 2);
	Serial.begin(9600);
	randomSeed(analogRead(1));
	stanje = POCETNO;
	duzina_reci = 0;
	broj_zivota = 10;
	flag = 0;
	broj_pogodaka = 0;
	dozvola = 1;
	broj_unetih_slova = 0;
}

void loop() 
{
	switch(stanje)
	{
		// Generisanje random reci iz baze i njen ispis na ekran
		case POCETNO:
			lcd.clear();
			duzina_reci = 0;
			broj_pogodaka = 0;
			broj_zivota = 10;
			
			broj_reci = random(0, 20);
			
			while(baza_reci[broj_reci][duzina_reci] != 0) 
			{
				rec[duzina_reci] = baza_reci[broj_reci][duzina_reci];
				duzina_reci++;
			}
			rec[duzina_reci] = 0;
			
			for(int i = 0; i < duzina_reci; i++) Serial.print(rec[i]);
			
			// Ispis reci na ekran u vidu crtica
			lcd.setCursor(0, 0);
			for(int i = 0; i < duzina_reci; i++) lcd.print("_");
			
			lcd.setCursor(0, 1);
			lcd.print(broj_zivota);
			
			stanje = ULAZ;
			ulaz_slovo = 97;
			broj_unetih_slova = 0;
		break;
		
		// Primanje ulaza sa serijskog porta ili sa tastera
		case ULAZ:
			/*
			while(Serial.available() == 0);
			delay(100);
			ulaz_slovo = Serial.read();
			stanje = PROVERA;
			*/
			
			taster = readButton();
			
			if(taster == UP && dozvola)
			{
				dozvola = 0;
				ulaz_slovo++;
				if(ulaz_slovo == 123) ulaz_slovo = 97;
			}
			
			if(taster == DOWN && dozvola)
			{
				dozvola = 0;
				ulaz_slovo--;
				if(ulaz_slovo == 96) ulaz_slovo = 122;
				
			}
			
			if(taster == SELECT && dozvola)
			{
				dozvola = 0;
				stanje = PROVERA;
			}
			
			if(taster == 0) dozvola = 1;
			
			lcd.setCursor(15, 1);
			lcd.print(ulaz_slovo);
			
		break;
		
		// Provera da li slovo postoji u reci
		case PROVERA:
			flag = 0;
			for(int i = 0; i < broj_unetih_slova; i++)
			{
				if(uneta_slova[i] == ulaz_slovo)
				{
					flag = 1;
					Serial.print("Slovo ");
					Serial.print(ulaz_slovo);
					Serial.print(" je vec pokusano!");
					Serial.println();
					flag = 1;
					stanje = ULAZ;
					break;
				}
			}
			if(!flag)
			{
				uneta_slova[broj_unetih_slova++] = ulaz_slovo;
				for(int i = 0; i < duzina_reci; i++)
					{
						if(rec[i] == ulaz_slovo)
						{
							flag = 1;
							broj_pogodaka++;
							lcd.setCursor(i, 0);
							lcd.print(ulaz_slovo);
						}
					}
					
					if(broj_pogodaka == duzina_reci) stanje = POBEDA;
					
					if(!flag) 
					{
						broj_zivota--;
						lcd.setCursor(1, 1);
						lcd.print(" ");
						lcd.setCursor(0, 1);
						lcd.print(broj_zivota);
					}
					if(broj_zivota == 0) stanje = PORAZ;
					
					if(stanje == PROVERA) stanje = ULAZ;
			}
			else flag = 0;
		break;
		
		
		case POBEDA:
			lcd.setCursor(4, 1);
			lcd.print("preziveo :)");
			
			taster = readButton();
			if(taster == SELECT && dozvola) 
			{
				stanje = POCETNO;
				dozvola = 0;
			}
			if(taster == 0) dozvola = 1;
		break;
		
		
		case PORAZ:
			lcd.setCursor(4, 1);
			lcd.print("obesen :(");
			
			lcd.setCursor(0, 0);
			for(int i = 0; i < duzina_reci; i++) lcd.print(rec[i]);
			
			taster = readButton();
			if(taster == SELECT && dozvola) 
			{
				stanje = POCETNO;
				dozvola = 0;
			}
			if(taster == 0) dozvola = 1;
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
