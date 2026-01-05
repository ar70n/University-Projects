"""
    CLASE: Clock
    DESCRIPCIÓN: Clase que representa un reloj que publica la hora actual en un intervalo definido 
                 y se comunica a través de MQTT.
    ATRIBUTOS:
        - time: Hora inicial del reloj.
        - increment: Intervalo de tiempo en segundos para publicar la hora.
        - rate: Tasa de actualización del reloj.
        - unacked_publish: Conjunto de mensajes publicados no confirmados.
        - mqttc: Cliente MQTT para la comunicación.
    MÉTODOS:
        - __init__: Inicializa el reloj y configura el cliente MQTT.
        - start: Inicia la publicación periódica de la hora.
        - close: Detiene el cliente MQTT y cierra la conexión.
        - on_subscribe: Callback para manejar la respuesta del broker al suscribirse.
        - on_unsubscribe: Callback para manejar la respuesta del broker al desuscribirse.
        - on_message: Callback para manejar mensajes recibidos.
        - on_connect: Callback para manejar la conexión al broker MQTT.
        - on_publish: Callback para manejar la confirmación de publicación de mensajes.
"""

import argparse
from datetime import datetime, timedelta
import paho.mqtt.client as mqtt
import time


class Clock:
    """
    FUNCIÓN: __init__(self, host, port, id, time, increment, rate)
    ARGS_IN: 
        - self: instancia de la clase Clock.
        - host: Dirección del broker MQTT.
        - port: Puerto del broker MQTT.
        - id: Identificador del reloj.
        - time: Hora inicial del reloj.
        - increment: Intervalo de tiempo en segundos para publicar la hora.
        - rate: Tasa de actualización del reloj.
    DESCRIPCIÓN: Inicializa el reloj y configura el cliente MQTT.
    ARGS_OUT: None
    """
    def __init__(self, host, port, time, increment, rate, id):
        self.time = datetime.strptime(time, "%H:%M:%S")
        self.increment = increment
        self.rate = rate
        self.id = id
        self.unacked_publish = set()
        self.mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.mqttc.on_connect = self.on_connect
        self.mqttc.on_message = self.on_message
        self.mqttc.on_subscribe = self.on_subscribe
        self.mqttc.on_unsubscribe = self.on_unsubscribe
        self.mqttc.on_publish = self.on_publish
        self.mqttc.user_data_set(self.unacked_publish)
        self.mqttc.connect(host, port)


    """
    FUNCIÓN: start(self)
    ARGS_IN: self - instancia de la clase Clock
    DESCRIPCIÓN: Inicia un bucle que publica la hora actual en un tópico MQTT a intervalos definidos por el atributo 'rate'. 
                    El bucle se ejecuta continuamente hasta que se interrumpe manualmente con un KeyboardInterrupt.
    ARGS_OUT: None
    """
    def start(self):
        self.mqttc.loop_start()
        try:
            topic = f"redes2/2301/06/{self.id}/home/climate/clock"
            global_time = time.time()
            while True:
                start_time = time.time()

                if start_time - global_time >= self.increment:
                    self.time = self.time + timedelta(seconds=self.increment)
                    global_time = start_time
                                
                msg_info = self.mqttc.publish(topic, self.time.strftime("%H:%M:%S"), qos=1)
                self.unacked_publish.add(msg_info.mid)
                msg_info.wait_for_publish()

                elapsed_time = time.time() - start_time
                time_to_sleep = max(0, 1/self.rate - elapsed_time)
                time.sleep(time_to_sleep)

        except KeyboardInterrupt:
            self.close()

    """
    FUNCIÓN: close(self)
    ARGS_IN: self - instancia de la clase Clock
    DESCRIPCIÓN: Detiene el cliente MQTT y cierra la conexión.
    ARGS_OUT: None
    """
    def close(self):
        self.mqttc.loop_stop()
        self.mqttc.disconnect()

    """
    FUNCIÓN: on_subscribe(self, client, userdata, mid, reason_code_list, properties)
    ARGS_IN:
        - self: instancia de la clase Clock.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - mid: ID del mensaje.
        - reason_code_list: lista de códigos de razón.
        - properties: propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la respuesta del broker al suscribirse. Solo comprueba que la suscripción fue exitosa.
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
        - self: instancia de la clase Clock.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - mid: ID del mensaje.
        - reason_code_list: lista de códigos de razón.
        - properties: propiedades del mensaje.
    DESCRIPCIÓN: Callback para manejar la respuesta del broker al desuscribirse. Solo comprueba que la desuscripción fue exitosa.
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
        - self: instancia de la clase Clock.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - message: mensaje recibido.
    DESCRIPCIÓN: Callback para manejar mensajes recibidos. Publica la hora actual en el tópico correspondiente y cambia la hora si el mensaje es válido.
    ARGS_OUT: None
    """
    def on_message(self, client, userdata, message):
        print(f"Received message: {message.payload.decode('utf-8')} on topic {message.topic}")
        
        if message.topic.endswith("/set"):
            topic = f"redes2/2301/06/{self.id}/home/climate/clock"
            self.mqttc.publish(topic, self.time.strftime("%H:%M:%S"), qos=1)        

        if message.topic.endswith("/set"):
            # Cambiar el estado del interruptor según el mensaje recibido
            try:
                payload_parts = message.payload.decode('utf-8').split(" ")
                state = payload_parts[0]
                confirmation_code = payload_parts[1]
                
                # El cambio tiene una probabilidad de fallar
                # Verificar si el formato del string es válido
                new_time = datetime.strptime(state, "%H:%M:%S")
                self.time = new_time
            except ValueError:
                print("Error: Formato de hora inválido. Debe ser '%H:%M:%S'")
            
                # Publicar el nuevo estado
            topic = f"redes2/2301/06/{self.id}/home/climate/clock/confirm"
            payload = f"{self.time.strftime('%H:%M:%S')} {confirmation_code}"
            self.mqttc.publish(topic, payload, qos=1)



    """
    FUNCIÓN: on_connect(self, client, userdata, flags, reason_code, properties)
    ARGS_IN:
        - self: instancia de la clase Clock.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - flags: banderas de conexión.
        - reason_code: código de razón de la conexión.
        - properties: propiedades de la conexión.
    DESCRIPCIÓN: Callback para manejar la conexión al broker MQTT. Se suscribe al tópico de comandos para este reloj.
    ARGS_OUT: None
    """
    def on_connect(self, client, userdata, flags, reason_code, properties):
        if reason_code.is_failure:
            print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
        else:
            # Suscribirse al tópico de comandos para este clock
            get_topic = f"redes2/2301/06/{self.id}/home/climate/clock/get"
            client.subscribe(get_topic)
            set_topic = f"redes2/2301/06/{self.id}/home/climate/clock/set"
            client.subscribe(set_topic)

    """
    FUNCIÓN: on_publish(self, client, userdata, mid, reason_code, properties)
    ARGS_IN:
        - self: instancia de la clase Clock.
        - client: cliente MQTT.
        - userdata: datos del usuario.
        - mid: ID del mensaje.
        - reason_code: código de razón de la publicación.
        - properties: propiedades de la publicación.
    DESCRIPCIÓN: Callback para manejar la confirmación de publicación de mensajes. Elimina el mensaje del conjunto de mensajes no confirmados.
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