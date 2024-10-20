

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

int isValidDenomination(float);
void userMoneyInput(float *);

void initializeArrays(int[], float[], int);

void selectItems(VendingItem[], int);
void processSelection(VendingItem[], int , char[][20], int[], float[], float *, int *);
void updateSelectedItems(char[][20], int[], float[], float *, VendingItem *, int *);
void printSelectedItems(char[][20], int[], float[], int, float);
