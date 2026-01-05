"""
Bridge.py
DESCRIPCIÓN:
    Este script implementa un bot de Discord que actúa como puente entre el usuario y un controlador de dispositivos.
    El bot permite al usuario enviar comandos al controlador y recibir respuestas.
    El bot se conecta a un socket TCP para comunicarse con el controlador.
    El bot utiliza la librería discord.py para interactuar con la API de Discord.
"""
# This bot requires the 'message_content' intent.

import discord
import os
from dotenv import load_dotenv
import sys
import socket

RECV_BUFFER = 1024

# Definimos el cliente de discord
intents = discord.Intents.default()
intents.message_content = True
client = discord.Client(intents=intents)

# Eventos
@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')

# Hay que hacer los comandos que puede recibir el bot y que acciones hacen esos comandos
# El bot tiene que poder mandar ordenes a los dispositivos, imprimir su estado, consultar editar y añadir reglas

"""
FUNCION: on_message(message)
ARGS_IN:
    - message: Mensaje recibido en el canal de Discord 
DESCRIPCIÓN: Hace un chequeo superficial del mensaje recibido y si es válido lo envía al controlador.
ARGS_OUT: None
"""
@client.event
async def on_message(message):
    if message.author == client.user:
        return
    
    if message.content.startswith('help'):
        await message.channel.send(
        """Bienvenido al bot de la casa inteligente!
Este bot te permite controlar los dispositivos de tu casa inteligente y consultar su estado.
Puedes usar los siguientes comandos:
- `add_device <id dispositivo>`: Registra un nuevo dispositivo.
- `get_device <id dispositivo>`: Consulta el estado de los dispositivos. Si usas `all`, muestra el de todos.
- `set_device <id> <new state>`: Establece el estado de un dispositivo.
- `remove_device <id>`: Elimina un dispositivo registrado.
- `add_rule si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>`: Añade una regla.
- `edit_rule <rule_id> si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>`: Edita una regla.
- `delete_rule <rule_id>`: Elimina una regla.
- `list_rules`: Lista las reglas.
- `help`: Muestra esta ayuda."""
            )
        return
    
    # Si el mensaje no empieza por uno de los comandos, no lo procesamos
    if not message.content.startswith(('add_device', 'get_device', 'set_device', 'remove_device', 'add_rule', 'edit_rule', 'delete_rule', 'list_rules')):
        await message.channel.send("Comando no reconocido. Usa `help` para ver la lista de comandos.")
        return

    client_socket.send(message.content.encode())
    print(f"Mensaje enviado al controlador: \"{message.content}\"")
    response = client_socket.recv(RECV_BUFFER).decode()
    print(f"Respuesta del controlador: \"{response}\"")
    if len(response) > 0:
        await message.channel.send(response)
        

"""
FUNCION: parse_args()
ARGS_IN: None
DESCRIPCIÓN: Método para parsear los argumentos de la línea de comandos.Puede recibir opcionalmente --host y --port
ARGS_OUT: args: Objeto con los argumentos parseados.
"""
def parse_args():
    import argparse
    parser = argparse.ArgumentParser(description='Controlador de dispositivos')
    parser.add_argument('--host', type=str, default='localhost', help='Host del controlador')
    parser.add_argument('--port', type=int, default=5000, help='Puerto del controlador')
    return parser.parse_args()  

# Método principal
args = parse_args()
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
#client_socket.settimeout(5)

try:
    client_socket.connect((args.host, args.port))
    #Conectar a discord
    load_dotenv()
    client.run(os.getenv('DISCORD_TOKEN'))
except socket.error as e:
    print("No se pudo conectar al socket del controlador. Asegúrate de que el controlador está en ejecución.")
    client_socket.close()
    sys.exit(1)
except KeyboardInterrupt:
    print("Saliendo del programa.")
    client_socket.close()
    sys.exit(0)