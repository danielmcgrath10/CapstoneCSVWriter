int inByte = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

//  establishContact();
}

void loop() {
  // put your main code here, to run repeatedly:

//  if (Serial.available() > 0) {
//    inByte = Serial.read();
//    Serial.println(inByte);
//  }
  Serial.println("voltage: 1.5");
  delay(1000);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}
