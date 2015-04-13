#include "driver.h"
#define PERIOD 0.02 // duration time the motor runs

/*Interrupt handler*/
//Ticker ticker_movement;
Ticker ticker_sup;

int command = 0;
int percent = 100;
int old_command = -1;  
volatile int flag = 0; 

void brake(){
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    Right_Forward   = 1;
    Right_Backward  = 1;
    Right_Enable    = 1;
    Left_Forward    = 1;
    Left_Backward   = 1;
    Left_Enable     = 1;
    Standby = 0;
    old_command = 0;
    }


void forward(){
//    delay_rw.lock();
    float duty = percent/ 100. ;
//    delay_rw.unlock();
    led1 = !led1;
    Standby = 1;
    Right_Forward   = 1;
    Right_Backward  = 0;
    Right_Enable.period(PERIOD);
    Right_Enable.write(duty);
    Left_Forward    = 1;
    Left_Backward   = 0;
    //Left_Enable     = 1;
    Left_Enable.period(PERIOD);
    Left_Enable.write(duty);
    old_command = 1;
//    wait(delay);
//    brake();
    }
void back(){
    led2 =!led2;
    Standby = 1;
//    delay_rw.lock();
    float duty = percent/ 100.;
//    delay_rw.unlock();
    Right_Forward   = 0;
    Right_Backward  = 1;
    Right_Enable.period(PERIOD);
    Right_Enable.write(duty);
    Left_Forward    = 0;
    Left_Backward   = 1;
    Left_Enable.period(PERIOD);
    Left_Enable.write(duty);
    old_command = 2;
//    wait(delay);
//    brake();
     }
     
void left(){
    led3 =!led3;
    Standby = 1;
//    delay_rw.lock();
    float duty = percent/ 100.;
//    delay_rw.unlock();
    Right_Forward   = 1;
    Right_Backward  = 0;
    Right_Enable.period(PERIOD);
    Right_Enable.write(duty);
    Left_Forward    = 1;
    Left_Backward   = 0;
    Left_Enable.period(PERIOD);
    Left_Enable.write(duty/3.);
    old_command = 3;
//    wait(delay);
//    brake();
    }
    
void right(){
    led4 =!led4;
    Standby = 1;
//    delay_rw.lock();
    float duty = percent/ 100.;
//    delay_rw.unlock();
    Right_Forward   = 1;
    Right_Backward  = 0;
    Right_Enable.period(PERIOD);
    Right_Enable.write(duty/3.);
    Left_Forward    = 1;
    Left_Backward   = 0;
    Left_Enable.period(PERIOD);
    Left_Enable.write(duty);
    old_command = 4;
//    wait(delay);
//    brake();
    }

void stop(){
//    ticker_movement.detach();
//    ticker_sup.detach();
    brake();
    // set encoder prev to current value
//    setInitPoint();
//    old_command = 0;
    }

void former_move(int command){
    switch(command) {
        case 1:
        forward();
        break;
        case 2:
        back();
        break;
        case 3:
        left();
        break;
        case 4:
        right();
        break;
        }
    }


void forward_sup() { // need to run periodically
    
    int current_cmd = old_command;
//    pc.printf("COMMAND NOW: %d\n", current_cmd);
    if (current_cmd == 1) {
        led3 = !led3;
        // forward
        getEncoderTicks();
        setInitPoint(); // set prev
        float ratio = rate; // get ratio from encoder class
//        pc.printf("initial ratio= %f\n", ratio);
        int i = 0;
        for ( i = 0; i < 5; i++ ) {
            if (ratio < 1.05 && ratio > 0.95) {
                break;
            } else if (ratio >= 1.05) {
                left();
                wait(0.1);
            } else {
                // leaning left
                right();
                wait(0.1);   
            }
            // update rate
            getEncoderTicks();
            ratio = rate; // update ratio
        }// end for loop
        // reset start point here
        setInitPoint();
        forward();
    }// end if current_cmd
    else {
        setInitPoint();
    }
    
}


void updateMovement()
{
        if (flag != 0){
        switch (command) {
            case 0:     // stop
                stop();
                break;
            case 1:     // move forward
                stop();
                forward();
//                float encoder_rate = rate;
//                pc.printf("driver: get ratio=%f\r\n", encoder_rate);
//                forward_sup();
//                ticker_sup.attach_us(&forward_sup, 1000000); // 1s
//                ticker_movement.attach_us(&forward,11000);
                break;
            case 2:     // move back
                stop();
                back();
//                ticker_movement.attach_us(&back,11000);
                break;
            case 3:     //turn left
                stop();
                left();
//                ticker_movement.attach_us(&left,11000);
//                supp_movement.attach_us(&left_sup, 11000);
                break;
            case 4:     //turn right
                stop();
                right();
//                ticker_movement.attach_us(&right,11000);
                break;
            case 5:
//                delay_rw.lock();
                if ( percent == 100 ) {
                    // maximum speed
                    pc.printf("Already Maximum Speed.\n");
                } else {
                    percent += 5;
                    pc.printf("Increase to %d%%\n", percent);
                }
//                delay_rw.unlock();
                
                former_move(old_command);
                
                break;
            case 6:
//                delay_rw.lock();
                if ( percent == 10 ) {
                    // minimum speed
                    pc.printf("Already Minimum Speed.\n");
                } else {
                    percent -= 5;
                    pc.printf("Decrease to %d%%\n", percent);
                }
//                delay_rw.unlock();
                
                former_move(old_command);
                break;
            default:
                stop();
                break;
        }
            flag = 0;
        }

}

 void movementControl(Int8& velocity_msg)
 {
     if((velocity_msg.data >= 0) && (velocity_msg.data <= 6))
     {
         command     = velocity_msg.data;
         flag = 1;
         // pc.printf("coming here");
     }
 }


void motor_controller(void const *)
{
    brake();
    // set standby to high
    Standby = 1;
    // forward self_adjustment    
    while(1) {
        // motor_receive_command();
        if(pc.readable())
        {
            Int8 velocity_msg;
            velocity_msg.data = pc.getc() - '0';
            movementControl(velocity_msg);
             pc.printf("I got %d\n",velocity_msg.data);
        }
        updateMovement();
        Thread::wait(10); // control frequency
    }
}