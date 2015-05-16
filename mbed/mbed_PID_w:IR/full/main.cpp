#include "mbed.h"
#include "rtos.h"
#include "driver.h"
#include "encoder.h"
#include "shared.h"
#include "imu.h"
#include "ir.h"
Ticker ticker_encoder;
//Ticker ticker_forward_sup;

int main (void)
{
    pc.baud(115200);
    reset_odo();
    driver_init(); //init pid objs
    former_l = left_encoder.read();
    former_r = right_encoder.read();
    ticker_encoder.attach_us(&getEncoderTicks, 10000);
    Thread t1(motor_controller);
    Thread t2(displayEncoderTicks);
//    Thread t3(getImuValues);
    Thread t4(read_ir);
//    getImuValues();
    
    while(1){
    Thread::wait(2000);
    };
}

