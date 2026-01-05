from saimazoom.clases.controller import Controller
import signal
import sys

def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el controlador...", flush=True)
    if controller:
        controller.close()
        if controller.connection and not controller.connection.is_closed:
            controller.connection.close()
    sys.exit(0)
            

if __name__ == "__main__":
    controller = Controller()
    signal.signal(signal.SIGINT, handle_sigint)

    try:
        print("Escuchando", flush=True)
        controller.channel.start_consuming()

    except Exception as e:
        print(f"Ha ocurrido un error: {e}", flush=True) 
        controller.close()
        if controller.connection and not controller.connection.is_closed:
            controller.connection.close()

