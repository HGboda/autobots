# Autonomous Vehicle Testbed
  * Independent Study Spring 2015
  * Developer: Zhi Li
  * Detail report can be found [here](https://github.com/snugglelamb/autobots/blob/master/IndependentStudyReport_ZhiLi.pdf).

## Introduction
  This autonomous vehicle testbed is designed to be a common platform for multiple research topics in autonomous driving, including scenario handling for safety assurance, localization and autonomous navigation. 

  Current functionality:

  * real-time exploration
  * waypoint navigation
  * static obstacle avoidance
  * PI control w/ straight driving
  * line following scenario handling
  
## Hardware
  Development Environment
    
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

## Demo
### 2D mapping
![alt text](https://github.com/snugglelamb/autobots/blob/master/resources/mlab_mapping_gif.gif "2D mapping of mlab")
### Simple Navigation (exploration)
![alt text](https://github.com/snugglelamb/autobots/blob/master/resources/nav_w:pid.gif "2D navigation with exploration")

