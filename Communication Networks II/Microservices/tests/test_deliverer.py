import unittest
from unittest.mock import patch
from saimazoom.clases.deliverer import Deliverer
from saimazoom import config

class TestDeliverer(unittest.TestCase):

    @patch('pika.BlockingConnection')
    def test_consume_callback_deliver(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Crear una instancia del Deliverer
        deliverer = Deliverer()

        # Simular un mensaje DELIVER
        body = b"DELIVER 12345"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()

        # Llamar a consume_callback
        deliverer.consume_callback(mock_channel, method, None, body)

        # Verificar que se enviaron dos mensajes al controlador: distributing y delivered/returned
        self.assertEqual(mock_channel.basic_publish.call_count, 2)

        # Verificar que se reconoció el mensaje
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_consume_callback_unrecognized_message(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Crear una instancia del Deliverer
        deliverer = Deliverer()

        # Simular un mensaje no reconocido
        body = b"UNKNOWN_ACTION"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()

        # Llamar a consume_callback
        deliverer.consume_callback(mock_channel, method, None, body)

        # Verificar que no se llamó a basic_publish
        mock_channel.basic_publish.assert_not_called()

        # Verificar que se reconoció el mensaje
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    @patch('saimazoom.clases.deliverer.Deliverer.deliver_order')
    def test_process_order_success(self, mock_deliver_order, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Configurar deliver_order para devolver True en el primer intento
        mock_deliver_order.return_value = True

        # Crear una instancia del Deliverer
        deliverer = Deliverer()

        # Llamar a process_order
        order_id = "12345"
        deliverer.process_order(order_id)

        # Verificar que se envió un mensaje DELIVERED
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key=config.deliver_response_queue,
            body=f"DELIVERED {order_id}"
        )

    @patch('pika.BlockingConnection')
    @patch('saimazoom.clases.deliverer.Deliverer.deliver_order')
    def test_process_order_failure(self, mock_deliver_order, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Configurar deliver_order para devolver False en todos los intentos
        mock_deliver_order.return_value = False

        # Crear una instancia del Deliverer
        deliverer = Deliverer()

        # Llamar a process_order
        order_id = "12345"
        deliverer.process_order(order_id)

        # Verificar que se envió un mensaje FAILED_DELIVERY
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key=config.deliver_response_queue,
            body=f"FAILED_DELIVERY {order_id}"
        )
