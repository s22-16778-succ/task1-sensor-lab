/*
* Carnegie Mellon University Mechatronics Spring 2022: Team 5
* Sensors Lab Code
* Authors: Felipe Borja (fborja)
*          Brandon Wang (bcwang)
*          Jaiden Napier (jinapier)
*          Ignacio Peon Zapata (ipeon)
*          Sahil Saini (sssaini)
*/

#include<math.h>

// Pin assignments
const int ECHO_PIN = 11;
const int TRIG_PIN = 12;
const int POT_PIN = A0;
const int IR_PIN = A1;

// Constants for IR sensor quadratic formula
const float a = -8169.1;
const float b = 4789.2;
const float c = 18.8;

// Global states
char last, readIn;

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  Serial.begin (9600);
  Serial.println("Mechatronic Design Sensors Lab: Team SUCC");
  printMenu();  
}

// This function prints character options in a menu through the Serial Monitor.
void printMenu(){
  Serial.println("The character commands are as follows:");
  Serial.println(" u: Show Ultrasonic Distance Sensor measurements (in inches).");
  Serial.println(" p: Show Potentiometer measurements.");
  Serial.println(" i: Show IR Distance sensor measurements (in inches).");
  Serial.println(" m: Print this menu of options.");
  Serial.println("To continue, insert the character of the option you want and hit 'Enter'.");
}

// This function handles the input commands from the user.
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

// Ultrasonic Distance Sensor
void readUDS() {
  digitalWrite(TRIG_PIN, LOW);
  delay(1);
  digitalWrite(TRIG_PIN, HIGH);
  delay(1);
  digitalWrite(TRIG_PIN, LOW);
  
  double travel_time = pulseIn(ECHO_PIN, HIGH);
  double distance = travel_time / (2 * 29); // in centimeters

  Serial.print("Distance: ");
  Serial.print(distance, 3);
  Serial.println(" cm");
  delay(200);
}

// Rotary Potentiometer
void readPot() {
  // get output num from rotpot and convert to voltage
  double pot_out = analogRead(POT_PIN);
  double volt_out = (pot_out/1023.0)*5.0;
  double angle_out = (pot_out/1000)*300;
  Serial.print("Angle: ");
  Serial.print(angle_out, 3);
  Serial.print(" (degrees)");
  Serial.print("\tVoltage: ");
  Serial.print(volt_out, 3);
  Serial.println(" (V)");
  delay(200);
}

// IR Proximity Sensor
void readIR(){

  int IR_Sum = 0;
  
  for (int i = 0;i<30;i++){ 
  int value = analogRead(IR_PIN); //Read the distance in cm and store it
  IR_Sum = IR_Sum+value;
  }  
  float v=(IR_Sum/30); // average voltage over last 30 samples
  float x = sqrt(-a/(c-v) + pow(b/(2*(c-v)),2)) - b/(2*(c-v));
  Serial.println("Distance: "+String(x)+(" cm"));  //display the string e.g "Distance = 40 cm"
  delay(100);//ten samples per second
}
  

void loop() {
  if (Serial.available()) {
    readIn = Serial.read();
    if ((int) readIn == 10) // line feed
      flagSwitch(last);
    last = readIn;
  }
}
