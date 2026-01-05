"""
CLASE: Robot
DESCRIPCIÓN: Clase para manejar el robot que busca productos en el almacén y los mueve a la cinta transportadora.
ATRIBUTOS:
    - connection: pika.BlockingConnection - Conexión a RabbitMQ.
    - channel: pika.Channel - Canal de comunicación con RabbitMQ.
MÉTODOS:
    - __init__(): Inicializa la conexión y el canal de RabbitMQ.
    - consume_callback(ch, method, properties, body): Callback para manejar los mensajes recibidos.
    - simulate_conveyor_belt(): Simula el tiempo de procesamiento en la cinta transportadora.
    - find_order(order_id, products_ids): Busca un pedido y verifica si todos los productos están disponibles.
    - find_product(product_id): Busca un producto en el almacén.
    - close(): Cierra el canal y la conexión de RabbitMQ.
"""

import random
import time
import pika
from saimazoom import config

class Robot:
    def __init__(self):
        # Inicializar la conexión a RabbitMQ
        self.connection = pika.BlockingConnection(pika.ConnectionParameters(host=config.queue_server))
        self.channel = self.connection.channel()

        #COLA DONDE RECIBIMOS TAREAS
        self.channel.queue_declare(queue=config.robot_queue, durable=False, auto_delete=True)
        self.channel.basic_qos(prefetch_count=1)
        self.channel.basic_consume(queue=config.robot_queue, on_message_callback=self.consume_callback)

        #COLA DONDE ENVIAMOS RESPUESTAS
        self.channel.queue_declare(queue=config.robot_response_queue, durable=False, auto_delete=True)
   
    """
    FUNCIÓN: consume_callback(ch, method, properties, body)
    ARGS_IN: ch - canal de comunicación
              method - método de entrega
              properties - propiedades del mensaje
              body - cuerpo del mensaje recibido
    DESCRIPCIÓN: Callback para manejar los mensajes recibidos en la cola del robot.
                Recibe mensajes de la forma "MOVE order_id product_id" y procesa el pedido.
    ARGS_OUT: None
    """
    def consume_callback(self, ch, method, properties, body):
        parts = body.decode('utf-8').split(" ")

        match parts[0]:
            case "MOVE":
                order_id = parts[1]
                products_ids = parts[2:]

                if self.find_order(order_id, products_ids):
                    self.channel.basic_publish(exchange='', routing_key=config.robot_response_queue, body=f"IN_CONVEYOR_BELT {order_id}") #MOVE order_id product_id  
                    print(f"Encontrado y movido a la cinta el pedido con id: {order_id}", flush=True)
                    self.simulate_conveyor_belt()
                    print(f"Listo para repartir el pedido con id: {order_id}", flush=True)
                    self.channel.basic_publish(exchange='', routing_key=config.robot_response_queue, body=f"READY {order_id}")
                    
                else:
                    self.channel.basic_publish(exchange='', routing_key=config.robot_response_queue, body=f"NOT_FOUND {parts[1]}") #NOT_FOUND order_id product_id
                    print(f"NO encontrado el pedido con id: {order_id}", flush=True)
            case _:
                print(f"Mensaje no reconocido: {body}", flush=True)
        
        # Confirmar el mensaje recibido
        ch.basic_ack(delivery_tag=method.delivery_tag)

    """
    FUNCIÓN: simulate_conveyor_belt()
    ARGS_IN: None
    DESCRIPCIÓN: Simula el tiempo de procesamiento en la cinta transportadora.
    ARGS_OUT: None
    """
    def simulate_conveyor_belt(self):
        time.sleep(random.randint(config.conveyor_min, config.conveyor_max))  # Simular tiempo de procesamiento

    """
    FUNCIÓN: find_order(order_id, products_ids)
    ARGS_IN: order_id - ID del pedido
              products_ids - lista de IDs de productos
    DESCRIPCIÓN: Busca un pedido y verifica si todos los productos están disponibles.
    ARGS_OUT: True si todos los productos están disponibles, False en caso contrario.
    """
    def find_order(self, order_id, products_ids):
        for product_id in products_ids:
            if not self.find_product(product_id):
                print(f"Robot NO encontró el producto ({product_id}) de la orden ({order_id})", flush=True)
                return False

        print(f"Robot encontró todos los productos de la orden ({order_id})", flush=True)
        return True

    """
    FUNCIÓN: find_product(product_id)
    ARGS_IN: product_id - ID del producto a buscar
    DESCRIPCIÓN: Busca un producto en el almacén.
    ARGS_OUT: True si el producto está disponible, False en caso contrario.
    """
    def find_product(self, product_id):
        print(f"Buscando producto con id: [{product_id}]...", flush=True)
        time.sleep(random.randint(config.robot_search_min, config.robot_search_max))  # Simular tiempo de procesamiento
        if random.random() < config.p_warehouse:
            print(f"Encontré el producto ({product_id})", flush=True)
            return True
        else:
            print(f"NO encontré el producto ({product_id})", flush=True)
            return False
    
    """
    FUNCIÓN: close()
    ARGS_IN: None
    DESCRIPCIÓN: Cierra el canal y la conexión de RabbitMQ.
    ARGS_OUT: None
    """
    def close(self):
        if self.channel and self.channel.is_open:
            self.channel.close()  # Cierra el canal si está abierto
        if self.connection and self.connection.is_open:
            self.connection.close()  # Cierra la conexión si está abierta


