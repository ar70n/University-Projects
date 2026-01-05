import argparse
import signal
import sys
from clases.Sensor import Sensor

def parse_arguments():
    parser = argparse.ArgumentParser(description="Dummy sensor program")
    parser.add_argument('--host', type=str, default="redes2.ii.uam.es", help='Host address')
    parser.add_argument('--port', '-p', type=int, default=1883, help='Port number')
    parser.add_argument('--interval', '-i', type=int, default=1, help='Time between deliveries in seconds')
    parser.add_argument('--min', '-m', type=int, default=20, help='Minimum value')
    parser.add_argument('--max', '-M', type=int, default=30, help='Maximum value')
    parser.add_argument('--increment', type=int, default=1, help='Increment value')
    parser.add_argument('id', type=str, help='ID of the sensor')
    return parser.parse_args()


def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el controlador...", flush=True)
    if sensor:
        sensor.close()
    sys.exit(0)

# Publicar la hora actual en un intervalo
try:
    args = parse_arguments()
    signal.signal(signal.SIGINT, handle_sigint)
    sensor = Sensor(args.host, args.port, args.interval, args.min, args.max, args.increment, args.id)
    sensor.start()

except Exception as e:
    print(f"Error: {e}", flush=True)
    if 'sensor' in locals():
        sensor.close()

