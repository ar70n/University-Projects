from saimazoom.clases.client import Client
from time import sleep
import signal
import sys

def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el delivery...", flush=True)
    if client:
        client.connection.close()
    sys.exit(0)


if __name__ == "__main__":
    client = Client()
    signal.signal(signal.SIGINT, handle_sigint)

    try:
        sleep(10)
        print("Client started", flush=True)
        print(client.register_client("virtual_client"), flush=True)
        i=1
        while True:
            print(client.add_order([i,i+1]), flush=True)
            print(client.show_all_orders(), flush=True)
            sleep(5)
            i+=2
            
    except BaseException as e:
        print(f"El programa salio con codigo: {e}")
        client.connection.close()