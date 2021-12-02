#include <Wire.h>

// Initializing values
int anem_1_p = A0;
int anem_1_n = A1;
int anem_2_p = A2;
int anem_2_n = A3;
int anem_3_p = A4;
int anem_3_n = A5;
float anem3Val = 0.0;
float anem4Val = 0.0;

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {
    ;
  }
  Wire.begin(9);
  Wire.onReceive(onReceiveVals);
//  establishContact();
}

// Callback function for when the Wire file receives data
// Called when the master arduino sends data over the bus to the slave
void onReceiveVals(int bytes){
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

void loop() {
  // put your main code here, to run repeatedly:
//  if(Serial.available() > 0) {
    float anem_1_rdg = getData(anem_1_p,anem_1_n);
    float anem_2_rdg = getData(anem_2_p, anem_2_n);
    float anem_3_rdg = getData(anem_3_p, anem_3_n);
  
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

    // Third Running Average Filter
    runningAvgBuffer3[nextRunningAvg3++] = anem_3_rdg;
    if(nextRunningAvg3 >= runningAvgCount3){
      nextRunningAvg3 = 0;
    }
    float runningAvgRdg3 = 0;
    for(int i = 0; i<runningAvgCount3; i++){
      runningAvgRdg3 += runningAvgBuffer3[i];
    }
    runningAvgRdg3 /= runningAvgCount3;
    
    Serial.print(runningAvgRdg);
    Serial.print(",");
    Serial.print(runningAvgRdg2);
    Serial.print(",");
    Serial.print(runningAvgRdg3);
    Serial.print(",");
    Serial.print(anem3Val);
    Serial.print(",");
    Serial.print(anem4Val);
    Serial.println();
//  }
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

// Outputting values to the Serial port while not receiving anything
//void establishContact() {
//  while (Serial.available() <= 0) {
//    Serial.println("0,0,0,0,0");   // send an initial string
//    delay(300);
//  }
//}
