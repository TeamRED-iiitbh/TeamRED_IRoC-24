/*decomment code before using
// This code integrates a stepper motor, an encoder, and a LCD using the AccelStepper library. The 
//stepper motor moves back and forth, and the encoder count is stored and also displayed on the LCD. 
//The direction of the stepper motor is being controlled by the encoder input. This code can be 
//modified as per the requirement of the project.
#include <AccelStepper.h>

#include <Wire.h>


#define encoderPinA  3 // Channel A must be on interrupt 0
#define encoderPinB  4 // Channel B can be on any pin
 

////// STEPPER DIRECTION AND STEP PINS:
const int dirPin1 = 5; //// X on CNC shield
const int stepPin1 = 2;

const int enablePin = 8;

// Define motor interface type (type 1 means A four-wire stepper motor where both winding pairs are used and an external stepper driver with Step and Direction pins)
#define motorInterfaceType 1

// Define steppers and the pins they use
AccelStepper stepper1(motorInterfaceType, stepPin1, dirPin1);

// Global variable
volatile int encoder_count = 0;
int distance = 5000;
String str="0";

unsigned long previousTimeLed1 = millis();
long timeIntervalLed1 = 100;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1); 

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(1, doEncoderA, RISING);

    lcd.begin(16, 2);
    lcd.print("START!");

  pinMode(enablePin, OUTPUT); // CNC shield enable pin
  digitalWrite(enablePin, HIGH);

  /////////// STEPPER PROPERTIES:
  stepper1.setMaxSpeed(4000);
  stepper1.setAcceleration(4000);

  stepper1.moveTo(distance);

  delay(3000);
} // Setup End

void loop() {
  
  if( stepper1.distanceToGo() == 0 ){
          distance = distance * -1;
          stepper1.moveTo( distance * -1 );
          delay(3000);
  }
  stepper1.run();

   unsigned long currentTime = millis();

  if(currentTime - previousTimeLed1 > timeIntervalLed1) {
    previousTimeLed1 = currentTime;
    str = String(encoder_count);
    lcd.clear();
  lcd.print(str);
  }
}

void doEncoderA() { 
  // If pin B is low when A trips, then A precedes B
  if(digitalRead(encoderPinB) == LOW) {
    encoder_count = encoder_count + 1; //Positive Rotation
  }

  if(digitalRead(encoderPinB) == HIGH) {
    encoder_count = encoder_count - 1; // Negative Rotation
  }
 // Serial.print("Encoder count:  ");
 // Serial.println (encoder_count);
  
  lcd.clear();
  lcd.print(str);
  delay(10);

}*/