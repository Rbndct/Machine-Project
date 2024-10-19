

// Structure for storing vending item details
typedef struct
{
    int itemNumber; // Item number for selection
    char name[20];  // Name of the item
    float price;    // Price of the item in PHP
    int stock;      // Available stock of the item
} VendingItem;

// Function Prototypes
void displayItems(VendingItem[], int);
void userMoneyInput(float *);
void selectItems(VendingItem[], int);
void printSelectedItems(char[][20], int[], float[], int, float);
