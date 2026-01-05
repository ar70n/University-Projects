# Documentación del Proyecto

## Ubicación de los contenidos

Dado que el enunciado resulta confuso, vamos a dejar claro donde se encuentra la documentación del proyecto:

- En este `README.md` se encuentra la guía de ejecución del proyecto.
- En el documento `/memoria/Requisistos.md` se encuentran:
    - Los reuisistos funcionales
    - La epxlicación de la implementación
    - El diagrama de clases
    - El diagrama de estados de un pedido
    - Los tres casos de uso
    - La descripción de la sintaxis y el formato de los mensajes (RFC)

## Requisitos Previos  

Antes de ejecutar el proyecto, asegúrese de contar con las siguientes dependencias instaladas:

- **Python 3.10**: Intérprete de Python.
- **RabbitMQ Server**: Servidor de mensajería.

## Configuración del Entorno

Para configurar el entorno correctamente, siga estos pasos:

1. Ejecute el script `setup.sh` ubicado en la carpeta `scripts`:
    ```sh
    cd scripts
    ./setup.sh
    ```
    Este script realizará las siguientes acciones:
    - Creará un entorno virtual de Python con las dependencias necesarias.
    - Generará la carpeta `/log` para almacenar los logs de ejecución de las distintas instancias.
    - Pondrá el marcha el servdior de rabbitmq.

2. Ajuste los parámetros de configuración en el archivo `saimazoom/config.py`. En este archivo podrá modificar:
    - Tiempos de simulación.
    - Nomenclatura de las colas.
    - Configuración del servidor de ejecución.

> **Nota:** Es fundamental ejecutar todos los scripts desde la carpeta `scripts` para evitar errores.

## Modelos de Ejecución

El proyecto incluye diferentes modelos de entornos de prueba. A continuación, se describen los scripts disponibles:

- **`simple_instance.sh`**: Modelo con un único cliente, un único robot y un único repartidor.
- **`multiple_clients_single_workers.sh`**: Modelo con dos clientes, un robot y un repartidor.
- **`multiple_clients_multiple_workers.sh`**: Modelo con múltiples clientes, robots y repartidores.

### Creación de un Modelo Personalizado

Para crear un modelo personalizado, siga estos pasos desde el directorio del proyecto:

1. Active el entorno virtual:
    ```sh
    source entorno_virtual/bin/activate
    ```

2. Inicie un controlador (solo debe haber un controlador en ejecución):
    ```sh
    python3 -m launchers.controller
    ```

3. Abra nuevas terminales para cada instancia que desee ejecutar o utilice `&` al final de cada línea para ejecutar en segundo plano:
    ```sh
    python3 -m launchers.commandline_client #&
    python3 -m launchers.launch_client #&
    python3 -m launchers.launch_robot #&
    python3 -m launchers.launch_deliverer #&
    ```

4. Para detener las instancias, puede:
    - Usar `Ctrl+C` en cada terminal.
    - Ejecutar el script `delete_instances.sh` (solo como último recurso, ya que puede ocasionar problemas).

## Ejecución de Pruebas

Para ejecutar las pruebas unitarias, siga estos pasos:


1. Abra una terminal en el directorio del proyecto, acceda al enterno virtual de python creado con el script `setup.sh` ejecutado anteriormente
    ```sh
    source entorno_virtual/bin/activate
    ```
2. Ejecute el siguiente comando:
    ```sh
    python -m unittest discover
    ```
    Este comando buscará y ejecutará todas las pruebas unitarias en el proyecto.
3. Si desea ejecutar pruebas específicas, puede hacerlo con el siguiente comando:
    ```sh
    python -m unittest <ruta_al_archivo_de_prueba>
    ```
4. Revise los resultados:
    - Si todas las pruebas pasan, verá un mensaje indicando que no hubo errores.
    - Si alguna prueba falla, se mostrará un mensaje detallado con el error correspondiente.

### Integración con Visual Studio Code

Visual Studio Code ofrece soporte integrado para pruebas unitarias:

1. Asegúrese de tener instalado el paquete de Python en VS Code.
2. Configure el descubrimiento de pruebas en su proyecto (utilizando `unittest` como framework).
3. Use la vista de pruebas para ejecutar y depurar las pruebas directamente desde el editor.

Esta integración le permitirá identificar y solucionar errores de manera eficiente sin salir del entorno de desarrollo.

