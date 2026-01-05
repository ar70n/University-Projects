import argparse
import signal
import sys
from clases.Switch import Switch

def parse_arguments():
    parser = argparse.ArgumentParser(description="Dummy switch program")
    parser.add_argument('--host', type=str, default="redes2.ii.uam.es", help='Host address')
    parser.add_argument('--port', '-p', type=int, default=1883, help='Port number')
    parser.add_argument('--probability', '-P', type=float, default=0.3, help='Probability of not switching')
    parser.add_argument('id', type=str, help='ID of the switch')
    return parser.parse_args()


def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el controlador...", flush=True)
    if switch:
        switch.close()
    sys.exit(0)

# Publicar la hora actual en un intervalo
try:
    args = parse_arguments()
    signal.signal(signal.SIGINT, handle_sigint)
    switch = Switch(args.host, args.port, args.probability, args.id)
    switch.start()

except Exception as e:
    print(f"Error: {e}", flush=True)
    if 'switch' in locals():
        switch.close()
