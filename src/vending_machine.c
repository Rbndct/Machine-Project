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
    printf("\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)",
           "Stock Left");
    printf(SEPARATOR "\n");

    int i;
    // Loop through the items array to display each item's details
    for (i = 0; i < menuSize; i++)
    {
        // Declare and initialize the item details variables
        int itemNumber = items[i].itemNumber;
        char *itemName = items[i].name;
        float price = items[i].price;
        int stock = items[i].stock;

        // Display item details
        printf("%-12d | %-15s | %-11.2f | %-3d",
               itemNumber,  // Item number
               itemName,    // Item name
               price,       // Item price
               stock        // Remaining stock
        );

        // Check if the item is out of stock and display a message if true
        if (stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);  // Display out of stock message
        }

        // Move to the next line after each item
        printf("\n");
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
    int isValid;  // Declare variable to track validity of denomination
    isValid = 0;  // Initialize the flag to 0, assuming invalid by default

    int i;  // Declare loop counter outside the loop

    // Loop through all valid denominations to find a match
    for (i = 0; i < NUM_VALID_DENOMINATIONS; i++)
    {
        float currentDenomination;  // Declare variable to hold the current denomination value
        currentDenomination =
            VALID_DENOMINATIONS[i];  // Initialize with the current valid denomination

        // Check if the inserted money matches the current valid denomination
        if (moneyInserted == currentDenomination)
        {
            isValid = 1;  // Mark as valid if the denominations match
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
    int i;  // Declare loop counter outside the loop

    // Loop through each denomination in the cash register
    for (i = 0; i < registerSize; i++)
    {
        float currentDenomination;  // Declare variable for current denomination
        currentDenomination =
            cashRegister[i].cashDenomination;  // Initialize with the current denomination

        // Check if the current denomination matches the one to be updated
        if (currentDenomination == denomination)
        {
            int amountLeft;                           // Declare variable for amount left
            amountLeft = cashRegister[i].amountLeft;  // Initialize with the current amount left

            amountLeft++;  // Increment the count of this denomination
            cashRegister[i].amountLeft =
                amountLeft;  // Update the register with the incremented amount
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
        "Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n" SEPARATOR);

    moneyInserted = -1;         // Initialize moneyInserted with a default value of -1
    while (moneyInserted != 0)  // Loop until the user inputs 0
    {
        // Prompt user for cash denomination input
        printf("\nEnter the cash denomination (0 when done): ");

        int scanfResult;  // Declare a variable to store the result of scanf
        scanfResult = scanf("%f", &moneyInserted);  // Validate input for numeric value

        if (scanfResult != 1)
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
        else
        {
            int validDenomination;  // Declare variable to store the result of the validity check
            validDenomination =
                isValidDenomination(moneyInserted);  // Check if the denomination is valid

            if (validDenomination)
            {
                *userMoney += moneyInserted;  // Add the valid denomination to the user's total
                printf("You inserted: %.2f PHP\nTotal so far: %.2f PHP\n", moneyInserted,
                       *userMoney);

                // Update the cash register with the inserted denomination
                updateCashRegister(cashRegister, registerSize, moneyInserted);
            }
            else
            {
                // Handle invalid denominations
                printf(INVALID_DENOM_MSG "\n");
            }
        }
    }
}

/**
 * @brief Allows the user to select items from the vending machine menu.
 * @param items Array of available vending items.
 * @param menuSize The total number of items in the menu.
 * @param selection Pointer to a UserSelection structure that tracks the selected items.
 * @param userMoney Pointer to a float representing the total money inserted by the user.
 */
void selectItems(VendingItem items[], int menuSize, UserSelection *selection, float *userMoney,
                 CashRegister cashRegister[], int cashRegisterSize)
{
    // Add default items (rice and egg) if not already selected
    if (selection->count == 0)  // If no items have been selected yet
    {
        int eggIndex = -1;   // Variable for egg index in the items array
        int riceIndex = -1;  // Variable for rice index in the items array
        int i;
        // Find the indexes of egg and rice
        for (i = 0; i < menuSize; i++)  // Iterate through the items array to find default items
        {
            // Compare the name of the current item with "Egg"
            // strcmp returns 0 if the strings are equal
            if (strcmp(items[i].name, "Egg") == 0)
            {
                eggIndex = i;  // Store the index of the "Egg" item
            }
            // Compare the name of the current item with "Rice"
            // strcmp returns 0 if the strings are equal
            else if (strcmp(items[i].name, "Rice") == 0)
            {
                riceIndex = i;  // Store the index of the "Rice" item
            }
        }

        // Automatically add 1 egg and 1 rice to the selection
        if (eggIndex != -1 && riceIndex != -1)  // Ensure both are available
        {
            printf("\nYour meal includes 1 Egg and 1 Rice by default.\n");
            processSelection(items, eggIndex, selection, userMoney, cashRegister, cashRegisterSize);
            processSelection(items, riceIndex, selection, userMoney, cashRegister,
                             cashRegisterSize);
        }
        else
        {
            printf("Error: Default items (Egg and/or Rice) are missing from inventory.\n");
        }
    }

    int done = 0;  // Initialize done to 0 (false)

    while (!done)  // Loop until the user finalizes their selection
    {
        int selectionIndex;  // Declare variable to store the user's item selection

        printf("\nEnter item number to order (1-%d).\nEnter 0 when done: ", menuSize);

        int scanfResult;  // Declare variable to store the result of scanf
        scanfResult = scanf("%d", &selectionIndex);  // Validate input for item number

        if (scanfResult != 1)
        {
            printf("Invalid input! Please enter a number between 0 and %d.\n", menuSize);
            while (getchar() != '\n');  // Clear invalid input from buffer
        }

        if (selectionIndex == 0)
        {
            if (selection->count > 0)
            {
                done = 1;  // Exit loop
            }
            else
            {
                printf("You must select at least one item before finalizing your order.\n");
            }
        }
        else if (selectionIndex >= 1 && selectionIndex <= menuSize)
        {
            processSelection(items, selectionIndex - 1, selection, userMoney, cashRegister,
                             cashRegisterSize);
        }
        else
        {
            printf("Invalid item number! Please try again.\n");
        }
    }

    printSelectedItems(selection);  // Print the user's selected items after finalization
}

/**
 * @brief Processes the user's selection of a vending item.
 * @param items Array of available vending items.
 * @param index The index of the selected item in the items array.
 * @param selection Pointer to a UserSelection structure that tracks the user's selected items.
 * @param userMoney Pointer to a float representing the total money inserted by the user.
 * @param cashRegister The array of cash register denominations.
 * @param registerSize The number of denominations in the cash register.
 */
void processSelection(VendingItem items[], int index, UserSelection *selection, float *userMoney,
                      CashRegister cashRegister[], int registerSize)
{
    int hasStock;  // Declare variable to check stock availability

    VendingItem *selectedItem;     // Declare pointer to the selected item
    selectedItem = &items[index];  // Initialize pointer to point to the selected item

    hasStock = (selectedItem->stock > 0);  // Check if the selected item is in stock
    if (hasStock)                          // If the item is in stock
    {
        float totalCost;     // Declare variable to store the total cost for selection
        int hasEnoughMoney;  // Declare variable to check if the user has enough money

        totalCost = selection->totalItemCost + selectedItem->price;  // Calculate the total cost
        hasEnoughMoney = (*userMoney >= totalCost);  // Check if the user has enough money

        if (hasEnoughMoney)  // If the user has enough money
        {
            updateSelectedItems(selection, selectedItem);  // Update the selection with the item
            selectedItem->stock--;  // Decrease the stock of the selected item

            // Display the selection and current total cost
            printf("You have selected: %s, which costs %.2f PHP\n", selectedItem->name,
                   selectedItem->price);
            printf("Current total cost is %.2f PHP\n", selection->totalItemCost);
        }
        else  // If the user does not have enough money
        {
            float moneyRequired;  // Declare variable to store how much more money is required
            int userChoice;       // Declare variable to store user's choice
            int scanfResult;      // Declare variable to store the result of scanf

            moneyRequired = totalCost - *userMoney;  // Calculate the money required

            // Notify the user of insufficient funds and provide options
            printf("\nInsufficient funds! You need %.2f PHP more to add '%s'.\n", moneyRequired,
                   selectedItem->name);
            printf("Would you like to: \n1. Insert more money\n2. Cancel the selection\n");

            userChoice = 0;                          // Initialize choice to 0
            scanfResult = scanf("%d", &userChoice);  // Validate user input

            while (scanfResult != 1 || (userChoice != 1 && userChoice != 2))
            {
                while (getchar() != '\n');  // Clear invalid input
                printf("Invalid input! Please enter 1 to insert more money or 2 to cancel: ");
                scanfResult = scanf("%d", &userChoice);  // Re-check user input
            }

            if (userChoice == 1)  // If the user chooses to insert more money
            {
                userMoneyInput(userMoney, cashRegister, registerSize);  // Call money input function

                // Re-process the selection
                processSelection(items, index, selection, userMoney, cashRegister, registerSize);
            }
            else if (userChoice == 2)  // If the user chooses to cancel the selection
            {
                printf("'%s' was not added to your selection.\n", selectedItem->name);
            }
        }
    }
    else  // If the item is out of stock
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
    int existingIndex;   // Declare variable to track if the item is already selected
    int i;               // Declare index variable for the loop
    int isItemExisting;  // Declare variable to check if the item exists in the selection

    existingIndex = -1;  // Initialize the index for tracking existing items

    // Check if the selected item is already in the user's selection
    for (i = 0; i < selection->count; i++)
    {
        int comparisonResult;  // Declare a variable to store the result of the string comparison
        comparisonResult =
            strcmp(selection->selectedItems[i], selectedItem->name);  // Compare the item name

        if (comparisonResult == 0)  // If the item is found
        {
            existingIndex = i;  // Update existingIndex if item is found
        }
    }

    isItemExisting = (existingIndex != -1);  // Check if the item already exists in the selection

    if (isItemExisting)  // If the item is already selected
    {
        // Increment quantity and update subtotal for the existing item
        selection->quantities[existingIndex]++;                      // Increment quantity
        selection->subTotals[existingIndex] += selectedItem->price;  // Update subtotal
    }
    else  // If the item is not already selected
    {
        // Add the new item to the selection
        strcpy(selection->selectedItems[selection->count], selectedItem->name);  // Copy item name
        selection->quantities[selection->count] = 1;                   // Initialize quantity to 1
        selection->subTotals[selection->count] = selectedItem->price;  // Set subtotal
        selection->count++;  // Increment the count of selected items
    }

    // Update the total cost of the selected items
    selection->totalItemCost += selectedItem->price;  // Add selected item's price to total cost
}

/**
 * @brief Prints the user's selected items along with their quantities and total
 * costs.
 * @param selection Pointer to a UserSelection structure containing details of
 * the selected items.
 */
void printSelectedItems(UserSelection *selection)
{
    int count;  // Declare variable to track the count of selected items

    printf("\nYou have selected:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    count = selection->count;  // Initialize the count variable with the number of selected items

    // Check if there are any selected items
    if (count > 0)
    {
        int i;  // Declare variable for the loop index
        // Loop through and print details of each selected item
        for (i = 0; i < count; i++)
        {
            char *itemName;                          // Declare variable to store item name
            itemName = selection->selectedItems[i];  // Get the item name

            int quantity;                         // Declare variable for item quantity
            quantity = selection->quantities[i];  // Get the item quantity

            float subtotal;                      // Declare variable for item subtotal
            subtotal = selection->subTotals[i];  // Get the item subtotal

            printf("%-15s | %-10d | %-10.2f\n", itemName, quantity, subtotal);
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

    // Declare variable for order confirmation input & user input
    int confirmationInput;
    int scanResult;
    float userChange;

    // Perform the scanf operation first
    scanResult = scanf("%d", &confirmationInput);

    // Loop if the input is not valid
    while (scanResult != 1)
    {
        // Clear invalid input from buffer
        while (getchar() != '\n');
        printf("Invalid input! Please enter 1 to confirm or 0 to cancel: ");

        // Perform the scanf operation again inside the loop
        scanResult = scanf("%d", &confirmationInput);
    }

    *confirmation = confirmationInput;  // Assign the validated input to confirmation pointer

    userChange = 0.0f;  // Declare variable to hold the calculated change
    // Order confirmation condition
    if (*confirmation == 1)  // Order confirmed
    {
        userChange = *userMoney - *totalItemCost;  // Calculate change
        // Print confirmation details
        printf("\n%-15s: %.2f PHP", "Final Total", *totalItemCost);
        printf("\n%-15s: %.2f PHP", "Money Input", *userMoney);
        printf("\n%-15s: %.2f PHP", "Change Total", userChange);
    }
    else  // Order canceled
    {
        userChange = *userMoney;  // Return all money
        printf("\n%-15s: %.2f PHP\n", "Money Refunded", userChange);
    }

    printf("\n" SEPARATOR);  // Print separator

    // Process change dispensing only if there is change to give
    if (userChange > 0)
    {
        dispenseChange(cash, registerSize, userChange);  // Dispense change
    }
    else
    {
        printf("\nNo change to dispense.\n");  // Inform if no change is needed
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
    int i = 0;  // Index for iterating over cash denominations

    printf("\nDispensing Change:\n");

    // Loop over the available denominations
    while (i < registerSize && amountToDispense >= 0.05f)
    {
        int dispensedCount = 0;

        // Dispense current denomination while possible
        while (amountToDispense >= cash[i].cashDenomination && cash[i].amountLeft > 0)
        {
            // Deduct the denomination from the amount to dispense
            amountToDispense -= cash[i].cashDenomination;
            cash[i].amountLeft--;
            dispensedCount++;

            // Round the amount to dispense to two decimal places to avoid floating point
            // imprecision (especially with small denominations like 0.05)
            amountToDispense = (float) ((int) (amountToDispense * 100 + 0.5)) / 100.0f;
        }

        // Display dispensed denominations if any
        if (dispensedCount > 0)
        {
            printf("%-15s: %.2f PHP x %d\n", "Dispensed", cash[i].cashDenomination, dispensedCount);
        }

        // Move to the next denomination
        i++;
    }
    printf(SEPARATOR);

    // Check if exact change was successfully dispensed
    if (amountToDispense >
        0.01f)  // If the remaining amount is above 0.01 PHP, we consider it an error.
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
    // Declare variable for the loop index
    int i;
    // Display the order summary header
    printf("\n\nOrder Summary:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    // Check if any items have been selected
    if (selection->count > 0)
    {
        // Loop through selected items to display their details
        for (i = 0; i < selection->count; i++)
        {
            // Display the item details
            printf("%-15s | %-10d | %-10.2f\n", selection->selectedItems[i],
                   selection->quantities[i], selection->subTotals[i]);
        }

        // Print the separator and the total order cost
        printf(SEPARATOR "\n");
        printf("Total Order Cost: %.2f PHP\n", selection->totalItemCost);
    }
    else
    {
        // Notify user if no items have been selected
        printf("No items selected.\n");
    }

    // Print final separator
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
    // Declare variables for the loop indices
    int i;
    int j;

    // Only cancel and return stock for items in the user's selection
    for (i = 0; i < userSelection->count; i++)
    {
        // Find the corresponding item in the menu and return stock only for canceled items
        for (j = 0; j < menuSize; j++)
        {
            // Compare item names
            int comparisonResult;
            comparisonResult = strcmp(availableItems[j].name, userSelection->selectedItems[i]);

            // If the item names match, return stock
            if (comparisonResult == 0)
            {
                availableItems[j].stock += userSelection->quantities[i];
            }
        }
    }

    // Reset the user's selection details
    userSelection->count = 0;
    userSelection->totalItemCost = 0.0f;

    // Reset the inserted money
    *insertedMoney = 0.0f;
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

    printf("Get Natsilog from Traybin\n");
}
