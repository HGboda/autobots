#include <iostream>
#include "mbed.h"
#include "rtos.h"
#include "HMC5843.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "shared.h"

class imu_9dof{
    
    public:
    imu_9dof();    
    imu_9dof(PinName Rx, PinName Tx);    
    std::string getAcclr();
    std::string getMagnt();
    std::string getGyro();

private:

    std::string intToString(int* reading, unsigned N);
    
HMC5843 cmp;
ADXL345 acc;
ITG3200 gyr;    

};

    void getImuValues(void const *);
    void getImuValues();
