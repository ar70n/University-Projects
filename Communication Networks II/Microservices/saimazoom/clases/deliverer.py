"""
CLASE: Deliverer
DESCRIPCIÓN: Clase para manejar la entrega de pedidos.
ATRIBUTOS:
    - connection: pika.BlockingConnection - Conexión a RabbitMQ.
    - channel: pika.Channel - Canal de comunicación con RabbitMQ.
MÉTODOS:
    - __init__(): Inicializa la conexión y el canal de RabbitMQ.
    - consume_callback(ch, method, properties, body): Callback para manejar los mensajes recibidos.
    - process_order(order_id): Procesa un pedido y lo intenta entregar.
    - deliver_order(): Simula el proceso de entrega de un pedido.
    - close(): Cierra el canal y la conexión de RabbitMQ.
"""

import random
import time
import pika 
from saimazoom import config


class Deliverer:
    def __init__(self):

        self.connection = pika.BlockingConnection(pika.ConnectionParameters(host=config.queue_server))
        self.channel = self.connection.channel()
    
        #COLA DONDE RECIBIMOS TAREAS
        self.channel.queue_declare(queue=config.deliver_queue, durable=False, auto_delete=True)
        self.channel.basic_consume(queue=config.deliver_queue, on_message_callback=self.consume_callback)

        #COLA DONDE ENVIAMOS RESPUESTAS
        self.channel.queue_declare(queue=config.deliver_response_queue, durable=False, auto_delete=True)
    
    """
    FUNCIÓN: consume_callback(ch, method, properties, body)
    ARGS_IN: ch - canal de comunicación
              method - método de entrega
              properties - propiedades del mensaje
              body - cuerpo del mensaje recibido
    DESCRIPCIÓN: Callback para manejar los mensajes recibidos en la cola de entrega.
                Recibe mensajes de la forma "DELIVER order_id" y procesa el pedido.
    ARGS_OUT: None
    """
    def consume_callback(self, ch, method, properties, body):
        parts = body.decode('utf-8').split(" ")
        print(f"Deliverer received {body}", flush=True)

        action = parts[0]

        match action:
            case "DELIVER":
                order_id = parts[1]
                print(f"Recibido pedido con id: {order_id}", flush=True)

                # Notificar al Controller que el pedido está en distribución
                self.channel.basic_publish(
                    exchange='',
                    routing_key=config.deliver_response_queue,
                    body=f"DISTRIBUTING {order_id}"  # DISTRIBUTION order_id
                )

                # Confirmar el mensaje recibido
                ch.basic_ack(delivery_tag=method.delivery_tag)

                # Procesar el pedido (intentar entregarlo)
                self.process_order(order_id)
                
            case _:
                print(f"Mensaje no reconocido: {body}", flush=True)
                ch.basic_ack(delivery_tag=method.delivery_tag)

    """
    FUNCIÓN: process_order(order_id)
    ARGS_IN: order_id - id del pedido a procesar
    DESCRIPCIÓN: Procesa un pedido y lo intenta entregar.
                Intenta entregar el pedido un número determinado de veces.
    ARGS_OUT: None
    """
    def process_order(self, order_id):
        success = False
        # Intentar entregar el pedido tantas veces como se haya configurado
        for _ in range(config.deliver_attempts):
            success = self.deliver_order()
            if success:
                break
        # Se notifica al controlador si la entrega fue exitosa o no
        if success:
            self.channel.basic_publish(exchange='', routing_key=config.deliver_response_queue, body=f"DELIVERED {order_id}") #DELIVERED order_id
        else:
            self.channel.basic_publish(exchange='', routing_key=config.deliver_response_queue, body=f"FAILED_DELIVERY {order_id}") #FAILED DELIVERY order_id
    
    """
    FUNCIÓN: deliver_order()
    ARGS_IN: None
    DESCRIPCIÓN: Simula el proceso de entrega de un pedido.
                Genera un número aleatorio para determinar si la entrega fue exitosa o no.
    ARGS_OUT: bool - True si la entrega fue exitosa, False en caso contrario.
    """
    def deliver_order(self):
        time.sleep(random.randint(config.deliver_min, config.deliver_max))  # Simular tiempo de procesamiento
        return random.random() < config.p_deliver
    
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