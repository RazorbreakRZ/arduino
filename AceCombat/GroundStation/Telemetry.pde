import processing.serial.*;

class Telemetry {
  int mode;
  
  Serial serialPort;
  String deviceName;
  int baudRate = 9600;
  
  int direction;
  int time;
  int speed;
  int energy;
  int altitude;
  
  Telemetry(PApplet sketch, int mode) {
    println("Loading Telemetry module...");
    this.mode = mode;
    direction = 0;
    time = 0;
    speed = 0;
    energy = 0;
    altitude = 0;
    switch(this.mode){
      case SENSOR:
        println("Reading data from Serial port");
        println("Listing serial devices:");
        for(String device: Serial.list()){
          println(" - "+device);
        }
        if(Serial.list().length == 0){
           println("No serial device available. Changing to Dummy mode...");
           this.mode = DUMMY;
           break;
        }
        String deviceName = Serial.list()[Serial.list().length - 1];
        println("Connected to device: "+deviceName+" ("+baudRate+" bps)");
        serialPort = new Serial(sketch, deviceName, baudRate);
        serialPort.bufferUntil('}');
        break;
      case DUMMY:
        println("Dummy data mode");
    }
    println("Data ready!");
  }
  
  void refresh() {
    switch(mode){
      case SENSOR:
        retrieveDataFromSerialPort();
        break;
      default:
        simulateData();
    }
  }
  
  void retrieveDataFromSerialPort(){
  //  if(serialPort.available()>1){
  //    String receivedData = serialPort.readStringUntil('}');
  //    if(receivedData != null){
  //      println(receivedData);
  //    }
  //  }
  }
  
  void simulateData() {
    time = (millis()/1000) % 5999;
    direction = (direction + 1) % 360;
    speed = (speed + 10) % 9999;
    energy = (energy + 1) % 100;
    altitude = (altitude + 1) % 9999;
  }
  
  
  
}

void serialEvent(Serial p) { 
  println(p.readString()); 
} 
