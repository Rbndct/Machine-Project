
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/**
 * @brief Structure for storing vending item details.
 */
typedef struct
{
    int itemNumber;  // Item number for selection
    char name[20];   // Name of the item
    float price;     // Price of the item in PHP
    int stock;       // Available stock of the item
} VendingItem;

/**
 * @brief Structure for storing cash on hand in the vending machine.
 */
typedef struct
{
    float cashDenomination;  // Cash denomination the machine accepts
    int amountLeft;          // Available number of that denomination
} CashRegister;

/**
 * @brief Structure for tracking user's selected items in the vending machine.
 */
typedef struct
{
    char selectedItems[50][20];  // Array to store names of selected items
    int quantities[50];          // Array to store quantities for each selected item
    float subTotals[50];         // Array to store subtotal costs for each selected item
    int count;                   // Number of items selected
    float totalItemCost;         // Total cost of all selected items
} UserSelection;

#endif  // DATA_STRUCTURES_H
