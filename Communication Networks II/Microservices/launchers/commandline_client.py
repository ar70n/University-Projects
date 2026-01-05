"""
CLASE: CommandLineClient
DESCRIPCIÓN: Clase que representa un cliente de línea de comandos para 
            interactuar con el sistema Saimazoom.
            Este es el programa que ejecuta el usuario.
ATRIBUTOS:
    - client: Client - Instancia de la clase Client para manejar las operaciones.
MÉTODOS:
    - __init__(): Inicializa la instancia de Client.
    - main(): Método principal que muestra el menú y maneja las opciones del usuario.
    - show_orders(): Muestra todos los pedidos.
    - add_order(): Agrega un nuevo pedido.
    - cancel_order(): Cancela un pedido existente.
    - register_client(): Registra un nuevo cliente.
    - exit(): Sale del programa.
"""
from saimazoom.clases.client import Client
import sys
import os

# Menú principal
def main():
    client = Client()
      
    while True:
        print("\n==== Saimazoom Menu ====")
        print("1. Show orders")
        print("2. Add order")
        print("3. Cancel order")
        print("4. Register Client")
        print("5. Exit")

        option = input("Choose an option: ")

        match option:
            case "1":
                show_orders(client)
            case "2":
                add_order(client)
            case "3":
                cancel_order(client)
            case "4":
                register_client(client)
            case "5":
                exit()
            case _:
                print("Invalid option, please try again.")


"""
FUNCIÓN: show_orders(client)
ARGS_IN: client: Client - Instancia de la clase Client.
DESCRIPCIÓN: Muestra todos los pedidos del cliente.
ARGS_OUT: None
"""
def show_orders(client):
    print(client.show_all_orders())
    return

"""
FUNCIÓN: add_order(client)
ARGS_IN: client: Client - Instancia de la clase Client.
DESCRIPCIÓN: Agrega un nuevo pedido al cliente.
ARGS_OUT: None
"""
def add_order(client):
    product_id = input("Enter the product ID: ")
    print(client.add_order(product_id))
    return

"""
FUNCIÓN: cancel_order(client)
ARGS_IN: client: Client - Instancia de la clase Client.
DESCRIPCIÓN: Cancela un pedido existente del cliente.
ARGS_OUT: None
"""
def cancel_order(client):
    order_id = input("Enter the order ID: ")
    print(client.cancel_order(order_id))
    return

"""
FUNCIÓN: register_client(client)
ARGS_IN: client: Client - Instancia de la clase Client.
DESCRIPCIÓN: Registra un nuevo cliente en el sistema.
ARGS_OUT: None
"""
def register_client(client):
    client_id = input("Enter your client ID: ")
    print(client.register_client(client_id))
    return

"""
FUNCIÓN: exit()
ARGS_IN: None
DESCRIPCIÓN: Sale del programa.
ARGS_OUT: None
"""
def exit():
    print("Exiting...")
    sys.exit(0)

# Punto de entrada
if __name__ == '__main__':
    try:
        main()
        
    except KeyboardInterrupt:
        print('\nInterrumpido')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)

    except BaseException as e:
        print(f"El programa salio con codigo: {e}")
        try:
            sys.exit(1)
        except SystemExit:
            os._exit(1)