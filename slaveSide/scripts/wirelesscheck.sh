#!/bin/bash

# check wireless connection with local network
# set as periodically executed script in crontab (every 1 minute)
# detect disconnection and reconnect

#if iwconfig wlan0 | grep -o "Access Point: Not-Associated"
#then
#	ifconfig wlan0 down
#	sleep 10
#	ifconfig wlan0 up
#fi

if ping -c 2 192.168.1.1 | grep -o "Destination Host Unreachable"
then
	ifconfig wlan0 down
	sleep 10
	iwconfig wlan0 essid BBBNet
	iwconfig wlan0 key 12345678
	ifconfig wlan0 up
fi

