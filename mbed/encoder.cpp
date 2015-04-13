#include "encoder.h"

volatile int r_count=0;
volatile int l_count=0;
int prev_r_count=0;
int prev_l_count=0;
int delta_l = 0;
int delta_r = 0;

int prev_display_l = 0;
int prev_display_r = 0;
int display_l = 0;
int display_r = 0;

float rate = 1; // rate is 0.9 by default
float display_rate = 1;

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

void displayEncoderTicks()
{
    display_l = l_count - prev_display_l;
    display_r = r_count - prev_display_r;
    prev_display_l = l_count;
    prev_display_r = r_count;//19.182 counts/inch
//    pc.printf("in 1000ms, l: %d, r: %d \n", delta_l, delta_r);
//    rate = get_ratio(delta_l, delta_r);
//    pc.printf("overall, l: %d, r: %d \n", l_count, r_count);
    led4 = !led4;
    display_rate = get_ratio(display_l, display_r);
}

void setInitPoint(){
    prev_l_count = l_count;
    prev_r_count = r_count;//19.182 counts/inch

}

void getEncoderTicks()
{
    delta_l = l_count - prev_l_count;
    delta_r = r_count - prev_r_count;
//    prev_l_count = l_count;
//    prev_r_count = r_count;//19.182 counts/inch
//    pc.printf("in 1000ms, l: %d, r: %d \n", delta_l, delta_r);
    rate = get_ratio(delta_l, delta_r);
//    pc.printf("overall, l: %d, r: %d \n", l_count, r_count);
//    led4 = !led4;
}

// handle encoder inputs, store in r_count, l_count
void right_slit(){  
    led1 = !led1;
    r_count+=1;
    }
void left_slit(){
//    pc.printf("SHIT I SEE LEFT SPIN\n");
    led2 = !led2;
    l_count+=1;
    }

void reset_odo(){
    __disable_irq();
    l_count=0;
    r_count=0;
    __enable_irq();
    prev_r_count=0;
    prev_l_count=0;
}

//int getEncoder_left(){
//    return delta_l;
//}
//
//int getEncoder_right(){
//    return delta_r;
//}
//
//float getEncoder_ratio(){
//    return rate;    
//}
//void updateEncoder() {
    //reset_odo();
//    right_encoder.fall(right_slit);
//    left_encoder.fall(left_slit);
//    pc.printf("encoder init.\n");
//    ticker.attach(&getEncoderTicks, 1);
    
//    while(1){    
//    getEncoderTicks();
//    pc.printf("encoder: ratio = %f\r\n", rate);
//    pc.printf("encoder: left = %d, right = %d\r\n", l_count, r_count);
//    Thread::wait(1000);
//    }
//}

