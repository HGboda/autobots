#include "control2Serial.h"

control2Serial::control2Serial(std::string port, unsigned int baud_rate, unsigned long time_out): Sc(port,baud_rate,500)
{
}

void control2Serial::listen_for_command()
{
	 ros::Subscriber sub = nh_.subscribe("motor_control", 1, &control2Serial::controlCallback, this);
	 ros::spin();
}


void control2Serial::transmitMessage(char c)
{
	switch(c)
	{
		case KEYCODE_L:
			ROS_DEBUG("LEFT");
			std::cout << "got command LEFT" << std::endl;
			velocity.data = 3;
			Sc.write(std::to_string(velocity.data));
			break;
		case KEYCODE_R:
			ROS_DEBUG("RIGHT");
			std::cout << "got command RIGHT" << std::endl;
			velocity.data = 4;
			Sc.write(std::to_string(velocity.data));
			break;
		case KEYCODE_F:
			ROS_DEBUG("FORWARD");
			std::cout << "got command FORWARD" << std::endl;
			velocity.data = 1;
			Sc.write(std::to_string(velocity.data));
			break;
		case KEYCODE_B:
			ROS_DEBUG("BACK");
			std::cout << "got command BACK" << std::endl;
			velocity.data = 2;
			Sc.write(std::to_string(velocity.data));
			break;
		case KEYCODE_SPACE:
			ROS_DEBUG("STOP");
			velocity.data = 0;
			std::cout << "got command STOP" << std::endl;
			Sc.write(std::to_string(velocity.data));
			break;
	        case KEYCODE_a:
		        ROS_DEBUG("ACCELERATE");
			velocity.data = 5;
			std::cout << "got command ACCELERATE" << std::endl;
			Sc.write(std::to_string(velocity.data));
		        break;
	        case KEYCODE_d:
		        ROS_DEBUG("DECELERATE");
		        velocity.data = 6;
		        std::cout << "got command DECELERATE" << std::endl;
		        Sc.write(std::to_string(velocity.data));
       		  break;
	}

}


void control2Serial::controlCallback(const std_msgs::String::ConstPtr& msg)
{
#if BOOST_REGEX
	const boost::regex e("(?<=BMAIN)(.*?)(?=EMAIN)");
	boost::smatch match;
			
	if (boost::regex_search(std::string (msg->data.c_str()), match, e))
	{
		std::cout << "I heard: " << match[1].str() << std::endl;
		transmitMessage(match[1].str()[0]);
	}
#else
	std::string delimStart = "BMAIN";
	std::string delimEnd  =  "EMAIN";	
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

