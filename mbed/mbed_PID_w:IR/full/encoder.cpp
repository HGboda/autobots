#include "encoder.h"

//unsigned int r_count=0;
//unsigned int l_count=0;
int r_count=0;
int l_count=0;
int prev_r_count=0;
int prev_l_count=0;
int leftTotalTicks = 0;
int rightTotalTicks = 0;
int delta_l = 0;
int delta_r = 0;
float former_l = 0;
float former_r = 0;
float rate = 1;
float left_speed = 0;
float right_speed = 0;

Timer t;

float get_ratio(int left, int right) {
    // might need mutex for r/w delta_l/r
    float ratio;
    if (right != 0) {
        ratio = (float)left / right;
    } else if (left == 0) {
        ratio = 1;
    } else {
        ratio = 25;
    }
    return ratio;
    }


void updateEncoderTicks()
{
    leftTotalTicks = l_count;
    rightTotalTicks = r_count;
    delta_l = leftTotalTicks - prev_l_count;
    delta_r = rightTotalTicks - prev_r_count;
    prev_l_count = leftTotalTicks;
    prev_r_count = rightTotalTicks;
    rate = get_ratio(delta_l, delta_r);
    
    //update speed
    t.stop();
    float dt = t.read();
    left_speed = delta_l / dt; // ticks/second
    right_speed = delta_r / dt;
    t.reset();
    t.start();
//    pc.printf("time passed: %f \r\n", dt);
//    pc.printf("leftTotalTicks: %d\r\n", leftTotalTicks);
//    pc.printf("rightTotalTicks: %d\r\n", rightTotalTicks);
//    pc.printf("leftSpeed: %f\r\n", left_speed);
//    pc.printf("rightSpeed: %f\r\n", right_speed);
    /*
    std::stringstream ss;
    ss << " BENC ";
    ss << delta_l;
    ss << "@";
    ss << delta_r;
    ss << " EENC\n";
    std::string output = ss.str();
    prints(output);
    */

}

void getEncoderTicks(){
    int i = 0;
    float avg_l = 0;
    float avg_r = 0;
    for (i = 0; i < 2; i++ ){
            avg_l += left_encoder.read();
            avg_r += right_encoder.read();
            wait(0.0005f); // every 0.5 ms
        }
    avg_l = avg_l / 2.0;
    avg_r = avg_r / 2.0;
//    pc.printf("left avg: %f;  right avg: %f\r\n", avg_l, avg_r);
//    pc.printf("left former: %f;  right former: %f\r\n", former_l, former_r);
    if (fabs(avg_l - former_l) > 0.9 ) {
        if (old_command == 2 ) {
            // back
            l_count--;
        } else {
            l_count++;
        }
//        led1 = !led1;
        }
    if (fabs(avg_r - former_r) > 0.9 ) { 
        if (old_command == 2 ) {
            r_count--;
        } else {
            r_count++;
        }
//        led2 = !led2;
    }
    former_l = avg_l;
    former_r = avg_r;
    }
void reset_odo(){
    __disable_irq();
    l_count=0;
    r_count=0;
    former_l = 0;
    former_r = 0;
    __enable_irq();
    // reset vars based on encoder ticks
    prev_r_count=0;
    prev_l_count=0;
    leftTotalTicks = 0;
    rightTotalTicks = 0;
    delta_l = 0;
    delta_r = 0;
    //reset timer
    t.stop();
    t.reset();
    t.start();
}

void displayEncoderTicks(void const *) {

    while(1){
        updateEncoderTicks();
        Thread::wait(100);
    }
    
}

