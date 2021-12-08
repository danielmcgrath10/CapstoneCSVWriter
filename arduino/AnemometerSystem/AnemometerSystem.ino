// Pin Connections
int anem_1_p = A0;
int anem_1_n = A1;
int anem_2_p = A2;
int anem_2_n = A3;

// Filter Variables
const int runningAvgCount = 15;
float runningAvgBuffer[runningAvgCount];
int nextRunningAvg;


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  float anem_1_rdg = getData(anem_1_p,anem_1_n);
  //float anem_2_rdg = getData(anem_2_p, anem_2_n);

  // Running average filter
  runningAvgBuffer[nextRunningAvg++] = anem_1_rdg;
  if(nextRunningAvg >= runningAvgCount){
    nextRunningAvg = 0;
  }
  float runningAvgRdg = 0;
  for(int i = 0; i<runningAvgCount; i++){
    runningAvgRdg += runningAvgBuffer[i];
  }
  runningAvgRdg  /= runningAvgCount;
  Serial.println(runningAvgRdg);
  delay(50);
  
}

float getData(int posPin, int negPin){
    // Collect Sensor Readings
    int SensorRdg_pos = analogRead(posPin);
    int SensorRdg_neg = analogRead(negPin);
    int diff = SensorRdg_pos - SensorRdg_neg;
    float airspeed = ((float)diff / 1023.0) * 20.0;
    //Serial.println(airspeed);
    return airspeed;
   
     
}
