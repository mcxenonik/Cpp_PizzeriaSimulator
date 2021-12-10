from enum import Enum


class CustomerStates(Enum):
    NEW = 1                 # Take table
    OM = 2                  # Order menu
    WFM = 3                 # Wait for menu
    SO = 4                  # Submit order
    WFAO = 5                # Wait for accept order
    WFPO = 6                # Wait for prepare order
    E = 7                   # Eat
    AFB = 8                 # Ask for Bill
    WFB = 9                 # Wait for bill
    TB = 10                 # Take bill
    WFPB = 11               # Wait for pay bill
    PB = 12                 # Pay bill
    OUT = 13                # Come out