#include <Servo.h>          // include servo.h library

// const int IrSensor = 12;
int DetectIr;

//Soil Moisture Sensor
const int MSensor = 11;
bool DetectMS;

//Inductive Proximity Sensor
const int ProSensor = 9;
bool DetectPro;

Servo servo_bin;
int servo_bin_pin = 7;    // PWM pin for servo control

Servo servo_plate;
int servo_plate_pin = 6;  // PWM pin for servo control


void setup() {
  // pinMode(IrSensor, INPUT);
  pinMode(MSensor, INPUT);
  pinMode(ProSensor, INPUT);

  servo_plate.attach(servo_plate_pin);
  servo_bin.attach(servo_bin_pin);

  Serial.begin(9600);

  servo_plate.write(20);


}

void loop() {

  if(Serial.available() > 0){
    DetectIr = Serial.read();
    if(DetectIr == '1')
    {
    Serial.println("Waste Detected");

    delay(5000);

    DetectMS = digitalRead(MSensor);
    DetectPro = digitalRead(ProSensor);
    if(DetectMS == HIGH)
    {
        Serial.println("Wet Waste");

        servo_bin.write(180);
        delay(570);
        servo_bin.write(90);
        
        delay(1000);

        servo_plate.write(130);
      
        delay(3000);

        servo_plate.write(20);

        servo_bin.write(0);
        // delay(570);
        delay(580);
        servo_bin.write(90);
    } 

    else{
    if (DetectPro == LOW)
    {
       Serial.println("Metal Waste");

      servo_bin.write(0);
      delay(590);//590
      servo_bin.write(90);

      delay(1000);

      servo_plate.write(130);

      delay(3000);

      servo_plate.write(20);

    
      servo_bin.write(180);
      delay(605);//610
      servo_bin.write(90);

    }
    else
    {
      Serial.println("Dry Waste");

      delay(1000);

      servo_plate.write(130);

      delay(3000);

      servo_plate.write(20);

    }
    }
  }
  }
  // DetectIr = digitalRead(IrSensor);
/*
  if(DetectIr == LOW)
  {
    Serial.println("Waste Detected");

    delay(7000);

    DetectMS = digitalRead(MSensor);
    DetectPro = digitalRead(ProSensor);
    if(DetectMS == HIGH)
    {
        Serial.println("Wet Waste");

        servo_bin.write(180);
        delay(570);
        servo_bin.write(90);
        
        delay(1000);

        servo_plate.write(135);
      
        delay(3000);

        servo_plate.write(15);

        servo_bin.write(0);
        // delay(570);
        delay(580);
        servo_bin.write(90);
    } 

    else{
    if (DetectPro == LOW)
    {
       Serial.println("Metal Waste");

      servo_bin.write(0);
      delay(590);//590
      servo_bin.write(90);

      delay(1000);

      servo_plate.write(135);

      delay(3000);

      servo_plate.write(15);

    
      servo_bin.write(180);
      delay(605);//610
      servo_bin.write(90);

    }
    else
    {
      Serial.println("Dry Waste");

      delay(1000);

      servo_plate.write(135);

      delay(3000);

      servo_plate.write(15);

    }
    }
  }
  delay(500); */
}
