"""
database.py
DESCRIPCIÓN: Módulo de base de datos para guardar y cargar datos.
    Este módulo proporciona funciones para guardar y cargar datos en archivos utilizando el módulo pickle.
    Es importante tener en cuenta que los datos se guardan en un formato binario, que puede no ser legible para humanos.
    Los datos se guardan en una estructura de directorios que se crea si no existe.
    La variable DB_ROOT especifica el directorio raíz para los archivos de la base de datos.
"""

import os
import pickle

DB_ROOT = "./data/"


"""
FUNCIÓN: save(data, file_name)
DESCRIPCIÓN: Guarda los datos en un archivo utilizando el módulo pickle.
ARGS_IN:
    - data: Los datos a guardar. Pueden ser de cualquier tipo que sea serializable por pickle.
    - file_name: El nombre del archivo donde se guardarán los datos. Se creará un directorio si no existe.
RETURNS: None
"""
def save(data, file_name):
    print("[Database] Saving data...", flush=True)
    file = os.path.join(DB_ROOT, file_name)
    os.makedirs(os.path.dirname(file), exist_ok=True)
    with open(file, 'wb') as f:
        pickle.dump(data, f)

"""
FUNCIÓN: load(file_name)
DESCRIPCIÓN: Carga los datos de un archivo utilizando el módulo pickle.
ARGS_IN:
    - file_name: El nombre del archivo desde el cual se cargarán los datos.
RETURNS: Los datos cargados desde el archivo. Pueden ser de cualquier tipo que haya sido guardado previamente.
"""
def load(file_name):
    print("[Database] Loading data...", flush=True)
    file = os.path.join(DB_ROOT, file_name)

    with open(file, 'rb') as f:
        data = pickle.load(f)
        return data