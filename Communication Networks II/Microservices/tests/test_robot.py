import unittest
from unittest.mock import patch
from saimazoom.clases.robot import Robot
from saimazoom import config

class TestRobot(unittest.TestCase):

    @patch('pika.BlockingConnection')
    def test_consume_callback_move_found(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Crear una instancia del Robot
        robot = Robot()

        # Mockear los métodos find_order y simulate_conveyor_belt
        robot.find_order = lambda order_id, products_ids: True
        robot.simulate_conveyor_belt = lambda: None

        # Simular un mensaje MOVE con productos encontrados
        body = b"MOVE 12345 101 102"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()

        # Llamar a consume_callback
        robot.consume_callback(mock_channel, method, None, body)

        # Verificar que se envió el mensaje IN_CONVEYOR_BELT
        mock_channel.basic_publish.assert_any_call(
            exchange='',
            routing_key=config.robot_response_queue,
            body="IN_CONVEYOR_BELT 12345"
        )

        # Verificar que se envió el mensaje READY
        mock_channel.basic_publish.assert_any_call(
            exchange='',
            routing_key=config.robot_response_queue,
            body="READY 12345"
        )

        # Verificar que se reconoció el mensaje
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_consume_callback_move_not_found(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Crear una instancia del Robot
        robot = Robot()

        # Mockear el método find_order para simular que no se encuentran los productos
        robot.find_order = lambda order_id, products_ids: False

        # Simular un mensaje MOVE con productos no encontrados
        body = b"MOVE 12345 101 102"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()

        # Llamar a consume_callback
        robot.consume_callback(mock_channel, method, None, body)

        # Verificar que se envió el mensaje NOT_FOUND
        mock_channel.basic_publish.assert_called_once_with(
            exchange='',
            routing_key=config.robot_response_queue,
            body="NOT_FOUND 12345"
        )

        # Verificar que se reconoció el mensaje
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)

    @patch('pika.BlockingConnection')
    def test_consume_callback_unrecognized_message(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de RabbitMQ
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        # Crear una instancia del Robot
        robot = Robot()

        # Simular un mensaje no reconocido
        body = b"UNKNOWN_ACTION"
        method = type('MockMethod', (object,), {'delivery_tag': 1})()

        # Llamar a consume_callback
        robot.consume_callback(mock_channel, method, None, body)

        # Verificar que no se llamó a basic_publish
        mock_channel.basic_publish.assert_not_called()

        # Verificar que se reconoció el mensaje
        mock_channel.basic_ack.assert_called_once_with(delivery_tag=1)