#!/bin/sh

# initialization script on BBB
## grant R/W permission
## source ~/.bashrc to update ROS_MASTER_URI
## source catkin directory's setup.bash file in order to use rosrun
## sync time with server using ntpdate and chrony

printf "rw authorization given to serial port\n"
./serialPermission.sh
printf "done\n"

#echo -n "prepare ros environment car_slam"
#. ~/hector_slam_tutorial/auto_car_slam/devel/setup.bash
#echo -n "done"
#sleep 1
printf "source bashrc\n"
. ~/.bashrc
cat ~/.bashrc | grep ROS_MASTER_URI
printf "done\n"

printf "prepare control_to_mbed\n"
. ~/hector_slam_tutorial/catkin_ws/devel/setup.bash
printf "done\n"

printf -n "sync time with ntp server\n"
sudo ntpdate 192.168.1.101
sudo invoke­rc.d chrony restart
sleep 1
printf -n "done\n"
