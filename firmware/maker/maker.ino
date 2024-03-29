
// Define pin numbers
const int stepPinx = A0;   // Step pin
const int dirPinx = A1;    // Direction pin
const int enPinx = 38;     // Enable pin
// pin y
const int stepPiny = A6;   // Step pin
const int dirPiny = A7;    // Direction pin
const int enPiny = A2;     // Enable pin
// pinz
const int stepPinz = 46;   // Step pin
const int dirPinz = 48;    // Direction pin
const int enPinz = A8;     // Enable pin
// pinE0
const int stepPine0 = 26;   // Step pin
const int dirPine0 = 28;    // Direction pin
const int enPine0 = 24;     // Enable pin




class StepperMotor {
  private:
    int stepPin;
    int dirPin;
    int enPin;

  public:
    StepperMotor(int stepPin, int dirPin, int enPin) {
      this->stepPin = stepPin;
      this->dirPin = dirPin;
      this->enPin = enPin;
      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
      pinMode(enPin, OUTPUT);
      digitalWrite(enPin, LOW); // Enable the stepper motor
    }

    void moveSteps(int steps, bool clockwise) {
      digitalWrite(dirPin, clockwise ? HIGH : LOW); // Set direction
      for (int i = 0; i < steps; i++) {
        digitalWrite(stepPin, HIGH); // Step pulse
        delayMicroseconds(250);      // Delay between steps
        digitalWrite(stepPin, LOW);
        delayMicroseconds(250);
      }
    }
};
// for pinout of mks board refer to this link https://reprap.org/wiki/File:RAMPS1.4schematic.png
// Xstep=A0,Xdir=A1
// Ystep =A6,Ydir=A7
// 
// 
// 

// Initialize the stepper motor object
StepperMotor myStepper1(stepPinx, dirPinx, enPinx);
StepperMotor myStepper2(stepPiny, dirPiny, enPiny);
StepperMotor myStepper3(stepPinz, dirPinz, enPinz);
StepperMotor myStepper4(stepPine0, dirPine0, enPine0);

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  // Send initialization message
  Serial.println("Stepper motor initialized");
}

void loop() {
  // Move 200 steps clockwise
  Serial.println("Clockwise direction");
  myStepper1.moveSteps(2000, true);
  myStepper2.moveSteps(2000, true);
  myStepper3.moveSteps(2000, true);
  myStepper4.moveSteps(2000, true);

  Serial.println("Clockwise rotation completed");
  delay(1000); // Delay for demonstration

  // Move 200 steps counterclockwise
  Serial.println("Counterclockwise direction");
  myStepper1.moveSteps(2000, false);
  myStepper2.moveSteps(2000, false);
  myStepper3.moveSteps(2000, false);
  myStepper4.moveSteps(2000, false);
  Serial.println("Counterclockwise rotation completed");
  delay(1000); // Delay for demonstration
}

