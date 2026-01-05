"""
CLASE: Database
DESCRIPCIÓN: Clase para manejar la base de datos de pedidos y clientes.
ATRIBUTOS:
    - orders: dict - Diccionario que almacena los pedidos.
    - clients_orders: dict - Diccionario que almacena los pedidos por cliente.
MÉTODOS:
    - save(data): Guarda los datos en un archivo binario.
    - load(): Carga los datos desde un archivo binario.
"""

import os
import pickle
from saimazoom import config

DB_FILE = f"./data/{config.data_file}"

"""
FUNCIÓN: save(data)
ARGS_IN: data: dict - Diccionario con los datos a guardar.
DESCRIPCIÓN: Guarda los datos en un archivo binario utilizando pickle.
ARGS_OUT: None
"""
def save(data):
    print("[Database] Saving data...", flush=True)
    os.makedirs(os.path.dirname(DB_FILE), exist_ok=True)
    with open(DB_FILE, 'wb') as f:
        pickle.dump(data, f)

"""
FUNCIÓN: load()
ARGS_IN: None
DESCRIPCIÓN: Carga los datos desde un archivo binario utilizando pickle.
ARGS_OUT: dict - Diccionario con los datos cargados.
"""
def load():
    print("[Database] Loading data...", flush=True)
    try:
        with open(DB_FILE, 'rb') as f:
            data = pickle.load(f)
            return data
    except (FileNotFoundError, EOFError, pickle.UnpicklingError):
        return {
            "orders": {},  # Diccionario vacío para pedidos
            "clients_orders": {},  # Diccionario vacío para pedidos por cliente
        }