
// Dummy data
int direction = 0;
int time = 0;
int speed = 0;
int energy = 0;

// Global vars
int bgcolor = 0;
PFont f;
Hud hud;

// Initialization
void setup() {
  size(720, 480);
  background(bgcolor);
  f = createFont("Consolas", 16, true);
  hud = new Hud();
}

// Main loop
void draw() {
  background(bgcolor);
  refreshData();
  hud.draw();
}

void refreshData() {
  time = (time + 1) % 5999;
  direction = (direction + 1) % 360;
  speed = (speed + 1) % 9999;
  energy = (energy + 1) % 100;
}

class Hud {
  Map map;
  Timer timer;
  Speedometer speedometer;
  Altimeter altimeter;
  Energy energy;
  
  Hud(){
    map = new Map();
    timer = new Timer();
    speedometer = new Speedometer();
    altimeter = new Altimeter();
    energy = new Energy();
  }
  
  void drawLimits() {
    noFill();
    stroke(0, 255, 0);
    // Upper line
    line(width*0.05 + map.diameter, height*0.05, width, height*0.05);
    line(0, height*0.05 + map.diameter*0.5, width*0.025, height*0.05 + map.diameter*0.5);
    // Lower line    
    line(width*0.75, height*0.75, width, height*0.75);
    line(0, height*0.95, width*0.75, height*0.95);
  }
  
  void draw(){
    drawLimits();
    map.draw();
    speedometer.draw();
    altimeter.draw();
    energy.draw();
    timer.draw();
  }
}

class Map {
  int mode;
  float centerX, centerY, diameter;
  float pointAX, pointAY, pointBX, pointBY;
  float pointCX, pointCY, pointDX, pointDY;
  float textAX, textAY, textASize;
  float textBX, textBY, textBSize;
  
  Map(){
    mode = CENTER;
    diameter = width*0.2;
    centerX = width*0.05 + diameter*0.5;
    centerY = height*0.05 + diameter*0.5;
    pointAX = centerX; 
    pointAY = centerY - diameter*0.5;
    pointBX = centerX; 
    pointBY = centerY + diameter*0.5;
    pointCX = centerX - diameter*0.5; 
    pointCY = centerY;
    pointDX = centerX + diameter*0.5; 
    pointDY = centerY;
    textASize = height*0.05;
    textAX = centerX - diameter*0.48;
    textAY = centerY - diameter*0.52;
    textBSize = height*0.05;
    textBX = centerX - diameter*0.48;
    textBY = centerY - diameter*0.35;
  }
  
  String formatDirection(int direction) {
    int angle = direction % 360;
    return (angle<100?"0":"")+(angle<10?"0":"")+angle+"º";
  }
  
  void draw(){
    // Corner
    rectMode(CORNERS);
    fill(0, 255, 0);
    stroke(0, 255, 0);
    rect(width*0.05, height*0.05, centerX, centerY);
    // Fill
    ellipseMode(mode);
    fill(bgcolor);
    noStroke();
    ellipse(centerX, centerY, diameter, diameter);
    // Cross
    stroke(0, 255, 0, 128);
    line(pointAX, pointAY, pointBX, pointBY);
    line(pointCX, pointCY, pointDX, pointDY);
    // Boder
    ellipseMode(mode);
    noFill();
    stroke(0, 255, 0);
    ellipse(centerX, centerY, diameter, diameter);
    // Text
    fill(0, 255, 0);
    textFont(f, textASize);
    textAlign(LEFT);
    text(formatDirection(direction), textAX, textAY);
    fill(255);
    textFont(f, textBSize);
    textAlign(LEFT);
    text((cos(radians(direction))>=0?"N":"S"), textBX, textBY);
    // Triangle
    pushMatrix();
    fill(255);
    noStroke();
    translate(centerX, centerY);
    rotate(radians(direction));
    triangle(0, -10, 10, 10, -10, 10);
    stroke(0, 255, 0, 192);
    line(0, 0, 0, -diameter*0.5);
    popMatrix();
  }
  
}

class Speedometer {
  int mode;
  float pointAX, pointAY, rectWidth, rectHeight;
  float centerX, centerY, radiusA, radiusB;
  float textX, textY, textSize;
  
  Speedometer() {
    mode = CORNER;
    rectWidth = width*0.2;
    rectHeight = rectWidth*0.25;
    pointAX = width*0.05;
    pointAY = height*0.5;
    radiusA = rectHeight*1.25;
    radiusB = rectHeight*0.4;
    centerX = pointAX;
    centerY = pointAY + rectHeight*0.5;
    textSize = rectHeight;
    textX = pointAX + rectWidth*0.9;
    textY = pointAY + rectHeight*0.85;
  }
  
  void draw() {
    // Fill
    rectMode(mode);
    fill(0, 255, 0);
    noStroke();
    rect(pointAX, pointAY, rectHeight, rectHeight);
    // Border
    rectMode(mode);
    noFill();
    stroke(0, 255, 0);
    rect(pointAX, pointAY, rectWidth, rectHeight);
    // Circle
    ellipseMode(CENTER);
    fill(bgcolor);
    stroke(0, 255, 0);
    ellipse(centerX, centerY, radiusA, radiusA);
    // Ball
    ellipseMode(CENTER);
    fill(0, 255, 0);
    stroke(0, 255, 0);
    ellipse(centerX, centerY, radiusB, radiusB);
    // Text
    fill(0, 255, 0);
    textFont(f, textSize);
    textAlign(RIGHT);
    text(speed, textX, textY);
  }
  
}

class Altimeter {

  Altimeter() {
    
  }
  
  void draw() {
    
  }
  
}

class Timer {
  int mode;
  float pointAX, pointAY, rectWidth, rectHeight;
  float centerX, centerY, ballSize;
  float textX, textY, textSize;
  
  Timer(){
    mode = CORNER;
    rectWidth = width*0.2;
    rectHeight = rectWidth*0.25;
    pointAX = width*0.05;
    pointAY = height*0.9 - rectHeight;
    ballSize = rectHeight*0.4;
    centerX = pointAX + rectHeight*0.5;
    centerY = pointAY + rectHeight*0.5;
    textSize = rectHeight;
    textX = pointAX + rectWidth*0.98;
    textY = pointAY + rectHeight*0.9;
  }  
  
  String formatTimer(int time) {
    int minutes = (time / 60) % 99;
    int seconds = time % 60;
    return (minutes<10?"0":"")+minutes+":"+(seconds<10?"0":"")+seconds;
  }
  
  void draw() {
    // Fill
    rectMode(mode);
    fill(0, 255, 0, 128);
    stroke(0, 255, 0);
    rect(pointAX, pointAY, rectHeight, rectHeight);
    // Ball
    ellipseMode(CENTER);
    fill(0, 255, 0);
    noStroke();
    ellipse(centerX, centerY, ballSize, ballSize);
    // Border
    rectMode(mode);
    noFill();
    stroke(0, 255, 0);
    rect(pointAX, pointAY, rectWidth, rectHeight);
    // Text    
    fill(0, 255, 0);
    textFont(f, textSize);
    textAlign(RIGHT);
    text(formatTimer(time), textX, textY);
  }
  
}

class Energy {

  Energy() {
    
  }
  
  void draw() {
    
  }
  
}

class Armament {}

class Info {}
