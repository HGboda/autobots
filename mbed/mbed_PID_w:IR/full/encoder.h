#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"
#include "driver.h"

#define COUNTS_PER_INCHES 19.1822 //after experiment
#define TWO_PI 6.2831853
#define WHEEL_BASE 0.013 //13cm//to be verified by measurement

extern float rate;
extern float display_rate;
extern float former_l;
extern float former_r;
extern int leftTotalTicks;
extern int rightTotalTicks;
extern float left_speed;
extern float right_speed;

static AnalogIn left_encoder(p16);
static AnalogIn right_encoder(p20);
void updateEncoderTicks();
void getEncoderTicks();
void reset_odo();
float get_ratio(int left, int right);
void displayEncoderTicks(void const *);

#endif