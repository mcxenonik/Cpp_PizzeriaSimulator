from enum import Enum


class TaskTypes(Enum):
    GM = 1                  # Give menu
    CO = 2                  # Collect order
    DO = 3                  # Deliver order
    GR = 4                  # Give receipt
    TR = 5                  # Take receipt
    
    