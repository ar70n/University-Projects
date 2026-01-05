import argparse
from datetime import datetime
import signal
import sys
from clases.Clock import Clock

def parse_arguments():
    parser = argparse.ArgumentParser(description="Dummy clock program")
    parser.add_argument('--host', type=str, default="redes2.ii.uam.es", help='Host address')
    parser.add_argument('--port', '-p', type=int, default=1883, help='Port number')
    parser.add_argument('--time', type=str, default=datetime.now().strftime("%H:%M:%S"), help='Time in HH:MM:SS format')
    parser.add_argument('--increment', type=int, default=1, help='Increment value in seconds')
    parser.add_argument('--rate', type=int, default=1, help='Rate of sending time updates in seconds')
    parser.add_argument('id', type=str, help='ID of the sensor')

    return parser.parse_args()


def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el clock...", flush=True)
    if clock:
        clock.close()
    sys.exit(0)

# Publicar la hora actual en un intervalo
try:
    args = parse_arguments()
    if args.increment <= 0 or args.rate <= 0:
        raise ValueError("El incremento y la tasa deben ser mayores que cero.")
    
    signal.signal(signal.SIGINT, handle_sigint)
    clock = Clock(args.host, args.port , args.time, args.increment, args.rate, args.id)
    clock.start()

except Exception as e:
    print(f"Error: {e}", flush=True)
    if 'clock' in locals():
        clock.close()
