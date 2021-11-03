#include "Wire.h"
#include "MicroTuple.h"


class RobotMasterI2C {
   
   public:
   void init();
   void send( double accelX, double accelY, double accelZ, double obstacleDistanceR);
   void sendSensors();


};

