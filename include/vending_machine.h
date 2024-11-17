#ifndef VENDING_MACHINE_H  // Include guard to prevent multiple inclusions
#define VENDING_MACHINE_H

#include "data_structures.h"

// Function Prototypes

// Display Functions
void displayItems(VendingItem[], int );
void printSelectedItems(UserSelection *);

// User Input Functions
int isValidDenomination(float );
void userMoneyInput(float *, CashRegister [], int );
void selectItems(VendingItem [], int , UserSelection *);
void processSelection(VendingItem [], int , UserSelection *);

// Selection Update Functions
void updateSelectedItems(UserSelection *, VendingItem *);
void getSilog(UserSelection *);

// Cash Transaction Functions
void getChange(CashRegister [], float *, int , float *, int *);

#endif  // VENDING_MACHINE_H
