#include<math.h>
const int IR_PIN = A1;
const float a = -8169.1;
const float b = 4789.2;
const float c = 18.8;
float IR_Sum = 0;
float IR_Count = 0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  readIR();
}

// IR Proximity Sensor
void readIR(){
  int value = analogRead(IR_PIN); //Read the distance in cm and store it

  IR_Sum = IR_Sum+value;
  IR_Count = IR_Count + 1;
  
  if (IR_Count == 30)
    {
    float v = (IR_Sum/IR_Count); // average voltage over last 30 samples
    float x = sqrt(-a/(c-v) + pow(b/(2*(c-v)),2)) - b/(2*(c-v)); 
    Serial.println("Distance = "+String(x)+(" cm"));  //display the string e.g "Distance = 40 cm"

     
    IR_Sum = 0;
    IR_Count = 0;
  }
    
   delay(100);//ten smaples per second
}
