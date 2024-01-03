#include <AFMotor.h>
#include <Servo.h>
#include <SoftwareSerial.h>

/* A0 is used as the shield allows only pin 2 to be used for i/o */
SoftwareSerial BTSerial(2, A0);

#define SPEED 200

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo servo_mech, servo_height;

unsigned char bt_data, servo_mech_angle, servo_height_angle;

void setup() 
{
  Serial.begin(9600);
  BTSerial.begin(38400);
  servo_mech.attach(9);  
  servo_mech.write(0);
  servo_height.attach(10);
  servo_height.write(0);
  motor1.setSpeed(SPEED);
  motor2.setSpeed(SPEED);
  motor3.setSpeed(SPEED);
  motor4.setSpeed(SPEED);
}

void loop()
{
  
  bt_data = BTSerial.read();
  Serial.println(bt_data);
  
  switch(bt_data)
  {
    case 1:
    Serial.println(bt_data);
    moveForward();
    break;
    
    case 2:
    Serial.println(bt_data);
    moveBackward();
    break;
    
    case 3:
    Serial.println(bt_data);
    moveLeft();
    break;
    
    case 4:
    Serial.println(bt_data);
    moveRight();
    break;
    
    case 5:
    Serial.println(bt_data);
    Stop();
    break;
    
    case 6: // gripper
    Serial.println(bt_data);
    if (servo_mech_angle < 80)
      servo_mech_angle += 5;
    servo_mech.write(servo_mech_angle);
    break;
    
    case 7: // gripper
    Serial.println(bt_data);
    if (servo_mech_angle >= 5)
      servo_mech_angle -= 5;
    servo_mech.write(servo_mech_angle);
    break;
    
    case 8: // tilt
    Serial.println(bt_data);
    if (servo_height_angle <= 50)
      servo_height_angle += 5;
    else
      servo_height_angle = 50; 
    servo_height.write(servo_height_angle);
    break;
    
    case 9: // tilt
    Serial.println(bt_data);
    if (servo_height_angle >= 5)
      servo_height_angle -= 5;
   else
      servo_height_angle = 0;
    servo_height.write(servo_height_angle);
    break;
  }
  delay(100);
}

/* motor movement functions */
void Stop() 
{
  Serial.println("Stop!");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveBackward() 
{
  Serial.println("Moving Backward");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void moveForward() 
{
  Serial.println("Moving Forward");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveRight() 
{
  Serial.println("Moving Right");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void moveLeft() 
{
  Serial.println("Moving Left");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
