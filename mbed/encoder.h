#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"

#define COUNTS_PER_INCHES 19.1822 //after experiment
#define TWO_PI 6.2831853
#define WHEEL_BASE 0.013 //13cm//to be verified by measurement

// read encoder data
static InterruptIn left_encoder(p25);
static InterruptIn right_encoder(p24);

extern float rate;
extern float display_rate;
extern int display_l;
extern int display_r;

void setInitPoint();
void displayEncoderTicks();
void getEncoderTicks();
void reset_odo();
void left_slit();
void right_slit();
float get_ratio(int left, int right);
//int getEncoder_left();
//int getEncoder_right();
//float getEncoder_ratio();
//void updateEncoder();

#endif