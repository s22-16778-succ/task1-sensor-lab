/*
* Carnegie Mellon University Mechatronics Spring 2022: Team 5
* Sensors Lab Code
* Authors: Felipe Borja (fborja)
*          Brandon Wang ()
*          Jaiden Napier ()
*          Ignacio Peon Zapata ()
*          Sahil Saini ()
*/

// Pin assignments
const int ECHO_PIN = 11;
const int TRIG_PIN = 12;
const int POT_PIN = A0;

// Global state
char last, readIn;

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  Serial.begin (9600);
}

// Ultrasonic Distance Sensor
void readUDS() {
  digitalWrite(TRIG_PIN, LOW);
  delay(1);
  digitalWrite(TRIG_PIN, HIGH);
  delay(1);
  digitalWrite(TRIG_PIN, LOW);
  
  double travel_time = pulseIn(ECHO_PIN, HIGH);
  double distance = travel_time / (2 * 29); // in centimeters

  Serial.print("Distance (cm): ");
  Serial.println(distance, 3);
  delay(200);
}

// Rotary Potentiometer
void readPot() {
  // get output num from rotpot and convert to voltage
  double pot_out = analogRead(POT_PIN);
  double volt_out = (potVolt/1023.0)*5.0;

  Serial.print("Sensor Output: ");
  Serial.print(pot_out, 3);
  Serial.print("\tVoltage: ");
  Serial.println(volt_out, 3);
  delay(200);
}

// IR Proximity Sensor
void readIR(){
  
}

void flagSwitch(char c) {
  switch (c) {
    case 'u':
      readUDS();
      break;
    case 'p':
      readPot();
      break;
    case 'i':
      readIR();
      break;
    default:
      Serial.print(c);
      Serial.println(" is not a valid input. Please enter 'u', 'p', or 'i'.");
  }
}

void loop() {
  if (Serial.available()) {
    readIn = Serial.read();
    if ((int) readIn == 10) // line feed
      flagSwitch(last);
    last = readIn;
  }
}
