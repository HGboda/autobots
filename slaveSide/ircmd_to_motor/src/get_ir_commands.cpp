#include "ros/ros.h"
#include "std_msgs/String.h"
#include "IRcmd2Serial.h"
#include <boost/regex.hpp>
#include <iostream>
#define BOOST_REGEX 0


int main(int argc, char **argv)
{
	int BaudRate = 115200;
	if(argc < 2)
	{
		std::cout <<" please enter a valid SERIAL PORT address" << std::endl;
		return 0;
	}
	if(argc == 3)
	{
		BaudRate = atoi(argv[2]);
	}
	ros::init(argc, argv, "ircmd_to_motor");
	std::string SerialPort = argv[1];
	IRcmd2Serial ir2ser(SerialPort,BaudRate,500);
	ir2ser.listen_for_command();
	return 0;
}
