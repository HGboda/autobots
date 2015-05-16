
#include <iostream>
#include <string>
#include <signal.h>
#include <boost/regex.hpp>
#include "Serial_Connect.h"
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/PointStamped.h>
#include <nav_msgs/Odometry.h>
#include <string.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Int8.h>
#include <stdio.h>
#include <math.h>

// using cm as measurement unit
#define WHEEL_BASE 0.14 ///12.5 cm
#define DISTANCE_PER_TICK 0.01021 //1.021 cm/count, 20 counts = 10 encoder ticks
#define TWO_PI 6.2831852

class encoderPublisher
{
public:
	encoderPublisher(std::string port, unsigned int baud_rate, unsigned long time_out );
	~encoderPublisher(){};
	void publishMessage(int left, int right);
	void setPublisher();
	void listenOnSerial();
	void encoderCallback(const std_msgs::String::ConstPtr& msg);
	void readEncoder(const geometry_msgs::PointStamped& encoder);
    tf::TransformBroadcaster odom_broadcaster;
	
private:

	ros::NodeHandle nh_;
	ros::Publisher pub;
    geometry_msgs::TransformStamped odom_tf;
    //   nav_msgs::Odometry odom;
	geometry_msgs::PointStamped encoder_odom;
	Serial_Connect	Sc;
	double x_pos;
	double y_pos;
	double theta;
    std::string base_link;
        std::string odom_;
};
