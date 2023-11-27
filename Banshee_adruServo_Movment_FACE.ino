#include <Servo.h>
#include <Wire.h>

Servo myservo1;
Servo myservo2;

int servo1_current_pos = 140; // Initial positions
int servo2_current_pos = 90;

void setup() {
  Serial.begin(9600);
  myservo1.attach(10);
  myservo2.attach(9);
  myservo1.write(140); // 
  //myservo2.write(10); // 

  delay(50);
}

void loop() {
  // Uncomment the function you want to use
  ReadSerial();
 }

void ReadSerial() {
  if (Serial.available() > 0) {
    char received_string[4] = {'0', '0', '3', 'w'};
    char command = Serial.read();

    if (command == 'a') {
      for (int i = 0; command != 'z' && i < 4; i++) {
        if (Serial.available() > 0) {
          command = Serial.read();
          received_string[i] = command;
        }
      }
    }

    delay(1);

    int servo_id = received_string[0] - '0'; // Change datatype from char to integer

    if (received_string[1] == '8') {
      servo1_current_pos = servo1_current_pos -3;
    }
    if (received_string[1] == '2') {
      servo1_current_pos = servo1_current_pos +3;
    }
    if (received_string[1] == '4') {
      servo2_current_pos = servo2_current_pos -3;
    }
    if (received_string[1] == '6') {
      servo2_current_pos = servo2_current_pos +3;
    }

    if (servo_id == 0) {
      myservo1.write(servo1_current_pos); // Move servo Y
    }
    delay(20);
    if (servo_id == 1) {
      myservo2.write(servo2_current_pos); // Move servo X
    
    }
  }
}
 
