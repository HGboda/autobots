#include "IRcmd2Serial.h"

IRcmd2Serial::IRcmd2Serial(std::string port, unsigned int baud_rate, unsigned long time_out): Sc(port,baud_rate,500)
{
}

void IRcmd2Serial::listen_for_command()
{
	 ros::Subscriber sub = nh_.subscribe("serial_generic", 1000, &IRcmd2Serial::controlCallback, this);
	 ros::spin();
}


void IRcmd2Serial::transmitMessage(char c)
{

	switch(c)
	{
		case IRCODE_L:
			ROS_DEBUG("LEFT");
			std::cout << "got command LEFT" << std::endl;
			velocity.data = 4;
			Sc.write(std::to_string(velocity.data));
			break;
		case IRCODE_R:
			ROS_DEBUG("RIGHT");
			std::cout << "got command RIGHT" << std::endl;
			velocity.data = 3;
			Sc.write(std::to_string(velocity.data));
			break;
		case IRCODE_F:
			ROS_DEBUG("FORWARD");
			std::cout << "got command FORWARD" << std::endl;
			velocity.data = 1;
			Sc.write(std::to_string(velocity.data));
			break;
		case IRCODE_B:
			ROS_DEBUG("BACK");
			std::cout << "got command BACK" << std::endl;
			velocity.data = 2;
			Sc.write(std::to_string(velocity.data));
			break;
		case IRCODE_S:
			ROS_DEBUG("STOP");
			velocity.data = 0;
			std::cout << "got command STOP" << std::endl;
			Sc.write(std::to_string(velocity.data));
			break;
	}


}


void IRcmd2Serial::controlCallback(const std_msgs::String::ConstPtr& msg)
{
#if BOOST_REGEX
	const boost::regex e("(?<=BIR)(.*?)(?=EIR)");
	boost::smatch match;
			
	if (boost::regex_search(std::string (msg->data.c_str()), match, e))
	{
		std::cout << "I heard: " << match[1].str() << std::endl;
		transmitMessage(match[1].str()[0]);
	}
#else
	std::string delimStart = "BIR";
	std::string delimEnd  =  "EIR";	
	std::size_t first 		= msg->data.find(delimStart);
	std::size_t last 		= msg->data.find(delimEnd);
	if((first  != std::string::npos) && (last  != std::string::npos))
	{
		std::string strNew 	= msg->data.substr(first + delimStart.length(),last-first - delimStart.length());
		strNew.erase(std::remove(strNew.begin(),strNew.end(),' '),strNew.end());
		if (strNew.length())
		   transmitMessage(strNew[0]);
		else
		   transmitMessage(' ');
	}

#endif

}

