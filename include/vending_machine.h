#ifndef VENDING_MACHINE_H  // Include guard to prevent multiple inclusions
#define VENDING_MACHINE_H

#include "data_structures.h"

// Function Prototypes

// Display Functions
void displayItems(VendingItem[], int);
void printSelectedItems(UserSelection *);

// User Input Functions
int isValidDenomination(float);
void userMoneyInput(float *, CashRegister[], int);
void processSelection(VendingItem[], int, UserSelection *, float *, CashRegister[], int);
void selectItems(VendingItem[], int, UserSelection *, float *, CashRegister[], int);
// Selection Update Functions
void updateSelectedItems(UserSelection *, VendingItem *);
void getSilog(UserSelection *);

// Cash Transaction Functions
void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost,
               int *confirmation);
void resetOrderAfterCancel(UserSelection *, float *, VendingItem[], int);
void dispenseChange(CashRegister cash[], int registerSize, float amountToDispense);
void resetOrderAfterConfirm(UserSelection *, float *);

#endif  // VENDING_MACHINE_H
