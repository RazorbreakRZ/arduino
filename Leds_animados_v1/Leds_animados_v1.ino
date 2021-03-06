#include <Adafruit_NeoPixel.h>
#include <math.h>

// BOARD PIN configuration
#define PIN_PIXEL       6
#define PIN_START 12
#define PIN_ANIM 8
#define PIN_COLOR 9
#define PIN_INC_INT 10
#define PIN_DEC_INT 11

// PIEZO configuration
#define PIEZO_MIN_FREQ  100       //Buzzer minimum working frequency
#define PIEZO_MAX_FREQ  50000     //Buzzer maximum audible working frequency

// LED STRIP configuration
#define PIXEL_TOTAL           120              //Total number of pixels
#define PIXEL_MIN             0
#define PIXEL_MAX             (PIXEL_TOTAL-1) //Position of the last available pixel
#define PIXEL_MIN_INTENSITY   0
#define PIXEL_MAX_INTENSITY   255
#define PIXEL_INTENSITY       30              //Amount of light to provide to a pixel (from 0 to 255)

// General program configuration
#define TIME_DELAY     1000

// Global objects
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_TOTAL, PIN_PIXEL, NEO_GRB + NEO_KHZ800);

// Global variables
uint32_t BLACK  = strip.Color(PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY);
uint32_t RED    = strip.Color(PIXEL_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY);
uint32_t YELLOW = strip.Color(PIXEL_INTENSITY, PIXEL_INTENSITY, PIXEL_MIN_INTENSITY);
uint32_t GREEN  = strip.Color(PIXEL_MIN_INTENSITY, PIXEL_INTENSITY, PIXEL_MIN_INTENSITY);
uint32_t CYAN   = strip.Color(PIXEL_MIN_INTENSITY, PIXEL_INTENSITY, PIXEL_INTENSITY);
uint32_t BLUE   = strip.Color(PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_INTENSITY);
uint32_t PURPLE = strip.Color(PIXEL_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_INTENSITY);
uint32_t WHITE  = strip.Color(PIXEL_INTENSITY, PIXEL_INTENSITY, PIXEL_INTENSITY);
uint32_t PINK   = strip.Color(PIXEL_INTENSITY, 0, PIXEL_INTENSITY*0.2);

uint32_t colors[] = { RED, YELLOW, GREEN, CYAN, BLUE, PURPLE };
int colorIndex = 0;
int colorTop = 5;
int detection = 0;

////////////////////////////////
// Program pre-initialization //
////////////////////////////////
void setup() {
  randomSeed(analogRead(0));

  strip.begin();
  strip.show();
  //loadingPixelsAnimation(1,GREEN);
  delay(TIME_DELAY);
  resetStrip();

//  pinMode(PIN_START, INPUT_PULLUP);
//  pinMode(PIN_ANIM, INPUT_PULLUP);
//  pinMode(PIN_COLOR, INPUT_PULLUP);
//  pinMode(PIN_INC_INT, INPUT_PULLUP);
//  pinMode(PIN_DEC_INT, INPUT_PULLUP);
}


///////////////
// Main loop //
///////////////
bool start = true;
int animation = 1;
void loop() {
  //checkInputs();
  switch(animation){
    case 0:
      animPingPong(colors[colorIndex],5,1);
      break;
    case 1:
      animPulsating(CYAN,0,PIXEL_INTENSITY,2,90);
      break;
    case 2:
      animWater(colors[colorIndex]);
      break;
    default:
      resetStrip();
      delay(500);
      break;
  }
}

void checkInputs(){
  if(digitalRead(PIN_START) == LOW){
    start = !start;
    delay(50);
  };
  if(start){
      if(digitalRead(PIN_COLOR == LOW)){
        rotateColor(true);
        delay(50);
      };
      if(digitalRead(PIN_ANIM) == LOW){
        resetStrip();
        animation = random(0,3);
        delay(50);
      };
      if(animation == 9){
        animation = 1;
      };
  }else{
    animation = 9;
  };
  delay(50);
}

// Efecto lluvia
void animWater(uint32_t colour){
  int pixel = random(PIXEL_MIN,PIXEL_MAX);
  animEmitPixel(colour,pixel,10,50);
  animEmitPixel(BLACK,pixel,10,75);
}

// Efecto emitter desde un pixel
void animEmitPixel(uint32_t colour, int center, int radius, int s){
  strip.setPixelColor(center, colour);
  for(int i=1; i<radius; i++){
    strip.setPixelColor(center+i, colour);
    strip.setPixelColor(center-i, colour);
    strip.show(); 
    delay(s);
  }
}

void animDegradePixel(uint32_t colour, int pixel, float percent){
  
}

// Efecto pulse
void animPulsating(uint32_t colour, int LOW_INTENSITY, int HIGH_INTENSITY, int DENSITY, int s){
  float R = (float)(colour>>16 & 255)/PIXEL_INTENSITY;
  float G = (float)(colour>>8 & 255)/PIXEL_INTENSITY;
  float B = (float)(colour & 255)/PIXEL_INTENSITY;
  int cR,cG,cB;
  for(int i=LOW_INTENSITY;i<=HIGH_INTENSITY;i++){    
    cR = round(R*i);
    cG = round(G*i);
    cB = round(B*i);
    setRangeOfPixels(strip.Color(cR,cG,cB), PIXEL_MIN, PIXEL_MAX, DENSITY, true);
    delay(s);
  }
  for(int i=HIGH_INTENSITY;i>=LOW_INTENSITY;i--){
    cR = round(R*i);
    cG = round(G*i);
    cB = round(B*i);
    setRangeOfPixels(strip.Color(cR,cG,cB), PIXEL_MIN, PIXEL_MAX, DENSITY, true);
    delay(s);
  }
  
}

// Efecto ping-pong de color COLOR, radio r y velocidad s
void animPingPong(uint32_t COLOR, int r, int s){
  animPing(COLOR,r,s);
  animPong(COLOR,r,s);
}

// Efecto ping
void animPing(uint32_t COLOR, int r, int s){
  int bottom,top;
  for(int i=PIXEL_MIN-2*r+r; i<PIXEL_MAX+2*r-r; i++){
    bottom = i-r;
    top = i+r;
    setRangeOfPixels(BLACK, PIXEL_MIN+r, PIXEL_MAX-r, 1, false);
    setRangeOfPixels(COLOR, bottom, top, 1, true);
    delay(s);
  }
}

// Efecto pong
void animPong(uint32_t COLOR, int r, int s){
  int bottom,top;
  for(int i=PIXEL_MAX+2*r-r; i>=PIXEL_MIN-2*r+r; i--){
    bottom = i-r;
    top = i+r;
    setRangeOfPixels(BLACK, PIXEL_MIN+r, PIXEL_MAX-r, 1, false);
    setRangeOfPixels(COLOR, bottom, top, 1, true);
    delay(s);
  }
}

///////////
// UTILS //
///////////
// Sets the colour of a range of pixels. The refresh boolean force the draw of the pixels.
void setRangeOfPixels(uint32_t colour, int nMin, int nMax, int space, bool refresh){
  //Serial.print("Call setRangeOfPixels(");Serial.print(colour);Serial.print(",");Serial.print(nMin);Serial.print(",");Serial.print(nMax);Serial.println(")");
  space = (space<1 ? 1 : space);
  nMin = (nMin<PIXEL_MIN ? PIXEL_MIN : nMin);
  nMax = (nMax>PIXEL_MAX ? PIXEL_MAX : nMax);
  if(nMax<nMin){
    int aux = nMax;
    nMax=nMin;
    nMin=aux;
  }
  for(int i=nMin; i<=nMax; i+=space){
    strip.setPixelColor(i, colour);
  }
  if(refresh)
    strip.show();
}

// Resets the strip colour to black (power off)
void resetStrip(){
  setRangeOfPixels(BLACK,PIXEL_MIN,PIXEL_MAX,1,true);
}

////////////////
// ANIMATIONS //
////////////////
// A thermal loading bar animation
void loadingPixelsAnimation2(int activationDelay){
  Serial.print("Call loadingPixelsAnimation2(");Serial.print(activationDelay);Serial.println(")");
  for(int i=PIXEL_MIN; i<=PIXEL_MAX; i++){
    strip.setPixelColor(i, calculateColorPercentage(i,0), calculateColorPercentage(i,1), calculateColorPercentage(i,2));
    strip.show();
    delay(activationDelay);
  }
}

// calculates the estimated colour value based on the pixels position (lower=red, higher=green)
int calculateColorPercentage(int pixel, int index){
  //Serial.print("Call calculateColorPercentage(");Serial.print(pixel);Serial.print(",");Serial.print(index);Serial.print(") = ");
  float value = 0; // Y

  float AR = 0.0;   //Min percentage
  float BR = 0.66;   //Top percentage
  float CR = 0.0;   //No puede tomar valor 1.0
  
  float AG = 0.33;   //Min percentage
  float BG = 1.0;   //Top percentage
  float CG = 1.0;   //No puede tomar valor 0.0

  float AB = 0.0;
  float BB = 1.0;
  float CB = 0.5;

  float pixelPercent = 0; // X
  
  if(index==0){//R
    pixelPercent = ((float)pixel+1.0)/((float)PIXEL_TOTAL*BR);
    if(pixelPercent<=1.0){
      value = ( pixelPercent<=CR ? 1.0 : (1.0/(1.0-CR))*(1.0-pixelPercent) );
    }
    //Serial.print(pixelPercent);Serial.print(" ");Serial.println(value);
    //Serial.println(value);
  }else if(index==1){//G
    pixelPercent = ((float)pixel+1.0)/(float)PIXEL_TOTAL;
    if(pixelPercent>=AG){
      value = ( pixelPercent>=CG ? 1.0 : (1.0/CG)*(pixelPercent-AG)*(1.0/(1.0-AG)) );
    }
    //Serial.print(pixelPercent);Serial.print(" ");Serial.println(value);
    //Serial.print(value);Serial.print(",");
  }else if(index==2){//B
    //pixelPercent = ((float)pixel+1.0)/((float)PIXEL_TOTAL*BB);
    //Serial.print(pixelPercent);Serial.print(" ");Serial.println(value);
    //Serial.print(value);Serial.print(",");
  }
  //Serial.println(value);
  return (int)(value*PIXEL_INTENSITY);
}

// Simulates a loading animation of a single color. Useful for test the strip.
void loadingPixelsAnimation(int activationDelay, uint32_t colorValue){
  for(int i=PIXEL_MIN; i<=PIXEL_MAX; i++){
    strip.setPixelColor(i, colorValue);
    strip.show();
    delay(activationDelay);
  }
}

// change the colour of the strip based on the constant list defined on the top
void rotateColor(bool next){
  if(next)
    colorIndex = (colorIndex+1>colorTop ? 0 : colorIndex+1);
  else
    colorIndex = (colorIndex-1<0 ? colorTop : colorIndex-1);
}
