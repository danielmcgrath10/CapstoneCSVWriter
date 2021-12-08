#include <Wire.h>

// Initializing values
const int anem_1_p = A0;
const int anem_1_n = A1;
const int anem_2_p = A2;
const int anem_2_n = A3;
const int anem_3_p = A4;
const int anem_3_n = A5;
const int anem_4_p = A6;
const int anem_4_n = A7;
const int pitot_pin_pos = A8;
const int pitot_pin_ref = A9;

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

// Filter Variables 4
const int runningAvgCount4 = 15;
float runningAvgBuffer4[runningAvgCount4];
int nextRunningAvg4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {
    ;
  }
//  establishContact();
}

void loop() {
    // put your main code here, to run repeatedly:

    // Grabbing the data from the Analog pins for the anemometers and pitot tube
    float anem_1_rdg = getData(anem_1_p,anem_1_n);
    delay(10);
    float anem_2_rdg = getData(anem_2_p, anem_2_n);
    delay(10);
    float anem_3_rdg = getData(anem_3_p, anem_3_n);
    delay(10);
    float anem_4_rdg = getData(anem_4_p, anem_4_n);
    delay(10);
    float pitot_rdg = getPitotData(pitot_pin_pos, pitot_pin_ref);
    delay(10);    

    // Getting the Anemometer averaged values
    float runningAvgRdg = getRunningAvgRdg(runningAvgCount, runningAvgBuffer, nextRunningAvg, anem_1_rdg);
    float runningAvgRdg2 = getRunningAvgRdg(runningAvgCount2, runningAvgBuffer2, nextRunningAvg2, anem_2_rdg);
    float runningAvgRdg3 = getRunningAvgRdg(runningAvgCount3, runningAvgBuffer3, nextRunningAvg3, anem_3_rdg);
    float runningAvgRdg4 = getRunningAvgRdg(runningAvgCount4, runningAvgBuffer4, nextRunningAvg4, anem_4_rdg);
    
    // Printing the values to the Serial port
    Serial.print(runningAvgRdg);
    Serial.print(",");
    Serial.print(runningAvgRdg2);
    Serial.print(",");
    Serial.print(runningAvgRdg3);
    Serial.print(",");
    Serial.print(runningAvgRdg4);
    Serial.print(",");
    Serial.print(pitot_rdg);
    Serial.println();
}

/**
 * @brief Get the Running Avg Rdg object
 * 
 * @param count The number of readings that need to be taken before the averaged airspeed can be calculated
 * @param buffer Stores the array of anemometer readings that are taken before the averaged reading is calculated
 * @param next The reading number
 * @param anem_reading The current anemometer airspeed reading
 * @return float The averaged airspeed value
 */
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

/**
 * @brief Get the Data object
 * 
 * @param posPin The analog pin corresponding to the positive wire on the anemometer
 * @param negPin The analog pin corresponding to the negative wire on the anemometer
 * @return float The airspeed value from the anemometer
 */
float getData(int posPin, int negPin){
    // Collect Sensor Readings
    int SensorRdg_pos = analogRead(posPin);
    int SensorRdg_neg = analogRead(negPin);
    int diff = SensorRdg_pos - SensorRdg_neg;
    float airspeed = ((float)diff / 1023.0) * 20.0;
    return airspeed;  
}

/**
 * @brief Get the Pitot Data object
 * 
 * @param posPin The analog pin corresponding to the positive wire of the pitot tube
 * @param refPin The analog pin corresponding to the ref wire of the pitot tube
 * @return float The reading from the pitot tube
 */
float getPitotData(int posPin, int refPin) {
  int pitot_voltage_pos = analogRead(posPin);
  int pitot_voltage_ref = analogRead(refPin);
  int pitot_voltage = pitot_voltage_pos - pitot_voltage_ref; 
  float pitotPressRdg = (((float)pitot_voltage / 1023.0) * 1244.2);
  float pitot_vel_rdg = sqrt((2*(pitotPressRdg))/density)-3.18;

  return pitot_vel_rdg;
}
