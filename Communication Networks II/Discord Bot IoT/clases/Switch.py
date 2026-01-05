"""
    CLASE: Switch
    DESCRIPCIÓN: Clase que simula un interruptor de una casa inteligente y se comunica con un broker MQTT.
    ATRIBUTOS:
        - host: Dirección del broker MQTT.
        - port: Puerto del broker MQTT.
        - probability: Probabilidad de que el cambio de estado falle.
        - id: Identificador del interruptor.
        - state: Estado actual del interruptor (ON/OFF).
        - unacked_publish: Conjunto de mensajes pendientes de confirmación.
        - mqttc: Cliente MQTT para la comunicación.
    MÉTODOS:
        - __init__: Inicializa el interruptor con los parámetros dados.
        - start: Inicia el bucle de publicación del estado del interruptor.
        - close: Cierra la conexión MQTT.
        - on_subscribe: Callback para manejar la suscripción a tópicos.
        - on_unsubscribe: Callback para manejar la desuscripción de tópicos.
        - on_message: Callback para manejar mensajes recibidos.
        - on_connect: Callback para manejar la conexión al broker MQTT.
        - on_publish: Callback para manejar la publicación de mensajes.
"""

import argparse
from enum import Enum
import paho.mqtt.client as mqtt
import time
import random

class State(Enum):
    ON = "ON"
    OFF = "OFF"

class Switch:

    """
    FUNCION: __init__(self, host, port, probability, id)
    ARGS_IN:
        - self: Instancia de la clase Switch.
        - host: Dirección del broker MQTT.
        - port: Puerto del broker MQTT.
        - probability: Probabilidad de que el cambio de estado falle.
        - id: Identificador del interruptor.
    DESCRIPCIÓN: Inicializa el interruptor con los parámetros dados.
    ARGS_OUT: None
    """
    def __init__(self, host, port, probability, id):
        self.host = host
        self.port = port
        self.probability = probability
        self.id = id 
        self.state = State.OFF
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
    FUNCION: start(self)
    ARGS_IN:
        - self: Instancia de la clase Switch.
    DESCRIPCIÓN: Inicia el bucle de publicación del estado del interruptor.
    ARGS_OUT: None
    """
    def start(self):
        # Publicar el estado actual del interruptor periódicamente
        self.mqttc.loop_start()
        topic = f"redes2/2301/06/{self.id}/home/climate/boiler_switch" # Topic en el que publicamos el estado
        
        try:            
            while True:                
                print(f"Enviando estado actual: {self.state.value}")
                msg_info = self.mqttc.publish(topic, self.state.value, qos=1)
                self.unacked_publish.add(msg_info.mid)
                msg_info.wait_for_publish()
                time.sleep(5) 

        except KeyboardInterrupt:
            print("Finalizando dummy-switch...")
            self.close()
    
    """
    FUNCION: close(self)
    ARGS_IN:
        - self: Instancia de la clase Switch.
    DESCRIPCIÓN: Cierra la conexión MQTT.
    ARGS_OUT: None
    """
    def close(self):
        self.mqttc.loop_stop()
        self.mqttc.disconnect()

    """
    FUNCION: on_subscribe(self, client, userdata, mid, reason_code_list, properties)
    ARGS_IN:
        - self: Instancia de la clase Switch.
        - client: Cliente MQTT.
        - userdata: Datos del usuario.
        - mid: ID del mensaje.
        - reason_code_list: Lista de códigos de razón.
        - properties: Propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la suscripción a tópicos.
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
    FUNCION: on_unsubscribe(self, client, userdata, mid, reason_code_list, properties)
    ARGS_IN:
        - self: Instancia de la clase Switch.
        - client: Cliente MQTT.
        - userdata: Datos del usuario.
        - mid: ID del mensaje.
        - reason_code_list: Lista de códigos de razón.
        - properties: Propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la desuscripción de tópicos.
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
    FUNCION: on_message(self, client, userdata, message)
    ARGS_IN:
        - self: Instancia de la clase Switch.
        - client: Cliente MQTT.
        - userdata: Datos del usuario.
        - message: Mensaje recibido.
    DESCRIPCIÓN: Callback para manejar mensajes recibidos. Cambia el estado del interruptor de forma aleatoria o publica el estado actual.
    ARGS_OUT: None
    """
    def on_message(self, client, userdata, message):
        print(f"Received message: {message.payload.decode('utf-8')} on topic {message.topic}")
        
        # Procesar el mensaje recibido
        if message.topic.endswith("/set"):
            # Cambiar el estado del interruptor según el mensaje recibido
            payload_parts = message.payload.decode('utf-8').split(" ")
            state = payload_parts[0]
            confirmation_code = payload_parts[1]
            
            # El cambio tiene una probabilidad de fallar
            if random.random() > self.probability:
                if state == "ON":
                    self.state = State.ON
                elif state == "OFF":
                    self.state = State.OFF
                else:
                    print(f"Unknown state: {state}")
                    return                
            else:
                print("Error simulado: no se ha podido cambiar el estado")
            
            # Publicar el nuevo estado
            topic = f"redes2/2301/06/{self.id}/home/climate/boiler_switch/confirm"
            payload = f"{self.state.value} {confirmation_code}"
            self.mqttc.publish(topic, payload, qos=1)

        elif message.topic.endswith("/get"):
            # Publicar el estado actual
            topic = f"redes2/2301/06/{self.id}/home/climate/boiler_switch"
            self.mqttc.publish(topic, self.state.value, qos=1)

    """
    FUNCION: on_connect(self, client, userdata, flags, reason_code, properties)
    ARGS_IN:
        - self: Instancia de la clase Switch.
        - client: Cliente MQTT.
        - userdata: Datos del usuario.
        - flags: Flags de conexión.
        - reason_code: Código de razón de la conexión.
        - properties: Propiedades de la conexión.
    DESCRIPCIÓN: Callback para manejar la conexión al broker MQTT. Se suscribe a los tópicos de comandos.
    ARGS_OUT: None
    """
    def on_connect(self, client, userdata, flags, reason_code, properties):
        if reason_code.is_failure:
            print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
        else:
            # Suscribirse al tópico de comandos para este interruptor
            set_topic = f"redes2/2301/06/{self.id}/home/climate/boiler_switch/set"
            client.subscribe(set_topic)
            get_topic = f"redes2/2301/06/{self.id}/home/climate/boiler_switch/get"
            client.subscribe(get_topic)
            print(f"Subscribed to {set_topic} and {get_topic}")

    """
    FUNCION: on_publish(self, client, userdata, mid, reason_code, properties)
    ARGS_IN:
        - self: Instancia de la clase Switch.
        - client: Cliente MQTT.
        - userdata: Datos del usuario.
        - mid: ID del mensaje.
        - reason_code: Código de razón de la publicación.
        - properties: Propiedades de la publicación.
    DESCRIPCIÓN: Callback para manejar la publicación de mensajes. Elimina el mensaje del conjunto de mensajes pendientes de confirmación.
    ARGS_OUT: None
    """
    def on_publish(self, client, userdata, mid, reason_code, properties):
        try:
            userdata.remove(mid)
        except KeyError:
            """print("on_publish() is called with a mid not present in unacked_publish")
            print("This is due to an unavoidable race-condition:")
            print("* publish() return the mid of the message sent.")
            print("* mid from publish() is added to unacked_publish by the main thread")
            print("* on_publish() is called by the loop_start thread")
            print("While unlikely (because on_publish() will be called after a network round-trip),")
            print(" this is a race-condition that COULD happen")
            print("")
            print("The best solution to avoid race-condition is using the msg_info from publish()")
            print("We could also try using a list of acknowledged mid rather than removing from pending list,")
            print("but remember that mid could be re-used !")"""