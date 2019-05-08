#include <Adafruit_NeoPixel.h>
#include <math.h>

// General program configuration
#define TIME_DELAY            1000

// BUTTONS
#define PIN_BUTTON 3

// LED INTENSITY
#define PIXEL_MIN_INTENSITY   0
#define PIXEL_MAX_INTENSITY   255
#define PIXEL_INTENSITY       30

// COLOR
#define BLACK 0
#define RED 1 
#define ORANGE 2 
#define YELLOW 3
#define GREEN 4
#define CYAN 5
#define BLUE 6
#define PURPLE 7
#define WHITE 8
#define PINK 9

// STRIP
#define FRONT 0
#define BRAKE 1
#define LEFT 2
#define RIGHT 3

// STRIP CONFIG
#define PIN_STRIP 0
#define LEDS_TOTAL 1
#define LEDS_COLOR 2

// STRIP CONFIG OBJECT
int stripCfg[][3] = { 
  //{ PIN_STRIP, LEDS_TOTAL, LEDS_COLOR }
  { 5, 20, WHITE }, // FRONT
  { 6, 25, RED }, // BRAKE
  { 7, 14, ORANGE }, // LEFT
  { 8, 14, ORANGE } // RIGHT
};

// STRIP OBJECT
Adafruit_NeoPixel strip[] = {
  Adafruit_NeoPixel(stripCfg[FRONT][LEDS_TOTAL], stripCfg[FRONT][PIN_STRIP], NEO_GRB + NEO_KHZ800), // FRONT
  Adafruit_NeoPixel(stripCfg[BRAKE][LEDS_TOTAL], stripCfg[BRAKE][PIN_STRIP], NEO_GRB + NEO_KHZ800), // BRAKE
  Adafruit_NeoPixel(stripCfg[LEFT][LEDS_TOTAL], stripCfg[LEFT][PIN_STRIP], NEO_GRB + NEO_KHZ800), // LEFT
  Adafruit_NeoPixel(stripCfg[RIGHT][LEDS_TOTAL], stripCfg[RIGHT][PIN_STRIP], NEO_GRB + NEO_KHZ800) // RIGHT
};
#define MAX_STRIPS (sizeof(strip)/sizeof(strip[0]))

uint32_t color[] = {
  strip[0].Color(PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY), // BLACK
  strip[0].Color(PIXEL_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY),     // RED
  strip[0].Color(PIXEL_INTENSITY, PIXEL_INTENSITY*0.25, PIXEL_MIN_INTENSITY),    // ORANGE
  strip[0].Color(PIXEL_INTENSITY, PIXEL_INTENSITY, PIXEL_MIN_INTENSITY),         // YELLOW
  strip[0].Color(PIXEL_MIN_INTENSITY, PIXEL_INTENSITY, PIXEL_MIN_INTENSITY),     // GREEN
  strip[0].Color(PIXEL_MIN_INTENSITY, PIXEL_INTENSITY, PIXEL_INTENSITY),         // CYAN
  strip[0].Color(PIXEL_MIN_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_INTENSITY),     // BLUE
  strip[0].Color(PIXEL_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_INTENSITY),         // PURPLE
  strip[0].Color(PIXEL_INTENSITY, PIXEL_INTENSITY, PIXEL_INTENSITY),             // WHITE
  strip[0].Color(PIXEL_INTENSITY, PIXEL_MIN_INTENSITY, PIXEL_INTENSITY*0.2)      // PINK
};


////////////////////////////////
// Program pre-initialization //
////////////////////////////////
void setup() {
  randomSeed(analogRead(0));
  for (int i=0; i<MAX_STRIPS; i++) {
    strip[i].begin();
    setStripColor(i, color[GREEN], true);
  }
  delay(TIME_DELAY);
}

///////////////
// Main loop //
///////////////
bool debug = true;
void loop() {
  if(debug || digitalRead(PIN_BUTTON)==HIGH){
    for(int i=0; i<MAX_STRIPS; i++) {
      powerOn(i, true);
    }
    delay(10000);
    for(int i=0; i<MAX_STRIPS; i++) {
      powerOff(i, true);
    }
    delay(5000);
  }
}

///////////
// UTILS //
///////////
void powerOn(unsigned int index, bool refresh){
  setStripColor(index, color[stripCfg[index][LEDS_COLOR]], refresh);
}

void powerOff(unsigned int index, bool refresh){
  setStripColor(index, color[BLACK], refresh);
}

void setStripColor(unsigned int index, uint32_t color, bool refresh) {
  for(int i=0; i<stripCfg[index][LEDS_TOTAL]; i++){
    strip[index].setPixelColor(i, color);
  }
  if(refresh)
    strip[index].show();
}

////////////////
// ANIMATIONS //
////////////////
// TODO: Create strip animations here
