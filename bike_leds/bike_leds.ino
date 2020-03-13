#include <Adafruit_NeoPixel.h>

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
#define DOWN 4

// STRIP CONFIG
#define PIN_STRIP 0
#define LEDS_TOTAL 1
#define LEDS_COLOR 2
#define PIN_ACTIVATION 3

// STRIP CONFIG OBJECT
int stripCfg[][4] = { 
  //{ PIN_STRIP, LEDS_TOTAL, LEDS_COLOR, PIN_ACTIVATION }
  { 8, 10, WHITE, 1 }, // FRONT
  { 9, 25, RED, 2 }, // BRAKE
  { 9, 25, ORANGE, 3 }, // LEFT
  { 9, 25, ORANGE, 4 }, // RIGHT
  { 7, 30, GREEN, 5 } // DOWN
};

// STRIP OBJECT
Adafruit_NeoPixel strip[] = {
  Adafruit_NeoPixel(stripCfg[FRONT][LEDS_TOTAL], stripCfg[FRONT][PIN_STRIP], NEO_GRB + NEO_KHZ800), // FRONT
  Adafruit_NeoPixel(stripCfg[BRAKE][LEDS_TOTAL], stripCfg[BRAKE][PIN_STRIP], NEO_GRB + NEO_KHZ800), // BRAKE
  Adafruit_NeoPixel(stripCfg[LEFT][LEDS_TOTAL], stripCfg[LEFT][PIN_STRIP], NEO_GRB + NEO_KHZ800), // LEFT
  Adafruit_NeoPixel(stripCfg[RIGHT][LEDS_TOTAL], stripCfg[RIGHT][PIN_STRIP], NEO_GRB + NEO_KHZ800), // RIGHT
  Adafruit_NeoPixel(stripCfg[DOWN][LEDS_TOTAL], stripCfg[DOWN][PIN_STRIP], NEO_GRB + NEO_KHZ800) // DOWN
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

////////////////
// ANIMATIONS //
////////////////
void animLoadingBar(int stripIndex, int colorIndex, int animDuration){
  int deltaTime = animDuration / stripCfg[stripIndex][LEDS_TOTAL];
  for(int led=0; led<stripCfg[stripIndex][LEDS_TOTAL]; led++) {
    strip[stripIndex].setPixelColor(led, color[colorIndex]);
    strip[stripIndex].show();
    delay(deltaTime);
  }
}

void animPulsating(int stripIndex, int colorIndex) {
  for(int led=0; led<stripCfg[stripIndex][LEDS_TOTAL]; led++) {
    strip[stripIndex].setPixelColor(led, color[colorIndex]);
    strip[stripIndex].show();
    delay(1000);
  }
}

////////////////////////////////
// Program pre-initialization //
////////////////////////////////
void setup() {
  strip[DOWN].begin();
  animLoadingBar(DOWN, GREEN, 1500);
}

///////////////
// Main loop //
///////////////
bool debug = true;
void loop() {
  delay(1000);
}

