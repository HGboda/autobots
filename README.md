# autobots
  Autonomous Vehicle Testbed (Independent Study)
  
  Zhi Li

## Introduction
  This autonomous vehicle testbed is designed to be a common platform for multiple research topics in autonomous driving, including scenario handling for safety assurance, localization and autonomous navigation. The car could now perform real time exploration and waypoint navigation using the LIDAR on top, as well as the traditional approach of building a map first and then achieve navigation capability based on the map generated. A PI controller is used to keep the car moving at a set speed calculated out of encoder ticks per sec, and could also enable straight line driving in the meantime. Line following capability enables the car to follow a preset track and cope with different turning scenarios, the detection of lanechange could also be achieved leveraging those IR sensors.

## Demo of 2D mapping
![alt text](https://github.com/snugglelamb/autobots/blob/master/resources/mlab_mapping_gif.gif "2D mapping of mlab")

## Software
* ROS
  * Control
    * keyboard_control.cpp
  * Mapping
    * Hector_SLAM  [[ROS package]](http://wiki.ros.org/hector_slam)
    * Odometry calibration: encoder_odom_tf.cpp
  * Localization
  * Navigation
* mbed
  * Motor Control (command subscriber)
  * Encoder Publisher
  * Implement rosserial_arduino on mbed

## Hardware
  1. Hokuyo URG-04LX-UG01 LIDAR
  2. mbed LPC1768
  3. Beaglebone Black
  4. h-bridge circuit
  5. Chassis car with two wheel encoders


