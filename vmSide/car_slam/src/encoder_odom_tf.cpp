/*
  In encoder msg, x = count of left wheel encoder,y = count of right wheel encoder.
  Encoder msg comes from encoder topic published on mbed
  We calculate the current position/pose of car in the world coordinates
  x_pose is the x position corresponding to the fixed fram
  y_pose is the y position corresponding to the fixed frame
  theta is the angle of x direction between the car's frame and the fixed frame.
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Int8.h>
#include <stdio.h>
#include <math.h>

#define WHEEL_BASE 13 ///13cm
#define DISTANCE_PER_TICK 0.1324 //0.1324 cm/tick, 19.1822 counts per inch
#define TWO_PI 3.1415926 * 2

double x_pos;
double y_pos;
double theta;

void readEncoder(const geometry_msgs::PointStamped& encoder)
{
  std::string base_link = "/base_footprint";
  std::string odom = "/odom";
  double delta_distance;
  double delta_theta;
  tf::TransformBroadcaster odom_broadcaster;
  geometry_msgs::TransformStamped odom_tf;

  delta_distance = (encoder.point.x + encoder.point.y)/2 * DISTANCE_PER_TICK;
  delta_theta = (encoder.point.y - encoder.point.x)*DISTANCE_PER_TICK/WHEEL_BASE; //rad
  theta += delta_theta;
  theta -= (double)((int)(theta/TWO_PI))* TWO_PI;
  x_pos += delta_distance * cos(theta); // front is x positive
  y_pos += delta_distance * sin(theta); // left is y positive
  odom_tf.header.seq = encoder.header.seq;
  odom_tf.header.stamp = ros::Time::now();
  odom_tf.transform.translation.x = x_pos;
  odom_tf.transform.translation.y = y_pos;
  odom_tf.transform.translation.z = 0;
  odom_tf.header.frame_id = odom;
  odom_tf.child_frame_id = base_link;

  //counter clock-wise is positive
  odom_tf.transform.rotation = tf::createQuaternionMsgFromYaw (theta); 
  odom_broadcaster.sendTransform(odom_tf);
  ros::spinOnce();
}

int main(int argc, char** argv)
{

  ros::init(argc, argv, "encoder_tf_odom");

  ros::NodeHandle nh;
  tf::TransformBroadcaster odom_broadcaster;
  geometry_msgs::TransformStamped odom_tf;

  std::string base_link;
  std::string odom;
	
  base_link = "/base_footprint";
  odom = "/odom";
  ros::Subscriber encoder_sub = nh.subscribe("encoder_pub",100, readEncoder);
  ros::Rate r(10.0);
  //ros::spin();
  while(nh.ok()){
    ros::spinOnce();

  odom_tf.header.seq = 0;
  odom_tf.header.frame_id = odom;
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
  r.sleep();
}

  return(0);
}
