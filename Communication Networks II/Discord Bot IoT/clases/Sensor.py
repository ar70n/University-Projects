"""
    CLASE: Sensor
    DESCRIPCIÓN: Clase que representa un sensor que publica su estado en un intervalo definido
    ATRIBUTOS:
        - host: Dirección del broker MQTT.
        - port: Puerto del broker MQTT.
        - interval: Intervalo de tiempo en segundos para publicar el estado.
        - min_value: Valor mínimo del sensor.
        - max_value: Valor máximo del sensor.
        - increment: Incremento o decremento del valor del sensor.
        - id: Identificador del sensor.
        - state: Estado actual del sensor.
        - unacked_publish: Conjunto de mensajes publicados no confirmados.
        - mqttc: Cliente MQTT para la comunicación.
    MÉTODOS:
        - __init__: Inicializa el sensor y configura el cliente MQTT.
        - start: Inicia la publicación periódica del estado del sensor.
        - close: Detiene el cliente MQTT y cierra la conexión.
        - on_subscribe: Callback para manejar la respuesta del broker al suscribirse.
        - on_unsubscribe: Callback para manejar la respuesta del broker al desuscribirse.
        - on_message: Callback para manejar mensajes recibidos.
        - on_connect: Callback para manejar la conexión al broker MQTT.
        - on_publish: Callback para manejar la confirmación de publicación de mensajes.
        - next_value: Calcula el siguiente valor del sensor basado en el estado actual.
"""

import argparse
import time
import paho.mqtt.client as mqtt
import random

class Sensor:
    """
    VARIABLES GLOBALES:
    p_change: Probabilidad de cambiar el valor del sensor
    """


    """
    FUNCIÓN: __init__(self, host, port, interval, min_value, max_value, increment, id)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - host: Dirección del broker MQTT.
        - port: Puerto del broker MQTT.
        - interval: Intervalo de tiempo en segundos para publicar el estado.
        - min_value: Valor mínimo del sensor.
        - max_value: Valor máximo del sensor.
        - increment: Incremento o decremento del valor del sensor.
        - id: Identificador del sensor.
    DESCRIPCIÓN: Inicializa el sensor y configura el cliente MQTT.
    ARGS_OUT: None
    """
    def __init__(self, host, port, interval, min_value, max_value, increment, id):
        self.host = host
        self.port = port
        self.interval = interval
        self.min_value = min_value
        self.max_value = max_value
        self.increment = increment
        self.id = id
        self.state = random.randint(self.min_value, self.max_value)  # Inicializar el estado con un valor aleatorio
        
        #Nos conectamos al broker
        self.unacked_publish = set()
        self.mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.mqttc.on_connect = self.on_connect
        self.mqttc.on_message = self.on_message
        self.mqttc.on_subscribe = self.on_subscribe
        self.mqttc.on_unsubscribe = self.on_unsubscribe
        self.mqttc.on_publish = self.on_publish
        self.mqttc.user_data_set(self.unacked_publish)
        #normalmente nos querremos conectar a mqtt.eclipseprojects.io
        self.mqttc.connect(host, port)
    
    """
    FUNCIÓN: start(self)
    ARGS_IN: self - instancia de la clase Sensor
    DESCRIPCIÓN: Inicia la publicación periódica del estado del sensor y cambia su estado
    ARGS_OUT: None
    """
    def start(self):
        # Publicar el estado actual del sensor periódicamente
        self.mqttc.loop_start()
        try:
            while True:
                # Enviar el estado actual
                topic = f"redes2/2301/06/{self.id}/home/climate/sensor"
                msg_info = self.mqttc.publish(topic, self.state, qos=1)
                self.unacked_publish.add(msg_info.mid)
                msg_info.wait_for_publish()

                # Esperar el intervalo definido
                time.sleep(self.interval)

                # Cambiar el estado del sensor
                self.state = self.next_value(self.state)

        except KeyboardInterrupt:
            print("Finalizando dummy-sensor...")
            self.close()
    
    """
    FUNCIÓN: close(self)
    ARGS_IN: self - instancia de la clase Sensor
    DESCRIPCIÓN: Detiene el cliente MQTT y cierra la conexión.
    ARGS_OUT: None
    """
    def close(self):
        self.mqttc.loop_stop()
        self.mqttc.disconnect()

    """
    FUNCIÓN: on_subscribe(self, client, userdata, mid, reason_code_list, properties)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - mid: ID del mensaje.
        - reason_code_list: lista de códigos de razón.
        - properties: propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la respuesta del broker al suscribirse.
    Solo comprueba que la suscripción fue exitosa.
    ARGS_OUT: None
    """
    def on_subscribe(self, client, userdata, mid, reason_code_list, properties):
        # Reason_code list guarda los códigos de respuesta del broker a cada tópico suscrito
        # El código de respuesta define si la suscripción fue exitosa o no
        # En este caso, on_suscribe se llama para un solo tópico a la vez, así que
        # el código de respuesta es único
        if reason_code_list[0].is_failure:
            print(f"Broker rejected you subscription: {reason_code_list[0]}")
        else:
            print(f"Broker granted the following QoS: {reason_code_list[0].value}")

    """
    FUNCIÓN: on_unsubscribe(self, client, userdata, mid, reason_code_list, properties)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - mid: ID del mensaje.
        - reason_code_list: lista de códigos de razón.
        - properties: propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la respuesta del broker al desuscribirse.
    Solo comprueba que la desuscripción fue exitosa.
    ARGS_OUT: None
    """
    def on_unsubscribe(self, client, userdata, mid, reason_code_list, properties):
        # Be careful, the reason_code_list is only present in MQTTv5.
        # In MQTTv3 it will always be empty
        if len(reason_code_list) == 0 or not reason_code_list[0].is_failure:
            print("unsubscribe succeeded (if SUBACK is received in MQTTv3 it success)")
        else:
            print(f"Broker replied with failure: {reason_code_list[0]}")
        client.disconnect()

    """
    FUNCIÓN: on_message(self, client, userdata, message)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - message: mensaje recibido.
    DESCRIPCIÓN: Callback para manejar mensajes recibidos.
    Maneja dos tipos de mensajes:
        1. Mensajes con el tópico que termina en "/set":
            - Cambia el estado del sensor si el nuevo valor está dentro del rango permitido.
            - Publica una confirmación con el nuevo estado y un código de confirmación.
        2. Mensajes con el tópico que termina en "/get":
            - Publica el estado actual del sensor.
    ARGS_OUT: None
    """
    def on_message(self, client, userdata, message):
        print(f"Received message: {message.payload.decode('utf-8')} on topic {message.topic}")

        if message.topic.endswith("/set"):
            # Esperamos payload: "<nuevo_valor> <confirmation_code>"
            payload_parts = message.payload.decode('utf-8').split(" ")
            try:
                new_value = int(payload_parts[0])
                confirmation_code = payload_parts[1]
            except (IndexError, ValueError):
                print("Invalid payload for /set")
                return

            # Cambiar el estado solo si está en rango
            if self.min_value <= new_value <= self.max_value:
                self.state = new_value
            else:
                print(f"Value {new_value} out of range")
                # Puedes decidir si quieres confirmar o no en este caso

            # Publicar confirmación
            confirm_topic = f"redes2/2301/06/{self.id}/home/climate/sensor/confirm"
            payload = f"{self.state} {confirmation_code}"
            self.mqttc.publish(confirm_topic, payload, qos=1)

        elif message.topic.endswith("/get"):
            # Publicar el estado actual
            topic = f"redes2/2301/06/{self.id}/home/climate/sensor"
            self.mqttc.publish(topic, self.state, qos=1)

    """
    FUNCIÓN: on_connect(self, client, userdata, flags, reason_code, properties)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - flags: banderas de conexión.
        - reason_code: código de razón de la conexión.
        - properties: propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la conexión al broker MQTT.
    Comprueba si la conexión fue exitosa y se suscribe al tópico de comandos para este sensor.
    ARGS_OUT: None
    """
    def on_connect(self, client, userdata, flags, reason_code, properties):
        if reason_code.is_failure:
            print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
        else:
            # Suscribirse a los tópicos de comandos para este sensor
            get_topic = f"redes2/2301/06/{self.id}/home/climate/sensor/get"
            set_topic = f"redes2/2301/06/{self.id}/home/climate/sensor/set"
            client.subscribe(get_topic)
            client.subscribe(set_topic)
            print(f"Subscribed to {get_topic} and {set_topic}")
    """
    FUNCIÓN: on_publish(self, client, userdata, mid, reason_code, properties)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - mid: ID del mensaje.
        - reason_code: código de razón de la publicación.
        - properties: propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la confirmación de publicación de mensajes.
    Comprueba si la publicación fue exitosa y elimina el mensaje de la lista de mensajes no confirmados.
    ARGS_OUT: None
    """
    def on_publish(self, client, userdata, mid, reason_code, properties):
        try:
            userdata.remove(mid)
        except KeyError:
            print("on_publish() is called with a mid not present in unacked_publish")
            print("This is due to an unavoidable race-condition:")
            print("* publish() return the mid of the message sent.")
            print("* mid from publish() is added to unacked_publish by the main thread")
            print("* on_publish() is called by the loop_start thread")
            print("While unlikely (because on_publish() will be called after a network round-trip),")
            print(" this is a race-condition that COULD happen")
            print("")
            print("The best solution to avoid race-condition is using the msg_info from publish()")
            print("We could also try using a list of acknowledged mid rather than removing from pending list,")
            print("but remember that mid could be re-used !")

    """
    FUNCIÓN: next_value(self, value)
    ARGS_IN:
        - self: instancia de la clase Sensor.
        - value: valor actual del sensor.
    DESCRIPCIÓN: Calcula el siguiente valor del sensor basado en el estado actual.
    El nuevo valor se calcula aleatoriamente sumando o restando el incremento al valor actual.
    Asegura que el nuevo valor esté dentro del rango definido por min_value y max_value.
    ARGS_OUT: El nuevo valor del sensor.
    """
    def next_value(self, value):
        global p_change 
        p_change = 0.5
        print("Next value. Current value:", value)

        if random.random() < p_change:
            value += self.increment
        else:
            value -= self.increment

        # Asegurarse de que el valor esté dentro del rango
        if value > self.max_value:
            value = self.max_value
        elif value < self.min_value:
            value = self.min_value

        return value