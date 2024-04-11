#include <Servo.h>
#include <Braccio.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

// Velocidad de los servos
const int servoSpeed = 10;

// Posiciones actuales de los servos
int basePos = 30;
int shoulderPos = 0;
int elbowPos = 180;
int wristVerPos = 140;
int wristRotPos = 10;
int gripperPos = 180;

bool moving = false;
char moveDirection;

void setup() {
  Serial.begin(9600);
  Braccio.begin();

  base.attach(11);
  shoulder.attach(10);
  elbow.attach(9);
  wrist_ver.attach(6);
  wrist_rot.attach(5);
  gripper.attach(3);

  // Mover todos los servos a la posición inicial
  Braccio.ServoMovement(servoSpeed, basePos, shoulderPos, elbowPos, wristVerPos, wristRotPos, gripperPos);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'P') {
      moving = false;
    } else {
      moving = true;
      moveDirection = command;
    }
  }

  if (moving) {
    switch (moveDirection) {
      case 'A': // Mover base +1 grado
        basePos = min(basePos + 1, 180);
        break;
      case 'D': // Mover base -1 grado
        basePos = max(basePos - 1, 0);
        break;
      case 'W': // Mover hombro +1 grado
        shoulderPos = min(shoulderPos + 1, 180);
        break;
      case 'S': // Mover hombro -1 grado
        shoulderPos = max(shoulderPos - 1, 15);
        break;
      case 'E': // Mover codo +1 grado
        elbowPos = min(elbowPos + 1, 180);
        break;
      case 'Q': // Mover codo -1 grado
        elbowPos = max(elbowPos - 1, 0);
        break;
      case 'R': // Mover muñeca vertical +1 grado
        wristVerPos = min(wristVerPos + 1, 180);
        break;
      case 'F': // Mover muñeca vertical -1 grado
        wristVerPos = max(wristVerPos - 1, 0);
        break;
      case 'T': // Mover muñeca rotación +1 grado
        wristRotPos = min(wristRotPos + 1, 180);
        break;
      case 'G': // Mover muñeca rotación -1 grado
        wristRotPos = max(wristRotPos - 1, 0);
        break;
      case 'H': // Abrir gripper +1 grado
        gripperPos = max(gripperPos + 1, 180);
        break;
      case 'Y': // Cerrar gripper -1 grado
        gripperPos = min(gripperPos - 1, 0);
        break;
    }

    // Mover los servos a las nuevas posiciones
    Braccio.ServoMovement(servoSpeed, basePos, shoulderPos, elbowPos, wristVerPos, wristRotPos, gripperPos);
  }

delay(10);
}
