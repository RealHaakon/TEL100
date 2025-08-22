#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
//Definerer lysdioder
int lR = 5;
int lY1 = 6;
int lY2 = 10;
int lG1 = 3;
int lG2 = 9;

//Definerer knapper og buzzer
int but1 = 7;
int but2 = 12;
int but3 = 13;
int buz = 2;

// Definerer LCD-skjerm
LiquidCrystal_I2C lcd(0x27,16,2);
uint8_t arrow[8] = { B00000, B00000, B00010, B11111, B00010, B00000, B00000, B00000 }; //pil-symbol

//Definerer andre variabler
int wt = 15; //Work-time
int sbt = 5*60; //Short-break-time
int lbt = 15*60; //Long-break-time
int nsb = 3; //Number of short breaks
int nlb = 2; //Number of long breaks

int pom[5] = {wt,sbt,lbt,nsb,nlb}; //Samler i array
String pomM[5] = {"   Tid arbeid:  ", "Tid kort pause: ", "Tid lang pause: ", "  Antall kort:  ", "  Antall lang:  "}; //Tekst til display



void setup() {
  //Setter opp lysdioder
  pinMode(lR,OUTPUT);
  pinMode(lY1,OUTPUT);
  pinMode(lY2,OUTPUT);
  pinMode(lG1,OUTPUT);
  pinMode(lG2,OUTPUT);

  //Setter opp knapper og buzzer
  pinMode(but1,INPUT);
  pinMode(but2,INPUT);
  pinMode(but3,INPUT);
  pinMode(buz,OUTPUT);

  //Setter opp LCD-Skjerm
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0,arrow);
}

void loop() {
  Menu();
}

void Clock(int time){
  int time2 = time;
  for(int i=0; i<=time; i++){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Tid igjen:");
    lcd.setCursor(7,1);
    lcd.print(time-i);

    if(time2 <= time*4/5){
      digitalWrite(lR,LOW);
    }
    else{
      digitalWrite(lR,HIGH);
    }
    if(time2 <= time*3/5){
      digitalWrite(lY1,LOW);
    }
    else{
      digitalWrite(lY1,HIGH);
    }
    if(time2 <= time*2/5){
      digitalWrite(lY2,LOW);
    }
    else{
      digitalWrite(lY2,HIGH);
    }
    if(time2 <= time/5){
      digitalWrite(lG1,LOW);
    }
    else{
      digitalWrite(lG1,HIGH);
    }
    if(time2 == 0){
      digitalWrite(lG2, LOW);
    }
    else{
      digitalWrite(lG2,HIGH);
    }
    time2 -= 1;
    
    delay(1000);
  }
  for(int i=0; i <= 50; i++){
    digitalWrite(buz,HIGH);
    delay(50);
    digitalWrite(buz,LOW);
    delay(50);
  }
}

void Pomodoro(int wt, int sbt, int lbt,int nsb,int nlb){
  for(int i=0; i < nlb; i++){
    for(int i=0; i< nsb; i++){
      Clock(wt);
      Clock(sbt);
    }
    if(i == nlb-1){
      Clock(wt);
    }
    else{
      Clock(wt);
      Clock(lbt);
    }
  }
}


void Menu(){
  lcd.setCursor(3,0);
  lcd.print("Velkommen");
  delay(3000);
  State1();
}

void ClockM(){
  lcd.clear();
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);
    lcd.setCursor(0,0);
    lcd.print(pomM[0]);
    lcd.setCursor(7,1);
    lcd.print(wt);
    if(but1Val == 1){
      Clock(wt);
      lcd.clear();
    }
    else if(but2Val == 1){
      delay(150);
      wt += 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(pomM[0]);
      lcd.setCursor(7,1);
      lcd.print(wt);

    }
    else if(but3Val == 1){
      delay(150);
      wt -= 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(pomM[0]);
      lcd.setCursor(7,1);
      lcd.print(wt);

    }
  } 
}

void PomodoroM(){
  lcd.clear();
  for(int i = 0; i<5; i++){
    lcd.setCursor(0,0);
    lcd.print(pomM[i]);
    lcd.setCursor(7,1);S
    lcd.print(pom[i]);
    while(true){
      int but1Val = digitalRead(but1);
      int but2Val = digitalRead(but2);
      int but3Val = digitalRead(but3);
      
      if(but1Val == 1){
        delay(150);
        lcd.clear();
        break;
      }
      else if(but2Val == 1){
        delay(150);
        pom[i] += 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pomM[i]);
        lcd.setCursor(7,1);
        lcd.print(pom[i]);

      }
      else if(but3Val == 1){
        delay(150);
        pom[i] -= 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pom[i]);
        lcd.setCursor(7,1);
        lcd.print(pom[i]);
      }
    }
  }
  Pomodoro(pom[0],pom[1],pom[2],pom[3],pom[4]);
}

void PresetsM(){


}

void State1(){
  lcd.clear();
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);
    
    lcd.setCursor(1, 0);
    lcd.write(0);
    lcd.print("Vanlig timer");
    lcd.setCursor(4,1);
    lcd.print("Pomodoro");


    if(but1Val == 1){
      delay(150);
      ClockM();
    }
    else if(but2Val == 1){
      delay(150);
      State2();
    }
    else if(but3Val ==1){
      delay(150);
      State3();
    }
  }
}

void State2(){
  lcd.clear();
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);
    
    lcd.setCursor(3, 0);
    lcd.write(0);
    lcd.print("Pomodoro");
    lcd.setCursor(4,1);
    lcd.print("Presets");


    if(but1Val == 1){
      delay(150);
      PomodoroM();
    }
    else if(but2Val == 1){
      delay(150);
      State3();
    }
    else if(but3Val == 1){
      delay(150);
      State1();
    }
  } 
}

void State3(){
  lcd.clear();
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);
    
    lcd.setCursor(3, 0);
    lcd.write(0);
    lcd.print("Presets");
    lcd.setCursor(1,1);
    lcd.print("Vanlig timer");


    if(but1Val == 1){
      delay(150);
      PresetsM();
    }
    else if(but2Val == 1){
      delay(150);
      State1();
    }
    else if(but3Val == 1){
      delay(150);
      State2();
    }
  }
}









