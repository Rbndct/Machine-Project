#ifndef VENDING_MACHINE_H  // Include guard to prevent multiple inclusions
#define VENDING_MACHINE_H

#include "data_structures.h"

// Function Prototypes

// Display Functions
void displayItems(VendingItem items[], int menuSize);
void printSelectedItems(UserSelection *selection);

// User Input Functions
int isValidDenomination(float denomination);
void userMoneyInput(float *userMoney, CashRegister cash[], int registerSize);
void selectItems(VendingItem items[], int menuSize, UserSelection *selection);
void processSelection(VendingItem items[], int menuSize, UserSelection *selection);

// Selection Update Functions
void updateSelectedItems(UserSelection *selection, VendingItem *selectedItem);
void getSilog(UserSelection *selection);

// Cash Transaction Functions
void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost,
               int *confirmation);

#endif  // VENDING_MACHINE_H
