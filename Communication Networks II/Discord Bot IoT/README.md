## Pre-Requisitos previos de ejecución

- Intérprete de Python3.10 idealmente y el modulo `venv` para crear un entorno virtual.  
- De forma opcional, un broker MQTT. En caso de no tener uno, se puede utilizar el broker público `mqtt.eclipseprojects.io` para realizar pruebas.  
- Una cuenta de discord y el bot de discord instalado con el siguiente 
[enlace](https://discord.com/oauth2/authorize?client_id=1363177430797389874)  


## Instrucciones de ejecución para pruebas

Antes que nada debes ejecutar el script `setup.sh`en la carpeta `scripts` para instalar las dependencias necesarias. Para ello, ejecuta el siguiente comando en la terminal:

```sh
cd scripts
chmod +x setup.sh
./setup.sh
```

Para probar el programa, hay que acceder al entorno virtual con `source entorno_virtual/bin/activate`.  Después, ejecutar en terminales separadas los siguientes comandos:

```sh
python3 controller.py --host <host> --mqtt_port <mqtt_port> --bot_port <bot_port> <database_filename>  
python3 bridge.py --host <host> --port <port>  
python3 -m launchers.dummy-clock.py --host <host> --port <port> --time <HH:MM:SS> --increment <incremento> --rate <rate> <id>  
python3 -m launchers.dummy-sensor.py --host <host> --port <port> --interval <intervalo> --min <min> --max <max> --increment <incremento> <id>  
python3 -m launchers.dummy-switch.py --host <host> --port <port> --probability <probabilidad> <id>  
```

Por ejemplo, para correrlo en localhost y con los valores por defecto:

```sh
python3 controller.py --host mqtt.eclipseprojects.io db.pkl
python3 bridge.py
python3 -m launchers.dummy-clock --host mqtt.eclipseprojects.io clock123
python3 -m launchers.dummy-sensor --host mqtt.eclipseprojects.io sensor123
python3 -m launchers.dummy-switch --host mqtt.eclipseprojects.io switch123
```

---

## Tests

Para ejecutar los tests implementados en el proyecto, debes acceder al entorno virtual de la misma manera que para ejecutar el proyecto y encontrarte en el directorio principal del proyecto.

Los comandos para ejecutar los tests son:

```sh
python3 -m tests.test_controller.py
python3 -m tests.test_device.py
```

---

## Reglas

Existen cuatro comandos referidos a las reglas: añadir, editar, listar y eliminar.

El formato de las reglas es:
"Si <id fuente> <operador> <estado a comparar> entonces <id destino> <nuevo estado>"

Por ejemplo, si queremos que cuando el dispositivo con id "sensor1" tenga un valor superior 25, el dispositivo con id "switch1" cambie su estado a "ON", introduciríamos la siguiente regla:
add_rule Si sensor1 > 25 entonces switch1 ON

Todas las reglas tienen un id único asignada, que se usa para editar y eliminar reglas.

---

## Comandos

- get_device <id dispositivo>: Consulta el estado de los dispositivos. Si usas all, muestra el de todos.
- set_devide <id> <new state>: Establece el estado de un dispositivo.
- add_rule si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>: Añade una regla.
- edit_rule <rule_id> si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>: Edita una regla.
- delete_rule <rule_id>: Elimina una regla.
- list_rules: Lista las reglas.
- add_device <device_id>: Añade un dispositivo al controlador. El tipo de dispositivo puede ser clock, sensor o switch.
- remove_device <device_id>: Elimina un dispositivo del controlador.
- help: Muestra esta ayuda.


---


## Comunicación con los sensores

Existen varias formas en las que el controlador puede comunicarse con los sensores a través de **mqtt**:

### 1. El sensor envía información periódicamente al controlador.

En este caso, el controlador publica su estado en el topic `redes2/2301/06/<device_id>/home/climate/<device_type>`. El controller lo recibe en `on_message` y lo procesa.

### 2. El controlador solicita el estado a un dispositivo.

Cuando el controlador recibe la orden `status`, marca los dispositivos pertinentes como "no actualizados", y les envía a cada uno petición vacía al topic `redes2/2301/06/<device_id>/home/climate/<device_type>/get`.  
Los dispositivos reciben dicha petición, y envían su estado por el topic `redes2/2301/06/<device_id>/home/climate/<device_type>`.  
Cuando el controlador recibe dicha petición, marca el dispositivo como actualizado y registra su estado.

### 3. El controlador establece el estado de un dispositivo.

Cuando el controlador recibe la orden `set`, genera un código de confirmación. Tras esto, envía el nuevo estado y el código de confirmación al dispositivo por el topic `redes2/2301/06/<device_id>/home/climate/<device_type>/set`, y añade el dispositivo a un diccionario de dispositivos a los que se está esperando. Tras esto, se queda esperando a que dicho diccionario se quede vacío, haciendo comprobaciones periódicas.  
El dispositivo recibe el mensaje del controlador, cambia su estado, y contesta al controlador con el nuevo estado y el código de confirmación por el topic `redes2/2301/06/<device_id>/home/climate/<device_type>/confirm`.  
El controlador recibe la confirmación, cuidando que el código de confirmación coincida. El objetivo de esto es asegurarnos de que el dispositivo está confirmando el `set` que le hemos mandado, en vez de ser una respuesta retardada a un `set` previo, logrando un sistema mucho más robusto. Una vez confirmado, se elimina al dispositivo del diccionario de dispositivos esperados y lo mueve al de dispositivos confirmados, registrando su nuevo estado, no sin antes comprobar las reglas del rule engine. Si dichas reglas dictan otro cambio de estado, el controlador vuelve a añadir dichos dispositivos al diccionario de esperados, y les notifica.  
En el momento en el que todos los dispositivos hayan confirmado su nuevo estado, o si se excede el tiempo límite, el bucle de espera y comprobación inicial acabará, y se notificará al bridge de todos los nuevos estados de los dispositivos modificados.

---
