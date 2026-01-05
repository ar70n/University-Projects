from saimazoom.clases.robot import Robot
import signal
import sys


def handle_sigint(signal_received, frame):
    """Manejador para la señal SIGINT."""
    print("\nSIGINT recibido. Cerrando el robot...", flush=True)
    if robot:
        robot.close()
    sys.exit(0)



# Punto de entrada 
if __name__ == "__main__":
    robot = Robot()
    signal.signal(signal.SIGINT, handle_sigint)

    try:
        print("Robot started", flush=True)
        robot.channel.start_consuming()

    except Exception as e:
        print(f"Ha ocurrido un error: {e}", flush=True)
        robot.close()