#!/bin/ash
while :
do
	N=$(date)
	SERVER=$(cat /root/scripts/ntp/ntp_server)
	echo "Executing ntpd..."
	echo "old date -> $N"
	ntpd -nqp $SERVER
	N=$(date)
	echo "new date -> $N"
	echo "Done executing ntpd, sleeping for 1 day"
	sleep 1d
done

