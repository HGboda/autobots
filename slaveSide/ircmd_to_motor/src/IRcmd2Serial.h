
#include <iostream>
#include <string>
#include <signal.h>
#include <boost/regex.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Serial_Connect.h"
#include <std_msgs/Int8.h>


class IRcmd2Serial
{
public:
	IRcmd2Serial(std::string port, unsigned int baud_rate, unsigned long time_out );
	~IRcmd2Serial(){};
	void transmitMessage(char c);
	void listen_for_command();
	void controlCallback(const std_msgs::String::ConstPtr& msg);
private:

	ros::NodeHandle nh_;
	std_msgs::Int8 velocity;
	ros::Publisher twist_pub_;
	Serial_Connect	Sc;
	static const char IRCODE_R 		= 0x33;
	static const char IRCODE_L 		= 0x34;
	static const char IRCODE_F 		= 0x31;
	static const char IRCODE_B 		= 0x32;
	static const char IRCODE_S 		= 0x30;
		
};
