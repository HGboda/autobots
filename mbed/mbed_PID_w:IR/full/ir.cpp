// ir receiver
#include "ir.h"

void read_ir(void const *)
{
//    float offset = 10.0;
    int AMBIENT_IR_VALUE  = 88;
    int count = 0;
    int prev_move[3];
    prev_move[0] = 0;
    prev_move[1] = 0;
    prev_move[2] = 0;
    int action = 0;
    bool started = false;
    bool straightline = false;
    bool turn = false;
//    float avg_l = 0;
//    float avg_m = 0;
//    float avg_r = 0;
   while (1) {
        bool b_left = false;
        bool b_middle = false;
        bool b_right = false;
        float left_val   = ir_left.read()*100.0f;
        float middle_val = ir_middle.read()*100.0f;
        float right_val  = ir_right.read()*100.0f;
//        pc.printf("l = %f M = %f R = %f \r\n",left_val,middle_val,right_val);
        if(left_val > AMBIENT_IR_VALUE)
            b_left = true;
        if(middle_val > AMBIENT_IR_VALUE)
            b_middle = true;
        if(right_val > AMBIENT_IR_VALUE)
            b_right = true;

        
        if (b_left && b_middle && b_right)
        {
            action = 1;
        }
        else if(b_left && b_middle )
        {
            action = 3;
        }
        else if(b_middle && b_right)
        {
            action = 4;
        }
        else if(b_left)
        {
            action = 3;
        }
        else if(b_right)
        {
            action = 4;
        }
        else
        {
            action = 0;
        }
        
        int prev1 = (count + 2) % 3; // count - 1
        int prev2 = (count + 1) % 3; // count - 2
        int prev3 = (count + 0) % 3; // count - 3
        
        if (prev_move[prev2] == 1 && prev_move[prev3] == 1) {
            straightline = true;
        } else {
            straightline = false;
        }
        
         if ((prev_move[prev2] == 3 && prev_move[prev3] == 3) || (prev_move[prev2] == 4 && prev_move[prev3] == 4)) {
            turn = true;
        } else {
            turn = false;
        }
        
//        if (prev_move[prev1] == 1 && action == 0 && !(straightline) ) {
//            action = 2;
//        } else if (prev_move[prev1] == 1 && action == 0 && straightline ) {
//            action = 0;
//        } else if ((prev_move[prev1] == 3 || prev_move[prev1] == 4) && (action == 0) && !(straightline) && !(turn)) {
//            // during turning
//            action = prev_move[prev1];
//        } else if ((prev_move[prev1] == 3 || prev_move[prev1] == 4) && (action == 0) && !(straightline) && turn) {
//            // stop after turning
//            action = 0;
//        } else if ((prev_move[prev1] == 3 || prev_move[prev1] == 4) && (action == 0) && straightline ) {
//            action = 7 - prev_move[prev1];
//        } else {
//            // do nothing
//        }
        if ((prev_move[prev1] == 3 || prev_move[prev1] == 4) && (action == 0) && !(turn)) {
            action = prev_move[prev1];
        } 
        
        if (!straightline && (action == 0) && started && (prev_move[prev1] == 3 || prev_move[prev1] == 4) ) {
            action = 2;
        }
        
        if ((action == 0) && started && (prev_move[prev1] == 2)) {
            action = 2;
        }
        
        
        switch(action) {
            case 0:
                prints(" BIR 0 EIR \n");
                started = false;
            break;
            case 1:
                prints(" BIR 1 EIR \n");
            break;
            case 2:
                prints(" BIR 2 EIR \n");    
            break;
            case 3:
                prints(" BIR 3 EIR \n");
            break;
            case 4:
                prints(" BIR 4 EIR \n");
            break;
        }
        prev_move[count] = action;
        count++;
        count = count % 3;
        started = true;
        Thread::wait(200);
    }

}