/*
* Carnegie Mellon University Mechatronics Spring 2022: Team 5
* Sensors Lab Code
* Authors: Felipe Borja (fborja)
*          Brandon Wang (bcwang)
*          Jaiden Napier (jinapier)
*          Ignacio Peon Zapata (ipeon)
*          Sahil Saini (sssaini)
*/

// Pin assignments
const int ECHO_PIN = 11;
const int TRIG_PIN = 12;
const int POT_PIN = A0;

// Global states
char last, readIn;

void setup() {
  Serial.println("echatronic Design Sensors Lab: Team SUCC");
  printMenu();
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  Serial.begin (9600);
}

void printMenu(){
  Serial.println("The character commands are as follows:");
  Serial.println(" u: Show Ultrasonic Distance Sensor measurements (in inches).");
  Serial.println(" p: Show potentiometer measurements.");
  Serial.println(" i: Show IR Distance sensor measurements (in inches).");
  Serial.println(" m: Print this menu of options.");
  Serial.println("To continue, insert the character of the option you want and hit 'Enter'.");
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
  double volt_out = (pot_out/1023.0)*5.0;

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
    case 'm':
      printMenu();
      break;
    default:
      Serial.print(c);
      Serial.println(" is not a valid input. Please enter 'u', 'p', 'i', or 'm'.");
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
