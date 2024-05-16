#include <Servo.h>
Servo servo1, servo2, servo3, servo4;


#define movementDuration 1000 // Duration for motor movement in milliseconds
int straightSpeed=255;
class myDCMotor {
private:
  int dirPin;
  int pwmPin;

public:
  myDCMotor(int dirPin, int pwmPin) {
    this -> dirPin = dirPin;
    this -> pwmPin = pwmPin;
    pinMode(dirPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
  }

  void motorMove(int speed) {
    digitalWrite(dirPin, LOW);
    analogWrite(pwmPin, speed);
  }

  void motorMoveB(int speed) {
    digitalWrite(dirPin, HIGH);
    analogWrite(pwmPin, speed);
  }

  void stop_it() {
    digitalWrite(dirPin, LOW);
    analogWrite(pwmPin, 0);
  }

  // Check if the motor movement duration has elapsed
  bool isMovementComplete(unsigned long currentTime) {
    static unsigned long movementStartTime = 0;
    if (currentTime - movementStartTime >= movementDuration) {
      movementStartTime = currentTime; // Reset the movement start time
      return true;
    }
    return false;
  }
};


myDCMotor motor1(26,6);
myDCMotor motor2(24, 4);
myDCMotor motor3(22, 2);
myDCMotor motor4(27, 7);
myDCMotor motor5(25, 5);
myDCMotor motor6(23, 3);

//myDCMotor motor1(2, 22);
//myDCMotor motor2(3, 23);
//myDCMotor motor3(4, 24);
//myDCMotor motor4(5, 25);
//myDCMotor motor5(6, 26);
//myDCMotor motor6(7, 27);

void setup() {
  Serial.begin(115200);
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
}

void loop(){
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'F':
        motor1.motorMove(straightSpeed);
        motor2.motorMove(straightSpeed);
        motor3.motorMove(straightSpeed);
        motor4.motorMove(straightSpeed);
        motor5.motorMove(straightSpeed);
        motor6.motorMove(straightSpeed);
       break;

       case 'B':
        motor1.motorMoveB(straightSpeed);
        motor2.motorMoveB(straightSpeed);
        motor3.motorMoveB(straightSpeed);
        motor4.motorMoveB(straightSpeed);
        motor5.motorMoveB(straightSpeed);
        motor6.motorMoveB(straightSpeed);
       break;

        case 'L':
        // Turn left
        // Stop all motors
          stop_motors();
          // Move the servos left
          servo1.write(120);
          servo2.write(60);
          servo3.write(120);
          servo4.write(60);
        break;
      case 'R':
        // Turn right
        // Stop all motors
          stop_motors();
          // Move the servos right
          servo1.write(60);
          servo2.write(120);
          servo3.write(60);
          servo4.write(120);
        break;

       case 'N':
          ninty();
         break;

       default:
        // Stop all motors for unknown commands
        stop_motors();
        break;
    }
  }
}

void ninty() {
    // Turn right
    stop_motors();
    servo1.write(90); // Move servo1 to the right position
    servo2.write(90); // Move servo2 to the right position
    servo3.write(90); // Move servo3 to the right position
    servo4.write(90); // Move servo4 to the right position
}


void stop_motors() {
  // Stop all DC motors
  motor1.stop_it();
  motor2.stop_it();
  motor3.stop_it();
  motor4.stop_it();
  motor5.stop_it();
  motor6.stop_it();
}