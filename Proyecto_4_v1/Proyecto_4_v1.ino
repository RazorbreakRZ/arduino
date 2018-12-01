const int R = 11;
const int G = 9;
const int B = 10;
const int BUZZER = 13;
const int MIN = 0;
const int MAX = 255;
const int timeDelay = 1;

const bool debug = false;

bool changeColour = false;

int rVal = MIN;
bool rInc = true;

int gVal = MAX;
bool gInc = true;

int bVal = MIN;
bool bInc = true;

void setup() {
  Serial.begin(9600);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  
  analogWrite(R,rVal);
  analogWrite(G,gVal);
  analogWrite(B,bVal);
  Serial.println("\n--- Program Ready ---\n");
}

void loop() {
  if(gVal==MIN && rVal==MAX){
    rVal = MIN;
    gVal = MAX;
  }
  
  for(int i=0; i<255; i++){
    if(!changeColour){
      rVal++;
    }else{
      gVal--;
    }
    if(debug){
    printColour(rVal,gVal,bVal);
  }else{
    setLedColour(rVal,gVal,bVal);
  }
    delay(timeDelay);
  }
  
  if(changeColour){
    changeColour = false;
  }else{
    changeColour = true;
  }

  if(debug){
    Serial.println("\n--- End of loop() ---\n");
  }

  tone(BUZZER,1000,10);
}

void printColour(int red, int green, int blue){
  Serial.print("RGB: (");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.println(") ");
}

void setLedColour(int red,int green, int blue){
  analogWrite(R,red);
  analogWrite(G,green);
  analogWrite(B,blue);
}

