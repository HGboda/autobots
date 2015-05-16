#ifndef __IR_H__
#define __IR_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"

#define FORWARD     1
#define BACKWARD    2
#define LEFT        3
#define RIGHT       4
#define STOP        0

// ir read
static AnalogIn   ir_left(p19);
static AnalogIn   ir_middle(p18);
static AnalogIn   ir_right(p17);


// function
void read_ir(void const *);

#endif