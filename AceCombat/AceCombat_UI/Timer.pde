
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
    text(formatTimer(data.time), textX, textY);
  }
  
}
