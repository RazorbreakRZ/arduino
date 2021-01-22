import processing.video.*;

class Video {
  int mode;
  Capture cam;
  String deviceName;
 
  Video(PApplet sketch, int mode){
    this.mode = mode;
    println("Loading Video module...");
    switch(this.mode){
      case SENSOR:
        String[] devices = Capture.list();
        if(devices.length == 0){
          println("No devices found!");
          mode = DUMMY;
          break;
        }
        deviceName = devices[devices.length-1];
        println(" - Seleted device: "+deviceName);
        cam = new Capture(sketch, deviceName);
        cam.start();
        break;
      case DUMMY:
        println("Dummy video mode");
        break;
    }
    println("Video ready!");
  }
  
  void draw(){
    switch(mode){
      case SENSOR:
        PImage frame = cam.get();
        frame.resize(width, height);
        background(frame);
        //image(frame, 0, 0);
        break;
      case DUMMY:
        if(second() % 2 == 0){
          textSize(height*0.05);
          textAlign(CENTER);
          fill(255, 0 ,0);
          text("- NO SIGNAL -", width/2, height/2);
        }
        break;
    }
  }
  
}

void captureEvent(Capture c){
  c.read();
  redraw = true;
}
