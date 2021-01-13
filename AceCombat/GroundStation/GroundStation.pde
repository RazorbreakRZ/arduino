
// Global vars
int tinit;
int bgcolor = 96;
PFont f;
Data data;
Hud hud;
//Capture cam;
Video video;

// Initialization
void setup() {
  size(800, 600);
  //fullScreen();
  frameRate(30);
  background(bgcolor);
  f = createFont("Consolas", 16, true);
  data = new Data(DUMMY);
  hud = new Hud();
  video = new Video(this);
  //cam = new Capture(this);
  //cam.start();
  tinit = millis();
}

// Main loop
void draw() {
  background(bgcolor);
  data.refresh();
  //image(cam, 0, 0);
  video.draw();
  hud.draw();
}

/*
void captureEvent(Capture cam) {
  cam.read();
}
*/
