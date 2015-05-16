#include "ros/ros.h"
#include "std_msgs/String.h"
#include "encoderPublisher.h"
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
	ros::init(argc, argv, "encoder_from_mbed");
	std::string SerialPort = argv[1];
	encoderPublisher encoderPublisher(SerialPort,BaudRate,500);
	encoderPublisher.setPublisher();
	encoderPublisher.listenOnSerial();
	
	return 0;
}
