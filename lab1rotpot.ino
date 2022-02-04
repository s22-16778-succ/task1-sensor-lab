void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

const int POT_PIN = 14;

void loop() {
  // put your main code here, to run repeatedly:
  double potVolt = analogRead(POT_PIN);

  String pot = String(potVolt,3);
  
  // print output to console
  Serial.println("Sensor Output Value: " + pot);
  double OutVal = (potVolt/1023.0)*5.0;
  String volt = String(OutVal,3);
  Serial.println("Sensor Output + Voltage: (" + pot + "," + volt + ")");

  delay(500);
}
