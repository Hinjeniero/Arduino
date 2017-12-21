curl --user "d5fcc3da-78d6-44bb-bc86-521ed1e80041:TTAWg8NJbg3GVFd+wacqWdGieF4PUYz0WsEQuldo468=" \
-X POST\
-d \
'{"msgText":",TempºC,24"}]}' \
--cacert ./root_ca.pem \
-v \
https://hinjeniero.broker.xively.com/messaging/publish/xi/blue/v1/4e737221-0d26-4064-a502-a104e488248a/d/d5fcc3da-78d6-44bb-bc86-521ed1e80041/Temperature 