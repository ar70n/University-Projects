import sys
import signal
import time
TIMEOUT = 1 # seconds
signal.signal(signal.SIGALRM, input)
signal.alarm(TIMEOUT)

print("\n\nRecibido por ARGV:")
for line in sys.argv:
    print(line)
    def kg_to_lbs(kg):
        return kg * 2.20462

    def celsius_to_fahrenheit(celsius):
        return (celsius * 9/5) + 32

    print("\nHora del servidor:")
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

    if len(sys.argv) > 1:
        try:
            if sys.argv[1] == "kg_to_lbs" and len(sys.argv) > 2:
                kg = float(sys.argv[2])
                print(f"{kg} kg son {kg_to_lbs(kg):.2f} libras.")
            elif sys.argv[1] == "celsius_to_fahrenheit" and len(sys.argv) > 2:
                celsius = float(sys.argv[2])
                print(f"{celsius} °C son {celsius_to_fahrenheit(celsius):.2f} °F.")
            else:
                print("Uso: [kg_to_lbs <kg>] o [celsius_to_fahrenheit <celsius>]")
        except ValueError:
            print("Por favor, proporciona un número válido.")
    else:
        print("No se proporcionaron argumentos.")