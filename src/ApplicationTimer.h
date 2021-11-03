#include <Arduino.h>
#include <Vector.h>

#include "RobotMasterI2C.h"
#include "RobotServer.h"

class ApplicationTimer
{
   const uint64_t ALARM_VALUE = 2000000;

   hw_timer_t *timer = timerBegin(0, 80, true);

   typedef void (*CustomFunction)();

   Vector<CustomFunction> functions;

   portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

   void toggleLed();
   void muxIn();
   void muxOut();
   void initTimer();

public:
   void init();
   void handleTimer();
   void attachFunction(CustomFunction fcnt);
};

ApplicationTimer applicationTimer;
RobotMasterI2C robotMasterI2C;
RobotServer robotServer;

void ApplicationTimer::attachFunction(CustomFunction fcnt)
{
   functions.push_back(fcnt);
}
void ApplicationTimer::initTimer()
{
   timerAttachInterrupt(
       timer, []()
       { applicationTimer.handleTimer(); },
       true);
   timerAlarmWrite(timer, ALARM_VALUE, true);
   timerAlarmEnable(timer);
}

void ApplicationTimer::init()
{

   this->initTimer();

   robotMasterI2C.init();
   robotServer.init();

   this->attachFunction([]()
                        { robotMasterI2C.sendSensors(); });
   this->attachFunction([]()
                        { robotServer.refresh(); });
}

void ApplicationTimer::toggleLed()
{
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void ApplicationTimer::handleTimer()
{
   this->muxIn();

   for (auto attachedFunction : this->functions)
   {
      attachedFunction();
      delay(10);
   }

   this->toggleLed();
   this->muxOut();
}

void ApplicationTimer::muxIn()
{
   portENTER_CRITICAL_ISR(&this->timerMux);
}

void ApplicationTimer::muxOut()
{
   portEXIT_CRITICAL_ISR(&this->timerMux);
}