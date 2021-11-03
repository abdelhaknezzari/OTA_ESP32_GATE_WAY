#include <stdint.h>
#include <MicroTuple.h>

class AcceleroMPU6050
{

    const int MPU_addr = 0x68;

    int minVal = 265;
    int maxVal = 402;

public:
    void init();

    MicroTuple<double, double, double> read();

    void print();
};

