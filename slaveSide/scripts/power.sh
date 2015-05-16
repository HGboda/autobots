#!/bin/bash

# restart USB power connection if turned down
# set as automatically executed every 2 minutes in crontab

#devmem2 0x47401c60 b 0x00
#sleep 1
#echo "usb1" > /sys/bus/usb/drivers/usb/unbind
#sleep 20
#echo "usb1" > /sys/bus/usb/drivers/usb/bind
#sleep 1
devmem2 0x47401c60 b 0x01
sh wirelesscheck.sh
