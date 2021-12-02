#include<Wire.h>

// Pin Connections
int anem_1_p = A0;
int anem_1_n = A1;
int anem_2_p = A2;
int anem_2_n = A3;

// Filter Variables
const int runningAvgCount = 15;
float runningAvgBuffer[runningAvgCount];
int nextRunningAvg;

// Filter Variables 2
const int runningAvgCount2 = 15;
float runningAvgBuffer2[runningAvgCount2];
int nextRunningAvg2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {
    ;
  }
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    Wire.beginTransmission(9);
    float anem_1_rdg = getData(anem_1_p,anem_1_n);
    float anem_2_rdg = getData(anem_2_p, anem_2_n);
  
    // Running average filter
    runningAvgBuffer[nextRunningAvg++] = anem_1_rdg;
    if(nextRunningAvg >= runningAvgCount){
      nextRunningAvg = 0;
    }
    float runningAvgRdg = 0;
    for(int i = 0; i<runningAvgCount; i++){
      runningAvgRdg += runningAvgBuffer[i];
    }
    runningAvgRdg /= runningAvgCount;

    // Second Running Average Filter
    runningAvgBuffer2[nextRunningAvg2++] = anem_2_rdg;
    if(nextRunningAvg2 >= runningAvgCount2){
      nextRunningAvg2 = 0;
    }
    float runningAvgRdg2 = 0;
    for(int i = 0; i<runningAvgCount2; i++){
      runningAvgRdg2 += runningAvgBuffer2[i];
    }
    runningAvgRdg2 /= runningAvgCount2;

    // Turning readings into strings to be sent over I2C Bus
    String st1 = String(runningAvgRdg, 3);
    String st2 = String(runningAvgRdg2, 3);

    // Concatenating Strings to send in one payload
    String st3 = st1 + ";" + st2;
    
    // Creating buffer of total string length
    char buffer[st3.length()];
    
    // Converting string to char array
    st3.toCharArray(buffer, st3.length());

    char buffer1[4] = "1;1";
    Wire.write(buffer1);
//    Wire.write(buffer);
    Wire.endTransmission();
  } else {
    Wire.beginTransmission(9);
    char buffer[4] = "1;1";
    Wire.write(buffer);
    Wire.endTransmission();
  }
  delay(300);
}

// Function for getting airspeed from anemometer p and n
float getData(int posPin, int negPin){
    // Collect Sensor Readings
    int SensorRdg_pos = analogRead(posPin);
    int SensorRdg_neg = analogRead(negPin);
    int diff = SensorRdg_pos - SensorRdg_neg;
    float airspeed = ((float)diff / 1023.0) * 20.0;
    //Serial.println(airspeed);
    return airspeed;  
}
