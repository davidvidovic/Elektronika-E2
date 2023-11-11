float a, b, c;
float dis;
float x1, x2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Unesite brojeve a b c: ");
  while(Serial.available() == 0);
  delay(100);
  a = Serial.parseFloat();
  b = Serial.parseFloat();
  c = Serial.parseFloat();

  
  dis = b*b - 4*a*c;
  if(dis < 0)
  {
    x1 = ((-1)*b) / (2*a);
    x2 = (sqrt((-1) * dis)) / (2*a);
    Serial.print("x1 = ");
    Serial.print(x1);
    Serial.print(" + i * ");
    Serial.print(x2);
    Serial.print(", x1 = ");
    Serial.print(x1);
    Serial.print(" - i * ");
    Serial.println(x2);
  }
  else
  {
    x1 = ((-1)*b + sqrt(dis)) / (2*a);
    x2 = ((-1)*b - sqrt(dis)) / (2*a);
    Serial.print("x1 = ");
    Serial.print(x1);
    Serial.print(", x2 = ");
    Serial.println(x2);
  }
  
}
