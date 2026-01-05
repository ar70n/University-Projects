import unittest
from unittest.mock import patch
from saimazoom import config
from saimazoom.clases.client import Client

class TestClient(unittest.TestCase):

    # =============================================================================
    # TESTS DE REGISTER
    # =============================================================================
    @patch('pika.BlockingConnection')
    def test_register_client_success(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"REGISTERED 123"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a register client
        response = client.register_client(123)

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "REGISTER CLIENT 123")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Client 123 registered successfully.")

    @patch('pika.BlockingConnection')
    def test_register_client_timeout(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()

        # Mock para simular un timeout (sin respuesta de RabbitMQ)
        def mock_process_data_events(*args, **kwargs):
            pass  # No llama a client_callback, simulando un timeout

        client.connection.process_data_events = mock_process_data_events

        # Llamar a register client
        response = client.register_client(123)

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "REGISTER CLIENT 123")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Time exceeded. Controller not responding.")


    # =============================================================================
    # TESTS DE ADD ORDER
    # =============================================================================
    @patch('pika.BlockingConnection')
    def test_add_order_success(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"ADDED 456"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a add_order
        response = client.add_order("1,2,3")

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "ADD ORDER 123 1,2,3")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Order 456 added")


    @patch('pika.BlockingConnection')
    def test_add_order_timeout(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular un timeout (sin respuesta de RabbitMQ)
        def mock_process_data_events(*args, **kwargs):
            pass  # No llama a client_callback, simulando un timeout

        client.connection.process_data_events = mock_process_data_events

        # Llamar a add_order
        response = client.add_order("1,2,3")

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "ADD ORDER 123 1,2,3")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Time exceeded. Controller not responding.")

    @patch('pika.BlockingConnection')
    def test_add_order_not_registered(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = -1  # Cliente no registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"ERROR Client -1 not registered"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a add_order
        response = client.add_order("1,2,3")

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Client not registered. Please register first.")


    # =============================================================================
    # TESTS DE SHOW ALL ORDERS
    # =============================================================================
    @patch('pika.BlockingConnection')
    def test_show_all_orders_success(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"SHOWED 123 Order1 Order2"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a show_all_orders
        response = client.show_all_orders()

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "SHOW ORDERS 123")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Orders made by client 123:\nOrder1 Order2")

    @patch('pika.BlockingConnection')
    def test_show_all_orders_no_orders(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"SHOWED 123"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a show_all_orders
        response = client.show_all_orders()

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Client 123 has no orders.")


    @patch('pika.BlockingConnection')
    def test_show_all_orders_not_registered(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = -1  # Cliente no registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"ERROR Client -1 not registered"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a show_all_orders
        response = client.show_all_orders()

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Client not registered. Please register first.")


    @patch('pika.BlockingConnection')
    def test_show_all_orders_timeout(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular un timeout (sin respuesta de RabbitMQ)
        def mock_process_data_events(*args, **kwargs):
            pass  # No llama a client_callback, simulando un timeout

        client.connection.process_data_events = mock_process_data_events

        # Llamar a show_all_orders
        response = client.show_all_orders()

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "SHOW ORDERS 123")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Time exceeded. Controller not responding.")


    # =============================================================================
    # TESTS DE CANCEL ORDER
    # =============================================================================
    @patch('pika.BlockingConnection')
    def test_cancel_order_success(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"CANCELLED 456"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a cancel_order
        response = client.cancel_order(456)

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "CANCEL ORDER 123 456")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Order 456 cancelled")

    @patch('pika.BlockingConnection')
    def test_cancel_order_timeout(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = 123  # Simular un cliente registrado

        # Mock para simular un timeout (sin respuesta de RabbitMQ)
        def mock_process_data_events(*args, **kwargs):
            pass  # No llama a client_callback, simulando un timeout

        client.connection.process_data_events = mock_process_data_events

        # Llamar a cancel_order
        response = client.cancel_order(456)

        # Verificar que basic_publish fue llamado
        self.assertTrue(mock_channel.basic_publish.called)

        # Verificar los argumentos de basic_publish
        call_args = mock_channel.basic_publish.call_args[1]
        self.assertEqual(call_args['exchange'], '')
        self.assertEqual(call_args['routing_key'], config.client_queue)
        self.assertEqual(call_args['body'], "CANCEL ORDER 123 456")
        self.assertEqual(call_args['properties'].correlation_id, client.corr_id)
        self.assertEqual(call_args['properties'].reply_to, 'mock_callback_queue')

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Time exceeded. Controller not responding.")

    @patch('pika.BlockingConnection')
    def test_cancel_order_not_registered(self, mock_blocking_connection):
        # Mock de la conexión, canal y cola de rabbitmq
        mock_connection = mock_blocking_connection.return_value
        mock_channel = mock_connection.channel.return_value
        mock_channel.queue_declare.return_value.method.queue = 'mock_callback_queue'

        client = Client()
        client.id = -1  # Cliente no registrado

        # Mock para simular una respuesta de RabbitMQ
        def mock_process_data_events(*args, **kwargs):
            client.client_callback(
                None, None, type('MockMethod', (object,), {'correlation_id': client.corr_id}),
                b"ERROR Client -1 not registered"
            )

        client.connection.process_data_events = mock_process_data_events

        # Llamar a cancel_order
        response = client.cancel_order(456)

        # Verificar la respuesta del cliente
        self.assertEqual(response, "Client not registered. Please register first.")
        

    if __name__ == '__main__':
        unittest.main()