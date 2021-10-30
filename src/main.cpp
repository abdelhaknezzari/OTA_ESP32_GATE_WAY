
#include <ESP32Servo.h>
#include "SharpGP2Y0E02B.h"
#include "AcceleroMPU6050.h"
#include <RobotServer.h>


SharpGP2Y0E02B distanceInfrared;
AcceleroMPU6050 acceleroMPU6050;
RobotServer robotServer;

int pinServoX = 33;
Servo servoX;



/*
 * Login page
 */

void initServo()
{
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servoX.setPeriodHertz(10);
  servoX.attach(pinServoX, 50, 2400);
}


void setup(void)
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  acceleroMPU6050.init();
  distanceInfrared.init();
  robotServer.init();

}

void loop(void)
{
 
  robotServer.refresh();
  delay(1);

  acceleroMPU6050.print();
  distanceInfrared.print();

  

  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);
}
