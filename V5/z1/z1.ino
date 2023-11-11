int n0, n1, n2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  n0 = 0;
  n1 = 1;
  n2 = 0;
}

void loop() {
  if(n0 > 32767 - n2)
  {
    n0 = 0;
    n1 = 1;
  }
  n2 = n0 + n1;
  Serial.println(n2);
  
  n0 = n1;
  n1 = n2;
  
  delay(500);
}
