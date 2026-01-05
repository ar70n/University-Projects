import unittest
import pika
from saimazoom import config
from saimazoom.clases.order_state import OrderState
from unittest.mock import patch
from saimazoom.clases.controller import Controller

class TestController(unittest.TestCase):

    @patch('pika.BlockingConnection')
    def test_client_callback_add(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Reemplazar el método add_order con una función que registre la llamada
        calls = []
        def mock_add_order(channel, method, properties, client_id, products_ids):
            calls.append((channel, method, properties, client_id, products_ids))
        controller.add_order = mock_add_order

        # Simular un mensaje ADD
        body = b"ADD ORDER 12345 101 102"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a client_callback
        controller.client_callback(mock_channel, method, properties, body)

        # Verificar que se llamó a add_order con los argumentos correctos
        self.assertEqual(len(calls), 1)
        self.assertEqual(calls[0], (mock_channel, method, properties, "12345", ["101", "102"]))

    @patch('pika.BlockingConnection')
    def test_client_callback_cancel(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Reemplazar el método cancel_order con una función que registre la llamada
        calls = []
        def mock_cancel_order(channel, method, properties, client_id, order_id):
            calls.append((channel, method, properties, client_id, order_id))
        controller.cancel_order = mock_cancel_order

        # Simular un mensaje CANCEL
        body = b"CANCEL ORDER 12345 67890"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a client_callback
        controller.client_callback(mock_channel, method, properties, body)

        # Verificar que se llamó a cancel_order con los argumentos correctos
        self.assertEqual(len(calls), 1)
        self.assertEqual(calls[0], (mock_channel, method, properties, "12345", "67890"))

    @patch('pika.BlockingConnection')
    def test_client_callback_show(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Reemplazar el método show_orders con una función que registre la llamada
        calls = []
        def mock_show_orders(channel, method, properties, client_id):
            calls.append((channel, method, properties, client_id))
        controller.show_orders = mock_show_orders

        # Simular un mensaje SHOW
        body = b"SHOW ORDER 12345"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a client_callback
        controller.client_callback(mock_channel, method, properties, body)

        # Verificar que se llamó a show_orders con los argumentos correctos
        self.assertEqual(len(calls), 1)
        self.assertEqual(calls[0], (mock_channel, method, properties, "12345"))

    @patch('pika.BlockingConnection')
    def test_client_callback_register(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Reemplazar el método register_client con una función que registre la llamada
        calls = []
        def mock_register_client(channel, method, properties, client_id):
            calls.append((channel, method, properties, client_id))
        controller.register_client = mock_register_client

        # Simular un mensaje REGISTER
        body = b"REGISTER ORDER 12345"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a client_callback
        controller.client_callback(mock_channel, method, properties, body)

        # Verificar que se llamó a register_client con los argumentos correctos
        self.assertEqual(len(calls), 1)
        self.assertEqual(calls[0], (mock_channel, method, properties, "12345"))

    @patch('pika.BlockingConnection')
    def test_client_callback_unknown_command(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un mensaje con un comando no reconocido
        body = b"UNKNOWN ORDER 12345"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a client_callback
        controller.client_callback(mock_channel, method, properties, body)

        # Verificar que se envió un mensaje de error
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body="ERROR Unknown command UNKNOWN"
        )

        # Verificar que se reconoció el mensaje
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)


    @patch('pika.BlockingConnection')
    def test_robot_callback_in_conveyor_belt(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear un pedido con estado inicial
        order_id = "NikeAzules"
        controller.orders[order_id] = type('MockOrder', (object,), {'state': OrderState.WAREHOUSE})()

        # Simular un mensaje IN_CONVEYOR_BELT
        body = f"IN_CONVEYOR_BELT {order_id}".encode('utf-8')
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a robot_callback
        controller.robot_callback(mock_channel, method, properties, body)

        # Verificar que el estado del pedido cambió a CONVEYOR_BELT
        self.assertEqual(controller.orders[order_id].state, OrderState.CONVEYOR_BELT)
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_robot_callback_ready(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear un pedido con estado inicial
        order_id = "NikeAzules"
        controller.orders[order_id] = type('MockOrder', (object,), {'state': OrderState.CONVEYOR_BELT})()

        # Simular un mensaje READY
        body = f"READY {order_id}".encode('utf-8')
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a robot_callback
        controller.robot_callback(mock_channel, method, properties, body)

        # Verificar que el estado del pedido cambió a READY_FOR_DISTRIBUTION
        self.assertEqual(controller.orders[order_id].state, OrderState.READY_FOR_DISTRIBUTION)

        # Verificar que se envió un mensaje al deliverer
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key=config.deliver_queue,
            properties=pika.BasicProperties(delivery_mode=pika.DeliveryMode.Persistent),
            body=f"DELIVER {order_id}"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_robot_callback_not_found(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear un pedido con estado inicial
        order_id = "NikeAzules"
        controller.orders[order_id] = type('MockOrder', (object,), {'state': OrderState.WAREHOUSE})()

        # Simular un mensaje NOT_FOUND
        body = f"NOT_FOUND {order_id}".encode('utf-8')
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a robot_callback
        controller.robot_callback(mock_channel, method, properties, body)

        # Verificar que el estado del pedido cambió a CANCELLED
        self.assertEqual(controller.orders[order_id].state, OrderState.CANCELLED)
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_robot_callback_unknown_message(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un mensaje desconocido
        body = b"UNKNOWN_ACTION NikeAzules"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a robot_callback
        controller.robot_callback(mock_channel, method, properties, body)

        # Verificar que no se cambió el estado del pedido
        mock_channel.basic_publish.assert_not_called()
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_deliver_callback_distributing(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear un pedido con estado inicial
        order_id = "NikeAzules"
        controller.orders[order_id] = type('MockOrder', (object,), {'state': OrderState.READY_FOR_DISTRIBUTION})()

        # Simular un mensaje DISTRIBUTING
        body = f"DISTRIBUTING {order_id}".encode('utf-8')
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a deliver_callback
        controller.deliver_callback(mock_channel, method, properties, body)

        # Verificar que el estado del pedido cambió a IN_DISTRIBUTION
        self.assertEqual(controller.orders[order_id].state, OrderState.IN_DISTRIBUTION)
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_deliver_callback_delivered(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear un pedido con estado inicial
        order_id = "NikeAzules"
        controller.orders[order_id] = type('MockOrder', (object,), {'state': OrderState.IN_DISTRIBUTION})()

        # Simular un mensaje DELIVERED
        body = f"DELIVERED {order_id}".encode('utf-8')
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a deliver_callback
        controller.deliver_callback(mock_channel, method, properties, body)

        # Verificar que el estado del pedido cambió a DELIVERED
        self.assertEqual(controller.orders[order_id].state, OrderState.DELIVERED)
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_deliver_callback_failed_delivery(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear un pedido con estado inicial
        order_id = "NikeAzules"
        controller.orders[order_id] = type('MockOrder', (object,), {'state': OrderState.IN_DISTRIBUTION})()

        # Simular un mensaje FAILED_DELIVERY
        body = f"FAILED_DELIVERY {order_id}".encode('utf-8')
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a deliver_callback
        controller.deliver_callback(mock_channel, method, properties, body)

        # Verificar que el estado del pedido cambió a RETURNED
        self.assertEqual(controller.orders[order_id].state, OrderState.RETURNED)
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_deliver_callback_unknown_message(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un mensaje desconocido
        body = b"UNKNOWN_ACTION NikeAzules"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {})()

        # Llamar a deliver_callback
        controller.deliver_callback(mock_channel, method, properties, body)

        # Verificar que no se cambió el estado del pedido
        mock_channel.basic_publish.assert_not_called()
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)


    @patch('pika.BlockingConnection')
    def test_add_order_success(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear datos iniciales
        client_id = "PrrPrrPatapim"
        products_ids = ["product_1", "product_2"]
        controller.clients_orders[client_id] = []

        # Simular un mensaje ADD
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a add_order
        controller.add_order(mock_channel, method, properties, client_id, products_ids)

        # Verificar que se añadió el pedido
        self.assertEqual(len(controller.clients_orders[client_id]), 1)
        new_order = controller.clients_orders[client_id][0]
        self.assertEqual(new_order.products_id, products_ids)
        self.assertIn(new_order.id, controller.orders)

        # Verificar que se enviaron los mensajes correctos
        self.assertEqual(mock_channel.basic_publish.call_count, 2)
        mock_channel.basic_publish.assert_any_call(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"ADDED {new_order.id}"
        )
        mock_channel.basic_publish.assert_any_call(
            exchange='',
            routing_key=config.robot_queue,
            properties=pika.BasicProperties(delivery_mode=pika.DeliveryMode.Persistent),
            body=f"MOVE {new_order.id} {products_ids}"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_add_order_client_not_registered(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un mensaje ADD con cliente no registrado
        client_id = "PrrPrrPatapim"
        products_ids = ["product_1", "product_2"]
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a add_order
        controller.add_order(mock_channel, method, properties, client_id, products_ids)

        # Verificar que no se añadió el pedido
        self.assertNotIn(client_id, controller.clients_orders)

        # Verificar que se envió un mensaje de error
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"ERROR Client {client_id} not registered"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_cancel_order_client_not_registered(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un mensaje CANCEL con cliente no registrado
        client_id = "PrrPrrPatapim"
        order_id = "order_456"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a cancel_order
        controller.cancel_order(mock_channel, method, properties, client_id, order_id)

        # Verificar que se envió un mensaje de error
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"ERROR Client {client_id} not registered"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_cancel_order_order_not_found(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear datos iniciales
        client_id = "PrrPrrPatapim"
        controller.clients_orders[client_id] = []

        # Simular un mensaje CANCEL con pedido no encontrado
        order_id = "order_456"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a cancel_order
        controller.cancel_order(mock_channel, method, properties, client_id, order_id)

        # Verificar que se envió un mensaje de error
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"ERROR Order {order_id} not found"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_cancel_order_cannot_be_cancelled(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear datos iniciales
        client_id = "PrrPrrPatapim"
        order_id = "order_456"
        controller.clients_orders[client_id] = []
        controller.orders[order_id] = type('MockOrder', (object,), {'id': order_id, 'state': OrderState.DELIVERED})()

        # Simular un mensaje CANCEL con pedido que no puede ser cancelado
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a cancel_order
        controller.cancel_order(mock_channel, method, properties, client_id, order_id)

        # Verificar que se envió un mensaje de error
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"ERROR Order {order_id} cannot be cancelled"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_cancel_order_success(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear datos iniciales
        client_id = "PrrPrrPatapim"
        order_id = "order_456"
        controller.clients_orders[client_id] = []
        controller.orders[order_id] = type('MockOrder', (object,), {'id': order_id, 'state': OrderState.WAREHOUSE})()

        # Simular un mensaje CANCEL exitoso
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a cancel_order
        controller.cancel_order(mock_channel, method, properties, client_id, order_id)

        # Verificar que el estado del pedido cambió a CANCELLED
        self.assertEqual(controller.orders[order_id].state, OrderState.CANCELLED)

        # Verificar que se envió un mensaje de confirmación
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"CANCELLED {order_id}"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)
        
    @patch('pika.BlockingConnection')
    def test_show_orders_client_not_registered(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un cliente no registrado
        client_id = "PrrPrrPatapim"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a show_orders
        controller.show_orders(mock_channel, method, properties, client_id)

        # Verificar que se envió un mensaje de error
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"ERROR Client {client_id} not registered"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_show_orders_success(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear datos iniciales
        client_id = "PrrPrrPatapim"
        mock_order_1 = type('MockOrder', (object,), {'__str__': lambda self: "Order1"})()
        mock_order_2 = type('MockOrder', (object,), {'__str__': lambda self: "Order2"})()
        controller.clients_orders[client_id] = [mock_order_1, mock_order_2]

        # Simular un mensaje SHOW
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a show_orders
        controller.show_orders(mock_channel, method, properties, client_id)

        # Verificar que se envió el mensaje correcto
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"SHOWED {client_id} Order1Order2"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)
            
    @patch('pika.BlockingConnection')
    def test_register_client_already_registered(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Mockear datos iniciales
        client_id = "PrrPrrPatapim"
        controller.clients_orders[client_id] = []

        # Simular un mensaje REGISTER para un cliente ya registrado
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a register_client
        controller.register_client(mock_channel, method, properties, client_id)

        # Verificar que se envió el mensaje de LOGGED_IN
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"LOGGED_IN {client_id}"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_register_client_new_client(self, mock_blocking_connection):
        # Mock de la conexión y el canal de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value

        # Crear una instancia del Controller
        controller = Controller()

        # Simular un mensaje REGISTER para un cliente nuevo
        client_id = "PrrPrrPatapim"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()
        properties = type('MockProperties', (object,), {
            'reply_to': 'mock_reply_to',
            'correlation_id': 'mock_corr_id'
        })()

        # Llamar a register_client
        controller.register_client(mock_channel, method, properties, client_id)

        # Verificar que el cliente fue registrado
        self.assertIn(client_id, controller.clients_orders)
        self.assertEqual(controller.clients_orders[client_id], [])

        # Verificar que se envió el mensaje de REGISTERED
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key='mock_reply_to',
            properties=pika.BasicProperties(correlation_id='mock_corr_id'),
            body=f"REGISTERED {client_id}"
        )
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)