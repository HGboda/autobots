
#include <iostream>
#include <string>
#include <signal.h>
#include <boost/regex.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Serial_Connect.h"
#include <std_msgs/Int8.h>


class control2Serial
{
public:
	control2Serial(std::string port, unsigned int baud_rate, unsigned long time_out );
	~control2Serial(){};
	void transmitMessage(char c);
	void listen_for_command();
	void controlCallback(const std_msgs::String::ConstPtr& msg);
private:

	ros::NodeHandle nh_;
	std_msgs::Int8 velocity;
	ros::Publisher twist_pub_;
	Serial_Connect	Sc;
	static const char KEYCODE_R 		= 0x43;
	static const char KEYCODE_L 		= 0x44;
	static const char KEYCODE_F 		= 0x41;
	static const char KEYCODE_B 		= 0x42;
	static const char KEYCODE_SPACE		= 0x20;
	static const char KEYCODE_a             = 0x61;
	static const char KEYCODE_d             = 0x64;
		
};
