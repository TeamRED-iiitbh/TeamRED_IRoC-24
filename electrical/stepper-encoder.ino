#include <AccelStepper.h>
#include <Wire.h>

// Define encoder pins
#define encoderPinA 3 // Channel A must be on interrupt 0
#define encoderPinB 4 // Channel B can be on any pin

// Define stepper motor pins
const int dirPin1 = 5;  // Direction pin for stepper motor
const int stepPin1 = 2; // Step pin for stepper motor

// Define motor interface type
#define motorInterfaceType 1 // Type 1: A four-wire stepper motor with external driver (Step and Direction pins)

// Create stepper object
AccelStepper stepper1(motorInterfaceType, stepPin1, dirPin1);

// Global variables
volatile int encoder_count = 0; // Encoder count
int distance = 5000;            // Initial distance
String str = "0";               // String to store encoder count

// LCD variables
unsigned long previousTimeLed1 = millis();
long timeIntervalLed1 = 100;

void setup() {
  Serial.begin(115200); // Initialize serial communication
  Serial.setTimeout(1);

  pinMode(encoderPinA, INPUT_PULLUP); // Set encoder pins as input with pull-up resistors
  pinMode(encoderPinB, INPUT_PULLUP);

  // Attach interrupt for encoder
  attachInterrupt(1, doEncoderA, RISING); // Interrupt 1 is for pin 3

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("START!");

  // Set stepper properties
  stepper1.setMaxSpeed(4000);     // Set maximum speed
  stepper1.setAcceleration(4000); // Set acceleration

  // Move stepper motor to initial position
  stepper1.moveTo(distance);

  delay(3000); // Delay for 3 seconds
}

void loop() {
  // Check if stepper motor has reached target position
  if (stepper1.distanceToGo() == 0) {
    // Change direction
    distance = distance * -1;
    stepper1.moveTo(distance * -1);
    delay(3000); // Delay for 3 seconds
  }
  stepper1.run(); // Run stepper motor

  // Update LCD display
  unsigned long currentTime = millis();
  if (currentTime - previousTimeLed1 > timeIntervalLed1) {
    previousTimeLed1 = currentTime;
    str = String(encoder_count);
    lcd.clear();
    lcd.print(str);
  }
}

// Interrupt service routine for encoder
void doEncoderA() {
  // Check the state of encoder pin B
  if (digitalRead(encoderPinB) == LOW) {
    encoder_count = encoder_count + 1; // Increment count for positive rotation
  }
  else {
    encoder_count = encoder_count - 1; // Decrement count for negative rotation
  }

  // Update LCD display
  lcd.clear();
  lcd.print(str);
  delay(10);
}