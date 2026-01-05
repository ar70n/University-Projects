"""
CLASE: OrderState
DESCRIPCIÓN: Enum que representa los diferentes estados de un pedido en 
el sistema. Son autodescriptivos.    
"""

from enum import Enum

class OrderState(Enum):
    WAREHOUSE = "Warehouse"
    CONVEYOR_BELT = "Conveyor Belt"
    READY_FOR_DISTRIBUTION = "Ready for Pickup"
    IN_DISTRIBUTION = "In Distribution"
    DELIVERED = "Delivered"
    RETURNED = "Returned" # El pedido no ha podido ser entregado
    CANCELLED = "Cancelled"