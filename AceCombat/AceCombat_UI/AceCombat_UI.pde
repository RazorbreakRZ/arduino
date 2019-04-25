
// Global vars
int bgcolor = 96;
PFont f;
Data data;
Hud hud;

// Initialization
void setup() {
  size(800, 600);
  frameRate(1);
  background(bgcolor);
  f = createFont("Consolas", 16, true);
  hud = new Hud();
  data = new Data(DUMMY);
}

// Main loop
void draw() {
  background(bgcolor);
  data.refresh();
  hud.draw();
}
