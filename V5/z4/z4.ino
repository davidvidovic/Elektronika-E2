char rec[32];
  int duzina;
  unsigned char flag;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Unesite rec: ");
  
  while(Serial.available() == 0);
  delay(100);
  duzina = Serial.available();
  Serial.readBytes(rec, duzina);
  rec[duzina] = 0;

  flag = 1;
  for(int i = 0; i < duzina / 2; i++)
  {
    if(rec[i] != rec[duzina-1 - i]) flag = 0;
  }

  Serial.print(rec);
  flag ? Serial.println(" jeste palindrom.") : Serial.println(" nije palindrom.");
}
