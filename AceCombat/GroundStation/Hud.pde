
class Hud {
  Map map;
  Timer timer;
  Speedometer speedometer;
  Altimeter altimeter;
  Energy energy;
  
  Hud(){
    println("Loading Hud module...");
    map = new Map();
    timer = new Timer();
    speedometer = new Speedometer();
    altimeter = new Altimeter();
    energy = new Energy();
    println("Hud ready!");
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
