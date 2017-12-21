#!/bin/ash
{
	USER=$(cat /root/scripts/server_update/server_user)
	PASS=$(cat /root/scripts/server_update/server_pass)
	DIR=$(cat /root/scripts/server_update/server_dir)
	MY_VERSION=$(cat /root/version.txt)
	while :
	do
		SERVER_VERSION = $(curl -u $USER:$PASS $DIR/version.txt)
		if [ $SERVER_VERSION -ne $MY_VERSION ]; then
			echo $SERVER_VERSION is greater than $MY_VERSION
			wget --user $USER --password $PASS -r --no-parent --reject="index.html*" -P $FOLDER -nc -q -nd $DIR
			break
		else
			echo The arduino is updated
		fi	
		sleep 1d
	done
	rm -r $FOLDER/scripts
	mkdir $FOLDER/scripts
	mv $FOLDER/scripts.tar.gz $FOLDER/scripts/
	tar -xvzf $FOLDER/scripts/scripts.tar.gz
	merge-sketch-with-bootloader.lua /root/sketche.hex
	run-avrdude /root/sketche.hex
}
