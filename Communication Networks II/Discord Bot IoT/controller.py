"""
Este programa implementa un controlador para gestionar dispositivos IoT utilizando MQTT como protocolo de comunicación. 
El flujo principal del programa se divide en varias etapas clave:
1. **Parseo de Argumentos**:
    - Se procesan los argumentos de línea de comandos para configurar el host, puerto y base de datos.
2. **Carga de la Base de Datos**:
    - Se cargan las reglas y el estado de los dispositivos desde una base de datos persistente. 
    - Si no se encuentra la base de datos o hay un error, se inicializan los diccionarios de estado y tipo de dispositivos.
3. **Conexión a MQTT**:
    - Se configura un cliente MQTT con callbacks para manejar eventos como conexión, recepción de mensajes, suscripciones y desuscripciones.
    - El cliente se conecta al broker MQTT especificado y comienza a escuchar mensajes.
4. **Conexión al Bot**:
    - Se configura un socket TCP para recibir comandos desde un bot. 
    - El bot envía comandos que el controlador procesa y responde.
5. **Bucle Principal**:
    - El programa entra en un bucle infinito donde espera conexiones del bot.
    - Una vez conectado, procesa los comandos recibidos, ejecuta las acciones correspondientes (como consultar o cambiar el estado de dispositivos, gestionar reglas, etc.) y responde al bot.
6. **Procesamiento de Mensajes del Bot**:
    - Los comandos del bot se procesan en la función `process_bot_msg`, que soporta acciones como:
      - Consultar el estado de dispositivos (`status`).
      - Cambiar el estado de un dispositivo (`set`).
      - Gestionar reglas del motor de reglas (`add_rule`, `edit_rule`, `delete_rule`, `list_rules`).
7. **Gestión de Mensajes MQTT**:
    - Los mensajes MQTT recibidos se procesan en el callback `on_message`, que actualiza el estado de los dispositivos, aplica reglas y gestiona confirmaciones de estado.
8. **Gestión de Estados de Dispositivos**:
    - Se implementan funciones para solicitar el estado de dispositivos individuales o de todos los dispositivos registrados.
    - También se manejan cambios de estado, ya sea por comandos del bot o por reglas del motor de reglas.
9. **Cierre del Programa**:
    - Al recibir una señal de interrupción (Ctrl+C), el programa realiza tareas de limpieza:
      - Cierra el socket del bot.
      - Detiene el cliente MQTT.
      - Guarda el estado actual de los dispositivos y las reglas en la base de datos.
      - Finaliza el programa de manera segura.
### Resumen de Componentes Clave:
- **Diccionarios Globales**:
  - `device_status_dict`: Almacena el estado actual de los dispositivos.
  - `device_type_dict`: Almacena el tipo de cada dispositivo.
  - `device_updated_dict`: Indica si el estado de un dispositivo está actualizado.
  - `awaiting_confirmation`: Dispositivos que esperan confirmación de cambio de estado.
  - `confirmed_devices`: Dispositivos que han confirmado su estado.
- **Callbacks MQTT**:
  - `on_connect`: Maneja la conexión al broker MQTT y suscribe a los tópicos relevantes.
  - `on_message`: Procesa mensajes recibidos y actualiza el estado de los dispositivos.
  - `on_subscribe` y `on_unsubscribe`: Gestionan eventos de suscripción y desuscripción.
- **Funciones Principales**:
  - `process_bot_msg`: Procesa comandos del bot.
  - `request_all_devices_status` y `request_device_status`: Solicitan el estado de dispositivos.
  - `set_state`: Cambia el estado de un dispositivo y gestiona confirmaciones.
  - `apply_rule_changes`: Aplica cambios de estado basados en reglas.
  - `close`: Realiza tareas de limpieza y cierra el programa.
### Flujo General:
1. El programa se inicializa cargando configuraciones y conectándose al broker MQTT y al bot.
2. En el bucle principal, espera comandos del bot y los procesa.
3. Los comandos pueden desencadenar publicaciones MQTT para interactuar con dispositivos IoT.
4. Los dispositivos responden a través de MQTT, y el programa actualiza su estado y aplica reglas si es necesario.
5. Al finalizar, el programa guarda el estado y cierra conexiones de manera segura.
"""
import argparse
import paho.mqtt.client as mqtt
import time
import os
import socket
import threading
import queue
import signal
import database
import uuid
import rule_engine

#HAY QUE HACER UNA FUNCION QUE SEA LA QUE LLAMA EL BOT PARA MANDAR COMANDOS O REVISAR EL ESTADO DE LOS DISPOSITIVOS

DEVICE_ANSWER_TIMEOUT = 1 # Tiempo de espera para recibir el estado de un dispositivo
DEVICE_ANSWER_SLEEP = 0.1 # Tiempo de espera entre comprobaciones del estado de los dispositivos
RECV_BUFFER = 1024


# Declaración de variables
device_status_dict = {} #Diccionario que guarda el estado de los dispositivos. La clave es el id del dispositivo y el valor es el estado del dispositivo
device_type_dict = {} #Diccionario que guarda el tipo de dispositivo. La clave es el id del dispositivo y el valor es el tipo de dispositivo (switch, clock...)
device_updated_dict = {} #Diccionario que guarda si el estado de un dispositivo está actualizado. La clave es el id del dispositivo y el valor es True si el estado está actualizado y False si no lo está
awaiting_confirmation = {} # Diccionario que guarda si el controller espera la confirmación del estado de un dispositivo. La clave es el id, el valor el código de confirmación
confirmed_devices = {} # Diccionario que guarda los dispositivos que han confirmado el estado. La clave es el id del dispositivo y el valor es el estado del dispositivo
mqttc = None

# Parseo de argumentos
def parse_arguments():
    """
    Analiza y procesa los argumentos de línea de comandos para el programa controlador.

    Argumentos:
        --host: Dirección del host al que se conectará el programa. 
                Es opcional y su valor por defecto es "redes2.ii.uam.es".
        --port, -p: Número de puerto al que se conectará el programa. 
                    Es opcional y su valor por defecto es 1883.
        database: Nombre de la base de datos. Este argumento es obligatorio.

    Retorna:
        Namespace: Un objeto que contiene los valores de los argumentos proporcionados.
    """
    parser = argparse.ArgumentParser(description="Controller program")
    parser.add_argument('--host', type=str, default="redes2.ii.uam.es", help='Host address')
    parser.add_argument('--mqtt_port', type=int, default=1883, help='MQTT port number')
    parser.add_argument('--bot_port', type=int, default=5000, help='Bot port number')
    parser.add_argument('database', type=str, help='Database name')
    return parser.parse_args()

# ==========================================================================================
# MÉTODOS DE MQTT
# ==========================================================================================
def on_subscribe(client, userdata, mid, reason_code_list, properties):
    """
    Callback que se ejecuta cuando el cliente MQTT se suscribe a un canal.

    Parámetros:
    - client: Instancia del cliente MQTT.
    - userdata: Datos definidos por el usuario que se pasan al cliente.
    - mid: Identificador único del mensaje de suscripción.
    - reason_code_list: Lista de códigos de razón que indican el resultado de la suscripción.
      Contiene un único elemento ya que la suscripción es a un solo canal.
    - properties: Propiedades adicionales asociadas con la suscripción (si las hay).

    Comportamiento:
    - Si el código de razón indica un fallo, se imprime un mensaje indicando que el broker
      rechazó la suscripción.
    - Si el código de razón indica éxito, se imprime el QoS otorgado por el broker.
    """
    # Since we subscribed only for a single channel, reason_code_list contains
    # a single entry
    if reason_code_list[0].is_failure:
        print(f"Broker rejected you subscription: {reason_code_list[0]}")
    else:
        print(f"Broker granted the following QoS: {reason_code_list[0].value}")

def on_unsubscribe(client, userdata, mid, reason_code_list, properties):
    """
    Callback que se ejecuta cuando el cliente se desuscribe de un tema en MQTT.

    Parámetros:
    - client: Instancia del cliente MQTT que realiza la desuscripción.
    - userdata: Datos definidos por el usuario que se pasaron al inicializar el cliente.
    - mid: ID del mensaje relacionado con la solicitud de desuscripción.
    - reason_code_list: Lista de códigos de razón que indican el resultado de la desuscripción.
      Nota: Esta lista solo está presente en MQTTv5. En MQTTv3 estará vacía.
    - properties: Propiedades adicionales asociadas con la desuscripción (solo en MQTTv5).

    Comportamiento:
    - Si la lista `reason_code_list` está vacía o el primer código no indica un fallo,
      se considera que la desuscripción fue exitosa.
    - Si el broker responde con un fallo, se imprime un mensaje indicando el error.
    - Finalmente, el cliente se desconecta del broker.
    """
    # Be careful, the reason_code_list is only present in MQTTv5.
    # In MQTTv3 it will always be empty
    if len(reason_code_list) == 0 or not reason_code_list[0].is_failure:
        print("Unsubscribe succeeded (if SUBACK is received in MQTTv3 it success)")
    else:
        print(f"Broker replied with failure: {reason_code_list[0]}")
    client.disconnect()

# userdata is the structure we choose to provide, here it's a list()
def on_message(client, userdata, message):
    """
    Callback que se ejecuta al recibir un mensaje en un cliente MQTT.
    Args:
        client: Cliente MQTT que recibe el mensaje.
        userdata: Datos definidos por el usuario que se pasan al callback.
        message: Objeto que contiene el mensaje recibido, incluyendo el payload y el topic.
    Descripción:
        - Imprime el mensaje recibido y el topic asociado.
        - Divide el topic en partes para validar su formato y extraer información relevante.
        - Extrae el ID del dispositivo desde el topic.
        - Procesa el payload para obtener el estado del dispositivo y actualiza un diccionario con el estado.
        - Verifica y aplica reglas relacionadas con el estado del dispositivo utilizando un motor de reglas.
        - Registra el tipo de dispositivo si no está previamente registrado.
        - Marca el dispositivo como actualizado en un diccionario de seguimiento.
        - Gestiona la confirmación del estado si el topic indica que es un mensaje de confirmación:
            - Verifica si se esperaba una confirmación para el dispositivo.
            - Valida el código de confirmación recibido.
            - Actualiza las estructuras de datos relacionadas con dispositivos confirmados y en espera de confirmación.
    Notas:
        - El formato esperado del topic es: 
          `redes2/2301/06/<id dispositivo>/home/climate/<tipo dispositivo>/[confirm]`
        - El payload esperado puede tener dos formatos:
          - Para estado: `"<estado>"`
          - Para confirmación: `"<estado> <código de confirmación>"`
    Excepciones:
        - Si el topic no tiene el formato esperado, se imprime un mensaje de error y se retorna.
        - Si el código de confirmación no coincide con el esperado, se imprime un mensaje de error.
    """
    print(f"Received message: [{message.payload.decode('utf-8')}] on topic [{message.topic}]")

    # Dividimos el topic en partes
    # Formato del topic de dispositivo: redes2/2301/06/<id dispositivo>/home/climate/<tipo dispositivo>/
    # Formato del topic de confirmación: redes2/2301/06/<id dispositivo>/home/climate/<tipo dispositivo>/confirm
    topic_parts = message.topic.split("/")
    
    # Comprobamos que el topic tiene el formato correcto
    if len(topic_parts) < 7:
        print(f"Invalid topic format: {message.topic}")
        return

    # Obtenemos el id
    device_id = topic_parts[3]

    # Si el dispositivo no está registrado, ignoramos el mensaje
    if device_id not in device_status_dict:
        print(f"Dispositivo {device_id} no registrado. Ignorando el mensaje.")
        return

    # Formato payload de estado: "<estado>""
    # Formato payload de confirmación: "<estado> <código de confirmación>"
    payload_parts = message.payload.decode('utf-8').split(" ")

    # Guardamos el estado del dispositivo
    status = payload_parts[0]    
    device_status_dict[device_id] = status # Actualizamos el estado del dispositivo en el diccionario con el contenido del mensaje
    rule_changes = rule_engine.check_rules(device_id, status)
    #print(f"Rule changes: {rule_changes}")

    # Hacemos los cambios de estado necesarios
    apply_rule_changes(rule_changes)

    # Obtenemos el tipo de dispositivo y lo registramos
    device_type = topic_parts[6]
    device_type_dict[device_id] = device_type        

    # Marcamos el dispositivo como actualizado
    device_updated_dict[device_id] = True

    # Gestionamos la confirmación del estado
    if len(topic_parts) == 8 and topic_parts[7] == "confirm":
        # Comprobamos que el código de confirmación es el correcto
        if device_id not in awaiting_confirmation:
            print(f"No se esperaba confirmación de {device_id}")
            return
        
        device_confirmation_code = awaiting_confirmation[device_id]

        if payload_parts[1] == device_confirmation_code:
            print(f"Dispositivo {device_id} ha confirmado el estado {status}")
            # Eliminamos el dispositivo de la lista de dispositivos que esperan confirmación
            del awaiting_confirmation[device_id]
            # Añadimos el dispositivo a la lista de dispositivos confirmados
            confirmed_devices[device_id] = status
        else:
            print("Código de confirmación incorrecto")

def on_connect(client, userdata, flags, reason_code, properties):
    """
    Callback que se ejecuta cuando el cliente MQTT se conecta al broker.

    Args:
        client (paho.mqtt.client.Client): Instancia del cliente MQTT.
        userdata (Any): Datos definidos por el usuario que se pasan al cliente.
        flags (dict): Indicadores de respuesta del broker.
        reason_code (paho.mqtt.client.ReasonCodes): Código que indica el resultado de la conexión.
        properties (paho.mqtt.properties.Properties): Propiedades asociadas a la conexión MQTT.

    Comportamiento:
        - Si el código de razón indica un fallo, se imprime un mensaje de error y el cliente intentará reconectarse automáticamente.
        - Si la conexión es exitosa, el cliente se suscribe a los topics relacionados con dispositivos de tipo "climate" 
          en el hogar, evitando el uso de la wildcard '#' para no recibir mensajes de tipo "set" o "get".
    """
    if reason_code.is_failure:
        print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
    else:
        # we should always subscribe from on_connect callback to be sure
        # our subscribed is persisted across reconnections.
        # Nos suscribimos a los topics de los dispositivos, sea cual sea su id y tipo
        # de dispositivo climate (switch, clock...)
        # No usaremos la wildcard '#' para evitar recibir mensajes de tipo set o get
        client.subscribe("redes2/2301/06/+/home/climate/+")
        client.subscribe("redes2/2301/06/+/home/climate/+/confirm")

# ===========================================================================================
# MÉTODOS DEL CONTROLADOR
# ===========================================================================================
def process_bot_msg(msg) -> str:
    """
    Procesa un mensaje recibido por el bot y ejecuta la acción correspondiente según el comando especificado.

    Args:
        msg (str): Mensaje recibido que contiene el comando y sus argumentos.

    Returns:
        str: Respuesta generada tras procesar el comando.

    Comandos soportados:
        - 'add_device <id>': Añade un nuevo dispositivo con el identificador <id>.
        - 'get_device <id|all>': Obtiene el estado de un dispositivo específico o de todos los dispositivos.
        - 'set_device <id> <estado>': Cambia el estado de un dispositivo específico.
        - 'remove_device <id>': Elimina un dispositivo existente identificado por <id>.
        - 'add_rule <regla>': Añade una nueva regla al motor de reglas.
        - 'edit_rule <id> <regla>': Edita una regla existente identificada por <id>.
        - 'delete_rule <id>': Elimina una regla existente identificada por <id>.
        - 'list_rules': Lista todas las reglas existentes en el motor de reglas.
        - Comando no reconocido: Devuelve un mensaje indicando que el comando no es válido.

    Excepciones:
        - Si ocurre un error al añadir, editar o eliminar una regla, se captura la excepción ValueError y se devuelve un mensaje de error.
    """
    split = msg.split(" ")

    match split[0]:
        case 'add_device':
            if len(split) != 2:
                print(f"Formato de add_device incorrecto. Utiliza \"add_device <id>\"")
                return "Formato de add_device incorrecto. Utiliza \"add_device <id>\""

            device_id = split[1]

            # Si el dispositivo ya está registrado, devolvemos un mensaje de error
            if device_id in device_status_dict:
                print(f"Dispositivo {device_id} ya registrado.")
                return f"Dispositivo {device_id} ya registrado."
            
            # Si no, lo registramos
            device_status_dict[device_id] = None # Estado nulo inicial
            device_type_dict[device_id] = None # Tipo nulo inicial

            return f"Dispositivo {device_id} registrado correctamente."

        case 'get_device':
            # Si el id es "all", solicitamos el estado de todos los dispositivos
            # Si no, solicitamos el estado del dispositivo con ese id
            if len(split) != 2:
                print(f"Formato de status incorrecto. Utiliza \"status <id>\" o \"status all\"")
                return "Formato de status incorrecto. Utiliza \"status <id>\" o \"status all\""
                            
            id = split[1]
            if id == "all":
                return request_all_devices_status(id)
            else:
                return request_device_status(id)
            
        case 'set_device':
            if len(split) != 3:
                print(f"Formato de set incorrecto. Utiliza \"set <id> <estado>\"")
                return "Formato de set incorrecto. Utiliza \"set <id> <estado>\""

            id = split[1]
            state = split[2]
            return set_state(id, state)
        
        case 'remove_device':
            if len(split) != 2:
                print(f"Formato de remove_device incorrecto. Utiliza \"remove_device <id>\"")
                return "Formato de remove_device incorrecto. Utiliza \"remove_device <id>\""
            
            # Eliminar el dispositivo de los diccionarios
            id = split[1]
            if id not in device_status_dict:
                print(f"Dispositivo {id} no encontrado.")
                return f"Dispositivo {id} no encontrado."
            del device_status_dict[id]
            del device_type_dict[id]
            del device_updated_dict[id]

            # Decirle al rule engine que se cargue la regla
            rule_engine.remove_rules(id)

            return f"Dispositivo {id} eliminado correctamente."
        
        case 'add_rule':
            # Le mandamos al rule engine todo el mensaje quitando 'add_rule ':
            rule = msg[9:]
            try:
                return add_rule(rule)
            except ValueError as e:
                print(f"Error al añadir la regla: {e}")
                return f"Error al añadir la regla: {e}"
            
        case 'edit_rule':
            if len(split) < 2:
                print(f"Formato de edit_rule incorrecto. Utiliza \"edit_rule <id> <regla>\"")
                return "Formato de edit_rule incorrecto. Utiliza \"edit_rule <id> <regla>\""
            
            # Le mandamos al rule engine el id y todo el mensaje quitando 'edit_rule <id>':
            id = split[1]
            start = len(split[0]) + len(split[1]) + 2
            rule = msg[start:]

            try:
                return edit_rule(id, rule)
            except ValueError as e:
                print(f"Error al editar la regla: {e}")
                return f"Error al editar la regla: {e}"
            
        case 'delete_rule':
            if len(split) != 2:
                print(f"Formato de delete_rule incorrecto. Utiliza \"delete_rule <id>\"")
                return "Formato de delete_rule incorrecto. Utiliza \"delete_rule <id>\""

            # Decirle al rule engine que se cargue la regla
            id = split[1]
            try:
                return rule_engine.delete_rule(id)
            except ValueError as e:
                print(f"Error al eliminar la regla: {e}")
                return f"Error al eliminar la regla: {e}"
            return
        case 'list_rules':
            return rule_engine.list_rules()
        case _:
            print(f"Comando \"{split[0]}\" no reconocido.")
            return f"Comando \"{split[0]}\" no reconocido."
        

def request_all_devices_status(id) -> str:
    """
    Solicita el estado de todos los dispositivos registrados y devuelve un resumen de sus estados.
    Args:
        id (int): Identificador del cliente que realiza la solicitud (actualmente no utilizado en la lógica).
    Returns:
        str: Resumen del estado de todos los dispositivos registrados. Si no hay dispositivos registrados,
        devuelve un mensaje de error. Si algún dispositivo no responde, incluye su último estado registrado.
    Comportamiento:
        - Si no hay dispositivos registrados en `device_status_dict`, imprime un mensaje de error y retorna
          "No hay dispositivos registrados."
        - Publica un mensaje MQTT para solicitar el estado de cada dispositivo registrado.
        - Espera un tiempo definido por `DEVICE_ANSWER_TIMEOUT` a que todos los dispositivos respondan.
        - Si todos los dispositivos responden dentro del tiempo límite, devuelve sus estados.
        - Si algún dispositivo no responde, incluye un mensaje indicando que no respondió y su último estado registrado.
    """
    # Si no hay dispositivos, devolvemos un mensaje de error
    if len(device_status_dict) == 0:
        print("No hay dispositivos registrados.")
        return "No hay dispositivos registrados."

    # Marcamos todos los dispositivos como no actualizados, y solicitamos esu estado
    for device_id in device_status_dict.keys():
        #print(f"[REQUEST STATUS] Notificando dispositivo {device_id} para que nos pase el estado")
        device_updated_dict[device_id] = False
        mqttc.publish(f"redes2/2301/06/{device_id}/home/climate/{device_type_dict[device_id]}/get", "", qos=1)

    response = ""

    # Esperamos a que todos los dispositivos nos pasen el estado
    chrono = 0
    while chrono < DEVICE_ANSWER_TIMEOUT:
        time.sleep(DEVICE_ANSWER_SLEEP)
        chrono += DEVICE_ANSWER_SLEEP

        # Si todos los dispositivos están actualizados, respondemos
        if all(device_updated_dict.values()):
            print("Todos los dispositivos han respondido.") 
            for device_id in device_status_dict.keys():
                response += f"Estado del dispositivo {device_id}: {device_status_dict[device_id]}\n"
            return response

    # Timeout
    for device_id in device_status_dict.keys():
        #print(f"[REQUEST STATUS] Estado de espera del dispositivo {device_id}: {device_updated_dict[device_id]}")
        if device_updated_dict[device_id] == True:
            #print(f"Estado del dispositivo {device_id}: {device_status_dict[device_id]}")
            response += f"Estado del dispositivo {device_id}: {device_status_dict[device_id]}\n"
        else:
            #print(f"Dispositivo {device_id} no responde. Último estado registrado: {device_status_dict[device_id]}")
            response += f"Dispositivo {device_id} no responde. Último estado registrado: {device_status_dict[device_id]}\n"
        
    return response
    

def request_device_status(id) -> str:      
    """
    Solicita el estado de un dispositivo específico y lo devuelve como una cadena de texto.
    Args:
        id (int): Identificador único del dispositivo cuyo estado se desea consultar.
    Returns:
        str: Una cadena que describe el estado actual del dispositivo o un mensaje de error
        si el dispositivo no responde o no se encuentra.
    Descripción:
        - Si el identificador del dispositivo no se encuentra en el diccionario `device_status_dict`,
          se devuelve un mensaje indicando que el dispositivo no fue encontrado.
        - Marca el dispositivo como no actualizado en el diccionario `device_updated_dict` y publica
          un mensaje MQTT para solicitar el estado del dispositivo.
        - Espera un tiempo definido (`DEVICE_ANSWER_TIMEOUT`) verificando periódicamente si el estado
          del dispositivo ha sido actualizado.
        - Si el dispositivo responde dentro del tiempo límite, devuelve el estado actualizado.
        - Si el dispositivo no responde dentro del tiempo límite, devuelve un mensaje indicando que
          no hubo respuesta y muestra el último estado registrado.
    Notas:
        - La función utiliza variables globales como `device_status_dict`, `device_updated_dict`,
          `device_type_dict`, `DEVICE_ANSWER_TIMEOUT`, `DEVICE_ANSWER_SLEEP` y `mqttc`.
        - Es necesario que el sistema esté configurado correctamente para manejar la comunicación MQTT
          y que los diccionarios mencionados estén inicializados.
    """
    if id not in device_status_dict:
        print(f"Dispositivo {id} no encontrado.")
        return f"Dispositivo {id} no encontrado."
    
    # Marcamos el dispositivo como no actualizado, y solicitamos el estado
    device_updated_dict[id] = False
    mqttc.publish(f"redes2/2301/06/{id}/home/climate/{device_type_dict[id]}/get", "", qos=1)
    
    # Esperamos a que el dispositivo nos pase el estado
    chrono = 0
    while chrono < DEVICE_ANSWER_TIMEOUT:
        time.sleep(DEVICE_ANSWER_SLEEP)
        chrono += DEVICE_ANSWER_SLEEP

        if device_updated_dict[id] == True:
            print(f"Estado del dispositivo {id}: {device_status_dict[id]}")
            return f"Estado del dispositivo {id}: {device_status_dict[id]}"

    # Timeout
    print(f"Dispositivo {id} no responde. Último estado registrado: {device_status_dict[id]}")
    return f"Dispositivo {id} no responde. Último estado registrado: {device_status_dict[id]}"    


# Método principal para cambiar el estado de un dispositivo
# Se ejecuta para los dispositivos que han sido setteados por el bot
def set_state(id, state) -> str:
    """
    Establece un nuevo estado para un dispositivo específico y gestiona la confirmación del cambio de estado.
    Args:
        id (str): Identificador único del dispositivo al que se desea cambiar el estado.
        state (str): Nuevo estado que se desea establecer para el dispositivo.
    Returns:
        str: Resumen del resultado del proceso, incluyendo los dispositivos que confirmaron el cambio de estado
             y aquellos que no respondieron.
    Detalles:
        - Si el dispositivo no está registrado en `device_status_dict`, se devuelve un mensaje de error.
        - Se genera un código de confirmación único utilizando `uuid4` y se envía al dispositivo junto con el nuevo estado.
        - Se publica el estado en un tópico MQTT específico para el dispositivo.
        - Se espera un tiempo definido (`DEVICE_ANSWER_TIMEOUT`) para que los dispositivos confirmen el cambio de estado.
        - Se recopila información sobre los dispositivos que confirmaron el cambio y aquellos que no respondieron.
    """
    # Si el dispositivo no está registrado, devolvemos un mensaje de error
    if id not in device_status_dict.keys():
        print(f"Dispositivo {id} no encontrado.")
        return f"Dispositivo {id} no encontrado.\n"
    
    # Limpiamos la lista de dispositivos por confirmar y confirmados
    awaiting_confirmation.clear()
    confirmed_devices.clear()

    # Generamos un código de confirmación único y aleatorio con uuid4
    device_confirmation_code = str(uuid.uuid4())
    awaiting_confirmation[id] = device_confirmation_code
    
    # Enviamos el estado al dispositivo
    topic = f"redes2/2301/06/{id}/home/climate/{device_type_dict[id]}/set"
    payload = f"{state} {device_confirmation_code}"
    mqttc.publish(topic, payload, qos=1)
    print (f"Estado \"{state}\" enviado al dispositivo \"{id}\" con código de confirmación \"{device_confirmation_code}\"")

    # Esperamos a que no queden dispositivos por confirmar
    chrono = 0
    while chrono < DEVICE_ANSWER_TIMEOUT:
        time.sleep(DEVICE_ANSWER_SLEEP)
        chrono += DEVICE_ANSWER_SLEEP

        if len(awaiting_confirmation) == 0:
            print("Todos los dispositivos han confirmado su estado.")
            break

    print(f"Confirmed devices: {confirmed_devices}")

    response = ""

    # Recogemos el estado de los dispositivos que han confirmado su estado
    for device_id, state in confirmed_devices.items():
        response += f"Nuevo estado del dispositivo {device_id}: {state}\n"

    # Recogemos el estado de los dispositivos que NO han confirmado su estado
    for device_id in awaiting_confirmation.keys():
        response += f"El dispositivo {device_id} no responde\n"
    
    return response


def add_rule(rule):    
    """
    Añade una nueva regla al motor de reglas, aplica los cambios necesarios en los dispositivos
    y recopila el estado de los dispositivos tras la aplicación de la regla.
    Args:
        rule (str): La regla a añadir al motor de reglas. Se espera que esté en un formato específico
                    que permita identificar el dispositivo y las condiciones de la regla.
    Returns:
        str: Un mensaje que incluye el resultado de añadir la regla al motor de reglas, el estado
             de los dispositivos que han confirmado su estado y una lista de los dispositivos que
             no han respondido.
    """

    # Añadimos la regla al rule engine
    rule_engine_ret = rule_engine.add_rule(rule)   

    # Limpiamos la lista de dispositivos por confirmar y confirmados
    awaiting_confirmation.clear()
    confirmed_devices.clear()

    # Aplicamos los cambios de estado necesarios
    device_id = rule.split(" ")[1]

    if device_id not in device_status_dict or device_status_dict[device_id] is None:
        print(f"El dispositivo {device_id} no está registrado o no tiene un estado, así que no se checkea la regla.")
        return f"Regla añadida: {rule_engine_ret}"

    rule_changes = rule_engine.check_rules(device_id, device_status_dict[device_id])
    apply_rule_changes(rule_changes)

    # Esperamos a que no queden dispositivos por confirmar
    chrono = 0
    while chrono < DEVICE_ANSWER_TIMEOUT:
        time.sleep(DEVICE_ANSWER_SLEEP)
        chrono += DEVICE_ANSWER_SLEEP

        if len(awaiting_confirmation) == 0:
            print("Todos los dispositivos han confirmado su estado.")
            break

    response = ""

    # Recogemos el estado de los dispositivos que han confirmado su estado
    for device_id, state in confirmed_devices.items():
        response += f"Nuevo estado del dispositivo {device_id}: {state}\n"

    # Recogemos el estado de los dispositivos que NO han confirmado su estado
    for device_id in awaiting_confirmation.keys():
        response += f"El dispositivo {device_id} no responde\n"

    # Retornamos el rule_engine_ret y response
    return f"Regla añadida: {rule_engine_ret}\n{response}"


def edit_rule(id, rule):
    """
    Edita una regla en el motor de reglas y gestiona los estados de los dispositivos.
    Esta función realiza las siguientes acciones:
    1. Edita la regla especificada en el motor de reglas.
    2. Limpia las listas de dispositivos por confirmar y confirmados.
    3. Aplica los cambios de estado necesarios basados en las reglas.
    4. Espera a que todos los dispositivos confirmen su estado dentro de un tiempo límite.
    5. Recoge y retorna el estado de los dispositivos confirmados y no confirmados.
    Args:
        id (int): Identificador único de la regla a editar.
        rule (str): Nueva regla que se aplicará en el motor de reglas.
    Returns:
        str: Resumen del resultado de la edición de la regla, incluyendo el estado de los dispositivos.
    """

    # Editamos la regla en el rule engine
    rule_engine_ret = rule_engine.edit_rule(id, rule)

    # Limpiamos la lista de dispositivos por confirmar y confirmados
    awaiting_confirmation.clear()
    confirmed_devices.clear()

    # Aplicamos los cambios de estado necesarios
    device_id = rule.split(" ")[1]
    rule_changes = rule_engine.check_rules(device_id, device_status_dict[device_id])
    apply_rule_changes(rule_changes)

    # Esperamos a que no queden dispositivos por confirmar
    chrono = 0
    while chrono < DEVICE_ANSWER_TIMEOUT:
        time.sleep(DEVICE_ANSWER_SLEEP)
        chrono += DEVICE_ANSWER_SLEEP

        if len(awaiting_confirmation) == 0:
            print("Todos los dispositivos han confirmado su estado.")
            break

    response = ""

    # Recogemos el estado de los dispositivos que han confirmado su estado
    for device_id, state in confirmed_devices.items():
        response += f"Nuevo estado del dispositivo {device_id}: {state}\n"

    # Recogemos el estado de los dispositivos que NO han confirmado su estado
    for device_id in awaiting_confirmation.keys():
        response += f"El dispositivo {device_id} no responde\n"

    # Retornamos el rule_engine_ret y response
    return f"Regla editada: {rule_engine_ret}\n{response}"


# Método secundario para cambiar el estado de un dispositivo
# Se ejecuta para los dispositivos cuyo estado debe cambiar debido
# a una regla del rule engine
def apply_rule_changes(changes):
    """
    Aplica cambios en las reglas de los dispositivos basados en un mensaje de entrada.
    Args:
        changes (str): Cadena de texto que contiene los cambios a aplicar. 
                       Cada cambio debe estar en una línea separada y tener el formato "id estado",
                       donde "id" es el identificador del dispositivo y "estado" es el nuevo estado a aplicar.
    Returns:
        None: La función no retorna ningún valor. Si no hay cambios (cadena vacía), simplemente retorna.
    Comportamiento:
        - Divide la cadena de cambios en líneas y procesa cada línea.
        - Cada línea debe contener exactamente dos partes separadas por un espacio: el id del dispositivo y el estado.
        - Genera un código de confirmación único para cada dispositivo utilizando `uuid4`.
        - Actualiza las listas de dispositivos en espera de confirmación (`awaiting_confirmation`) y elimina el dispositivo
          de la lista de dispositivos confirmados (`confirmed_devices`) si ya estaba presente.
        - Publica el nuevo estado del dispositivo en un tópico MQTT específico con el formato adecuado.
        - Imprime un mensaje indicando que el estado ha sido enviado al dispositivo junto con el código de confirmación.
    Notas:
        - La función asume que las variables globales `awaiting_confirmation`, `confirmed_devices`, `device_type_dict` y `mqttc`
          están definidas y disponibles en el contexto donde se ejecuta.
        - Si una línea no tiene el formato esperado (dos partes separadas por un espacio), se ignora.
    """
    # Si no hay cambios, devolvemos un mensaje de error
    if changes == "":
        return

    changes_parts = changes.split("\n")
    for change in changes_parts:
        # Dividimos el mensaje en partes
        change_parts = change.split(" ")
        if len(change_parts) != 2:
            continue

        # Obtenemos el id y el estado del dispositivo
        id = change_parts[0]
        state = change_parts[1]

        # Generamos un código de confirmación único y aleatorio con uuid4
        device_confirmation_code = str(uuid.uuid4())
        awaiting_confirmation[id] = device_confirmation_code

        # Eliminamos el dispositivo de la lista de dispositivos confirmados
        if id in confirmed_devices:
            del confirmed_devices[id]
        
        # Enviamos el estado al dispositivo
        topic = f"redes2/2301/06/{id}/home/climate/{device_type_dict[id]}/set"
        payload = f"{state} {device_confirmation_code}"
        mqttc.publish(topic, payload, qos=1)
        print (f"Estado \"{state}\" enviado al dispositivo \"{id}\" con código de confirmación \"{device_confirmation_code}\"")


# ============================================================================================
# MÉTODO DE CIERRE
# ============================================================================================
def close ():
    def close():
        """
        Cierra el programa realizando varias tareas de limpieza y desconexión.

        Este método realiza las siguientes acciones:
        1. Cierra el socket del bot si está conectado.
        2. Detiene el bucle del cliente MQTT y lo desconecta.
        3. Guarda el estado actual de los dispositivos en la base de datos.
        4. Finaliza el programa de manera segura.

        Notas:
        - Se asegura de cerrar correctamente las conexiones de red y guardar los datos necesarios antes de salir.
        - Utiliza `os._exit(0)` para finalizar el programa inmediatamente.

        Variables utilizadas:
        - `conn`: Conexión del socket del bot.
        - `server_socket`: Socket del servidor.
        - `mqttc`: Cliente MQTT.
        - `rule_engine`: Motor de reglas para guardar configuraciones.
        - `args.database`: Ruta de la base de datos.
        - `device_status_dict`: Diccionario con el estado de los dispositivos.
        - `device_type_dict`: Diccionario con los tipos de dispositivos.
        - `database`: Objeto para interactuar con la base de datos.

        """
    print("Cerrando el programa...")
    # Desconectamos el socket del bot
    print("Cerrando el socket del bot...")
    if conn is not None:
        conn.close()
    server_socket.close()

    # Desconectamos el cliente MQTT
    print("Desconectando el cliente MQTT...")
    mqttc.loop_stop()
    mqttc.disconnect()

    # Guardamos el estado de los dispositivos en la base de datos
    print("Guardando el estado en la base de datos...")
    rule_engine.save_rules(args.database)
    data = {
            "device_status_dict": device_status_dict,
            "device_type_dict": device_type_dict,
    }    
    database.save(data, args.database)

    print("Programa cerrado correctamente.")
    os._exit(0)


# ============================================================================================
# MAIN
# ============================================================================================
if __name__ == "__main__":
    args = parse_arguments()
    conn = None
    #print ("Argumentos parseados")

    # Cargamos la base de datos
    rule_engine.load_rules(args.database)

    try:        
        data = database.load(args.database)
        device_status_dict = data["device_status_dict"]
        device_type_dict = data["device_type_dict"]
        print ("Base de datos cargada")        
    except Exception as e:
        device_status_dict = {}
        device_type_dict = {}

    #CONEXION A MQTT    
    unacked_publish = set()
    mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    mqttc.on_connect = on_connect
    mqttc.on_message = on_message
    mqttc.on_subscribe = on_subscribe
    mqttc.on_unsubscribe = on_unsubscribe

    mqttc.user_data_set(unacked_publish)
    #normalmente nos querremos conectar a mqtt.eclipseprojects.io
    print(f"Conectando a {args.host}:{args.mqtt_port}")
    mqttc.connect(args.host, args.mqtt_port)
    print("Conectado")
    mqttc.loop_start()

    #CONEXION AL BOT
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server_socket.bind(('localhost', args.bot_port))
    except socket.error as e:
        print(f"Error al enlazar el socket: {e}")
        close()

    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Permitir reutilizar la dirección inmediatamente
    server_socket.listen(1)  # Escuchamos solo al bot

    #BUCLE PRINCIPAL
    try:        
        while True: #Solo se sale de este bule cuando nos desconectamos
            conn, addr = server_socket.accept()
            print(f"Connected to bot at {addr}")
            
            while True:
                data = conn.recv(RECV_BUFFER)
                if not data:
                    print("Client disconnected.")
                    break  # Salimos del bucle si el cliente se desconecta
                
                print(f"\033[94mReceived command from bot: {data.decode('utf-8')}\033[0m")
                response = process_bot_msg(data.decode("utf-8"))  # Lo procesamos y enviamos a mqtt y luego vamos a tener que contestarle
                print(f"Response to bot: {response}")
                conn.send(response.encode('utf-8'))

    except KeyboardInterrupt:
        close()	