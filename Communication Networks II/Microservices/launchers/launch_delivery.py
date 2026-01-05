from saimazoom.clases.deliverer import Deliverer
import signal
import sys


def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el delivery...", flush=True)
    if deliverer:
        deliverer.close()
    sys.exit(0)


if __name__ == "__main__":
    deliverer = Deliverer()
    signal.signal(signal.SIGINT, handle_sigint)

    try:
        print("Deliverer started", flush=True)
        deliverer.channel.start_consuming()
        
    except Exception as e:
        print(f"Ha ocurrido un error: {e}", flush=True)
        deliverer.close()