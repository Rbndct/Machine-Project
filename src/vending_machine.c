#include "vending_machine.h"

#define OUT_OF_STOCK_MSG "Out of Stock"
#define INVALID_DENOM_MSG "Invalid denomination! Please try again."
#define SEPARATOR "--------------------------------------------------------------"

// Define valid denominations as constants
const float VALID_DENOMINATIONS[] = {20, 50, 100, 200, 500, 1, 5, 10, 0.25, 0.10, 0.05};
const int NUM_VALID_DENOMINATIONS = 11;

/**
 * @brief Displays the available items in the vending machine.
 * @param items An array of VendingItem structs.
 * @param menuSize The number of items available.
 */
void displayItems(VendingItem items[], int menuSize)
{
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)", "Stock Left");
    printf(SEPARATOR "\n");

    // Loop through the items and display their details
    for (int i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-11.2f | %-3d", items[i].itemNumber, items[i].name, items[i].price, items[i].stock);
        // Check if the item is out of stock and display a message if true
        if (items[i].stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");
}

/**
 * @brief Checks if the inserted money denomination is valid for the vending machine.
 * @param moneyInserted The monetary amount to be validated.
 * @return int Returns 1 (true) if valid, and 0 (false) otherwise.
 */
int isValidDenomination(float moneyInserted)
{
    for (int i = 0; i < NUM_VALID_DENOMINATIONS; i++)
    {
        if (moneyInserted == VALID_DENOMINATIONS[i])
        {
            return 1; // Valid denomination
        }
    }
    return 0; // Invalid denomination
}

/**
 * @brief Accepts money input from the user for the vending machine.
 * @param userMoney Tracks the total money inserted by the user.
 */
void userMoneyInput(float *userMoney)
{
    float moneyInserted;

    printf("Insert money into the vending machine.\n"
           "Allowed Denominations:\n"
           "Bills: 20, 50, 100, 200, 500 (PHP)\n"
           "Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");

    while (1)
    {
        printf("\nEnter the cash denomination (0 when done): ");
        scanf("%f", &moneyInserted);

        if (moneyInserted == 0)
            break;

        if (isValidDenomination(moneyInserted))
        {
            *userMoney += moneyInserted;
            printf("You inserted: %.2f PHP\nTotal so far: %.2f PHP\n", moneyInserted, *userMoney);
        }
        else
        {
            printf(INVALID_DENOM_MSG "\n");
        }
    }
    printf("Total money inserted: %.2f PHP\n" SEPARATOR "\n", *userMoney);
}

/**
 * @brief Initializes the quantities and subtotals arrays to zero.
 * @param quantities An array to store quantities of items.
 * @param subTotals An array to store subtotal values.
 * @param menuSize The number of items in the menu.
 */
void initializeArrays(int quantities[], float subTotals[], int menuSize)
{
    for (int i = 0; i < menuSize; i++)
    {
        quantities[i] = 0;
        subTotals[i] = 0;
    }
}

/**
 * @brief Allows the user to select items from a vending machine menu.
 * @param items An array of VendingItem structs.
 * @param menuSize The number of items available in the menu.
 */
void selectItems(VendingItem items[], int menuSize, float *totalItemCost)
{
    int done = 0;
    char selectedItems[menuSize][20];
    int quantities[menuSize];
    float subTotals[menuSize];
    int count = 0;

    initializeArrays(quantities, subTotals, menuSize);

    while (!done)
    {
        int selection;
        printf("\n\nEnter item number to order (1-%d).\nEnter 0 when done: ", menuSize);
        scanf("%d", &selection);

        // If the user enters 0, exit the selection process
        if (selection == 0)
        {
            done = 1; // Exit the selection loop
        }
        else if (selection >= 1 && selection <= menuSize)
        {
            processSelection(items, selection - 1, selectedItems, quantities, subTotals, totalItemCost, &count);
        }
        else
        {
            printf("Invalid item number! Please try again.\n");
        }
    }

    printSelectedItems(selectedItems, quantities, subTotals, count, totalItemCost);
}

/**
 * @brief Processes the user's item selection and updates stock and totals.
 * @param items The array of VendingItem structs.
 * @param index The index of the selected item.
 * @param selectedItems Array of selected item names.
 * @param quantities Array of item quantities.
 * @param subTotals Array of subtotals for selected items.
 * @param totalItemCost Pointer to the total item cost.
 * @param count Pointer to the current count of unique selected items.
 */
void processSelection(VendingItem items[], int index, char selectedItems[][20], int quantities[], float subTotals[], float *totalItemCost, int *count)
{
    VendingItem *selectedItem = &items[index];

    // Check stock and process selection
    if (selectedItem->stock > 0)
    {
        // Update selection if item is already chosen
        updateSelectedItems(selectedItems, quantities, subTotals, totalItemCost, selectedItem, count);

        selectedItem->stock--; // Decrease stock for selected item

        printf("You have selected: %s, which costs %.2f\n", selectedItem->name, selectedItem->price);
        printf("Current total cost is %.2f\n", *totalItemCost);
    }
    else
    {
        printf("Sorry, %s is currently out of stock!\n", selectedItem->name);
    }
}

/**
 * @brief Updates the quantities and subtotals for selected items.
 * @param selectedItems Array of selected item names.
 * @param quantities Array of item quantities.
 * @param subTotals Array of subtotals for selected items.
 * @param totalItemCost Pointer to the total item cost.
 * @param selectedItem Pointer to the selected VendingItem.
 * @param count Pointer to the current count of unique selected items.
 */
void updateSelectedItems(char selectedItems[][20], int quantities[], float subTotals[], float *totalItemCost, VendingItem *selectedItem, int *count)
{
    int existingIndex = -1; // Initialize to -1 to indicate no match found yet

    // Check if the item is already in the list
    for (int i = 0; i < *count; i++)
    {

        // Compare the name of the selected item with item stored in the selectedItems array at index[i]
        if (strcmp(selectedItems[i], selectedItem->name) == 0)
        {
            existingIndex = i; // Match found, store the index
            break;
        }
    }

    // If item is already in the list, update its quantity and subtotal
    if (existingIndex != -1)
    {
        quantities[existingIndex]++;                     // Increase the quantity of the selected item
        subTotals[existingIndex] += selectedItem->price; // Update the subtotal for the selected item
    }
    else
    {
        // If item is not found, add a new entry
        // Copies the current selected item onto selectedItems array at index[count]
        strcpy(selectedItems[*count], selectedItem->name);

        // Set the initial quantity to 1 for the newly selected item
        quantities[*count] = 1;

        // Add the price of the selected item as the subtotal for this item
        subTotals[*count] = selectedItem->price;
        (*count)++; // Increment count for the new item
    }

    *totalItemCost += selectedItem->price; // Update the total cost
}

/**
 * @brief Prints the selected items, their quantities, and their total costs.
 * @param selectedItems Array containing the names of the selected items.
 * @param quantities An array containing the quantities of each selected item.
 * @param subTotals An array containing the subtotal cost for each selected item.
 * @param count The number of unique selected items.
 * @param finalTotal The final total cost of all selected items.
 */
void printSelectedItems(char selectedItems[][20], int quantities[], float subTotals[], int count, float *totalItemCost)
{
    printf("\n\nYou have selected:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    // Check if count is greater than 0
    if (count > 0)
    {
        // Print each selected item with its quantity and total cost
        for (int i = 0; i < count; i++)
        {
            printf("%-15s | %-10d | %-10.2f\n", selectedItems[i], quantities[i], subTotals[i]);
        }
    }
    else
    {
        printf("No items selected.\n"); // Inform the user if no items were selected
    }

    printf(SEPARATOR "\n");
}

void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost)
{
    float userChange = *userMoney - *totalItemCost;
    printf("%-15s %-5.2f %-5s", "Final Total:", *totalItemCost, "PHP");
    printf("\n%-15s %-5.2f %-5s", "Money Input:", *userMoney, "PHP");
    printf("\n%-15s %-5.2f %-5s", "Change Total:", userChange, "PHP");

    printf("\n" SEPARATOR);
    for (int i = 0; i < registerSize; i++) // Iterating through cash register
    {
        // Check if userMoney can accommodate the cash denomination
        while (userChange >= cash[i].cashDenomination && cash[i].amountLeft > 0)
        {
            // Dispense this denomination
            userChange -= cash[i].cashDenomination; // Update remaining user money
            cash[i].amountLeft--;                   // Decrease available amount in the cash register

            printf("\n%-15s %-5.2f %-5s", "Dispensed", cash[i].cashDenomination, "PHP");
        }
    }
    printf("\n" SEPARATOR);
    if (userChange > 0)
    {
        printf("Unable to dispense exact change. Remaining amount: %.2f\n", userChange);
    }
    else
    {
        printf("\nChange successfully dispensed.\n");
    }
}
