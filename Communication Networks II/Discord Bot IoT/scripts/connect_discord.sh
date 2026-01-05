#!/bin/bash
cd ..
source entorno_virtual/bin/activate

python3 controller.py --host localhost db.pkl &
sleep 5
python3 bridge.py
PID_BRIDGE=$!

kill $PID_BRIDGE


