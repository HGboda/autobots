#include "mbed.h"
#include "rtos.h"
#include "driver.h"
//#include "ir.h"
//#include "zigbee.h"
#include "encoder.h"
#include "shared.h"
// #include "HMC5843.h"
// #include "ADXL345.h"
// #include "ITG3200.h"

// // Serial port for showing RX data. (imu)
// HMC5843 cmp(p28, p27);      // sda, scl
// ADXL345 acc(p28, p27);      // sda, scl
// ITG3200 gyr(p28, p27);      // sda, scl

Ticker ticker_encoder;
Ticker ticker_forward_sup;

int main (void)
{
    pc.baud(115200);
    reset_odo();
    right_encoder.fall(right_slit);
    left_encoder.fall(left_slit);
    pc.printf("encoder init.\n");
    ticker_encoder.attach_us(&displayEncoderTicks, 3000000);
//    ticker_forward_sup.attach_us(&forward_sup, 600000);
//    Thread t1(receive_command);
//    Thread t2(read_ir);
    Thread t3(motor_controller);
//    Thread t4(updateEncoder);


    
//    pc.printf("Line Following Starts");
    // int readings[3];
    // int final[9];
    // char buffer[3];

    // cmp.setDefault();
    // wait(0.1);

 #if 0
       cmp.getAddress(buffer);
    if (acc.setPowerControl(0x00)){
         return 0;  }
    wait(.001);

       if(acc.setDataFormatControl(0x0B)){
        return 0;  }
    wait(.001);
    if(acc.setDataRate(ADXL345_3200HZ)){
        return 0;    }
     wait(.001);
    if(acc.setPowerControl(MeasurementMode)) {
        return 0;   } 
    pc.printf("Acc Id=%x \n\r", acc.getDeviceID());
    gyr.setLpBandwidth(LPFBW_256HZ);
    wait(1);
       
    while(1) 
        {

            cmp.readData(readings);
            final[0] = (int16_t)readings[0];
            final[1] = (int16_t)readings[1];
            final[2] = (int16_t)readings[2];
            wait(0.05);

            acc.getOutput(readings);
            final[3] = (int16_t)readings[0];
            final[4] = (int16_t)readings[1];
            final[5] = (int16_t)readings[2];
            wait(0.05);
            
            final[6] = (int16_t)gyr.getGyroX();
            final[7] = (int16_t)gyr.getGyroY();
            final[8] = (int16_t)gyr.getGyroZ();

            pc.printf("B %+4i %+4i %+4i %+5i %+5i %+5i %+5i %+5i %+5i E \r\n",final[0],final[1],final[2],final[3],final[4],final[5],final[6],final[7],final[8]);
            wait(0.05);

        }    
#else
while(1){
    pc.printf("main: rate = %f\n", display_rate);
    pc.printf("main: left = %d\n", display_l);
    pc.printf("main: right = %d\n", display_r);
    Thread::wait(3000);
    };
#endif
}

