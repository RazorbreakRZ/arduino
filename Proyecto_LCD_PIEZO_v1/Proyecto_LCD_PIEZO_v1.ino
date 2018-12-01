#include <LiquidCrystal.h>

//        PIN_LCD[] = [ Vss, Vcc, V0, RS, RW,  E, D0, D1, D2, D3, D4, D5, D6, D7, LED+, LED-]
const int PIN_LCD[] = {   0,   0,  0,  8,  0,  9,  0,  0,  0,  0,  2,  3,  4,  5,    0,    0}; //Conexiones pines LCD[i]:1-16 en placa[j]:2-13
const int PIN_PIEZO = 13;

const int FREQ_MIN = 100;    //Min frecuencia del Piezo en placa Uno: 31Hz
const int FREQ_MAX = 50000; //Max frecuencia del Piezo en placa Uno: 65535Hz

LiquidCrystal lcd(PIN_LCD[3],PIN_LCD[5],PIN_LCD[10],PIN_LCD[11],PIN_LCD[12],PIN_LCD[13]);

bool loaded = false;
bool explode = true;

int speedTime = 1000;

int hours = 0;
int minutes = 0;
int seconds = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);  
  makeNoise(2000,5,10,1);
  lcdPrintTemporalText("Starting...",0,0,0,true);
  fillScreen(".",11,0,50);
  makeNoise(2000,5,10,1);
  lcd.clear();
}

void loop() {
  if(!loaded){
    lcdLoadingScreen(20);
    makeNoise(3000,5,10,1);
    lcdPrintTemporalText("D.VA ONLINE!",0,0,2000,true);
    makeNoise(4000,5,100,2);
  }  
  lcd.setCursor(8,1);
  lcdPrintTime(8,1);
  lcd.setCursor(0,0);
  lcd.print(speedTime);
  delay(speedTime);
  
  increaseTimeBySeconds();
  makeNoise(50,10,20,1);

  speedTime = speedTime/1.01;
  //Serial.println(speedTime);
  
  /*decreaseTimeBySeconds();  
  if(seconds>0 or minutes>0 or hours>0){
    //makeNoise(4500,10,120,1);
    if(hours==0){
      if(minutes==0){
        if(seconds<5){
          speedTime = 100;
        }else if(seconds<15){
          speedTime = 250;
        }else if(seconds<30){
          speedTime = 500;
        }
      }
    }
  }else{
    if(explode){
      makeNoise(4000,100,120,20);
      explode = false;
    }
  }
  */
  
  lcd.clear();
}

void increaseTimeBySeconds(){
  if(seconds<59){
    seconds++;
  }else{
    seconds=0;
    if(minutes<59){
      minutes++;
    }else{
      minutes=0;
      hours++;
    }
  }
}

void decreaseTimeBySeconds(){
  if(seconds>0){
    seconds--;
  }else if(minutes>0){
    seconds=59;
    minutes--;
  }else if(hours>0){
    minutes=59;
    hours--;
  }
}

void lcdPrintTime(int col, int row){
  lcd.setCursor(col,row);
  if(hours<10){
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if(minutes<10){
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if(seconds<10){
    lcd.print("0");
  }
  lcd.print(seconds);
}

void lcdPrintTemporalText(String text, int col, int row, int duration, bool cleanScreen){
  lcd.setCursor(col,row);
  if(cleanScreen)
    lcd.clear();
  lcd.print(text);
  if(duration>0){
    delay(duration);
    lcd.clear();
  }
  delay(5);
}

void makeNoise(int frequency, int duration, int wait, int times){
  for(int i=0;i<times;i++){
    tone(PIN_PIEZO,frequency,duration);
    delay(wait);
  }
}

void lcdLoadingScreen(int milis){
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("Loading...");
  for(int i=0;i<=100;i++){
    lcd.setCursor(12,1);
    if(i<10){
      lcd.print("..");
    }else if(i<100){
      lcd.print(".");
    }
    lcd.print(i);
    lcd.print("%");
    delay(milis);
  }
  loaded = true;
}

void cleanScreen(int milis){  
  for(int row=0; row<2; row++){
    for(int col=0; col<16; col++){
      lcd.setCursor(col,row);
      lcd.print(" ");
      delay(milis);
    }
  }
}

void fillScreen(String s, int startCol, int startRow, int milis){  
  for(int row=startRow; row<2; row++){
    for(int col=startCol; col<16; col++){
      lcd.setCursor(col,row);
      lcd.print(s);
      delay(milis);
    }
    startCol = 0;
  }
}

