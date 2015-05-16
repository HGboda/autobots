# autobots
  Autonomous Vehicle Testbed (Independent Study)
  
  Developer: Zhi Li

  Detail report can be found in IndependentStudyReport_ZhiLi.pdf.

## Introduction
  This autonomous vehicle testbed is designed to be a common platform for multiple research topics in autonomous driving, including scenario handling for safety assurance, localization and autonomous navigation. The car could now perform real time exploration and waypoint navigation using the LIDAR on top, as well as the traditional approach of building a map first and then achieve navigation capability based on the map generated. A PI controller is used to keep the car moving at a set speed calculated out of encoder ticks per sec, and could also enable straight line driving in the meantime. Line following capability enables the car to follow a preset track and cope with different turning scenarios, the detection of lanechange could also be achieved leveraging those IR sensors.

## Demo of 2D mapping
![alt text](https://github.com/snugglelamb/autobots/blob/master/resources/mlab_mapping_gif.gif "2D mapping of mlab")
## Demo of Simple Navigation (exploration)
![alt text](https://github.com/snugglelamb/autobots/blob/master/resources/nav_1_w:PID.mov "2D navigation with exploration")

## Hardware
* Development Environment
  OS: Ubuntu 12.04
  ROS ver: Hydro
  LIDAR: Hokuyo URG-04LX-UG01
  Robot car base: DFRobot with encoder
  Platform: Beaglebone Black (ubuntu 12.04 + ROS Hydro)
  Hardware: mbed LPC1768, H-bridge, Wifi Dongle (WNA1100), Adafruit Powerboost 500
  Battery: Adafruit Lithium Ion 3.7V 6600mAh
  [Param sheet](https://www.dropbox.com/sh/ujqpz4cp4h5fzak/AAAGaUGlNwOzu-JbHHehNdq4a?dl=0) for parts mentioned above

## Software
* ROS
  * Simulation on VM
  * System Overview
  * ROS
    * Distributed ROS setup
    * Synchronization across platforms
    * ROS control
    * Line following
    * Mapping
    * Navigation
  * mbed
    * PID driver control
    * encoder data reading
    * ir sensor data reading
  * bash scripts


