#define T1_MAX  25
#define T2_MAX  25
#define V1_MAX  20
#define V2_MAX  16
#define V3_MAX  16

int n;
int sum;
unsigned char stanje;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  stanje = 0;
  sum = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(stanje)
  {
    case 0:
      Serial.println("Unesite broj poena za T1: ");
      while(Serial.available() == 0);
      delay(100);
      n = Serial.parseInt();
      if(n < 0 || n > T1_MAX)
      {
        Serial.println("Nekorektan broj poena za T1!");
        stanje = 0;
        sum = 0;
      }
      else
      {
        sum += n;
        stanje++;
      }
    break;


    case 1:
      Serial.println("Unesite broj poena za T2: ");
      while(Serial.available() == 0);
      delay(100);
      n = Serial.parseInt();
      if(n < 0 || n > T2_MAX)
      {
        Serial.println("Nekorektan broj poena za T2!");
        stanje = 0;
        sum = 0;
      }
      else
      {
        sum += n;
        stanje++;
      }
    break;


    case 2:
      Serial.println("Unesite broj poena za V1: ");
      while(Serial.available() == 0);
      delay(100);
      n = Serial.parseInt();
      if(n < 0 || n > V1_MAX)
      {
        Serial.println("Nekorektan broj poena za V1!");
        stanje = 0;
        sum = 0;
      }
      else
      {
        sum += n;
        stanje++;
      }
    break;


    case 3:
      Serial.println("Unesite broj poena za V2: ");
      while(Serial.available() == 0);
      delay(100);
      n = Serial.parseInt();
      if(n < 0 || n > V2_MAX)
      {
        Serial.println("Nekorektan broj poena za V2!");
        stanje = 0;
        sum = 0;
      }
      else
      {
        sum += n;
        stanje++;
      }
    break;


    case 4:
      Serial.println("Unesite broj poena za V3: ");
      while(Serial.available() == 0);
      delay(100);
      n = Serial.parseInt();
      if(n < 0 || n > V3_MAX)
      {
        Serial.println("Nekorektan broj poena za V3!");
        stanje = 0;
        sum = 0;
      }
      else
      {
        sum += n;
        stanje++;
      }
    break;

    case 5:
      odredi_ocenu(sum);
      stanje = 0;
    break;
  }
}

void odredi_ocenu(int n)
{
  if(n < 51) 
  {
    Serial.print("Uneli Ste ");
    Serial.print(n);
    Serial.print(" poena.");
    Serial.println("Niste polozili.");
  }
  else if(n < 61) 
  {
    Serial.print("Uneli Ste ");
    Serial.print(n);
    Serial.print(" poena.");
    Serial.println("Dobili Ste ocenu 6.");
  }
  else if(n < 71) 
  {
    Serial.print("Uneli Ste ");
    Serial.print(n);
    Serial.print(" poena.");
    Serial.println("Dobili Ste ocenu 7.");
  }
  else if(n < 81) 
  {
    Serial.print("Uneli Ste ");
    Serial.print(n);
    Serial.print(" poena.");
    Serial.println("Dobili Ste ocenu 8.");
  }
  else if(n < 91) 
  {
    Serial.print("Uneli Ste ");
    Serial.print(n);
    Serial.print(" poena.");
    Serial.println("Dobili Ste ocenu 9.");
  }
  else
  {
    Serial.print("Uneli Ste ");
    Serial.print(n);
    Serial.print(" poena.");
    Serial.println("Dobili Ste ocenu 10.");
  }
}
