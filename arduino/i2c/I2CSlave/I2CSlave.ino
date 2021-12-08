#include <Wire.h>

// Initializing values
const int anem_1_p = A0;
const int anem_1_n = A1;
const int anem_2_p = A2;
const int anem_2_n = A3;
const int pitot_pin_pos = A4;
const int pitot_pin_ref = A5;
float anem3Val = 0.0;
float anem4Val = 0.0;

// Physical Constants
float density = 1.2;

// Filter Variables
const int runningAvgCount = 15;
float runningAvgBuffer[runningAvgCount];
int nextRunningAvg;

// Filter Variables 2
const int runningAvgCount2 = 15;
float runningAvgBuffer2[runningAvgCount2];
int nextRunningAvg2;

// Filter Variables 3
const int runningAvgCount3 = 15;
float runningAvgBuffer3[runningAvgCount3];
int nextRunningAvg3;

// Callback function for when the Wire file receives data
// Called when the master arduino sends data over the bus to the slave
static void onReceiveVals(int bytes){
  int index = 0;
  String dataString1 = "";
  String dataString2 = "";
  // Looping when the wire is receiving data
  while(Wire.available()) {
    // Grabbing the next character passed on the wire
    char c = Wire.read();
    // Checking for the delimiter
    if(c != ';') {
      if(index == 0) { 
        // Passing to the first of the two anemometer data strings
        dataString1 = dataString1 + c;
      } else if(index == 1) {
        // Passing to the second of the two anemometer data strings
        dataString2 = dataString2 + c;
      }
    } else {
      index++;
    }
  }
  // Turning the data strings back into floats to get the anemometer values
  anem3Val = dataString1.toFloat();
  anem4Val = dataString2.toFloat();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  while(!Serial) {
//    ;
//  }
//  Wire.begin(9);
//  Wire.onReceive(onReceiveVals);
//  establishContact();
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(Serial.available() > 0) {
    float anem_1_rdg = getData(anem_1_p,anem_1_n);
    Serial.println(anem_1_rdg);
//    float anem_2_rdg = getData(anem_2_p, anem_2_n);
//    float pitot_rdg = getPitotData(pitot_pin_pos, pitot_pin_ref);    

    // Getting the Anemometer Reading Values
//    float runningAvgRdg = getRunningAvgRdg(runningAvgCount, runningAvgBuffer, nextRunningAvg, anem_1_rdg);
//    float runningAvgRdg2 = getRunningAvgRdg(runningAvgCount2, runningAvgBuffer2, nextRunningAvg2, anem_2_rdg);
//    float runningAvgRdg = anem_1_rdg;
//    float runningAvgRdg2 = anem_2_rdg;
    
//    Serial.print(runningAvgRdg);
//    Serial.print(",");
//    Serial.print(runningAvgRdg2);
//    Serial.print(",");
//    Serial.print(anem3Val);
//    Serial.print(",");
//    Serial.print(anem4Val);
//    Serial.print(",");
//    Serial.print(pitot_rdg);
//    Serial.println();
//  }
  delay(300);
}

float getRunningAvgRdg(int count, float buffer[], int next, float anem_reading) {
  buffer[next++] = anem_reading; 
  if(next >= count) {
    next = 0;
  }
  float reading = 0.0;
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

float getPitotData(int posPin, int refPin) {
  int pitot_voltage_pos = analogRead(posPin);
  int pitot_voltage_ref = analogRead(refPin);
  int pitot_voltage = pitot_voltage_pos - pitot_voltage_ref; 
  float pitotPressRdg = (((float)pitot_voltage / 1023.0) * 1244.2);
  float pitot_vel_rdg = sqrt((2*(pitotPressRdg))/density)-3.18;
}

// Outputting values to the Serial port while not receiving anything
//void establishContact() {
//  while (Serial.available() <= 0) {
//    Serial.println("0,0,0,0,0");   // send an initial string
//    delay(300);
//  }
//}
