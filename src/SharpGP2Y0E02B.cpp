#include "SharpGP2Y0E02B.h"
#include "Wire.h"
#include <Update.h>

void SharpGP2Y0E02B::init(){
      // Start comms
  Wire.beginTransmission(ADDRESS);    
  Wire.write(SHIFT);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 1);
  while(Wire.available() == 0);
  shift = Wire.read();

}

void SharpGP2Y0E02B::print(){
  Serial.print("obstacle distance in CM= ");
  Serial.println(read());
}

double SharpGP2Y0E02B::read(){
  int distance = 0;   // Stores the calculated distance
  
  uint8_t high, low = 0; // High and low byte of distance

 // Request and read the 2 address bytes from the GP2Y0E02B
  Wire.beginTransmission(ADDRESS);
  Wire.write(DISTANCE_REG);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 2);
  
  while(Wire.available() < 2);
  
  high = Wire.read();
  low = Wire.read();
  
  distance = (high * 16 + low)/16/(int)pow(2,shift); // Calculate the range in CM
  return distance;


}

