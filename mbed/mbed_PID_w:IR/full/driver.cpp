#include "driver.h"
#define PERIOD 50 // 50 us duration time the motor runs
#define RATE 0.01 // PID calculation interval
#define NINETY_DEGREE_COUNTS 35
//PID controller
//Kc, Ti, Td, RATE
// 0.65, 0.7, 0 works fine for straight line without adjusting but not smooth
#define Kc  0.65
#define Ti  0.15
#define Td  0

PID controller_left(Kc, Ti, Td, RATE);
PID controller_right(Kc, Ti, Td, RATE);
//PID controller_diff(Kc, Ti, Td, RATE);
int goal = 18; // PID Set velocity to reach

Ticker ticker_movement;
bool pid_turn = false;
bool driveStraight = false;
int command = 0;
int percent = 100;
int old_command = -1;  
volatile int flag = 0; 

void driver_init() {
    
    // PID initialization
    controller_left.setInputLimits(0, 35); // 30 counts/second at full speed
    controller_left.setOutputLimits(0.0, 1.0); // pwm duty cycle
    controller_left.setBias(0.0); 
    controller_left.setMode(AUTO_MODE);

    controller_right.setInputLimits(0, 35);
    controller_right.setOutputLimits(0.0, 1.0);
    controller_right.setBias(0.0);
    controller_right.setMode(AUTO_MODE);
    
    brake();
}

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
    ticker_movement.detach();
    }


void forward(){
    
//    float duty = percent/ 100. ;
    led1 = !led1;
    float leftSpeed = left_speed;
    float rightSpeed = right_speed;
        // drive straight
    if (driveStraight) {
        float diff = leftSpeed - rightSpeed;
        int count = 0;
        if (diff > 5 && count < 1 && rightSpeed > 9) {
            controller_left.setSetPoint(goal - 0.5);
            controller_right.setSetPoint(goal);
            count++;
        } else if (diff < -5 && count < 1 && leftSpeed > 9) {
            controller_left.setSetPoint(goal);
            controller_right.setSetPoint(goal - 0.5);
            count++;
        } else {
            // do nothing
            if (count > 1 || count == 0){
                controller_left.setSetPoint(goal);
                controller_right.setSetPoint(goal - 0.2);
                count = 0;
            } else {
                count++;
            }
        }     
    } else {
        controller_left.setSetPoint(goal);
        controller_right.setSetPoint(goal);
    }
    controller_left.setProcessValue(leftSpeed);
    controller_right.setProcessValue(rightSpeed);
    float rightDuty = controller_right.compute();
    float leftDuty = controller_left.compute();

//        // debug
//        float rightDuty = 0.9;
//        float leftDuty = 0.9;        
        
        // set value
        Standby = 1;
        Right_Forward   = 0;
        Right_Backward  = 1;
        Right_Enable.period_us(PERIOD);
        //Right_Enable.write(duty);
        Right_Enable.write(rightDuty);
        Left_Forward    = 0;
        Left_Backward   = 1;
        //Left_Enable     = 1;
        Left_Enable.period_us(PERIOD);
        //Left_Enable.write(duty);
        Left_Enable.write(leftDuty);
        old_command = 1;
}

void back(){
    led2 =!led2;
    Standby = 1;
//    delay_rw.lock();
    float duty = 0.9 * percent/ 100.0;
//    delay_rw.unlock();
    Right_Forward   = 1;
    Right_Backward  = 0;
    Right_Enable.period_us(PERIOD);
    Right_Enable.write(duty);
    Left_Forward    = 1;
    Left_Backward   = 0;
    Left_Enable.period_us(PERIOD);
    Left_Enable.write(duty);
    old_command = 2;
//    wait(delay);
//    brake();
     }
     
void left(){
    led3 =!led3;
    float leftDuty = 0;
    float rightDuty = 0;
    if (pid_turn) {
    //    delay_rw.lock();
//    float duty = percent/ 100.;
//    delay_rw.unlock();
//    int pulseCount = NINETY_DEGREE_COUNTS;
//    int base = leftTotalTicks - rightTotalTicks;
    controller_right.setSetPoint(goal);
    controller_left.setSetPoint(goal/3.0);
//    int startTicksLeft = leftTotalTicks;
//    int startTicksRight = rightTotalTicks;
//    float leftDuty = 0.8;
//    float rightDuty = 0.8;
// turn 90 degrees
//    while(( rightTotalTicks + leftTotalTicks - startTicksLeft - startTicksRight) < (pulseCount + base)) {
    controller_right.setProcessValue(right_speed);
    rightDuty = controller_right.compute();
    controller_left.setProcessValue(left_speed);
    leftDuty = controller_left.compute();
    } else {
        leftDuty = 0.3;
        rightDuty = 0.9;
    }
    
//        pc.printf("PID::> leftDuty: %f\r\n", leftDuty);
//        pc.printf("PID::> rightDuty: %f\r\n", rightDuty);
        // set motor value
    Standby = 1;
    Right_Forward   = 0;
    Right_Backward  = 1;
    Right_Enable.period_us(PERIOD);
    Right_Enable.write(rightDuty);
    //Right_Enable.write(duty);
    Left_Forward    = 0;
    Left_Backward   = 1;
    Left_Enable.period_us(PERIOD);
    Left_Enable.write(leftDuty);
    //Left_Enable.write(duty/3.);
    old_command = 3;    
    //wait_ms(50);
//}
//    stop(); //reset odom
}
    
void right(){
    led4 =!led4;
    Standby = 1;
    float leftDuty = 0;
    float rightDuty = 0;
    if (pid_turn){
//    delay_rw.lock();
//    float duty = percent/ 100.;
//    delay_rw.unlock();
//    int pulseCount = NINETY_DEGREE_COUNTS;
//    int base = rightTotalTicks - leftTotalTicks;
    controller_right.setSetPoint(goal/3.0);
    controller_left.setSetPoint(goal);
//    int startTicksLeft = leftTotalTicks;
//    int startTicksRight = rightTotalTicks;
////        // debug
//    float leftDuty = 0.8;
//    float rightDuty = 0.8;

//    while(( rightTotalTicks + leftTotalTicks - startTicksLeft - startTicksRight) < (pulseCount + base)) {
        controller_right.setProcessValue(right_speed);
        rightDuty = controller_right.compute();
        controller_left.setProcessValue(left_speed);
        leftDuty = controller_left.compute();
//        pc.printf("PID::> leftDuty: %f\r\n", leftDuty);
//        pc.printf("PID::> rightDuty: %f\r\n", rightDuty);
    } else {
        leftDuty = 0.9;
        rightDuty = 0.3;
    }
        // set motor value
        Standby = 1;
        Right_Forward   = 0;
        Right_Backward  = 1;
        Right_Enable.period_us(PERIOD);
        Right_Enable.write(rightDuty);
        //Right_Enable.write(duty);
        Left_Forward    = 0;
        Left_Backward   = 1;
        Left_Enable.period_us(PERIOD);
        Left_Enable.write(leftDuty);
        //Left_Enable.write(duty/3.);
        old_command = 4;
//        wait_ms(50);
//    }
//    stop(); //reset odom
}

void stop(){
//    ticker_sup.detach();
    brake();
    // set encoder prev to current value
    //    setInitPoint();
    controller_left.reset();
    controller_right.reset();
    reset_odo();

}

//void former_move(int command){
//    switch(command) {
//        case 1:
//        forward();
//        break;
//        case 2:
//        back();
//        break;
//        case 3:
//        left();
//        break;
//        case 4:
//        right();
//        break;
//        }
//    }


void updateMovement()
{
        if (flag != 0){
        switch (command) {
            case 0:     // stop
                stop();
                break;
            case 1:     // move forward
//                brake();
                ticker_movement.detach();
                reset_odo();
//                forward();
//                float encoder_rate = rate;
//                pc.printf("driver: get ratio=%f\r\n", encoder_rate);
//                forward_sup();
//                ticker_sup.attach_us(&forward_sup, 1000000); // 1s
                ticker_movement.attach_us(&forward,100000); // 50 ms
                break;
            case 2:     // move back
//                brake();
//                back();
                ticker_movement.detach();
                ticker_movement.attach_us(&back,50000);
                break;
            case 3:     //turn left
//                brake();
//                left();
                ticker_movement.detach();
                ticker_movement.attach_us(&left,50000);
//                supp_movement.attach_us(&left_sup, 11000);
                break;
            case 4:     //turn right
//                brake();
//                right();
                ticker_movement.detach();
                ticker_movement.attach_us(&right,50000);
                break;
            case 5:
//                delay_rw.lock();
                if ( percent == 100 ) {
                    // maximum speed
                    pc.printf("Already Maximum Speed.\n");
                } else {
                    percent += 5;
                    goal = (int) 18 * percent/100.0;
                    pc.printf("Increase to %d%%\n", percent);
                }
//                delay_rw.unlock();
                
//                former_move(old_command);
                
                break;
            case 6:
//                delay_rw.lock();
                if ( percent == 10 ) {
                    // minimum speed
                    pc.printf("Already Minimum Speed.\n");
                } else {
                    percent -= 5;
                    goal = (int) 18 * percent/100.0;
                    pc.printf("Decrease to %d%%\n", percent);
                }
//                delay_rw.unlock();
                
//                former_move(old_command);
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