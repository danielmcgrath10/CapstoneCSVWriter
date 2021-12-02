// Pitot Tube Connections
const int pitot_pin_pos = A0;
const int pitot_pin_ref = A1;

// Physical Constants
float density = 1.2;


void setup() {
  Serial.begin(9600);
  while(!Serial){;}
}
/*
void loop(){
  // Get Voltage from tube
  int pitot_voltage_pos = analogRead(pitot_pin_pos);
  int pitot_voltage_ref = analogRead(pitot_pin_ref);
  int pitot_voltage = pitot_voltage_pos - pitot_voltage_ref;
  float pitot_press_rdg = (((float)pitot_voltage / 1023.0) * 68947.6); // Convert to Pa
  float pitot_vel_rdg = sqrt((2*(pitot_press_rdg))/density)-25.96;
  Serial.println(pitot_vel_rdg);
}*/




void loop() {

  // Get Voltage from tube
  int pitot_voltage_pos = analogRead(pitot_pin_pos);
  Serial.print("Pos Pin Voltage: ");
  Serial.println(pitot_voltage_pos);
  int pitot_voltage_ref = analogRead(pitot_pin_ref);
  Serial.print("Ref Pin Voltage: ");
  Serial.println(pitot_voltage_ref);
  int pitot_voltage = pitot_voltage_pos - pitot_voltage_ref;
  Serial.print("Voltage Diff: ");
  Serial.println(pitot_voltage);
  float pitot_press_rdg = (((float)pitot_voltage / 1023.0) * 1244.2); // Convert to Pa
  float pitot_vel_rdg = sqrt((2*(pitot_press_rdg))/density)-3.18;
  Serial.print("Velocity: ");
  Serial.print(pitot_vel_rdg);
  Serial.println(" m/s\n----------------------\n");
  delay(500);
  
}
