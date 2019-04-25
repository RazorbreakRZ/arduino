

// Global vars
int bgcolor = 0;
PFont f;
Data data;
Hud hud;

// Initialization
void setup() {
  size(720, 480);
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
