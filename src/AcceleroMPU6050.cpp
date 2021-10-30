#include "Wire.h"
#include "AcceleroMPU6050.h"
#include "MicroTuple.h"
#include <Update.h>

void AcceleroMPU6050::init() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
};

MicroTuple<double, double, double>  AcceleroMPU6050::read() {
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


double x,
 y,
 z;

      Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, 1);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);


  return {x, y, z};

}

void AcceleroMPU6050::print() {

    MicroTuple<double, double, double>   accelor = read() ;
      Serial.print("AngleX= ");
  Serial.println((double)accelor.get<0>(), 2);
  Serial.print("AngleY= ");
  Serial.println((double)accelor.get<1>(), 2);
  Serial.print("AngleZ= ");
  Serial.println((double)accelor.get<2>(), 2);
  Serial.println("-----------------------------------------");

}