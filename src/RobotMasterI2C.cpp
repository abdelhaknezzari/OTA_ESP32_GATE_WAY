#include "RobotMasterI2C.h"
#include "AcceleroMPU6050.h"
#include "SharpGP2Y0E02B.h"
#include <Update.h>

SharpGP2Y0E02B distanceInfrared;
AcceleroMPU6050 acceleroMPU6050;

void RobotMasterI2C::init()
{
    Wire.begin();
    acceleroMPU6050.init();
    distanceInfrared.init();
}

void RobotMasterI2C::send(double accelX, double accelY, double accelZ, double obstacleDistanceR)
{

    Wire.beginTransmission(4); // transmit to device #4
    char buffer[60];
    sprintf(buffer, "%f,%f,%f,%f", accelX, accelY, accelZ, obstacleDistanceR);

    Serial.println(buffer);

    Wire.write(buffer);     // sends one byte
    Wire.endTransmission(); // stop transmitting
}

void RobotMasterI2C::sendSensors()
{
    MicroTuple<double, double, double> accelo = acceleroMPU6050.read();

    send(accelo.get<0>(), accelo.get<1>(), accelo.get<2>(), distanceInfrared.read());
}