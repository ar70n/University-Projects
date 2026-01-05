"""
CLASE: Order
DESCRIPCIÓN: Clase que representa un pedido en el sistema.
ATRIBUTOS:
    - id: int - ID del pedido.
    - products_id: list - Lista de IDs de productos en el pedido.
    - state: OrderState - Estado actual del pedido.
MÉTODOS:
    - __init__(): Inicializa el pedido con un ID, una lista de productos y un estado por defecto.
    - __str__(): Devuelve una representación en cadena de texto del pedido.
"""

from saimazoom.clases.order_state import OrderState

class Order:
    def __init__(self):
        self.id = None
        self.products_id = [] #List of product ids
        self.state = OrderState.WAREHOUSE #Order state
    
    def __str__(self):
        return f"Order with id:{self.id},products_id:{self.products_id}, order_state:{self.state}\n"