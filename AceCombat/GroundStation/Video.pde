import processing.video.*;

class Video {
  Capture cam;
 
  Video(PApplet sketch){
    cam = new Capture(sketch);
    cam.start();
  }
  
  void draw(){
    image(cam, 0, 0);
  }
  
  void captureEvent(Capture c){
    c.read();
  }
  
}
