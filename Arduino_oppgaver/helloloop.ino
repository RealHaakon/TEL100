void setup() {
  Serial.begin(9600);
  
  printHelloNR(12);
}

void loop() {
}

void printHelloNR(int len)
{
  Serial.println("Start Hello");
  int i;
  
  // draw the line
  for (i = 1; i <= len; i++) {
    Serial.print(i);
    Serial.println(" Hello");
    
  }
  Serial.print("Hello loop is done");
}