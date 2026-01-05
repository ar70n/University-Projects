#!/bin/bash
cd ..
source entorno_virtual/bin/activate


# Ejecutar un script de Python en segundo plano
python3 -m launchers.launch_controller > log/controller.log 2>&1 &
PID_CONTROLLER=$!
python3 -m launchers.launch_robot > log/robot.log 2>&1 &
PID_ROBOT=$!
python3 -m launchers.launch_delivery > log/delivery.log 2>&1 &
PID_DELIVERY=$!

#echo "PID_CONTROLLER: $PID_CONTROLLER"
#echo "PID_ROBOT: $PID_ROBOT"
#echo "PID_DELIVERY: $PID_DELIVERY"


python3 -m launchers.commandline_client


# Terminar los scripts de Python en segundo plano
kill -n 2 $PID_ROBOT
kill -n 2 $PID_DELIVERY
kill -n 2 $PID_CONTROLLER

