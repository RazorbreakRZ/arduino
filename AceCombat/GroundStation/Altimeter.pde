
class Altimeter {
  int mode;
  float pointAX, pointAY, rectWidth, rectHeight;
  float pointBX, pointBY, rectVWidth, rectVHeight;
  PVector[] hline, altIndicator;
  float textX, textY, textSize;
  int nhline, nlhline;
  float displacement, size;

  Altimeter() {
    println("Loading Altimeter module...");
    mode = CORNER;
    rectWidth = width*0.18;
    rectHeight = height*0.08;
    pointAX = width*0.72;
    pointAY = height*0.45;
    rectVWidth = rectHeight;
    rectVHeight = rectWidth;
    pointBX = pointAX + rectWidth;
    pointBY = pointAY;
    textSize = rectHeight;
    textX = pointAX + rectWidth*0.95;
    textY = pointAY + rectHeight*0.85;
    nhline = 12;
    nlhline = 5;
    hline = new PVector[2];
    hline[0] = new PVector(pointBX, pointBY + rectVHeight*0.05);
    hline[1] = new PVector(pointBX + rectVWidth, hline[0].y);
    size = 1.5;
    altIndicator = new PVector[4];
    altIndicator[0] = new PVector(pointBX*0.95, hline[0].y + 10*rectVHeight/nhline);
    altIndicator[1] = new PVector(pointBX*0.99, altIndicator[0].y);
    altIndicator[2] = new PVector(width*0.97, altIndicator[0].y);
    altIndicator[3] = new PVector(width, altIndicator[0].y);
    println("Altimeter ready!");
  }
  
  void draw() {
    // Lines
    stroke(0, 255, 0);
    displacement = 0;
    for(int i=0; i<nhline; i++){
      displacement = i*rectVHeight/nhline;
      size = rectVWidth*((i-telemetry.altitude)%nlhline==0 ? 0.5 : 0.75);
      line(hline[0].x + size, hline[0].y + displacement, hline[1].x, hline[1].y + displacement);
    }
    line(altIndicator[0].x, altIndicator[0].y, altIndicator[1].x, altIndicator[1].y);
    line(altIndicator[2].x, altIndicator[2].y, altIndicator[3].x, altIndicator[3].y);
    // Border vertical
    rectMode(mode);
    noFill();
    stroke(0, 255, 0);
    rect(pointBX, pointBY, rectVWidth, rectVHeight);
    // Border horizontal
    rectMode(mode);
    noFill();
    stroke(0, 255, 0);
    rect(pointAX, pointAY, rectWidth, rectHeight);
    // Text
    fill(0, 255, 0);
    textFont(f, textSize);
    textAlign(RIGHT);
    text(telemetry.altitude, textX, textY);
  }
  
}
