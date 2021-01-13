// Constants
static final int SENSOR = 0;
static final int DUMMY = 1;

class Data {
  int mode;
  
  int direction;
  int time;
  int speed;
  int energy;
  int altitude;
  
  Data(int mode) {
    println("Loading Data module...");
    this.mode = mode;
    direction = 0;
    time = 0;
    speed = 0;
    energy = 0;
    altitude = 0;
    switch(this.mode){
      case SENSOR:
        println("Real data mode");
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
    // TODO
  }
  
  void simulateData() {
    time = (millis()/1000) % 5999;
    direction = (direction + 1) % 360;
    speed = (speed + 10) % 9999;
    energy = (energy + 1) % 100;
    altitude = (altitude + 1) % 9999;
  }
  
}
