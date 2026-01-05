#!/bin/bash

# Define variables
VENV_DIR="entorno_virtual"

cd ..
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

