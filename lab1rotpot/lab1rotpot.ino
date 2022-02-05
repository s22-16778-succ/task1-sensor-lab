void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

const int POT_PIN = 14;

void getRotPot() {

  // get output num from rotpot and convert to voltage
  double potVolt = analogRead(POT_PIN);
  double OutVal = (potVolt/1023.0)*5.0;

  // convert doubles to strings
  String pot_out = String(potVolt,3);
  String volt_out = String(OutVal,3);

  // print out values
  Serial.println("Sensor Output + Voltage: (" + pot_out + "," + volt_out + ")");
}

void loop() {
  // put your main code here, to run repeatedly:
  getRotPot();

}
