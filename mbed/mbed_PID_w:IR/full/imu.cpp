#include "imu.h"
#include <sstream>      // std::stringstream

    imu_9dof::imu_9dof():cmp(p28, p27),acc(p28, p27), gyr(p28, p27)
    {
     //ID Buffer
        char buffer[3];
       cmp.setDefault();
        wait(0.1);
        cmp.getAddress(buffer);
        if (acc.setPowerControl(0x00)){
        exit(0);
        }
        wait(.001);
        
        if(acc.setDataFormatControl(0x0B)){
        exit(0);
        }
        wait(.001);
         
        if(acc.setDataRate(ADXL345_3200HZ)){
        exit(0);
        }
        wait(.001);
         
        if(acc.setPowerControl(MeasurementMode)) {
        exit(0);
        } 
        gyr.setLpBandwidth(LPFBW_256HZ);
        wait(1);
        
        
    }
    imu_9dof::imu_9dof(PinName Tx, PinName Rx):cmp(Tx, Rx),acc(Tx, Rx),gyr(Tx, Rx)
    {
      //ID Buffer
        char buffer[3];
       cmp.setDefault();
        wait(0.1);
        cmp.getAddress(buffer);
        if (acc.setPowerControl(0x00)){
        exit(0);
        }
        wait(.001);
        
        if(acc.setDataFormatControl(0x0B)){
        exit(0);
        }
        wait(.001);
         
        if(acc.setDataRate(ADXL345_3200HZ)){
        exit(0);
        }
        wait(.001);
         
        if(acc.setPowerControl(MeasurementMode)) {
        exit(0);
        } 
        gyr.setLpBandwidth(LPFBW_256HZ);
        wait(1);
        
       
    }


    std::string imu_9dof::getAcclr()
    {
        int readings[3];
        cmp.readData(readings);
        wait(0.05);
        return imu_9dof::intToString(readings,3);
    }
    
    std::string imu_9dof::getMagnt()
    {
        int readings[3];
        acc.getOutput(readings);
        wait(0.05);
        return imu_9dof::intToString(readings,3);
        
    }

    std::string imu_9dof::getGyro()
    {
        int readings[3];
        readings[0] = gyr.getGyroX();
        readings[1] = gyr.getGyroY();
        readings[2] = gyr.getGyroZ();
        wait(0.05);
        return imu_9dof::intToString(readings,3);        
    }
    
    std::string imu_9dof::intToString(int* reading, unsigned N)
    {
        std::string s ;
        for (int i = 0 ; i < N ; i ++)
        {
            std::stringstream ss;
            ss << (int16_t)reading[i];
            s += ss.str() + " ";
        }
       return s;
    }
    
    void getImuValues(void const *)
    {
        pc.printf("coming ");
        int i = 0;
            imu_9dof imu;
        while(true) {
            std::string output = " B " + imu.getAcclr()+ imu.getGyro() + imu.getMagnt() + " E \n";
            prints(output);
//            pc.printf( imu.getAcclr().c_str());
//            pc.printf( imu.getGyro().c_str());
//            pc.printf( imu.getMagnt().c_str());
//            pc.printf("E\n");
            //led1 = i;
//            i = !i;
            Thread::wait(100);
        }        
    }

//    void getImuValues()
//    {
//        int i = 0;
//            imu_9dof imu;
//        while(1) {
//            pc.printf("B ");
//            pc.printf( imu.getAcclr().c_str());
//            pc.printf( imu.getGyro().c_str());
//            pc.printf( imu.getMagnt().c_str());
//            pc.printf("E\n");
//            led1 = i;
//            i = !i;
//            wait(0.2);
//        }        
//    }
