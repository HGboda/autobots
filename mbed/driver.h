#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"
#include "encoder.h"

// control
static DigitalOut Right_Forward    (p13);
static DigitalOut Right_Backward   (p14);
//static DigitalOut Right_Enable     (p7);
static DigitalOut Left_Forward     (p11);
static DigitalOut Left_Backward    (p10);
//static DigitalOut Left_Enable      (p10);
static DigitalOut Standby          (p12); //need to be high
static PwmOut Left_Enable (p23);
static PwmOut Right_Enable (p22);
//extern float rate;

struct Int8{
 uint8_t data;
 };
 
 
//extern int old_command; 

void brake();
void forward();
void back();
void left();
void right();
void stop();
void forward_sup();
void updateMovement();
void movementControl(Int8& velocity_msg);
void motor_controller(void const *);


#endif