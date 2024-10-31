#include "vending_machine.h"

#define OUT_OF_STOCK_MSG "Out of Stock"
#define INVALID_DENOM_MSG "Invalid denomination! Please try again."
#define SEPARATOR "--------------------------------------------------------------"

// Define valid denominations as constants
const float VALID_DENOMINATIONS[] = {20, 50, 100, 200, 500, 1, 5, 10, 0.25, 0.10, 0.05};
const int NUM_VALID_DENOMINATIONS = 11;

/**
 * @brief Displays the list of vending items with their details.
 * @param items An array of VendingItem structures containing item details.
 * @param menuSize The total number of items in the array.
 */
void displayItems(VendingItem items[], int menuSize)
{
    // Print header for the item details table
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)",
           "Stock Left");
    printf(SEPARATOR "\n");

    // Loop through the items array to display each item's details
    for (int i = 0; i < menuSize; i++)
    {
        // Display item details
        printf("%-12d | %-15s | %-11.2f | %-3d",
               items[i].itemNumber,  // Item number
               items[i].name,        // Item name
               items[i].price,       // Item price
               items[i].stock        // Remaining stock
        );

        // Check if the item is out of stock and display a message if true
        if (items[i].stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);  // Display out of stock message
        }
        printf("\n");  // Move to the next line after each item
    }

    // Print footer for the item details table
    printf(SEPARATOR "\n");
}

/**
 * @brief Checks if the inserted money is a valid denomination.
 * @param moneyInserted The amount of money to be checked for validity.
 * @return 1 if the denomination is valid, 0 otherwise.
 */
int isValidDenomination(float moneyInserted)
{
    // Loop through all valid denominations to find a match
    for (int i = 0; i < NUM_VALID_DENOMINATIONS; i++)
    {
        // Check if the inserted money matches the current valid denomination
        if (moneyInserted == VALID_DENOMINATIONS[i])
        {
            return 1;  // Valid denomination found
        }
    }

    // If no match is found, return 0 for an invalid denomination
    return 0;
}

/**
 * @brief Updates the cash register by incrementing the count of a specific
 * denomination.
 * @param cashRegister The array of cash register denominations.
 * @param registerSize The number of denominations in the cash register.
 * @param denomination The specific denomination to be updated.
 */
void updateCashRegister(CashRegister cashRegister[], int registerSize, float denomination)
{
    // Loop through each denomination in the cash register
    for (int i = 0; i < registerSize; i++)
    {
        // Check if the current denomination matches the one to be updated
        if (cashRegister[i].cashDenomination == denomination)
        {
            cashRegister[i].amountLeft++;  // Increment the count of this denomination
            return;                        // Exit the function once the denomination is found and
                                           // updated
        }
    }
}

/**
 * @brief Handles user input for inserting money into the vending machine.
 * @param userMoney Pointer to the total amount of money the user has inserted.
 * @param cashRegister The array of cash register denominations.
 * @param registerSize The number of denominations in the cash register.
 */
void userMoneyInput(float *userMoney, CashRegister cashRegister[], int registerSize)
{
    float moneyInserted;  // Variable to store the user's inserted amount

    // Display available denominations to the user
    printf(
        "Insert money into the vending machine.\n"
        "Allowed Denominations:\n"
        "Bills: 20, 50, 100, 200, 500 (PHP)\n"
        "Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");
    while (1)  // Infinite loop for user input
    {
        // Prompt user for cash denomination input
        printf("\nEnter the cash denomination (0 when done): ");

        // Validate input for numeric value
        if (scanf("%f", &moneyInserted) != 1)
        {
            // Clear invalid input from buffer
            while (getchar() != '\n');
            printf("Invalid input! Please enter a numeric value.\n");
            continue;  // Continue to the next iteration of the loop
        }

        // Exit loop if user inputs 0
        if (moneyInserted == 0) break;

        // Check if the inserted denomination is valid
        if (isValidDenomination(moneyInserted))
        {
            *userMoney += moneyInserted;  // Add the valid denomination to user's total
            printf("You inserted: %.2f PHP\nTotal so far: %.2f PHP\n", moneyInserted, *userMoney);

            // Update the cash register with the inserted denomination
            updateCashRegister(cashRegister, registerSize, moneyInserted);
        }
        else  // Handle invalid denominations
        {
            printf(INVALID_DENOM_MSG "\n");
        }
    }

    // Display the total money inserted after exiting the loop
    printf("Total money inserted: %.2f PHP\n" SEPARATOR "\n", *userMoney);
}

/**
 * @brief Allows the user to select items from the vending machine menu.
 * @param items Array of available vending items.
 * @param menuSize The total number of items in the menu.
 * @param selection Pointer to a UserSelection structure that tracks the
 * selected items.
 */
void selectItems(VendingItem items[], int menuSize, UserSelection *selection)
{
    int done = 0;  // Flag to track when the user is finished selecting items

    while (!done)  // Loop until the user finalizes their selection
    {
        int selectionIndex;  // Variable to store the user's item selection
        printf("\nEnter item number to order (1-%d).\nEnter 0 when done: ", menuSize);

        // Validate input for item number
        if (scanf("%d", &selectionIndex) != 1)
        {
            printf("Invalid input! Please enter a number between 0 and %d.\n", menuSize);
            while (getchar() != '\n');  // Clear invalid input from buffer
            continue;                   // Continue to the next iteration of the loop
        }

        // Check if the user wants to finalize their order
        if (selectionIndex == 0)
        {
            // Ensure at least one item has been selected
            if (selection->count > 0)
            {
                done = 1;  // Set done to true to exit the loop
            }
            else
            {
                printf(
                    "You must select at least one item before finalizing your "
                    "order.\n");
            }
        }
        // Check if the selection index is valid
        else if (selectionIndex >= 1 && selectionIndex <= menuSize)
        {
            processSelection(items, selectionIndex - 1,
                             selection);  // Process the selected item
        }
        else
        {
            printf("Invalid item number! Please try again.\n");  // Handle invalid
                                                                 // item numbers
        }
    }

    printSelectedItems(selection);  // Print the user's selected items after finalization
}

/**
 * @brief Processes the user's selection of a vending item.
 * @param items Array of available vending items.
 * @param index The index of the selected item in the items array.
 * @param selection Pointer to a UserSelection structure that tracks the user's
 * selected items.
 */
void processSelection(VendingItem items[], int index, UserSelection *selection)
{
    VendingItem *selectedItem = &items[index];  // Pointer to the selected item

    // Check if the selected item is in stock
    if (selectedItem->stock > 0)
    {
        // Update the user's selection with the selected item
        updateSelectedItems(selection, selectedItem);

        selectedItem->stock--;  // Decrease the stock count for the selected item

        // Display the selection and current total cost
        printf("You have selected: %s, which costs %.2f PHP\n", selectedItem->name,
               selectedItem->price);
        printf("Current total cost is %.2f PHP\n", selection->totalItemCost);
    }
    else
    {
        // Inform the user that the selected item is out of stock
        printf("Sorry, %s is currently out of stock!\n", selectedItem->name);
    }
}

/**
 * @brief Updates the user's selection with the selected vending item.
 * @param selection Pointer to a UserSelection structure that tracks the user's
 * selected items.
 * @param selectedItem Pointer to the VendingItem that the user has selected.
 */
void updateSelectedItems(UserSelection *selection, VendingItem *selectedItem)
{
    int existingIndex = -1;  // Initialize the index for tracking existing items

    // Check if the selected item is already in the user's selection
    for (int i = 0; i < selection->count; i++)
    {
        if (strcmp(selection->selectedItems[i], selectedItem->name) == 0)
        {
            existingIndex = i;  // Update existingIndex if item is found
            break;
        }
    }

    // Update the selection based on whether the item is already selected
    if (existingIndex != -1)
    {
        // Increment quantity and update subtotal for the existing item
        selection->quantities[existingIndex]++;
        selection->subTotals[existingIndex] += selectedItem->price;
    }
    else
    {
        // Add the new item to the selection
        strcpy(selection->selectedItems[selection->count], selectedItem->name);
        selection->quantities[selection->count] = 1;                   // Initialize quantity to 1
        selection->subTotals[selection->count] = selectedItem->price;  // Set subtotal
        selection->count++;  // Increment the count of selected items
    }

    // Update the total cost of the selected items
    selection->totalItemCost += selectedItem->price;
}

/**
 * @brief Prints the user's selected items along with their quantities and total
 * costs.
 * @param selection Pointer to a UserSelection structure containing details of
 * the selected items.
 */
void printSelectedItems(UserSelection *selection)
{
    printf("\n\nYou have selected:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    // Check if there are any selected items
    if (selection->count > 0)
    {
        // Loop through and print details of each selected item
        for (int i = 0; i < selection->count; i++)
        {
            printf("%-15s | %-10d | %-10.2f\n", selection->selectedItems[i],
                   selection->quantities[i], selection->subTotals[i]);
        }
    }
    else
    {
        // Inform the user that no items have been selected
        printf("No items selected.\n");
    }

    printf(SEPARATOR "\n");  // Print separator for better visual distinction
}

/**
 * @brief Calculates and dispenses change based on the user's order confirmation
 * and total item cost.
 * @param cash Array of CashRegister structures representing the available
 * denominations and their counts.
 * @param userMoney Pointer to the total amount of money inserted by the user.
 * @param registerSize Size of the cash register array.
 * @param totalItemCost Pointer to the total cost of items selected by the user.
 * @param confirmation Pointer to an integer that will hold the user's
 * confirmation input.
 */
void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost,
               int *confirmation)
{
    // Prompt the user for order confirmation
    printf("Order Confirmation (1 - Confirm / 0 - Cancel Order): ");
    while (scanf("%d", confirmation) != 1)  // Ensure only integer input is accepted
    {
        while (getchar() != '\n')  // Clear invalid input from buffer
            ;
        printf("Invalid input! Please enter 1 to confirm or 0 to cancel: ");
    }

    float userChange;        // Variable to hold the calculated change
    if (*confirmation == 1)  // If the order is confirmed
    {
        userChange = *userMoney - *totalItemCost;  // Calculate the change to be returned
        printf("%-15s %-5.2f %-5s", "Final Total:", *totalItemCost, "PHP");
        printf("\n%-15s %-5.2f %-5s", "Money Input:", *userMoney, "PHP");
        printf("\n%-15s %-5.2f %-5s", "Change Total:", userChange, "PHP");
    }
    else  // If the order is canceled
    {
        userChange = *userMoney;  // User receives all money back
        printf("\n%-15s %-5.2f %-5s", "Money Input:", *userMoney, "PHP");
    }

    printf("\n" SEPARATOR);

    // Amount to dispense as change
    float amountToDispense = userChange;

    // Iterate through cash register denominations to dispense change
    for (int i = 0; i < registerSize && amountToDispense >= 0.05; i++)
    {
        // While loop to dispense the denomination as many times as possible
        while (amountToDispense >= cash[i].cashDenomination && cash[i].amountLeft > 0)
        {
            amountToDispense -= cash[i].cashDenomination;  // Deduct denomination from remaining
                                                           // amount
            cash[i].amountLeft--;  // Decrement the count of this denomination
                                   // in the cash register

            printf("\n%-15s %-5.2f %-5s", "Dispensed", cash[i].cashDenomination, "PHP");

            // Check if the remaining amount to dispense is too small for more
            // of this denomination
            if (amountToDispense < 0.05)
            {
                break;  // Exit while loop if the remaining amount is too low
            }
        }
    }

    printf("\n" SEPARATOR);

    // Check if exact change was dispensed or if any remains
    if (amountToDispense > 0.05)
        printf("\nUnable to dispense exact change. Remaining amount: %.2f\n", amountToDispense);
    else
        printf("\nChange successfully dispensed.\n");
}

/**
 * @brief Displays the order summary for selected items and instructs the user
 * to retrieve the silog.
 * @param selection Pointer to a UserSelection structure
 */
void getSilog(UserSelection *selection)
{
    // Display the order summary header
    printf("\n\nOrder Summary:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    // Check if any items have been selected
    if (selection->count > 0)
    {
        // Loop through selected items to display their details
        for (int i = 0; i < selection->count; i++)
        {
            printf("%-15s | %-10d | %-10.2f\n", selection->selectedItems[i],
                   selection->quantities[i], selection->subTotals[i]);
        }
        printf(SEPARATOR "\n");
        printf("Total Order Cost: %.2f PHP\n", selection->totalItemCost);
    }
    else
    {
        // Notify user if no items have been selected
        printf("No items selected.\n");
    }

    printf(SEPARATOR "\n");
    // Instruction for the user to retrieve the silog
    printf("Get silog from tray bin.\n");
}
