#!/bin/ash

echo Initiating ntp script
/bin/ash /root/scripts/ntp/ntp_script.sh &
echo Initiating updates server script
/bin/ash /root/scripts/server_update/server_script.sh &
echo Initiating xively script
/bin/ash /root/scripts/xively/xively_mqtt_script.sh &
echo Done Initiating all scripts
