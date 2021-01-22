

// Constants
static final int SENSOR = 0;
static final int DUMMY = 1;

// Global vars
int tinit;
int bgcolor = 0;
PFont f;
Telemetry telemetry;
Hud hud;
Video video;

// Initialization
void setup() {
  size(800, 600);
  //fullScreen();
  frameRate(30);
  background(bgcolor);
  f = createFont("Consolas", 16, true);
  telemetry = new Telemetry(this, DUMMY);
  hud = new Hud();
  video = new Video(this, DUMMY);
  tinit = millis();
  
}

// Main loop
void draw() {
  background(bgcolor);
  telemetry.refresh();
  video.draw();
  hud.draw();
}
