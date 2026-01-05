import database
from dataclasses import dataclass, field
from typing import Callable


"""
Representa una regla para un sistema de motor de reglas.

Atributos:
    id (int): Identificador único para la regla.
    source_device_id (str): Identificador del dispositivo fuente que activa la regla.
    condition (Callable[[str], bool]): Una función que evalúa una condición basada en el estado del dispositivo fuente.
    state_to_compare (str): El estado del dispositivo fuente a comparar al evaluar la condición.
    target_device_id (str): Identificador del dispositivo objetivo afectado por la regla.
    new_state (str): El nuevo estado que se asignará al dispositivo objetivo si se activa la regla.
    rule_str (str): Una representación en cadena de la regla para propósitos de registro o depuración.
"""
@dataclass
class Rule:

    id: int
    source_device_id: str
    condition: Callable[[str], bool]  # o cualquier tipo adecuado
    state_to_compare: str
    target_device_id: str
    new_state: str
    rule_str: str

rules_by_source_id_dict = {}
rules_by_rule_id_dict = {}

# Formato de las reglas: 
# "si <id dispositivo modificado> <operador comparación> 
# <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>"
# Ejemplo: "Si 1 == ON entonces 2 OFF" 
"""
Añade una nueva regla al motor de reglas.
Esta función toma una cadena que representa una regla, verifica si ya existe 
en el sistema y, si no existe, la añade a los diccionarios correspondientes 
para su gestión. Si la regla ya existe, lanza una excepción.
Args:
    rule_str (str): Una cadena que representa la regla a añadir. 
                    Debe seguir un formato específico.
Returns:
    str: Un mensaje indicando que la regla fue añadida exitosamente junto con su ID.
Raises:
    ValueError: Si la regla ya existe en el sistema.
    Exception: Si ocurre un error al intentar crear la regla.
Notas:
    - La función utiliza una variable global `last_rule_id` para asignar un ID único 
        a cada regla nueva.
    - La regla se almacena en dos diccionarios globales:
        - `rules_by_source_id_dict`: Agrupa las reglas por el ID del dispositivo fuente.
        - `rules_by_rule_id_dict`: Almacena las reglas por su ID único.
    - Si ocurre un error durante la creación de la regla, el ID global se revierte 
        para evitar inconsistencias.
"""
def add_rule(rule_str):

    global last_rule_id
    last_rule_id += 1

    # Si la regla ya existe, no se añade
    source_device_id = rule_str.split(" ")[1] # ID del dispositivo que se va a comparar
    if source_device_id not in rules_by_source_id_dict:
        rules_by_source_id_dict[source_device_id] = []
        
    for rule in rules_by_source_id_dict[source_device_id]:
        if rule.rule_str == rule_str:
            print(f"La regla ya existe: {rule_str}")
            raise ValueError(f"La regla ya existe: {rule_str}")

    try:
        rule = create_rule(rule_str, last_rule_id)

        # Añadir la regla a los diccionarios
        if rule.source_device_id not in rules_by_source_id_dict:
            rules_by_source_id_dict[rule.source_device_id] = []
            
        rules_by_source_id_dict[rule.source_device_id].append(rule)        
        rules_by_rule_id_dict[rule.id] = rule

        print(f"Regla añadida: {rule_str}")
        return f"Regla añadida exitosamente con id: {last_rule_id}"
    
    except Exception as e:
        last_rule_id -= 1
        print(f"No se ha podido crear la regla: {rule_str}")
        print(f"Error: {e}")
        raise e


"""
Edita una regla existente en el sistema.
Args:
    rule_id (int o str): El identificador único de la regla que se desea editar. 
                            Si se proporciona como cadena, se intentará convertir a entero.
    rule_str (str): La nueva definición de la regla en formato de cadena. 
                    El formato esperado es:
                    'Si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>'
Raises:
    ValueError: Si el `rule_id` no es un entero válido.
    ValueError: Si no se encuentra una regla con el `rule_id` proporcionado.
    ValueError: Si el formato de `rule_str` no cumple con el formato esperado.
Returns:
    str: Mensaje indicando que la regla fue editada exitosamente.
Ejemplo de uso:
    edit_rule(1, "Si 101 == 1 entonces 202 0")
"""
def edit_rule(rule_id, rule_str):

    # Parsear rule_id a int
    try:
        rule_id = int(rule_id)
    except ValueError:
        print(f"ID de regla inválido: {rule_id}")
        raise ValueError(f"ID de regla inválido: {rule_id}")

    # Verificar si la regla existe
    if rule_id not in rules_by_rule_id_dict:
        print(f"No se ha encontrado la regla con id: {rule_id}")
        raise ValueError(f"No se ha encontrado la regla con id: {rule_id}")

    # Dividir la regla en partes
    parts = rule_str.split(" ")
    if len(parts) != 7:
        print(f"Formato inválido: {rule_str}")
        raise ValueError("Formato inválido. Formato esperado: 'Si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>'")
    
    # Obtener los parámetros de la regla
    source_device_id = parts[1] # ID del dispositivo que se va a comparar
    operator = parts[2] # Operador de comparación (==, >, <)
    state_to_compare = parts[3] # Estado a comparar
    target_device_id = parts[5] # ID del dispositivo que se va a modificar si se cumple la regla
    new_state = parts[6] # Nuevo estado a asignar al dispositivo si se cumple la regla
    condition = create_condition_function(operator, state_to_compare) # Función de condición

    # Actualizar la regla
    rule = rules_by_rule_id_dict[rule_id]
    rule.source_device_id = source_device_id
    rule.condition = condition
    rule.state_to_compare = state_to_compare
    rule.target_device_id = target_device_id
    rule.new_state = new_state
    rule.rule_str = rule_str

    print(f"Regla editada: {rule.id}")
    return f"Regla editada exitosamente con id: {rule_id}"

"""
Elimina una regla del sistema dado su identificador único.

Args:
    rule_id (int o str): El identificador único de la regla que se desea eliminar. 
                            Si se proporciona como cadena, se intentará convertir a entero.

Raises:
    ValueError: Si el `rule_id` no es un entero válido o si no se encuentra una regla con el ID proporcionado.

Returns:
    str: Mensaje indicando que la regla fue eliminada exitosamente.

Detalles:
    - Verifica si el `rule_id` es válido y si existe una regla asociada a dicho ID.
    - Elimina la regla de los diccionarios `rules_by_rule_id_dict` y `rules_by_source_id_dict`.
    - Imprime mensajes informativos durante el proceso de eliminación.
"""
def delete_rule(rule_id):

    # Parsear rule_id a int
    try:
        rule_id = int(rule_id)
    except ValueError:
        print(f"ID de regla inválido: {rule_id}")
        raise ValueError(f"ID de regla inválido: {rule_id}")

    # Verificar si la regla existe
    if rule_id not in rules_by_rule_id_dict:
        print(f"No se ha encontrado la regla con id: {rule_id}")
        raise ValueError(f"No se ha encontrado la regla con id: {rule_id}")

    # Obtener la regla
    rule = rules_by_rule_id_dict[rule_id]

    # Eliminar la regla de los diccionarios
    rules_by_source_id_dict[rule.source_device_id].remove(rule)
    del rules_by_rule_id_dict[rule.id]

    print(f"Regla eliminada: {rule.id}")
    return f"Regla eliminada exitosamente con id: {rule.id}"

"""
Crea una regla a partir de una cadena de texto que describe la regla y un identificador único.
Args:
    rule_str (str): Cadena de texto que describe la regla en el formato:
        'Si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>'.
        Ejemplo: 'Si dispositivo1 == encendido entonces dispositivo2 apagado'.
    rule_id (int): Identificador único para la regla.
Returns:
    Rule: Objeto que representa la regla creada.
Raises:
    ValueError: Si el formato de la cadena de texto no es válido o no cumple con el formato esperado.
"""
def create_rule(rule_str, rule_id):

    # Dividir la regla en partes
    parts = rule_str.split(" ")
    if len(parts) != 7:
        print(f"Formato inválido: {rule_str}")
        raise ValueError("Formato inválido. Formato esperado: 'Si <id dispositivo modificado> <operador comparación> <estado a comparar> entonces <id dispositivo a modificar> <nuevo estado>'")
    
    source_device_id = parts[1] # ID del dispositivo que se va a comparar
    operator = parts[2] # Operador de comparación (==, >, <)
    state_to_compare = parts[3] # Estado a comparar
    target_device_id = parts[5] # ID del dispositivo que se va a modificar si se cumple la regla
    new_state = parts[6] # Nuevo estado a asignar al dispositivo si se cumple la regla
    condition = create_condition_function(operator, state_to_compare) # Función de condición
    
    # Crear la regla
    rule = Rule(
        id = rule_id,
        source_device_id = source_device_id,
        condition = condition,
        state_to_compare = state_to_compare,
        target_device_id = target_device_id,
        new_state = new_state,
        rule_str = rule_str
    )

    return rule

"""
Crea una función de condición basada en un operador y un estado para comparar.

Parámetros:
operator (str): El operador a utilizar para la comparación. Puede ser "==", ">", o "<".
state_to_compare (str): El estado con el cual se comparará el valor proporcionado.

Retorna:
function: Una función lambda que toma un parámetro `state` y realiza la comparación
            especificada con el operador y el estado proporcionado.

Excepciones:
ValueError: Se lanza si el operador proporcionado no es soportado.
"""
def create_condition_function(operator, state_to_compare):

    if operator == "==":
        return lambda state: str(state) == state_to_compare
    elif operator == ">":
        return lambda state: float(state) > float(state_to_compare)
    elif operator == "<":
        return lambda state: float(state) < float(state_to_compare)
    else:
        print(f"Operador no soportado: {operator}")
        raise ValueError(f"Operador no soportado: {operator}")


"""
Verifica y evalúa las reglas asociadas a un dispositivo específico y su estado actual.
Args:
    device_id (str): El identificador único del dispositivo cuyo estado ha cambiado.
    state (Any): El nuevo estado del dispositivo.
Returns:
    str: Una cadena que contiene los cambios de estado de los dispositivos objetivo 
    en formato "target_device_id new_state", separados por saltos de línea. Si no 
    se cumplen reglas o no hay reglas asociadas al dispositivo, devuelve una cadena vacía.
Comportamiento:
    - Si no existen reglas asociadas al dispositivo proporcionado, imprime un mensaje 
        indicando que no hay reglas y retorna una cadena vacía.
    - Para cada regla asociada al dispositivo:
        - Evalúa la condición de la regla con el estado proporcionado.
        - Si la condición se cumple, imprime un mensaje indicando que la regla se cumplió 
            y agrega el cambio de estado del dispositivo objetivo al resultado.
        - Si la condición no se cumple, imprime un mensaje indicando que la regla no se cumplió.
"""
def check_rules(device_id, state):

    response = ""

    # Verificar si hay reglas para el dispositivo modificado
    if device_id not in rules_by_source_id_dict:
        print(f"No hay reglas para el dispositivo: {device_id}")
        return response
    
    # Evaluar las reglas    
    for rule in rules_by_source_id_dict[device_id]:        
        # Evaluar la condición
        if rule.condition(state):
            # Si se cumple la condición, modificar el estado del dispositivo objetivo
            print(f"Regla cumplida: {device_id} : {state} -> {rule.target_device_id} : {rule.new_state}")
            response += f"{rule.target_device_id} {rule.new_state}\n"
        else:
            print(f"Regla no cumplida")
    
    return response


"""
Lista las reglas definidas en el diccionario `rules_by_rule_id_dict`.

Si no hay reglas definidas, imprime y devuelve un mensaje indicando que no hay reglas.
Si hay reglas, recorre el diccionario `rules_by_rule_id_dict`, imprime cada regla con su ID 
y construye una cadena de texto con todas las reglas definidas.

Returns:
    str: Un mensaje indicando que no hay reglas definidas o una lista de las reglas existentes 
    con sus respectivos IDs en formato de texto.
"""
def list_rules():

    if len(rules_by_rule_id_dict) == 0:
        print("No hay reglas definidas.")
        return "No hay reglas definidas."

    response = "Reglas definidas:\n"

    for rule in rules_by_rule_id_dict.values():
        print(f"ID: {rule.id}, Regla: {rule.rule_str}")
        response += f"ID: {rule.id}, Regla: \"{rule.rule_str}\"\n"

    return response

def remove_rules(source_id):
    """
    Elimina todas las reglas asociadas a un dispositivo específico.

    Args:
        source_id (str): El ID del dispositivo cuyas reglas se desean eliminar.

    Returns:
        str: Un mensaje indicando que las reglas han sido eliminadas exitosamente.
    """

    # Quitar las reglas de rules_by_rule_id_dict
    if source_id in rules_by_source_id_dict:
        del rules_by_source_id_dict[source_id]
        print(f"Reglas eliminadas para el dispositivo: {source_id}")
        return
    
    # Quitar las reglas de rules_by_source_id_dict
    for rule in rules_by_rule_id_dict.values():
        if rule.source_device_id == source_id:
            del rules_by_rule_id_dict[rule.id]
            print(f"Regla eliminada: {rule.id}")
            return f"Regla eliminada exitosamente con id: {rule.id}"


#=====================================================================================
# Funciones para guardar y cargar las reglas en la base de datos
#=====================================================================================
"""
Guarda las reglas actuales en una base de datos especificada.

Args:
    db_name (str): El nombre de la base de datos donde se guardarán las reglas.

Detalles:
    - Recolecta todas las reglas almacenadas en el diccionario `rules_by_rule_id_dict`.
    - Cada regla se guarda como una tupla que contiene el ID de la regla y su representación en forma de cadena (`rule_str`).
    - También guarda el último ID de regla utilizado (`last_rule_id`).
    - Los datos se almacenan en un archivo generado por la función `get_rule_db_file_name` utilizando el nombre de la base de datos proporcionado.

Nota:
    Asegúrate de que las variables `rules_by_rule_id_dict`, `last_rule_id`, y la función `get_rule_db_file_name` estén definidas en el contexto global.
"""
def save_rules(db_name):
    rules = []
    for rule in rules_by_rule_id_dict.values():
        rules.append((rule.id, rule.rule_str))      

    data = {
        "rules": rules,
        "last_rule_id": last_rule_id
    }

    database.save(data, get_rule_db_file_name(db_name))

"""
Carga las reglas desde una base de datos y las organiza en diccionarios globales.
Args:
    db_name (str): El nombre de la base de datos desde donde se cargarán las reglas.
Variables globales:
    rules_by_source_id_dict (dict): Diccionario que organiza las reglas por el ID del dispositivo fuente.
    rules_by_rule_id_dict (dict): Diccionario que organiza las reglas por su ID único.
    last_rule_id (int): El último ID de regla utilizado.
Comportamiento:
    - Intenta cargar los datos de reglas desde un archivo de base de datos.
    - Si ocurre un error durante la carga, inicializa los diccionarios globales como vacíos y establece 
        `last_rule_id` en 0.
    - Procesa las reglas cargadas, creando objetos de regla y organizándolos en los diccionarios globales.
    - Imprime un mensaje indicando si las reglas se han cargado correctamente o no.
Excepciones:
    - Captura cualquier excepción durante la carga de datos y maneja el error inicializando las estructuras 
        globales en un estado vacío.
"""
def load_rules(db_name):
    global rules_by_source_id_dict
    global rules_by_rule_id_dict
    global last_rule_id

    try:
        data = database.load(get_rule_db_file_name(db_name))
    except Exception as e:
        print(f"No se han podido cargar datos de rule engine.")
        rules_by_source_id_dict = {}
        rules_by_rule_id_dict = {}
        last_rule_id = 0
        return

    rules = data["rules"]
    last_rule_id = data["last_rule_id"]

    for rule_info in rules:
        rule_id = rule_info[0]
        rule_str = rule_info[1]
        rule_obj = create_rule(rule_str, rule_id)
        if rule_obj.source_device_id not in rules_by_source_id_dict:
            rules_by_source_id_dict[rule_obj.source_device_id] = []
            
        rules_by_source_id_dict[rule_obj.source_device_id].append(rule_obj)        
        rules_by_rule_id_dict[rule_obj.id] = rule_obj

    print(f"Reglas cargadas.")

"""
Genera el nombre de archivo para una base de datos de reglas a partir del nombre de archivo dado.

Args:
    db_name (str): Nombre del archivo de la base de datos, que debe terminar en ".pkl".

Returns:
    str: Nombre del archivo modificado, con "_rules" añadido antes de la extensión ".pkl".

Nota:
    Si el nombre del archivo no termina en ".pkl", se devuelve el nombre original con "_rules.pkl" añadido.
"""
def get_rule_db_file_name(db_name):
    # db_name acaba en .pkl
    # Queremos poner "_rule" antes de .pkl
    if db_name.endswith(".pkl"):
        db_name = db_name[:-4]
    return db_name + "_rules.pkl"