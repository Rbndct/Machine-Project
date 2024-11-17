#include "vending_machine.h"

#include "constants.h"
#include "data_structures.h"

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
    int isValid = 0;  // Flag to track if a valid denomination is found

    // Loop through all valid denominations to find a match
    for (int i = 0; i < NUM_VALID_DENOMINATIONS; i++)
    {
        // Check if the inserted money matches the current valid denomination
        if (moneyInserted == VALID_DENOMINATIONS[i])
        {
            isValid = 1;  // Mark as valid
        }
    }

    // Return the result after completing the loop
    return isValid;
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
    float moneyInserted = -1;  // Variable to store the user's inserted amount

    // Display available denominations to the user
    printf(
        "Insert money into the vending machine.\n"
        "Allowed Denominations:\n"
        "Bills: 20, 50, 100, 200, 500 (PHP)\n"
        "Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");

    while (moneyInserted != 0)  // Loop until the user inputs 0
    {
        // Prompt user for cash denomination input
        printf("\nEnter the cash denomination (0 when done): ");

        // Validate input for numeric value
        if (scanf("%f", &moneyInserted) != 1)
        {
            // Clear invalid input from buffer
            while (getchar() != '\n');
            printf("Invalid input! Please enter a numeric value.\n");
            moneyInserted = -1;  // Reset input to continue the loop
        }
        else if (moneyInserted == 0)
        {
            // User indicates they are done inserting money
            printf("Total money inserted: %.2f PHP\n" SEPARATOR "\n", *userMoney);
        }
        else if (isValidDenomination(moneyInserted))  // Check if the denomination is valid
        {
            *userMoney += moneyInserted;  // Add the valid denomination to the user's total
            printf("You inserted: %.2f PHP\nTotal so far: %.2f PHP\n", moneyInserted, *userMoney);

            // Update the cash register with the inserted denomination
            updateCashRegister(cashRegister, registerSize, moneyInserted);
        }
        else  // Handle invalid denominations
        {
            printf(INVALID_DENOM_MSG "\n");
        }
    }
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
    int done = 0;  // Variable to track when the user is finished selecting items

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
        selectedItem->stock--;

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
 * @brief Handles the change calculation and dispensing process
 * @param cash Array of CashRegister structures
 * @param userMoney Pointer to a float representing the total amount of money inserted by the user
 * @param registerSize Size of the cash register array
 * @param totalItemCost Pointer to a float representing the total cost of the items selected by the
 * user
 * @param confirmation Pointer to an integer indicating the user's choice
 */
void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost,
               int *confirmation)
{
    // Prompt the user for order confirmation
    printf("Order Confirmation (1 - Confirm / 0 - Cancel Order): ");
    while (scanf("%d", confirmation) != 1)  // Ensure only integer input is accepted
    {
        while (getchar() != '\n');  // Clear invalid input from buffer
        printf("Invalid input! Please enter 1 to confirm or 0 to cancel: ");
    }

    float userChange = 0.0f;  // Variable to hold the calculated change
    if (*confirmation == 1)   // Order confirmed
    {
        userChange = *userMoney - *totalItemCost;
        printf("\n%-15s: %.2f PHP", "Final Total", *totalItemCost);
        printf("\n%-15s: %.2f PHP", "Money Input", *userMoney);
        printf("\n%-15s: %.2f PHP\n", "Change Total", userChange);
    }
    else  // Order canceled
    {
        userChange = *userMoney;  // Return all money
        printf("\n%-15s: %.2f PHP\n", "Money Refunded", userChange);
    }

    printf("\n" SEPARATOR);

    // Process change dispensing only if there is change to give
    if (userChange > 0)
    {
        dispenseChange(cash, registerSize, userChange);
    }
    else
    {
        printf("\nNo change to dispense.\n");
    }
}

/**
 * @brief Dispenses the change using the cash register denominations
 * @param cash Array of CashRegister structures
 * @param registerSize Size of the cash register array
 * @param amountToDispense The total amount of change to dispense
 */
void dispenseChange(CashRegister cash[], int registerSize, float amountToDispense)
{
    printf("\nDispensing Change:\n");

    for (int i = 0; i < registerSize && amountToDispense >= 0.05f; i++)
    {
        int dispensedCount = 0;

        // Dispense current denomination while possible
        while (amountToDispense >= cash[i].cashDenomination && cash[i].amountLeft > 0)
        {
            amountToDispense -= cash[i].cashDenomination;
            cash[i].amountLeft--;
            dispensedCount++;
        }

        // Display dispensed denominations if any
        if (dispensedCount > 0)
        {
            printf("%-15s: %.2f PHP x %d\n", "Dispensed", cash[i].cashDenomination, dispensedCount);
        }
    }

    printf("\n" SEPARATOR);

    // Check if exact change was successfully dispensed
    if (amountToDispense > 0.05f)
    {
        printf("\nUnable to dispense exact change. Remaining amount: %.2f PHP\n", amountToDispense);
    }
    else
    {
        printf("\nChange successfully dispensed.\n");
    }
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
    // Print message to retrieve the silog
    printf("Get silog from tray bin.\n");
}
/**
 * @brief Resets the user's order and related data when the order is canceled
 * @param userSelection Pointer to a UserSelection structure
 * @param insertedMoney Pointer to the total amount of money inserted by the user
 * @param availableItems Array of VendingItem structures
 * @param menuSize Size of the vending machine item array
 */
void resetOrderAfterCancel(UserSelection *userSelection, float *insertedMoney,
                           VendingItem availableItems[], int menuSize)
{
    // Only cancel and return stock for items in the user's selection
    for (int i = 0; i < userSelection->count; i++)
    {
        // Find the corresponding item in the menu and return stock only for canceled items
        for (int j = 0; j < menuSize; j++)
        {
            if (strcmp(availableItems[j].name, userSelection->selectedItems[i]) == 0)
            {
                // Return stock for canceled items (only if it's canceled, not transacted)
                availableItems[j].stock += userSelection->quantities[i];
            }
        }
    }

    // Reset the user's selection details
    userSelection->count = 0;
    userSelection->totalItemCost = 0.0f;
    *insertedMoney = 0.0f;

    printf("\nOrder has been canceled and reset. Ready for a new transaction.\n");
}

/**
 * @brief Resets the user's order details after confirming the transaction.

 * @param userSelection Pointer to a UserSelection structure
 * @param insertedMoney Pointer to a float representing the total amount of money inserted by the
 user.
 */
void resetOrderAfterConfirm(UserSelection *userSelection, float *insertedMoney)
{
    // Reset the user's selection details after confirming the order
    userSelection->count = 0;
    userSelection->totalItemCost = 0.0f;
    *insertedMoney = 0.0f;

    printf("\nOrder has been completed and reset. Ready for a new transaction.\n");
}
