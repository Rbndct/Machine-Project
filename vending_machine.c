#include "vending_machine.h"

/**
 * @brief Displays the available items in the vending machine.
 *
 * This function prints a table showing the item number, name, price, and stock for each vending item. It also indicates if an item is out of stock.
 *
 * @param items An array of VendingItem structs, each representing an item in the vending machine.
 * @param menuSize The number of items available in the vending machine menu.
 */
void displayItems(VendingItem items[], int menuSize)
{
    // Headers for the vending machine item display
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)", "Stock Left");
    printf("--------------------------------------------------------------\n");

    // Loop through the items and display their details
    for (int i = 0; i < menuSize; i++)
    {
        // Print item details (item number, name, price, and stock)
        printf("%-12d | %-15s | %-11.2f | %-3d", (items[i]).itemNumber, (items[i]).name, (items[i]).price, (items[i]).stock);

        // Check if the item is out of stock and display a message if true
        if ((items[i]).stock == 0)
        {
            printf(" %-12s", "Out of Stock");
        }

        printf("\n");
    }
    printf("--------------------------------------------------------------\n");
}

/**
 * @brief Accepts money input from the user for the vending machine.
 *
 * This function prompts the user to insert valid cash denominations until they are done.
 * It updates the total amount of money inserted and checks for invalid denominations.
 *
 * @param userMoney Tracks the total money inserted by the user.
 */
void userMoneyInput(float *userMoney)
{
    int done = 0;        // Control variable to indicate when the user is done inserting money
    float moneyInserted; // Holds the value of each money denomination inserted

    printf("Insert money into the vending machine.\n");
    printf("Allowed Denominations:\n");
    printf("Bills: 20, 50, 100, 200, 500 (PHP)\n");
    printf("Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");

    // Loop to accept money input until the user is done
    while (!done)
    {
        printf("\nEnter the cash denomination: ");
        printf("Enter 0 when done: ");
        scanf("%f", &moneyInserted);

        // If the user enters 0, exit the loop
        if (moneyInserted == 0)
        {
            done = 1;
        }
        // Check if the inserted amount is a valid denomination
        else if (moneyInserted == 20 || moneyInserted == 50 ||
                 moneyInserted == 100 || moneyInserted == 200 ||
                 moneyInserted == 500 || moneyInserted == 1 || moneyInserted == 5 ||
                 moneyInserted == 10 || moneyInserted == 0.25 ||
                 moneyInserted == 0.10 || moneyInserted == 0.05)
        {
            *userMoney += moneyInserted; // Update total money inserted
            printf("You inserted: %.2f PHP\n", moneyInserted);
            printf("Total money inserted so far: %.2f PHP\n", *userMoney);
        }
        // Handle invalid denominations
        else
        {
            printf("Invalid denomination! Please try again.\n");
        }
    }

    // Display total money inserted once the user is done
    printf("Total money inserted: %.2f PHP\n", *userMoney);
    printf("--------------------------------------------------------------\n");
}

/**
 * @brief Allows the user to select items from a vending machine menu.
 *
 * The user can select items by entering the corresponding item number.
 * The function checks if the item is available in stock and processes the selection by updating the quantity,
 * subtotal, and total cost of the selected item(s).
 * The function stops when the user enters '0'.
 *
 * @param items An array of VendingItem structs representing the items in the vending machine.
 * @param menuSize The number of items available in the vending machine menu.
 */
void selectItems(VendingItem items[], int menuSize)
{
    int done = 0, selection;
    float totalItemCost = 0;
    char selectedItems[menuSize][20]; // Array to store selected item names
    int quantities[menuSize];         // Array to store quantities
    float subTotals[menuSize];        // Array to store subtotals
    int count = 0;                    // Counter for unique selected items

    // Initialize quantities and subtotals arrays to zero
    for (int i = 0; i < menuSize; i++)
    {
        quantities[i] = 0;
        subTotals[i] = 0;
    }

    while (!done)
    {
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
                    strcpy(selectedItems[count], (*selectedItem).name);
                    quantities[count] = 1; // First time selected, quantity is 1
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
 *
 * This function displays the selected items in a table format, showing the item name,
 * the quantity selected, and the total cost for each item. It also displays the final total cost.
 *
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
    printf("--------------------------------------------------------------\n");

    // Print each selected item with its quantity and total cost
    for (int i = 0; i < count; i++)
    {
        printf("%-15s | %-10d | %-10.2f\n", selectedItems[i], quantities[i], subTotals[i]);
    }

    // Print the final total cost
    printf("--------------------------------------------------------------\n");
    printf("Final Total: %.2f\n", finalTotal);
}