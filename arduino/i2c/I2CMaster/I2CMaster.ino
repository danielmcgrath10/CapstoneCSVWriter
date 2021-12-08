#include<Wire.h>

// Pin Connections
const int anem_1_p = A0;
const int anem_1_n = A1;
const int anem_2_p = A2;
const int anem_2_n = A3;

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
  //while(!Serial) {
    //;
  //}
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(9);
  float anem_1_rdg = getData(anem_1_p,anem_1_n);
  float anem_2_rdg = getData(anem_2_p, anem_2_n);

  // Getting the Anemometer Reading Values
    float runningAvgRdg = getRunningAvgRdg(runningAvgCount, runningAvgBuffer, nextRunningAvg, anem_1_rdg);
    float runningAvgRdg2 = getRunningAvgRdg(runningAvgCount2, runningAvgBuffer2, nextRunningAvg2, anem_2_rdg);

  // Turning readings into strings to be sent over I2C Bus
    String st1 = String(runningAvgRdg, 3);
    String st2 = String(runningAvgRdg2, 3);

//  String st1 = String(anem_1_rdg, 3);
//  String st2 = String(anem_2_rdg, 3);

  // Concatenating Strings to send in one payload
  String st3 = st1 + ";" + st2;
  
  // Creating buffer of total string length
  char buffer[st3.length()];
  
  // Converting string to char array
  st3.toCharArray(buffer, st3.length());
  Wire.write(buffer);
  Wire.endTransmission();
  delay(300);
}

float getRunningAvgRdg(int count, float buffer[], int next, float anem_reading) {
  buffer[next++] = anem_reading; 
  if(next >= count) {
    next = 0;
  }
  float reading = 0;
  for(int i = 0; i < count; i++) {
    reading += buffer[i];
  }
  return reading /= count;
}

// Function for getting airspeed from anemometer p and n
float getData(int posPin, int negPin){
    // Collect Sensor Readings
    int SensorRdg_pos = analogRead(posPin);
    int SensorRdg_neg = analogRead(negPin);
    int diff = SensorRdg_pos - SensorRdg_neg;
    float airspeed = ((float)diff / 1023.0) * 20.0;
    return airspeed;  
}
