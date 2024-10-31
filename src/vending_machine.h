/**
 * @brief Structure for storing vending item details.
 */
typedef struct
{
    int itemNumber;      // Item number for selection
    char name[20];       // Name of the item
    float price;         // Price of the item in PHP
    int stock;           // Available stock of the item
} VendingItem;

/**
 * @brief Structure for storing cash on hand in the vending machine.
 */
typedef struct
{
    float cashDenomination; // Cash denomination the machine accepts
    int amountLeft;         // Available number of that denomination
} CashRegister;

/**
 * @brief Structure for tracking user's selected items in the vending machine.
 */
typedef struct 
{
    char selectedItems[50][20]; // Array to store names of selected items (up to 50 items)
    int quantities[50];         // Array to store quantities for each selected item
    float subTotals[50];        // Array to store subtotal costs for each selected item
    int count;                  // Number of items selected
    float totalItemCost;        // Total cost of all selected items
} UserSelection;

// Function Prototypes

// Display Functions
void displayItems(VendingItem items[], int menuSize);
void printSelectedItems(UserSelection *selection);

// User Input Functions
int isValidDenomination(float denomination);
void userMoneyInput(float *userMoney, CashRegister cash[], int registerSize);
void selectItems(VendingItem items[], int menuSize, UserSelection *selection);
void processSelection(VendingItem items[], int index, UserSelection *selection);

// Selection Update Functions
void updateSelectedItems(UserSelection *selection, VendingItem *selectedItem);
void getSilog(UserSelection *selection);

// Cash Transaction Functions
void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost, int *confirmation);
