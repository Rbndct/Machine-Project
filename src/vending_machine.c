#include "vending_machine.h"

#define OUT_OF_STOCK_MSG "Out of Stock"
#define INVALID_DENOM_MSG "Invalid denomination! Please try again."
#define SEPARATOR "--------------------------------------------------------------"

/**
 * @brief Displays the available items in the vending machine.
 * @param items An array of VendingItem structs, each representing an item in the vending machine.
 * @param menuSize The number of items available in the vending machine menu.
 */
void displayItems(VendingItem items[], int menuSize)
{
    // Headers for the vending machine item display
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)", "Stock Left");
    printf(SEPARATOR "\n");

    // Loop through the items and display their details
    for (int i = 0; i < menuSize; i++)
    {
        // Print item details (item number, name, price, and stock)
        printf("%-12d | %-15s | %-11.2f | %-3d", (items[i]).itemNumber, (items[i]).name, (items[i]).price, (items[i]).stock);

        // Check if the item is out of stock and display a message if true
        if ((items[i]).stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");
}

/**
 * @brief Accepts money input from the user for the vending machine.
 * @param userMoney Tracks the total money inserted by the user.
 */
void userMoneyInput(float *userMoney)
{
    float moneyInserted; // Holds the value of each money denomination inserted

    printf("Insert money into the vending machine.\n" "Allowed Denominations:\n" 
    "Bills: 20, 50, 100, 200, 500 (PHP)\n" "Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");

    // Loop to accept money input until the user is done
    while (1)
    {
        printf("\nEnter the cash denomination (0 when done): ");
        scanf("%f", &moneyInserted);

        // If the user enters 0, exit the loop
        if (moneyInserted == 0) break;

        // Check if the inserted amount is a valid denomination
        if (isValidDenomination(moneyInserted)) 
        {
            *userMoney += moneyInserted; // Update total money inserted
            printf("You inserted: %.2f PHP\nTotal so far: %.2f PHP\n", moneyInserted, *userMoney);
        }
        // Handle invalid denominations
        else
        {
            printf(INVALID_DENOM_MSG "\n");
        }
    }
    // Display total money inserted once the user is done
        printf("Total money inserted: %.2f PHP\n" SEPARATOR "\n", *userMoney);
}

/**
 * @brief Checks if the inserted money denomination is valid for the vending machine.
 * - Bills: 20, 50, 100, 200, 500 (PHP)
 * - Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)
 * @param moneyInserted The monetary amount to be validated.
 * @return int Returns 1 (true) if the denomination is valid, and 0 (false) otherwise.
 */
int isValidDenomination(float moneyInserted) {
    float validDenominations[] = {20, 50, 100, 200, 500, 1, 5, 10, 0.25, 0.10, 0.05};
    int numValidDenominations = 11;
    // Check if the inserted amount matches any valid denomination
    for (int i = 0; i < numValidDenominations; i++) {
        if (moneyInserted == validDenominations[i]) {
            return 1; // Valid denomination
        }
    }
    return 0; // Invalid denomination
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
 * @param items An array of VendingItem structs representing the items in the vending machine.
 * @param menuSize The number of items available in the vending machine menu.
 */
void selectItems(VendingItem items[], int menuSize)
{
    int done = 0;
    float totalItemCost = 0;
    char selectedItems[menuSize][20]; // Array to store selected item names
    int quantities[menuSize];         // Array to store quantities
    float subTotals[menuSize];        // Array to store subtotals
    int count = 0;                    // Counter for unique selected items

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
            VendingItem *selectedItem = &items[selection - 1];

            // Check stock and process selection
            if ((*selectedItem).stock > 0)
            {
                // Check if the item is already in the selectedItems array
                int found = 0;
                for (int i = 0; i < count; i++)
                {
                    // Compares the name of selected item with item stored in the selectedItems array at index[i]
                    // Indicates that the same item has already been selected -- avoids item repetition in final order receipt
                    if (strcmp(selectedItems[i], (*selectedItem).name) == 0)
                    {
                        // Item already selected, update quantity and subtotal
                        quantities[i]++;
                        subTotals[i] = (*selectedItem).price * quantities[i];
                        totalItemCost += (*selectedItem).price;
                        found = 1;
                        break;
                    }
                }

                // If the item was not previously selected, add it to the list of selected items
                if (!found)
                {
                    //Copies current selected item onto selectedItems array at index[count]
                    // Adding newly selected item to selectedItems list
                    strcpy(selectedItems[count], (*selectedItem).name);
                    quantities[count] = 1; // First time selected, quantity is 1

                    // Calculates subtotal per item
                    subTotals[count] = (*selectedItem).price;
                    totalItemCost += (*selectedItem).price;
                    count++;
                }

                (*selectedItem).stock--; // Decrement stock

                // Inform the user of their selection and the current total cost
                printf("You have selected: %s, which costs %.2f\n", (*selectedItem).name, (*selectedItem).price);
                printf("Current total cost is %.2f\n", totalItemCost);
            }
            else
            {
                printf("Sorry, %s is currently out of stock!\n", (*selectedItem).name);
            }
        }
        else
        {
            printf("Invalid item number! Please try again.\n");
        }
    }

    // Print the selected items and total
    printSelectedItems(selectedItems, quantities, subTotals, count, totalItemCost); // Call to print function
}


/**
 * @brief Prints the selected items, their quantities, and their total costs.
 * @param selectedItems Array containing the names of the selected items.
 * @param quantities An array containing the quantities of each selected item.
 * @param subTotals An array containing the subtotal cost for each selected item.
 * @param count The number of unique selected items. (So that each item is only printed once)
 * @param finalTotal The final total cost of all selected items.
 */
void printSelectedItems(char selectedItems[][20], int quantities[], float subTotals[], int count, float finalTotal)
{
    // Print table header
    printf("\n\nYou have selected:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    // Print each selected item with its quantity and total cost
    for (int i = 0; i < count; i++)
    {
        printf("%-15s | %-10d | %-10.2f\n", selectedItems[i], quantities[i], subTotals[i]);
    }

    // Print the final total cost
    printf(SEPARATOR "\n");
    printf("Final Total: %.2f\n", finalTotal);
}