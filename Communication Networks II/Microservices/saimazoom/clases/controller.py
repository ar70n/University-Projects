"""
    CLASE: Controller
    DESCRIPCIÓN: Clase que representa el controlador principal del sistema. 
                Se encarga de gestionar los pedidos, clientes y la comunicación con los robots y repartidores 
                a través de RabbitMQ. Implementa un patrón Singleton.
    ATRIBUTOS:
        - orders: Diccionario que almacena los pedidos por su ID.
        - clients_orders: Diccionario que almacena los pedidos asociados a cada cliente.
        - lock: Objeto threading.Lock para manejar la concurrencia.
        - connection: Conexión a RabbitMQ.
        - channel: Canal de comunicación con RabbitMQ.
    MÉTODOS:
        - __init__: Inicializa el controlador, carga los datos de la base de datos y configura las colas de RabbitMQ.
        - close: Guarda los datos en la base de datos y cierra el controlador.
        - client_callback: Callback para manejar los mensajes provenientes de los clientes.
        - robot_callback: Callback para manejar los mensajes provenientes de los robots.
        - deliver_callback: Callback para manejar los mensajes provenientes de los repartidores.
        - add_order: Añade un nuevo pedido al sistema.
        - cancel_order: Cancela un pedido existente.
        - show_orders: Muestra todos los pedidos asociados a un cliente.
        - register_client: Registra un nuevo cliente en el sistema.
        - simulate_conveyor_belt: Simula el funcionamiento de la cinta transportadora.
"""

import pika
import random
import time
from saimazoom.clases.order import Order
from saimazoom import database
from saimazoom import config
import threading
from saimazoom.clases.order_state import OrderState
from uuid import uuid4

class Controller:
    def __init__(self):
        data = database.load()
        self.orders = data["orders"]  # Diccionario de pedidos
        self.clients_orders = data["clients_orders"]  # Diccionario de pedidos por cliente
        self.lock = threading.Lock() # Lock para manejar la concurrencia

        #print(f"Loaded orders: {self.orders}", flush=True)
        #print(f"Loaded clients orders: {self.clients_orders}", flush=True)

        # Conexión a la cola de mensajes
        self.connection = pika.BlockingConnection(pika.ConnectionParameters(host=config.queue_server))
        self.channel = self.connection.channel()
        
        #CLIENTE
        self.channel.queue_declare(queue=config.client_queue, durable=False, auto_delete=True)
        self.channel.basic_qos(prefetch_count=1) #ESTO CREO QUE AFECTA A TODOS
        self.channel.basic_consume(queue=config.client_queue, on_message_callback = self.client_callback)
        
        #ROBOT
        self.channel.queue_declare(queue=config.robot_queue, durable=False, auto_delete=True)
        self.channel.queue_declare(queue=config.robot_response_queue, durable=False, auto_delete=True)
        self.channel.basic_consume(queue=config.robot_response_queue, on_message_callback = self.robot_callback)
        
        #DELIVER
        self.channel.queue_declare(queue=config.deliver_queue, durable=False, auto_delete=True)
        self.channel.queue_declare(queue=config.deliver_response_queue, durable=False, auto_delete=True)
        self.channel.basic_consume(queue=config.deliver_response_queue, on_message_callback = self.deliver_callback)

    """
    FUNCIÓN: close(self)
    ARGS_IN: self - instancia de la clase Controller
    DESCRIPCIÓN: Cierra la conexión con RabbitMQ y guarda los datos en la base de datos.
    ARGS_OUT: None
    """
    def close(self):
        print("Closing controller", flush=True)
        data = {
            "orders": self.orders,
            "clients_orders": self.clients_orders,
        }
        database.save(data)


    #FUNCIONES CALLBACK
    """
    FUNCIÓN: client_callback(self, ch, method, properties, body)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                body - cuerpo del mensaje
    DESCRIPCIÓN: Callback para manejar los mensajes provenientes de los clientes.
    ARGS_OUT: None
    """
    def client_callback(self, ch, method, properties, body):
        parts = body.decode('utf-8').split(" ")

        client_id = parts[2]
        
        match parts[0]:
            case "ADD":
                self.add_order(ch, method, properties, client_id, parts[3:])
            case "CANCEL":
                self.cancel_order(ch, method, properties, client_id, parts[3])
            case "SHOW":
                self.show_orders(ch, method, properties, client_id)
            case "REGISTER":
                self.register_client(ch, method, properties, client_id)
            case  _:
                # Si el comando no se reconoce, se envía un mensaje de error al cliente
                ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
                body=f"ERROR Unknown command {parts[0]}")
                ch.basic_ack(delivery_tag=method.delivery_tag)
                print (f"Mensaje desconocido recibido de un cliente: {body}", flush=True)

    """
    FUNCIÓN: robot_callback(self, ch, method, properties, body)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                body - cuerpo del mensaje
    DESCRIPCIÓN: Callback para manejar los mensajes provenientes de los robots.
    ARGS_OUT: None
    """
    def robot_callback(self, ch, method, properties, body):
        parts = body.decode('utf-8').split(" ")

        action = parts[0]

        #Si la acción no se conoce, no se hace nada
        if action not in {"IN_CONVEYOR_BELT", "READY", "NOT_FOUND"}:
            ch.basic_ack(delivery_tag=method.delivery_tag)
            print(f"Mensaje desconocido recibido de un robot: {body}", flush=True)
            return

        order_id = parts[1]
        if self.orders[order_id].state != OrderState.CANCELLED:
            match action:
                case "IN_CONVEYOR_BELT":                
                    self.orders[order_id].state = OrderState.CONVEYOR_BELT
                case "READY":
                    self.orders[order_id].state = OrderState.READY_FOR_DISTRIBUTION
                    # Notificar al deliverer de que el pedido está listo para repartir
                    self.channel.basic_publish(exchange='', routing_key=config.deliver_queue, properties=pika.BasicProperties(
                    delivery_mode=pika.DeliveryMode.Persistent), body=f"DELIVER {order_id}")
                    print(f"Pedido ({order_id}) listo para repartir")
                case "NOT_FOUND":
                    self.orders[order_id].state = OrderState.CANCELLED
                    print(f"Falta uno de los productos del pedido ({order_id}). Se cancela el pedido")

        # Confirmamos el mensaje
        ch.basic_ack(delivery_tag=method.delivery_tag)
        
    """
    FUNCIÓN: deliver_callback(self, ch, method, properties, body)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                body - cuerpo del mensaje
    DESCRIPCIÓN: Callback para manejar los mensajes provenientes de los repartidores.
    ARGS_OUT: None
    """
    def deliver_callback(self, ch, method, properties, body):
        parts = body.decode('utf-8').split(" ")

        action = parts[0]
        order_id = parts[1]

        match action:
            case "DISTRIBUTING":
                self.orders[order_id].state = OrderState.IN_DISTRIBUTION
                print(f"Pedido ({order_id}) en distribución")
            case "DELIVERED":
                self.orders[order_id].state = OrderState.DELIVERED
                print(f"Pedido ({order_id}) entregado")
            case "FAILED_DELIVERY":
                self.orders[order_id].state = OrderState.RETURNED
                print(f"Pedido ({order_id}) retornado")
            case _:
                print(f"Mensaje desconocido recibido de un repartidor: {body}", flush=True)

        # Confirmamos el mensaje
        ch.basic_ack(delivery_tag=method.delivery_tag)


    # FUNCIONES PRINCIPALES 
    """
    FUNCIÓN: add_order(self, ch, method, properties, client_id, products_ids)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                client_id - ID del cliente
                products_ids - lista de IDs de los productos
    DESCRIPCIÓN: Añade un nuevo pedido al sistema.
    ARGS_OUT: None
    """  
    def add_order(self, ch, method, properties, client_id, products_ids):
        # Comprobamos si el cliente está registrado
        if client_id not in self.clients_orders.keys():
            ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
            body=f"ERROR Client {client_id} not registered")
            ch.basic_ack(delivery_tag=method.delivery_tag)
            print(f"Error al añadir un pedido. Cliente {client_id} no registrado", flush=True)
            return
        
        new_order = Order()
        
        # Asignamos un id al pedido
        with self.lock:
            new_order.id = str(uuid4())

        new_order.products_id = products_ids
        self.clients_orders[client_id].append(new_order)
        self.orders[new_order.id] = new_order

        print(f"Pedido registrado: [{ new_order.id}]", flush=True)
        print("Ids de los productos: ", new_order.products_id, flush=True)

        # Informamos al cliente de que se ha añadido el pedido
        ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
        body=f"ADDED {new_order.id}")
        ch.basic_ack(delivery_tag=method.delivery_tag)
        
        # Enviamos el pedido a los robots
        self.channel.basic_publish(exchange='', routing_key=config.robot_queue, properties=pika.BasicProperties(
        delivery_mode=pika.DeliveryMode.Persistent), body=f"MOVE {new_order.id} {products_ids}")

        print(f"Pedido ({new_order.id}) registrado correctamente", flush=True)

    """
    FUNCIÓN: cancel_order(self, ch, method, properties, client_id, order_id)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                client_id - ID del cliente
                order_id - ID del pedido
    DESCRIPCIÓN: Cancela un pedido existente.
    ARGS_OUT: None
    """
    def cancel_order(self, ch, method, properties, client_id, order_id):
        # Comprobamos si el cliente está registrado
        if client_id not in self.clients_orders.keys():
            ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
            body=f"ERROR Client {client_id} not registered")
            ch.basic_ack(delivery_tag=method.delivery_tag)
            print(f"Error al cancelar un pedido. Cliente {client_id} no registrado", flush=True)
            return
        
        # Comprobamos si el pedido existe
        if order_id not in self.orders.keys():
            ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
            body=f"ERROR Order {order_id} not found")
            ch.basic_ack(delivery_tag=method.delivery_tag)
            print(f"Error. Pedido {order_id} no encontrado", flush=True)
            return
        
        # Comprobamos si el pedido se puede cancelar
        order = self.orders[order_id]

        if order.state in {OrderState.READY_FOR_DISTRIBUTION, OrderState.IN_DISTRIBUTION, OrderState.DELIVERED, OrderState.RETURNED, OrderState.CANCELLED}:
            ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
            body=f"ERROR Order {order.id} cannot be cancelled")
            ch.basic_ack(delivery_tag=method.delivery_tag)
            print(f"Error. El pedido {order.id} no puede ser cancelado", flush=True)
            return

        # Cancelamos el pedido
        ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
        body=f"CANCELLED {order.id}")
        ch.basic_ack(delivery_tag=method.delivery_tag)
        print(f"Pedido cancelado con id: {order.id}", flush=True)
        order.state = OrderState.CANCELLED


    """
    FUNCIÓN: show_orders(self, ch, method, properties, client_id)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                client_id - ID del cliente
    DESCRIPCIÓN: Muestra todos los pedidos asociados a un cliente.
    ARGS_OUT: None
    """
    def show_orders(self, ch, method, properties, client_id):
        # Comprobamos si el cliente está registrado
        if client_id not in self.clients_orders.keys():
            ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
            body=f"ERROR Client {client_id} not registered")
            ch.basic_ack(delivery_tag=method.delivery_tag)
            print(f"Sent ERROR Client {client_id} not registered", flush=True)
            return
        
        response = ""
        for order in self.clients_orders[client_id]:
            response += order.__str__()
        
        # Le mandamos al cliente la lista de pedidos
        ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
        body=f"SHOWED {client_id} {response}")
        ch.basic_ack(delivery_tag=method.delivery_tag)
        print(f"Sent SHOWED {client_id} {response}", flush=True)


    """
    FUNCIÓN: register_client(self, ch, method, properties, client_id)
    ARGS_IN: self - instancia de la clase Controller
                ch - canal de comunicación con RabbitMQ
                method - método de comunicación
                properties - propiedades del mensaje
                client_id - ID del cliente
    DESCRIPCIÓN: Registra un nuevo cliente en el sistema.
    ARGS_OUT: None
    """
    def register_client(self, ch, method, properties, client_id):
        print("Registering client", flush=True)
        body = ""
        if client_id in self.clients_orders.keys():
            print("Logged in", flush=True)
            body = f"LOGGED_IN {client_id}"
        else:
            self.clients_orders[client_id] = []
            print("Registered", flush=True)
            body = f"REGISTERED {client_id}"

        # Informamos al cliente de su registro/inicio de sesión
        ch.basic_publish(exchange='', routing_key=properties.reply_to, properties=pika.BasicProperties(correlation_id=properties.correlation_id),
        body=body)
        ch.basic_ack(delivery_tag=method.delivery_tag)
        print(f"Cliente loggeado/registrado: {client_id}", flush=True) # with correlation id {properties.correlation_id}