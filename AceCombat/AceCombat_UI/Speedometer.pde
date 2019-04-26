
class Speedometer {
  int mode;
  float pointAX, pointAY, rectWidth, rectHeight;
  float centerX, centerY, radiusA, radiusB;
  float textX, textY, textSize;
  
  Speedometer() {
    mode = CORNER;
    rectWidth = width*0.22;
    rectHeight = height*0.08;
    pointAX = width*0.08;
    pointAY = height*0.45;
    radiusA = rectHeight*1.25;
    radiusB = rectHeight*0.4;
    centerX = pointAX;
    centerY = pointAY + rectHeight*0.5;
    textSize = rectHeight;
    textX = pointAX + rectWidth*0.95;
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
    pushMatrix();
    ellipseMode(CENTER);
    rectMode(CENTER);
    fill(0, 255, 0);
    stroke(0, 255, 0);
    translate(centerX, centerY);
    rotate(radians(data.speed%360));
    ellipse(0, 0, radiusB, radiusB);
    rect(0, 0, radiusA*0.98, radiusB*0.5);
    popMatrix();
    // Text
    fill(0, 255, 0);
    textFont(f, textSize);
    textAlign(RIGHT);
    text(data.speed, textX, textY);
  }
  
}
