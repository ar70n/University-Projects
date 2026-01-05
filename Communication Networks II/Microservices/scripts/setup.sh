#!/bin/bash

# Define variables
VENV_DIR="entorno_virtual"
LOG_DIR="log"

cd ..
pwd
# Create virtual environment if it doesn't exist
if [ ! -d "$VENV_DIR" ]; then
    echo "Creating virtual environment..."
    python3 -m venv "$VENV_DIR"
    echo "Virtual environment created at $VENV_DIR"

    source "$VENV_DIR/bin/activate"
    pwd
    pip install -r requirements.txt
    deactivate
else
    echo "Virtual environment already exists at $VENV_DIR"
fi

# Create log directory if it doesn't exist
if [ ! -d "$LOG_DIR" ]; then
    echo "Creating log directory..."
    mkdir "$LOG_DIR"
    echo "Log directory created at $LOG_DIR"
else
    echo "Log directory already exists at $LOG_DIR"
fi

#Start RabbitMQ server if it is not running
if systemctl is-active --quiet rabbitmq-server; then
    echo "RabbitMQ server is already running"
else
    echo "Starting RabbitMQ server..."
    systemctl start rabbitmq-server
    echo "RabbitMQ server started"

fi