// ROS control with keyboard over mbed
/*
  use arrow keys to control movement: 
    up---straight
    down---back
    right---turn right
    left---turn left
    a---accelerate
    d---decelerate
    other keys: stop
*/

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_F 0x41
#define KEYCODE_B 0x42
#define KEYCODE_SPACE 0x20
#define KEYCODE_a 0x61 
#define KEYCODE_d 0x64
class TeleopCar
{
public:
  TeleopCar();
  void keyLoop();

private:
  ros::NodeHandle nh_;
  std_msgs::String msg;
  ros::Publisher twist_pub_;
  
};

TeleopCar::TeleopCar()
{
  msg.data = " ";
  twist_pub_ = nh_.advertise<std_msgs::String>("motor_control", 1);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_car");
  TeleopCar teleop_car;

  signal(SIGINT,quit);

  teleop_car.keyLoop();
  
  return(0);
}


void TeleopCar::keyLoop()
{
  char c;
  bool dirty=false;


  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the car.");


  for(;;)
    {
      // get the next event from the keyboard
      if(read(kfd, &c, 1) < 0)
	{
	  perror("read():");
	  exit(-1);
	}

      msg.data = " ";
      ROS_DEBUG("value: 0x%02X\n", c);
  
      switch(c)
	{
	case KEYCODE_L:
	  ROS_DEBUG("LEFT");
	  msg.data = "BMAIN D EMAIN";
	  std::cout << "LEFT COMMAND SENT" << std::endl;
	  dirty = true;
	  break;
	case KEYCODE_R:
	  ROS_DEBUG("RIGHT");
	  msg.data = "BMAIN C EMAIN";
	  std::cout << "RIGHT COMMAND SENT" << std::endl;
	  dirty = true;
	  break;
	case KEYCODE_F:
	  ROS_DEBUG("FORWARD");
	  msg.data = "BMAIN A EMAIN";
	  std::cout << "FORWARD COMMAND SENT" << std::endl;
	  dirty = true;
	  break;
	case KEYCODE_B:
	  ROS_DEBUG("BACK");
	  msg.data = "BMAIN B EMAIN";
	  std::cout << "BACK COMMAND SENT" << std::endl;
	  dirty = true;
	  break;

	case KEYCODE_SPACE:
	  ROS_DEBUG("STOP");
	  std::cout << "STOP COMMAND SENT" << std::endl;
	  msg.data = "BMAIN EMAIN";
	  dirty = true;
	  break;
	
	case KEYCODE_a:
	  ROS_DEBUG("ACCELERATE");
	  std::cout << "ACCELERATE COMMAND SENT" << std::endl;
	  msg.data = "BMAIN a EMAIN";
	  dirty = true;
	  break;
	
	case KEYCODE_d:
	  ROS_DEBUG("DECELERATE");
	  std::cout << "DECELERATE COMMAND SENT" << std::endl;
	  msg.data = "BMAIN d EMAIN";
	  dirty = true;
	  break;
	}
   
    
      if(dirty ==true)
	{
	  twist_pub_.publish(msg);
	  dirty=false;
	}
    }


  return;
}
