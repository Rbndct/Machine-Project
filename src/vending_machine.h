

// Structure for storing vending item details
typedef struct
{
    int itemNumber; // Item number for selection
    char name[20];  // Name of the item
    float price;    // Price of the item in PHP
    int stock;      // Available stock of the item
} VendingItem;

// Structure for storing cash on hand
typedef struct
{
    float cashDenomination; // Cash denomination the machine accepts
    int amountLeft;         // Available # of that denomination
} CashRegister;

typedef struct {
    char selectedItems[50][20]; // Assuming max 50 items can be selected
    int quantities[50];
    float subTotals[50];
    int count;
    float totalItemCost;
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