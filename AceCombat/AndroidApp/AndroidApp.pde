
import ketai.camera.*;
import ketai.sensors.*;

KetaiSensor sensor;
KetaiLocation location;
KetaiCamera cam;

PVector accel, gps, gyro, mag, game, grav;
float light;

void setup() {
  fullScreen();
  orientation(PORTRAIT);
  
  imageMode(CENTER);
  textFont(createFont("SansSerif", displayDensity*16));
  
  accel = new PVector();
  gps = new PVector();
  gyro = new PVector();
  mag = new PVector();
  game = new PVector();
  grav = new PVector();
  light = 0.0;
  
  location = new KetaiLocation(this);  
  location.setUpdateRate( 5000, 1);
  
  sensor = new KetaiSensor(this);
  sensor.list();
  sensor.start();
  
  cam = new KetaiCamera(this, 1920, 1080, 30);
  
}

void draw() {
  // Draw camera frame
  if (cam != null && cam.isStarted()){
    image(cam, width/2, height/2, width, height);
  }else{
    background(0);
    textAlign(CENTER);
    fill(255, 0 ,0);
    if(second() % 2 == 0){
      text("- NO SIGNAL -", width/2, height/2);
    }
  }
  // Draw sensor and location
  textAlign(LEFT);
  fill(255);
  text(
    "Accelerometer\n x: " + accel.x + "\n y: " + accel.y + "\n z: " + accel.z + "\n" +
    "Gyroscope\n x: " + gyro.x + "\n y: " + gyro.y + "\n z: " + gyro.z + "\n" +
    "Magnetometer\n x: " + mag.x + "\n y: " + mag.y + "\n z: " + mag.z + "\n" +
    "Game rotation\n x: " + game.x + "\n y: " + game.y + "\n z: " + game.z + "\n" +
    "Gravity\n x: " + grav.x + "\n y: " + grav.y + "\n z: " + grav.z + "\n" +
    "Light\n x: " + light + "\n" +
    "Coordinates ("+location.getProvider()+")\n lat: " + gps.x + "\n lon: " + gps.y + "\n alt: " + gps.z + "\n"
    , 0, 0, width, height);
}

public void onResume() {
  super.onResume();
  if(sensor!=null){
    sensor.start();
  }
}

public void onPause() {
  super.onPause();
  if(sensor!=null){
    sensor.stop();
  }
}

//void onAccelerometerEvent(float x, float y, float z)
void onLinearAccelerationEvent(float x, float y, float z)
{
  accel.set(x,y,z);
}

void onGyroscopeEvent(float x, float y, float z)
{
  gyro.set(x, y, z);
}

void onLinearOrientationEvent(float x, float y, float z){
  mag.set(x, y, z);
}

void onLightEvent(float d){
  light = d;
}

void onGameRotationEvent(float x, float y, float z){
  game.set(x, y, z);
}

void onGravityEvent(float x, float y, float z){
  grav.set(x, y, z);
}

void onLocationEvent(double lat, double lon, double alt)
{
  gps.set((float)lat, (float)lon, (float)alt);
}

void onCameraPreviewEvent()
{
  cam.read();
}

void mousePressed(){
  if (cam.isStarted()) {
    cam.stop();
  } else {
    cam.start();
  }
}
