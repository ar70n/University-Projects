"""
    CLASE: Client
    DESCRIPCIÓN: Clase que representa al cliente (no la aplicación de consola). 
                Se encarga de la comunicación con el controlador a través de RabbitMQ.
    ATRIBUTOS:
        - id: ID del cliente.
        - corr_id: ID de correlación para identificar las respuestas del controlador.
        - connection: Conexión a RabbitMQ.
        - channel: Canal de comunicación con RabbitMQ.
        - callback_queue: Cola de respuestas del cliente.
    MÉTODOS:
        - __init__: Inicializa la conexión a RabbitMQ y declara la cola de respuestas.
        - show_all_orders: Muestra todos los pedidos del cliente.
        - add_order: Añade un nuevo pedido.
        - cancel_order: Cancela un pedido existente.
        - register_client: Registra un nuevo cliente.
        - client_callback: Callback para recibir mensajes del controlador.
"""

from saimazoom.clases.order import Order
import pika
from saimazoom import config
from uuid import uuid4
import time


class Client(object):
    def __init__(self):
        self.id = -1
        self.corr_id = None

        try:
            # Establecer conexión con RabbitMQ
            self.connection = pika.BlockingConnection(pika.ConnectionParameters(config.queue_server))
            self.channel = self.connection.channel()

            # Declarar la cola de respuestas
            result = self.channel.queue_declare(queue=f'{config.base_client_response_queue}_{str(uuid4())}', durable=False, auto_delete=True)
            self.callback_queue = result.method.queue

            # Configurar el consumidor para la cola de respuestas
            self.channel.basic_consume(queue=self.callback_queue, on_message_callback=self.client_callback, auto_ack=True)

            print("Conexión establecida con RabbitMQ.")

        except pika.exceptions.AMQPConnectionError as e:
            print(f"Error al conectar con RabbitMQ: {e}.")
            self.connection = None

    """
    FUNCIÓN: show_all_orders(self)
    ARGS_IN: self - instancia de la clase Client
    DESCRIPCIÓN: muestra todos los pedidos del cliente
    ARGS_OUT: None    
    """
    def show_all_orders(self):
        self.response = None
        self.corr_id = str(uuid4())

        # Enviar mensaje al controlador para mostrar todos los pedidos
        self.channel.basic_publish(exchange='', routing_key=config.client_queue, properties=pika.BasicProperties(
                reply_to=self.callback_queue,
                correlation_id=self.corr_id,
            ), body=f"SHOW ORDERS {self.id}")

        # Esperar la respuesta
        self.connection.process_data_events(time_limit=config.client_timeout)

        if self.response == None:
            return "Time exceeded. Controller not responding."
        elif self.response == "ERROR Client -1 not registered":
            return "Client not registered. Please register first."
        elif self.response == "":
            return "No orders found."

        return self.response
    
    """
    FUNCIÓN: show_order(self, order_id)
    ARGS_IN: self - instancia de la clase Client
             order_id - id del pedido a mostrar
    DESCRIPCIÓN: muestra un pedido del cliente
    ARGS_OUT: None
    """
    def add_order(self, products_id):
        self.response = None
        self.corr_id = str(uuid4())

        # Enviar el mensaje para añadir el pedido al controlador
        self.channel.basic_publish(
            exchange='',
            routing_key=config.client_queue,
            properties=pika.BasicProperties(
                reply_to=self.callback_queue,
                correlation_id=self.corr_id,
            ),
            body=f"ADD ORDER {self.id} {products_id}"
        )

        # Esperar la respuesta
        self.connection.process_data_events(time_limit=config.client_timeout)

        if self.response == None:
            return "Time exceeded. Controller not responding."
        elif self.response == "ERROR Client -1 not registered":
            return "Client not registered. Please register first."

        return self.response

    """
    FUNCIÓN: show_order(self, order_id)
    ARGS_IN: self - instancia de la clase Client
             order_id - id del pedido a mostrar
    DESCRIPCIÓN: muestra un pedido del cliente
    ARGS_OUT: None
    """
    def cancel_order(self, order_id):
        self.response = None
        self.corr_id = str(uuid4())
        # Enviar el mensaje de cancelación al controlador
        self.channel.basic_publish(exchange='', routing_key=config.client_queue, properties=pika.BasicProperties(
                reply_to=self.callback_queue,
                correlation_id=self.corr_id,
            ), body=f"CANCEL ORDER {self.id} {order_id}")

        # Esperar la respuesta
        self.connection.process_data_events(time_limit=config.client_timeout)

        if self.response == None:
            return "Time exceeded. Controller not responding."
        elif self.response == "ERROR Client -1 not registered":
            return "Client not registered. Please register first."
        
        return self.response

    """
    FUNCIÓN: login(self, client_id)
    ARGS_IN: self - instancia de la clase Client
             client_id - id del cliente a loguear
    DESCRIPCIÓN: loguea al cliente
    ARGS_OUT: None
    """
    def register_client(self, client_id):
        self.response = None
        self.corr_id = str(uuid4())
        self.id = client_id
        # Enviar el mensaje de registro al controlador
        self.channel.basic_publish(exchange='', routing_key=config.client_queue, properties=pika.BasicProperties(
                reply_to=self.callback_queue,
                correlation_id=self.corr_id,
            ), body=f"REGISTER CLIENT {self.id}")

        # Esperar la respuesta
        self.connection.process_data_events(time_limit=config.client_timeout)

        if self.response == None:
            return "Time exceeded. Controller not responding."
        
        return self.response
    
    """
    FUNCIÓN: client_callback(self, ch, method, properties, body)
    ARGS_IN: self - instancia de la clase Client
             ch - canal de comunicación
             method - método de comunicación
             properties - propiedades del mensaje
             body - cuerpo del mensaje
    DESCRIPCIÓN: callback para recibir mensajes del controlador
    ARGS_OUT: None
    """
    def client_callback(self, ch, method, properties, body):
        if self.corr_id != properties.correlation_id:
            self.response = "Received a message with a different correlation ID. Ignoring."
            return
        
        parts = body.decode('utf-8').split(" ")

        match parts[0]:
            case "REGISTERED":
                self.response = f"Client {parts[1]} registered successfully."

            case "LOGGED_IN":
                self.response = f"Client {parts[1]} logged in successfully."

            case "SHOWED":
                if len(parts) <= 3:
                    self.response = f"Client {parts[1]} has no orders."
                else:
                    self.response = f"Orders made by client {parts[1]}:\n"
                    self.response += " ".join(parts[2:])
                    
            case "CANCELLED":
                self.response = f"Order {parts[1]} cancelled"

            case "ADDED":
                self.response = f"Order {parts[1]} added"

            case "ERROR":
                self.response = body.decode('utf-8')

            case _:
                self.response = f"Unknown response: {body}"
                
        return