#include "data_structures.h"

// Maintenance Function Prototypes
int maintenanceValidation(int *);
void viewInventory(VendingItem[], int);
void modifyPrice(VendingItem[], int);
void restockInventory(VendingItem[], int);

void handleAmountBasedCashOut(CashRegister[], int);
void handleQuantityBasedCashOut(CashRegister[], int);
void cashOut(CashRegister[], int);

void reStockRegister(CashRegister[], int);
void viewCashRegister(CashRegister[], int);
