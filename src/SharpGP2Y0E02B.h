
#include <stdint.h>
class SharpGP2Y0E02B
{

  const int ADDRESS = 0x80 >> 1; // Arduino uses 7 bit addressing so we shift address right one bit
  const int DISTANCE_REG = 0x5E;
  const int SHIFT = 0x35;

  int shift = 0; // Value in shift bit register

public:
  void init();
  double read();
};
