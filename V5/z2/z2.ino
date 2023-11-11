int n;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
	do
	{
      Serial.println("Unesite broj poena: ");
      while(Serial.available() == 0);
      delay(100);
      n = Serial.parseInt();
	} while(n < 0 || n > 100);
    
	odredi_ocenu(n);
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
