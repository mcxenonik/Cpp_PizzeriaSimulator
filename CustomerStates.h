#ifndef CUSTOMER_STATES_H
#define CUSTOMER_STATES_H

enum class CustomerStates
{
    NEW = 1,                 // Take table
    OM = 2,                  // Order menu
    WFM = 3,                 // Wait for menu
    SO = 4,                  // Submit order
    WFAO = 5,                // Wait for accept order
    WFPO = 6,                // Wait for prepare order
    E = 7,                   // Eat
    AFR = 8,                 // Ask for Receipt
    WFR = 9,                 // Wait for Receipt
    TR = 10,                 // Take Receipt
    WFPR = 11,               // Wait for pay Receipt
    PR = 12,                 // Pay Receipt
    OUT = 13                 // Come out
};

#endif