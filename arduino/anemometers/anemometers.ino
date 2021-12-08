int firstSensorPlus = 0;    // first analog sensor, positive differential
int firstSensorMinus = 0;   // first analog sensor, negative differential
int secondSensorPlus = 0;   // second analog sensor, positive differential
int secondSensorMinus = 0;    // second analog sensor, negative differential
int inByte = 0;         // incoming serial byte

void setup() {
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    // read first analog input:
    firstSensorPlus = analogRead(A4);
    firstSensorMinus = analogRead(A5);
    // read second analog input:
//    secondSensorPlus = analogRead(A2);
//    secondSensorMinus = analogRead(A2);

    int diff = firstSensorPlus - firstSensorMinus;
    float conv = ((float)diff / 1023.0) * 20.0;
    Serial.print(firstSensorPlus);
    Serial.print(", ");
    Serial.println(firstSensorMinus);

    
//    Serial.print(",");
//    Serial.println(thirdSensor);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}
