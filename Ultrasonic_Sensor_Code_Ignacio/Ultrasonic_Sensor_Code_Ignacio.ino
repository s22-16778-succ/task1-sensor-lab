int trig_pin = 12;
int echo_pin = 11;
double travel_time;
double distance;

void setup() {
  // put your setup code here, to run once:
  
pinMode (trig_pin, OUTPUT);

pinMode (echo_pin, INPUT);

Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite (trig_pin, LOW);
delay (1);

digitalWrite (trig_pin, HIGH);
delay(1);

digitalWrite (trig_pin, LOW);

travel_time = pulseIn (echo_pin, HIGH);
distance = ((travel_time / 2) / 29)/ 2.54;
delay (200);

Serial.print ("The distance is (inches):");
Serial.println (distance);
}
