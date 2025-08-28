#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

//Definerer lysdioder
int lR = 7;
int lY1 = 6;
int lY2 = 3;
int lG1 = 4;
int lG2 = 8;

//Definerer knapper og buzzer
int but1 = 5;
int but2 =  12;
int but3 = 10;
int buz = 9;

// Definerer LCD-skjerm
LiquidCrystal_I2C lcd(0x27,16,2);
uint8_t arrow[8] = { B00000, B00000, B00010, B11111, B00010, B00000, B00000, B00000 }; //pil-symbol

//Definerer andre variabler
//Work-time
int minwt = 1; 
int sekwt = 5;
//Short-break-time
int minsbt = 0; 
int seksbt = 30;
//Long-break-time
int minlbt = 2; 
int seklbt = 15;

int nsb = 3; //Number of short breaks
int nlb = 2; //Number of long breaks

int pomt[3][2] = {{minwt, sekwt},{minsbt, seksbt},{minlbt,seklbt}}; //Samler tidsvariabler i array
String pomtM[3][2] = {{"   Min arbeid:  ", "   Sek arbeid:  "},{" Min kort pause:"," Sek kort pause:"},{" Min lang pause:"," Sek lang pause:"}}; //Tekst til display
int pomn[2] = {nsb,nlb}; //Samler nummervariabler i array
String pomnM[2] = {"Antall kort:","  Antall lang:  "}; //Tekst til display
String ms[2] = {"Min: ", "Sek:"}; //Tekst til display


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
  lcd.clear();
  Menu();

}

void Clock(int time){
  int time2 = time;
  int tim[2] = {time / 60 ,time % 60};
  for(int i=0; i<=time; i++){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Tid igjen:");
    lcd.setCursor(0,1);
    lcd.print("Min: ");
    lcd.print(tim[0]);
    lcd.print(" Sek: ");
    lcd.print(tim[1]);

    if(time2 <= time*4/5){
      digitalWrite(lG2,LOW);
    }
    else{
      digitalWrite(lG2,HIGH);
    }
    if(time2 <= time*3/5){
      digitalWrite(lG1,LOW);
    }
    else{
      digitalWrite(lG1,HIGH);
    }
    if(time2 <= time*2/5){
      digitalWrite(lY2,LOW);
    }
    else{
      digitalWrite(lY2,HIGH);
    }
    if(time2 <= time/5){
      digitalWrite(lY1,LOW);
    }
    else{
      digitalWrite(lY1,HIGH);
    }
    if(time2 == 0){
      digitalWrite(lR, LOW);
    }
    else{
      digitalWrite(lR,HIGH);
    }
    time2 -= 1;
    tim[1] -= 1;
    if(tim[1] < 0){
      tim[0] -= 1;
      tim[1] += 60;
    } 
    int pc = 0;
    while(true){
      int but1Val =digitalRead(but1);
      if(but1Val == 1){
        delay(150);
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("Pause");
        lcd.setCursor(0,1);
        lcd.print("Enter for forts.");
        while(true){
          int but1Val = digitalRead(but1);
          if(but1Val == 1){
            delay(150);
            break;
          }
        }
      }
      delay(1);
      pc += 1;
      if(pc >= 945){
        break;
      }
    }

  }
  for(int i=0; i <= 1500; i++){
    digitalWrite(buz,HIGH);
    delay(1);
    digitalWrite(buz,LOW);
    delay(1);
  }
}

void Pomodoro(int wt, int sbt, int lbt,int nsb,int nlb){
  for(int i=0; i < nlb; i++){
    for(int i=0; i< nsb; i++){
      Clock(wt);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Trykk Enter for");
      lcd.setCursor(0,1);
      lcd.print("  aa fortsette  ");
      while(true){
        int but1Val = digitalRead(but1);
        if(but1Val == 1){
          delay(150);
          break;
        }
      }
      Clock(sbt);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Trykk Enter for");
      lcd.setCursor(0,1);
      lcd.print("  aa fortsette  ");
      while(true){
        int but1Val = digitalRead(but1);
        if(but1Val == 1){
          delay(150);
          break;
        }
      }
    }
    if(i == nlb-1){
      Clock(wt);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Trykk Enter for");
      lcd.setCursor(0,1);
      lcd.print("  aa fortsette  ");
      while(true){
        int but1Val = digitalRead(but1);
        if(but1Val == 1){
          delay(150);
          break;
        }
      }
    }
    else{
      Clock(wt);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Trykk Enter for");
      lcd.setCursor(0,1);
      lcd.print("  aa fortsette  ");
      while(true){
        int but1Val = digitalRead(but1);
        if(but1Val == 1){
          delay(150);
          break;
        }
      }
      Clock(lbt);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Trykk Enter for");
      lcd.setCursor(0,1);
      lcd.print("  aa fortsette  ");
      while(true){
        int but1Val = digitalRead(but1);
        if(but1Val == 1){
          delay(150);
          break;
        }
      }
    }
  }
}

void ClockM(){

  for(int i = 0; i<2; i++){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(pomtM[0][i]);
    lcd.setCursor(7,1);
    lcd.print(pomt[0][i]);

    while(true){
      int but1Val = digitalRead(but1);
      int but2Val = digitalRead(but2);
      int but3Val = digitalRead(but3);


      if(but1Val == 1){
        delay(150);
        break;
      }
      else if(but2Val == 1){
        delay(150);
        if(pomt[0][i] >= 59){
          pomt[0][i] = 0;
        }
        else{
          pomt[0][i] += 1;
        } 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pomtM[0][i]);
        lcd.setCursor(7,1);
        lcd.print(pomt[0][i]);

      }
      else if(but3Val == 1){
        delay(150);
        if(pomt[0][i] <= 0){
          pomt[0][i] = 59;
        }
        else{
          pomt[0][i] -= 1;
        } 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pomtM[0][i]);
        lcd.setCursor(7,1);
        lcd.print(pomt[0][i]);

      }
    }
  }
  int time = 60*pomt[0][0] + pomt[0][1];
  Clock(time);
} 

void PomodoroM(){
  for(int i = 0; i<3; i++){
    for(int n = 0; n<2; n++){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(pomtM[i][n]);
      lcd.setCursor(7,1);
      lcd.print(pomt[i][n]);
      while(true){
        int but1Val = digitalRead(but1);
        int but2Val = digitalRead(but2);
        int but3Val = digitalRead(but3);
        
        if(but1Val == 1){
          delay(150);
          break;
        }
        else if(but2Val == 1){
          delay(150);
          if(pomt[i][n] >= 59){
            pomt[i][n] = 0;
          }
          else{
            pomt[i][n] += 1;
          }
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(pomtM[i][n]);
          lcd.setCursor(7,1);
          lcd.print(pomt[i][n]);

        }
        else if(but3Val == 1){
          delay(150);
          if(pomt[i][n] <= 0){
            pomt[i][n] = 59;
          }
          else{
            pomt[i][n] -= 1;
          } 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(pomtM[i][n]);
          lcd.setCursor(7,1);
          lcd.print(pomt[i][n]);
        }
      }
    }
  }

  for(int i = 0; i<2; i++){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(pomnM[i]);
    lcd.setCursor(7,1);
    lcd.print(pomn[i]);
    while(true){
      int but1Val = digitalRead(but1);
      int but2Val = digitalRead(but2);
      int but3Val = digitalRead(but3);
      
      if(but1Val == 1){
        delay(150);
        break;
      }
      else if(but2Val == 1){
        delay(150);
        pomn[i] += 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pomnM[i]);
        lcd.setCursor(7,1);
        lcd.print(pomn[i]);

      }
      else if(but3Val == 1){
        delay(150);
        pomn[i] -= 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pomnM[i]);
        lcd.setCursor(7,1);
        lcd.print(pomn[i]);
      }
    }
  }

  int wt = pomt[0][0]*60 + pomt[0][1];
  int sbt = pomt[1][0]*60 + pomt[1][1];
  int lbt = pomt[2][0]*60 + pomt[2][1];
  int nsb = pomn[0];
  int nlb = pomn[1];
  Pomodoro(wt,sbt,lbt,nsb,nlb);
}

void Menu(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Velkommen");
  delay(3000);
  State1();
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
      Pr1();
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

void Pr1(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.write(0);
  lcd.print("25 - 5");
  lcd.setCursor(3,1);
  lcd.print("45 - 15");
  
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);

    if(but1Val == 1){
      delay(150);
      Pomodoro(25*60, 5*60, 15*60, 4, 1);
    }
    else if(but2Val == 1){
      delay(150);
      Pr2();
    }
    else if(but3Val == 1){
      delay(150);
      Pr3();
    }
  }
}

void Pr2(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.write(0);
  lcd.print("45 - 15");
  lcd.setCursor(3,1);
  lcd.print("40 - 10");
  
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);

    if(but1Val ==  1){
      delay(150);
      Pomodoro(45*60, 15*60, 30*60, 4, 1);
    }
    else if(but2Val == 1){
      delay(150);
      Pr3();
    }
    else if(but3Val == 1){
      delay(150);
      Pr1();
    }
  }
}

void Pr3(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.write(0);
  lcd.print("40 - 10");
  lcd.setCursor(3,1);
  lcd.print("25 - 5");
  
  while(true){
    int but1Val = digitalRead(but1);
    int but2Val = digitalRead(but2);
    int but3Val = digitalRead(but3);

    if(but1Val ==  1){
      delay(150);
      Pomodoro(40*60, 10*60, 20*60, 4, 1);
    }
    else if(but2Val == 1){
      delay(150);
      Pr1();
    }
    else if(but3Val == 1){
      delay(150);
      Pr2();
    }
  }
}

