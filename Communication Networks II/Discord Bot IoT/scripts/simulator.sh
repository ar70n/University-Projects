#!/bin/bash
cd ..
mkdir -p log
rm -f log/*.log
source entorno_virtual/bin/activate

python3 -m controller --host mqtt.eclipseprojects.io db.pkl >> log/controller.log 2>>log/controller.log &
PID_CONTROLLER=$!

python3 -m launchers.dummy-switch --host mqtt.eclipseprojects.io -P 0 switch1 > log/switch.log & 
PID_SWITCH=$!

python3 -m launchers.dummy-sensor --host mqtt.eclipseprojects.io sensor1 > log/sensor.log &
PID_SENSOR=$!



sleep 1
echo "add_device switch1" | nc -w 1 localhost 5000
echo ""
echo "add_device sensor1" | nc -w 1 localhost 5000
echo ""
sleep 1
echo "add_rule si sensor1 > 25 entonces switch1 ON" | nc -w 1 localhost 5000
echo ""


#echo $PID_CONTROLLER
#echo $PID_SWITCH
#echo $PID_SENSOR

#Dejemos que corra un rato
sleep 10

kill -n 2 $PID_SWITCH
kill -n 2 $PID_SENSOR
kill $PID_CONTROLLER

echo "Fin del script"