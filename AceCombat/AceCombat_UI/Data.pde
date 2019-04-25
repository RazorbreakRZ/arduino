// Constants
static final int SENSOR = 0;
static final int DUMMY = 1;

class Data {
  int mode;
  
  int direction;
  int time;
  int speed;
  int energy;
  
  Data(int mode) {
    this.mode = mode;
    direction = 0;
    time = 0;
    speed = 0;
    energy = 0;
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
    time = (time + 1) % 5999;
    direction = (direction + 1) % 360;
    speed = (speed + 1) % 9999;
    energy = (energy + 1) % 100;
  }
  
}
