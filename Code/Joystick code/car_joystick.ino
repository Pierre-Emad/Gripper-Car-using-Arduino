#include <SoftwareSerial.h>

/* initiate serial port at pins 2 and 3 */
SoftwareSerial BTSerial(2, 3); 

#define JOYSTICK_LOWER_BOUND  350
#define JOYSTICK_HIGHER_BOUND 700

const int xPinServo = A0;
const int yPinServo = A1;
const int xPinCar = A2;
const int yPinCar = A3;
int xValueCar, yValueCar, xValueServo, yValueServo;
unsigned char move, prev_move;

void setup() 
{
  Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop() {
  /* Read the analog values from the joystick */
  xValueCar = analogRead(xPinCar);
  yValueCar = analogRead(yPinCar);
  xValueServo = analogRead(xPinServo);
  yValueServo = analogRead(yPinServo);
  
  /* if car joystick is connected to 3.3v --> lower resolution, we need to change the range 
   * leave it commented if you connect all modules on 5v */
//  xValueCar = map(xValueCar, 0, 671, 0, 1023);
//  yValueCar = map(yValueCar, 0, 671, 0, 1023);

  car_control();  
  servo_control();
  
  move -= '0'; // bluetooth sends data in ASCII, so we convert it to a number
  BTSerial.write(move);
  if (move != prev_move)
  {
    /* print the values to the serial monitor if there is a new command */
    Serial.print("X: ");
    Serial.print(xValueCar);
    Serial.print("\tY: ");
    Serial.println(yValueCar);
    Serial.print("X: ");
    Serial.print(xValueServo);
    Serial.print("\tY: ");
    Serial.println(yValueServo);
    Serial.print("Move: ");
    Serial.println(move);
  }
  prev_move = move;

  delay(100);
}

void car_control()
{
  if (xValueCar > JOYSTICK_HIGHER_BOUND)
  {
    /* move right */
    move = '4';
  }
  else if (xValueCar < JOYSTICK_LOWER_BOUND)
  {
    /* move left */
    move = '3';
  }
  else
  {
    if (yValueCar > JOYSTICK_HIGHER_BOUND)
    {
      /* move forward */
      move = '1';
    }
    else if ( yValueCar < JOYSTICK_LOWER_BOUND )
    {
      /* move backward */
      move = '2';
    }
    else 
      move = '5'; // stop
  }
}

void servo_control()
{
  if (xValueServo > JOYSTICK_HIGHER_BOUND)
  {
    /* close gripper */
    move = '6';
  }
  else if (xValueServo < JOYSTICK_LOWER_BOUND)
  {
    /* open gripper */
    move = '7';
  }
  else
  {
    if (yValueServo > JOYSTICK_HIGHER_BOUND)
    {
      /* servo up */
      move = '9';
    }
    else if ( yValueServo < JOYSTICK_LOWER_BOUND )
    {
      /* servo down */
      move = '8';
    }
  }
}
