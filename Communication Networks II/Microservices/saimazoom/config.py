# Raíz nombrado colas
QUEUE_ROOT = "2301-14_"

# Nombre de las colas
client_queue = f"{QUEUE_ROOT}client_petitions"
base_client_response_queue = f"{QUEUE_ROOT}client_responses"
robot_queue = f"{QUEUE_ROOT}robot_work"
robot_response_queue = f"{QUEUE_ROOT}robot_responses"
deliver_queue = f"{QUEUE_ROOT}deliver_work"
deliver_response_queue = f"{QUEUE_ROOT}deliver_responses"

# Servidor RabbitMQ
queue_server = 'localhost'

# Tiempos de simulacion
robot_search_min = 1
robot_search_max = 1

conveyor_min = 1
conveyor_max = 1

deliver_min = 1
deliver_max = 1

# Probabilidades simulacion
p_warehouse = 0.8
p_deliver = 0.7

# Intentos de entrega
deliver_attempts = 3

# Fichero de datos
data_file = 'data.pkl'

# Timeout del cliente
client_timeout = 3