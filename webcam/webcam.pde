import processing.video.*;

Capture cam;
String selectedCamera;

void setup() {
  size(640, 480);

  String[] cameras = Capture.list();
  
  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(" - "+cameras[i]);
    }
    
    // The camera can be initialized directly using an 
    // element from the array returned by list():
    selectedCamera = cameras[cameras.length-1];
    cam = new Capture(this, 640, 480, selectedCamera, 30);
    cam.start();     
  }  
}

void draw() {
  if (cam.available() == true) {
    cam.read();
  }
  //image(cam, 0, 0);
  // The following does the same, and is faster when just drawing the image
  // without any additional resizing, transformations, or tint.
  set(0, 0, cam);
  drawTimestamp();
  drawFPS();
}

void drawFPS(){
  fill(255, 255, 255);
  textSize(32);
  text((int)frameRate, 580, 40);  
}

void drawTimestamp(){
  String time = hour()+":"+minute()+":"+second();
  fill(255, 255, 255);
  textSize(32);
  text(time, 10, 460);  
}
