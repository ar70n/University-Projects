import unittest
from unittest.mock import patch, MagicMock
import sys
import argparse
import random
import time
import paho.mqtt.client as mqtt
from clases.Sensor import Sensor
from clases.Switch import Switch
from clases.Switch import State
from clases.Clock import Clock


class TestDevice(unittest.TestCase):
    @patch('paho.mqtt.client.Client')
    def test_broker_connection_sensor(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value
        # Simulate a successful connection
        mock_client_instance.connect.return_value = mqtt.MQTT_ERR_SUCCESS

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        interval = 10
        min_value = 0
        max_value = 100
        increment = 5
        sensor_id = "1"

        # Create a Sensor instance
        sensor = Sensor(host, port, interval, min_value, max_value, increment, sensor_id)

        # Assert that the MQTT client was initialized and connected with the correct parameters
        MockMqttClient.assert_called_once()
        mock_client_instance.connect.assert_called_once_with(host, port)

        # Assert that the MQTT client callbacks were set
        self.assertEqual(sensor.mqttc.on_connect, sensor.on_connect)
        self.assertEqual(sensor.mqttc.on_message, sensor.on_message)
        self.assertEqual(sensor.mqttc.on_subscribe, sensor.on_subscribe)
        self.assertEqual(sensor.mqttc.on_unsubscribe, sensor.on_unsubscribe)
        self.assertEqual(sensor.mqttc.on_publish, sensor.on_publish)

    @patch('paho.mqtt.client.Client')
    def test_broker_connection_failure_sensor(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value

        # Simulate a connection failure
        mock_client_instance.connect.side_effect = Exception("Connection failed")

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        interval = 10
        min_value = 0
        max_value = 100
        increment = 5
        sensor_id = "1"

        # Attempt to create a Sensor instance and handle the exception
        with self.assertRaises(Exception) as context:
            sensor = Sensor(host, port, interval, min_value, max_value, increment, sensor_id)

        # Assert that the exception message is as expected
        self.assertEqual(str(context.exception), "Connection failed")

        # Assert that the MQTT client was initialized and connect was called
        MockMqttClient.assert_called_once()
        mock_client_instance.connect.assert_called_once_with(host, port)

    @patch('paho.mqtt.client.Client')
    def test_broker_connection_switch(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value
        # Simulate a successful connection
        mock_client_instance.connect.return_value = mqtt.MQTT_ERR_SUCCESS

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        probability = 0.5
        switch_id = "1"

        # Create a switch instance
        switch = Switch(host, port, probability, switch_id)

        # Assert that the MQTT client was initialized and connected with the correct parameters
        MockMqttClient.assert_called_once()
        mock_client_instance.connect.assert_called_once_with(host, port)

        # Assert that the MQTT client callbacks were set
        self.assertEqual(switch.mqttc.on_connect, switch.on_connect)
        self.assertEqual(switch.mqttc.on_message, switch.on_message)
        self.assertEqual(switch.mqttc.on_subscribe, switch.on_subscribe)
        self.assertEqual(switch.mqttc.on_unsubscribe, switch.on_unsubscribe)
        self.assertEqual(switch.mqttc.on_publish, switch.on_publish)

    @patch('paho.mqtt.client.Client')
    def test_broker_connection_failure_switch(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value

        # Simulate a connection failure
        mock_client_instance.connect.side_effect = Exception("Connection failed")

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        probability = 0.5
        switch_id = "1"

        # Attempt to create a Switch instance and handle the exception
        with self.assertRaises(Exception) as context:
            switch = Switch(host, port, probability, switch_id)

        # Assert that the exception message is as expected
        self.assertEqual(str(context.exception), "Connection failed")

        # Assert that the MQTT client was initialized and connect was called
        MockMqttClient.assert_called_once()
        mock_client_instance.connect.assert_called_once_with(host, port)

    @patch('paho.mqtt.client.Client')
    def test_broker_connection_clock(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value
        # Simulate a successful connection
        mock_client_instance.connect.return_value = mqtt.MQTT_ERR_SUCCESS

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        time = "00:00:00"
        rate = 2
        increment = 5
        clock_id = "1"

        # Create a clock instance
        clock = Clock(host, port, time, increment, rate, clock_id)

        # Assert that the MQTT client was initialized and connected with the correct parameters
        MockMqttClient.assert_called_once()
        mock_client_instance.connect.assert_called_once_with(host, port)

        # Assert that the MQTT client callbacks were set
        self.assertEqual(clock.mqttc.on_connect, clock.on_connect)
        self.assertEqual(clock.mqttc.on_message, clock.on_message)
        self.assertEqual(clock.mqttc.on_subscribe, clock.on_subscribe)
        self.assertEqual(clock.mqttc.on_unsubscribe, clock.on_unsubscribe)
        self.assertEqual(clock.mqttc.on_publish, clock.on_publish)

    @patch('paho.mqtt.client.Client')
    def test_broker_connection_failure_clock(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value

        # Simulate a connection failure
        mock_client_instance.connect.side_effect = Exception("Connection failed")

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        time = "00:00:00"
        rate = 2
        increment = 5
        clock_id = "1"

        # Attempt to create a clock instance and handle the exception
        with self.assertRaises(Exception) as context:
            clock = Clock(host, port, time, increment, rate, clock_id)

        # Assert that the exception message is as expected
        self.assertEqual(str(context.exception), "Connection failed")

        # Assert that the MQTT client was initialized and connect was called
        MockMqttClient.assert_called_once()
        mock_client_instance.connect.assert_called_once_with(host, port)
        
        
    @patch('paho.mqtt.client.Client')
    def test_switch_state_change(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        probability = 0
        switch_id = "1"

        # Create a switch instance
        switch = Switch(host, port, probability, switch_id)

        # Simulate receiving an MQTT message to change the switch state
        message = MagicMock()
        message.payload = b"ON 0"  # Simulate a payload that toggles the switch state
        switch.on_message(mock_client_instance, None, message)

        # Assert that the state has changed correctly
        self.assertEqual(switch.state, State.ON)

    @patch('paho.mqtt.client.Client')
    def test_sensor_state_change(self, MockMqttClient):
        # Mock the MQTT client
        mock_client_instance = MockMqttClient.return_value

        # Define test parameters
        host = "mqtt.eclipseprojects.io"
        port = 1883
        interval = 3
        min_value = 0
        max_value = 100
        increment = 5
        sensor_id = "1"

        # Create a Sensor instance
        sensor = Sensor(host, port, interval, min_value, max_value, increment, sensor_id)
        initial_state = sensor.state

        time.sleep(interval)        
        final_state = sensor.next_value(initial_state)


        self.assertTrue(final_state == initial_state+increment or initial_state-increment)

        
if __name__ == '__main__':
    unittest.main()