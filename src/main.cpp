
#include <ESP32Servo.h>
#include "ApplicationTimer.h"


int pinServoX = 33;
Servo servoX;

int i = 0;

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

  applicationTimer.init();


}

void loop(void)
{

  delay(1);
}
