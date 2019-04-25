
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
    text(formatDirection(data.direction), textAX, textAY);
    fill(255);
    textFont(f, textBSize);
    textAlign(LEFT);
    text((cos(radians(data.direction))>=0?"N":"S"), textBX, textBY);
    // Triangle
    pushMatrix();
    fill(255);
    noStroke();
    translate(centerX, centerY);
    rotate(radians(data.direction));
    triangle(0, -10, 10, 10, -10, 10);
    stroke(0, 255, 0, 192);
    line(0, 0, 0, -diameter*0.5);
    popMatrix();
  }
  
}
