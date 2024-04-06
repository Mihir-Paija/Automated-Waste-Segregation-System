#include <Servo.h>             // include servo.h library
#include <LiquidCrystal.h>   //  include liquid crytstal library

Servo servo;

//LiquidCrystal lcd(A3, A2,13 , 12, 11, 10);

//Ir sensor
const int IrSensor = 10;
int DetectIr = HIGH;


//Inductive Proximity Sensor
const int ProSensor = 9;
int DetectPro = HIGH;

//Soil Moisture Sensor
const int MSensor = 8;
int DetectMS = HIGH;

//Buzzer
const int buzzer = 11;

int Waste_Status = false;

// Motor A connections
const int in1 = 7;
const int in2 = 6;

// Motor B connections
const int in3 = 5;
const int in4 = 4;

//servo motor
const int servo_pin = 12; // PWM pin for servo control
int pos = 0;

/*//ultra-sonic sensor
const int trigPin = 3;
const int echoPin = 2;

long duration;
int s2b; //distance from sensor to emplty bin
int hight; //hight of bin
int distance; // distance from sensor to non-empty bin
int duration;
int filled_bin; //s2b - distance */


void setup() {
  pinMode(IrSensor, INPUT);
  pinMode(MSensor, INPUT);
  pinMode(ProSensor, INPUT);

/*  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);*/

  pinMode(buzzer, OUTPUT);

  servo.attach(servo_pin); 

  pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

  Serial.begin(9600);

  // Turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  servo.write(0);
  
  delay(15);
  /*// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  s2b = duration * 0.034 / 2;

  lcd.begin(16, 2);
  lcd.print("    WELCOME"); */
}

void loop() {
  
  /*lcd.setCursor(0, 0);  
  lcd.print("  WAITING...");*/
 
  DetectIr = digitalRead(IrSensor);
  
  
  //if Ir sensor detect the object
  if ( DetectIr == LOW) 
  {
    Serial.println("Waste Detected");
    //lcd.print("WASTE DETECTED");
    // Turn on motor A & B //start conveyor belt
	  digitalWrite(in1, LOW);
	  digitalWrite(in2, HIGH);
	  digitalWrite(in3, HIGH);
	  digitalWrite(in4, LOW);
    delay(7000);
    
    DetectPro = digitalRead(ProSensor);
    if ( DetectPro == LOW) 
    {
      Serial.println("Metal Waste");
      //lcd.print(" METAL ");
      Waste_Status = true;

      //turn on servo motor and rotate metal bin...
      servo.write(90);
      delay(10000);

      //display metal
      
    }
    else
    {  
      delay(5000);

      DetectMS = digitalRead(MSensor);
      if (DetectMS == LOW) 
      {
        Serial.println("Wet Waste");
        //lcd.print(" WET ");

        Waste_Status = true;
        
        servo.write(180);
        delay(5000);
        //display wet
      }
      else
      {
        Serial.println("Dry Waste");
        //lcd.print(" DRY ");

        Waste_Status = true;

        servo.write(0);
        delay(5000);
      }      
    }
    Serial.println("The waste will go in the bin");

    tone(buzzer, 700); 
    delay(500);      
    noTone(buzzer);
    delay(1000);

    // Turn off motors
	  digitalWrite(in1, LOW);
	  digitalWrite(in2, LOW);
	  digitalWrite(in3, LOW);
	  digitalWrite(in4, LOW);

    /*// Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    filled_bin = s2b - distance;

    percentage = (filled_bin/height)*100;
    
    //lcd.print(String(percentage)+String("%")+String(" BIN FILLED "));
    //Serial.println(String(percentage)+String("%")+String(" bin filled"));*/
    servo.write(0);
  }
}
