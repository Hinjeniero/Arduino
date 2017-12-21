#!/bin/ash

while :
do
	sleep 2m
	TEMPERATURE=$(sqlite3 -line /tmp/temp_sensor.db 'SELECT temp FROM sensor ORDER BY timestamp DESC LIMIT 1')
	HUMIDITY=$(sqlite3 -line /tmp/temp_sensor.db 'SELECT humidity FROM sensor ORDER BY timestamp DESC LIMIT 1')
	
	mosquitto_pub \
	-p 8883 \
	-h broker.xively.com \
	-i 4e737221-0d26-4064-a502-a104e488248a \
	-d \
	-u d5fcc3da-78d6-44bb-bc86-521ed1e80041 \
	-P TTAWg8NJbg3GVFd+wacqWdGieF4PUYz0WsEQuldo468= \
	-t xi/blue/v1/4e737221-0d26-4064-a502-a104e488248a/d/d5fcc3da-78d6-44bb-bc86-521ed1e80041/Temperature \
	-m ",Tempº,$TEMPERATURE" \
	--cafile "./root_ca.pem" 

        mosquitto_pub \
        -p 8883 \
        -h broker.xively.com \
        -i 4e737221-0d26-4064-a502-a104e488248a \
        -d \
        -u d5fcc3da-78d6-44bb-bc86-521ed1e80041 \
        -P TTAWg8NJbg3GVFd+wacqWdGieF4PUYz0WsEQuldo468= \
        -t xi/blue/v1/4e737221-0d26-4064-a502-a104e488248a/d/d5fcc3da-78d6-44bb-bc86-521ed1e80041/Humidity \
        -m ",Humidity%,$HUMIDITY" \
        --cafile "./root_ca.pem"
done
