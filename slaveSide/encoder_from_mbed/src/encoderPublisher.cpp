#include "encoderPublisher.h"

encoderPublisher::encoderPublisher(std::string port, unsigned int baud_rate, unsigned long time_out): Sc(port,baud_rate,500)
{
    base_link = "/base_stablized";
    odom_ = "/odom";
    odom_tf.header.seq = 0;
    odom_tf.header.frame_id = odom_;
    odom_tf.header.stamp.sec = 0;
    odom_tf.header.stamp.nsec = 0;
    odom_tf.child_frame_id = base_link;
    odom_tf.transform.translation.x = 0;
    odom_tf.transform.translation.y = 0;
    odom_tf.transform.translation.z = 0;
    odom_tf.transform.rotation = tf::createQuaternionMsgFromYaw(0);

    x_pos = 0;
    y_pos = 0;
    theta = 0;
    odom_broadcaster.sendTransform(odom_tf);
}

void encoderPublisher::readEncoder(const geometry_msgs::PointStamped& encoder)
{
  base_link = "/base_stablized";
  odom_ = "/odom";
  double delta_distance;
  double delta_theta;

  delta_distance = (encoder.point.x + encoder.point.y)/2 * DISTANCE_PER_TICK;
  delta_theta = (encoder.point.y - encoder.point.x)*DISTANCE_PER_TICK/WHEEL_BASE; //rad
  theta += delta_theta;
  if (theta >= TWO_PI) {
    theta -= (int)(theta/TWO_PI)* TWO_PI;
  } else if (theta <= -1 * TWO_PI) {
    theta -= ((int)(theta/TWO_PI))* TWO_PI;
  }

  x_pos += delta_distance * cos(theta); // front is x positive
  y_pos += delta_distance * sin(theta); // left is y positive
  odom_tf.header.seq = encoder.header.seq;
  odom_tf.header.stamp = ros::Time::now();
  odom_tf.transform.translation.x = x_pos;
  odom_tf.transform.translation.y = y_pos;
  odom_tf.transform.translation.z = 0;
  odom_tf.header.frame_id = odom_;
  odom_tf.child_frame_id = base_link;

  //counter clock-wise is positive
  odom_tf.transform.rotation = tf::createQuaternionMsgFromYaw (theta); 
  odom_broadcaster.sendTransform(odom_tf);
}


void encoderPublisher::listenOnSerial()
{
	ros::Subscriber sub = nh_.subscribe("serial_generic", 1, &encoderPublisher::encoderCallback, this);
	ros::spin();
}

void encoderPublisher::setPublisher()
{
  //  pub = nh_.advertise<geometry_msgs::PointStamped>("encoder_pub", 50);	
}

void encoderPublisher::publishMessage(int left, int right)
{
    char odom_frame[] = "/odom";
    ros::Time current_time = ros::Time::now();
    encoder_odom.point.x = left;
    encoder_odom.point.y = right;
    encoder_odom.point.z = 0;
    encoder_odom.header.stamp = current_time;
    encoder_odom.header.seq = 0;
    encoder_odom.header.frame_id = odom_frame;
    /*
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";
    odom.pose.pose.position.x = left;
    odom.pose.pose.position.y = right;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(0);
    odom.child_frame_id = "base_footprint";
    odom.twist.twist.linear.x = 0;
    odom.twist.twist.linear.y = 0;
    odom.twist.twist.angular.z = 0;    
    */
    readEncoder(encoder_odom);
    //  pub.publish(encoder_odom);
    // ros::spinOnce();

}


void encoderPublisher::encoderCallback(const std_msgs::String::ConstPtr& msg)
{

#if BOOST_REGEX
	const boost::regex e("(?<=BENC)(.*?)@(.*?)(?=EENC)");
	boost::smatch match;
			
	if (boost::regex_search(std::string (msg->data.c_str()), match, e))
	{
		std::cout << "I heard left: " << match[1].str()[0] << std::endl;
		std::cout << "I heard right: " << match[1].str()[1] << std::endl;
		
		publishMessage(std::stoi(match[1].str()[0]), std::stoi(match[1].str()[1]));
	}
#else
	std::string delimStart = "BENC";
	std::string delimMid = "@";
	std::string delimEnd  =  "EENC";	
	std::size_t first 		= msg->data.find(delimStart);
	std::size_t last 		= msg->data.find(delimEnd);
	std::size_t mid			= msg->data.find(delimMid);
	
	if((first  != std::string::npos) && (last  != std::string::npos) && (mid  != std::string::npos))
	{
		std::string left 	= msg->data.substr(first + delimStart.length(),mid-first - delimStart.length());
		std::string right 	= msg->data.substr(mid + 1,last-mid - 1);
		left.erase(std::remove(left.begin(), left.end(),' '),left.end());
		right.erase(std::remove(right.begin(), right.end(),' '),right.end());
		if ((left.length() != 0) && (right.length() != 0))
		   publishMessage(std::stoi(left), std::stoi(right));
		else if (left.length() == 0 && right.length() != 0) {
		  publishMessage(0, std::stoi(right));
		} else if (left.length() != 0 && right.length() == 0) {
		  publishMessage(std::stoi(left), 0);
		} else {
		  std::cout << "got both empty." << std::endl;
		}
	}

#endif

}

