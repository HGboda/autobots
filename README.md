# autobots
Autonomous Vehicle Testbed project
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
  * usage of rosserial

## Hardware
  1. Hokuyo URG-04LX-UG01 LIDAR
  2. mbed LPC1768
  3. Beaglebone Black
  4. h-bridge circuit
  5. Chassis car with two wheel encoders
