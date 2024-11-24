#include "vending_machine.h"

#include <math.h>

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
 * @pre The list of valid denominations should be properly defined before calling this function.
 */
int isValidDenomination(float moneyInserted)
{
    int isValid = 0;  // Flag to track validity, initialized to 0 (invalid by default)

    // Iterate through all valid denominations to find a match
    for (int i = 0; i < NUM_VALID_DENOMINATIONS; i++)
    {
        float currentDenomination = VALID_DENOMINATIONS[i];  // Get the current valid denomination

        // If a match is found, mark as valid
        if (moneyInserted == currentDenomination)
        {
            isValid = 1;  // Set the validity flag to 1
        }
    }
    return isValid;  // Return the validity status (1 or 0)
}

/**
 * @brief Updates the cash register by incrementing the count of a specific denomination.
 * @param cashRegister The array of CashRegister structures,
 * @param registerSize The number of denominations in the cashRegister array.
 * @param denomination The specific denomination whose count will be incremented.
 * @pre The cashRegister array must be properly initialized before calling this function.
 */
void updateCashRegister(CashRegister cashRegister[], int registerSize, float denomination)
{
    int i;  // Declare loop counter to iterate over cash denominations

    // Iterate through each denomination in the cash register
    for (i = 0; i < registerSize; i++)
    {
        float currentDenomination =
            cashRegister[i].cashDenomination;  // Get the current denomination value

        // Check if the current denomination matches the one to be updated
        if (currentDenomination == denomination)
        {
            int amountLeft =
                cashRegister[i].amountLeft;  // Retrieve the current count of the denomination

            amountLeft++;  // Increment the count of this specific denomination

            cashRegister[i].amountLeft = amountLeft;  // Update the register with the new count
        }
    }
}

/**
 * @brief Handles the process of inserting money into the vending machine.
 * @param userMoney A pointer to a float that stores the total amount of money the user input
 * @param cashRegister An array of CashRegister structures representing the available cash
 * @param registerSize The number of available denominations in the cash register.
 * @pre The cashRegister should be initialized with valid denominations before calling this
 * function.
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
    while (moneyInserted != 0)  // Loop until the user inputs 0 to stop
    {
        // Prompt user for cash denomination input
        printf("\nEnter the cash denomination (0 when done): ");

        int scanfResult;                            // Variable to store the result of scanf
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
            int validDenomination;  // Variable to store the result of the validity check
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
 * @param items Array of VendingItem structures, where each item represents a product available.
 * @param menuSize The total number of items in the menu.
 * @param selection Pointer to a UserSelection structure.
 * @param userMoney Pointer to a float representing the total amount of money the user has.
 * @param cashRegister The array of CashRegister structures.
 * @param cashRegisterSize The total number of cash denominations in the cashRegister array.
 * @pre The items array must be initialized with the available items, and the `selection`
 * structure should be properly initialized to track selected items.
 */
void selectItems(VendingItem items[], int menuSize, UserSelection *selection, float *userMoney,
                 CashRegister cashRegister[], int cashRegisterSize)
{
    // Add default items (rice and egg) if not already selected
    if (selection->count == 0)  // If no items have been selected yet
    {
        int eggIndex, riceIndex, i;  // Declare variables for item indexes and loop counter
        eggIndex = -1;               // Initialize to indicate "not found"
        riceIndex = -1;              // Initialize to indicate "not found"

        // Find the indexes of egg and rice in the menu
        for (i = 0; i < menuSize; i++)  // Iterate through the items array to find default items
        {
            if (strcmp(items[i].name, "Egg") == 0)
            {
                eggIndex = i;  // Store the index of the "Egg" item
            }
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

    int done;                    // Declare control variable for the loop
    int additionalItemSelected;  // Declare flag for additional item selection
    done = 0;                    // Initialize loop control variable
    additionalItemSelected = 0;  // Initialize flag to track if an additional item was selected

    while (!done)  // Loop until the user finalizes their selection
    {
        int selectionIndex, scanfResult;  // Declare variables for user input and validation result

        printf("\nEnter item number to order (1-%d).\nEnter 0 when done: ", menuSize);
        scanfResult = scanf("%d", &selectionIndex);  // Read user input and store validation result

        if (scanfResult != 1)  // Check if the input is not a valid integer
        {
            printf("Invalid input! Please enter a number between 0 and %d.\n", menuSize);
            while (getchar() != '\n');  // Clear invalid input from buffer
        }
        else  // If input is a valid integer, proceed
        {
            if (selectionIndex == 0)
            {
                if (additionalItemSelected)
                {
                    done = 1;  // Exit loop if at least one additional item was selected
                }
                else
                {
                    printf(
                        "You must select at least one add-on item before finalizing your order.\n");
                }
            }
            else if (selectionIndex >= 1 && selectionIndex <= menuSize)
            {
                processSelection(items, selectionIndex - 1, selection, userMoney, cashRegister,
                                 cashRegisterSize);
                additionalItemSelected = 1;  // Mark that an additional item has been selected
            }
            else
            {
                printf("Invalid item number! Please try again.\n");
            }
        }
    }

    printSelectedItems(selection);  // Print the user's selected items after finalization
}

/**
 * @brief Processes the user's selection of a vending item.
 * @param items Array of VendingItem structures representing the available items.
 * @param index The index of the selected item in the items array.
 * @param selection Pointer to a UserSelection structure.
 * @param userMoney Pointer to a float representing the total amount of money the user has.
 * @param cashRegister The array of CashRegister structures representing the available cash.
 * @param registerSize The total number of cash denominations in the cashRegister array.
 * @pre The items array must be initialized with the available items, and the selection
 * structure should be properly initialized to track the user's selections and total cost.
 */
void processSelection(VendingItem items[], int index, UserSelection *selection, float *userMoney,
                      CashRegister cashRegister[], int registerSize)
{
    int hasStock;  // Variable to check if the selected item is in stock

    VendingItem *selectedItem = &items[index];  // Pointer to the selected item
    hasStock = (selectedItem->stock > 0);       // Check if the item is in stock

    if (hasStock)  // If the item is in stock
    {
        float totalCost;     // Variable to store the total cost of the current selection
        int hasEnoughMoney;  // Variable to check if the user has enough money

        totalCost = selection->totalItemCost +
                    selectedItem->price;  // Calculate total cost including selected item
        hasEnoughMoney =
            (*userMoney >=
             totalCost);  // Check if the user has enough money to complete the purchase

        if (hasEnoughMoney)  // If the user has enough money
        {
            updateSelectedItems(selection, selectedItem);  // Update the selection with the item
            selectedItem->stock--;  // Decrease the stock of the selected item

            // Display the selection and the current total cost
            printf("You have selected: %s, which costs %.2f PHP\n", selectedItem->name,
                   selectedItem->price);
            printf("Current total cost is %.2f PHP\n", selection->totalItemCost);
        }
        else  // If the user does not have enough money
        {
            float moneyRequired;  // Variable to store how much more money is needed
            int userChoice;       // Variable to store user's choice (insert more money or cancel)
            int scanfResult;      // Variable to store the result of scanf

            moneyRequired = totalCost - *userMoney;  // Calculate the additional amount needed

            // Notify the user about insufficient funds and provide options
            printf("\nInsufficient funds! You need %.2f PHP more to add '%s'.\n", moneyRequired,
                   selectedItem->name);
            printf("Would you like to: \n1. Insert more money\n2. Cancel the selection\n");

            userChoice = 0;                          // Initialize user choice
            scanfResult = scanf("%d", &userChoice);  // Validate user input

            // Loop until valid input is provided
            while (scanfResult != 1 || (userChoice != 1 && userChoice != 2))
            {
                while (getchar() != '\n');  // Clear invalid input from buffer
                printf("Invalid input! Please enter 1 to insert more money or 2 to cancel: ");
                scanfResult = scanf("%d", &userChoice);  // Re-check user input
            }

            if (userChoice == 1)  // If the user chooses to insert more money
            {
                userMoneyInput(userMoney, cashRegister,
                               registerSize);  // Call function to input more money

                // Re-process the selection after money is inserted
                processSelection(items, index, selection, userMoney, cashRegister, registerSize);
            }
            else if (userChoice == 2)  // If the user chooses to cancel the selection
            {
                printf("'%s' was not added to your selection.\n", selectedItem->name);
            }
        }
    }
    else  // If the selected item is out of stock
    {
        // Inform the user that the item is out of stock
        printf("Sorry, %s is currently out of stock!\n", selectedItem->name);
    }
}

/**
 * @brief Updates the user's selection with the selected vending item.
 * @param selection Pointer to a UserSelection structure
 * @param selectedItem Pointer to the VendingItem that the user has selected.
 * @pre The selection structure should be initialized.
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
        int comparisonResult;  // Variable to store the result of the string comparison
        comparisonResult =
            strcmp(selection->selectedItems[i], selectedItem->name);  // Compare item names

        if (comparisonResult == 0)  // If the item is found in the selection
        {
            existingIndex = i;  // Store the index of the existing item
        }
    }

    isItemExisting = (existingIndex != -1);  // Determine if the item is already in the selection

    if (isItemExisting)  // If the item is already selected
    {
        // Increment quantity and update the subtotal for the existing item
        selection->quantities[existingIndex]++;  // Increase quantity
        selection->subTotals[existingIndex] +=
            selectedItem->price;  // Update subtotal with item price
    }
    else  // If the item is not already selected
    {
        // Add the new item to the selection at the next available index
        strcpy(selection->selectedItems[selection->count], selectedItem->name);  // Copy item name
        selection->quantities[selection->count] = 1;                   // Initialize quantity to 1
        selection->subTotals[selection->count] = selectedItem->price;  // Set subtotal for the item
        selection->count++;  // Increment the count of selected items
    }

    // Update the total cost of all selected items
    selection->totalItemCost +=
        selectedItem->price;  // Add the price of the selected item to the total cost
}

/**
 * @brief Prints the user's selected items along with their quantities and total costs.
 * @param selection Pointer to a UserSelection structure that contains the user's selection.
 * @pre The selection structure should be properly populated.
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

            // Print item details in table format
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
 * @brief Handles the change calculation and dispensing process.
 * @param cash Array of CashRegister structures representing the available cash denominations.
 * @param userMoney Pointer to a float representing the total amount of money inserted by the user.
 * @param registerSize Size of the cash register array.
 * @param totalItemCost Pointer to a float representing the total cost of the items selected.
 * @param confirmation Pointer to an integer: 1 for confirming the order, 0 for canceling.
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
 * @brief Dispenses the change using the available cash register denominations.
 * @param cash Array of CashRegister structure.
 * @param registerSize The number of denominations available in the cash register array.
 * @param amountToDispense The total amount of change that needs to be returned to the user.
 * @pre The amountToDispense should be a positive value representing the change to be returned.
 */
void dispenseChange(CashRegister cash[], int registerSize, float amountToDispense)
{
    int i = 0;  // Index for iterating over cash denominations

    printf("\nDispensing Change:\n");

    // Loop over the available denominations
    while (i < registerSize && amountToDispense >= 0.05f)
    {
        int dispensedCount = 0;  // Counter for the number of times a denomination is dispensed

        // Dispense current denomination while possible
        while (amountToDispense >= cash[i].cashDenomination && cash[i].amountLeft > 0)
        {
            // Deduct the denomination from the amount to dispense
            amountToDispense -= cash[i].cashDenomination;
            cash[i].amountLeft--;  // Reduce the available stock of this denomination
            dispensedCount++;      // Increment the count of dispensed notes/coins

            // Round the amount to dispense to two decimal places.
            amountToDispense = roundf(amountToDispense * 100) / 100.0f;
        }

        // Display the denomination dispensed, if any
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
        0.01f)  // If the remaining amount is above 0.01 PHP, consider it an error
    {
        printf("\nUnable to dispense exact change. Remaining amount: %.2f PHP\n", amountToDispense);
    }
    else
    {
        printf("\nChange successfully dispensed.\n");
    }
}

/**
 * @brief Displays the order summary and instructs the user to retrieve the silog.
 * @param selection Pointer to a UserSelection structure containing the details of the
 *                  user's selected items, quantities, and subtotals.
 * @pre The selection structure must be populated with valid user selections, including
 *      item names, quantities, and subtotals.
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
            // Display the item details: name, quantity, and subtotal
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

    printf(SEPARATOR "\n");

    // Print message to retrieve the silog from the tray bin
    printf("Get silog from tray bin.\n");
}

/**
 * @brief Resets the user's order and related data when the order is canceled.
 * @param userSelection Pointer to a UserSelection structure containing the user's current order.
 * @param insertedMoney Pointer to a float representing the total amount of money inserted.
 * @param availableItems Array of VendingItem structures representing the available items.
 * @param menuSize The number of items in the vending machine (size of the `availableItems` array).
 * @pre The userSelection structure must contain valid data, including selected items, quantities,
 *      and total cost.
 */
void resetOrderAfterCancel(UserSelection *userSelection, float *insertedMoney,
                           VendingItem availableItems[], int menuSize)
{
    // Declare variables for loop indices
    int i;
    int j;

    // Loop through the user's selection to return stock for each item
    for (i = 0; i < userSelection->count; i++)
    {
        // Search for the corresponding item in the available items menu
        for (j = 0; j < menuSize; j++)
        {
            int comparisonResult;
            // Compare the item name from the user's selection with the available items
            comparisonResult = strcmp(availableItems[j].name, userSelection->selectedItems[i]);

            // If the item names match, return stock to the available items
            if (comparisonResult == 0)
            {
                availableItems[j].stock += userSelection->quantities[i];  // Restore the stock
            }
        }
    }

    // Reset the user's order details
    userSelection->count = 0;             // Reset the number of selected items
    userSelection->totalItemCost = 0.0f;  // Reset the total cost of the order

    // Reset the inserted money
    *insertedMoney = 0.0f;  // Set the inserted money to zero
}

/**
 * @brief Resets the user's order details after confirming the transaction.
 * @param userSelection Pointer to a UserSelection structure containing the user's selected items.
 * @param insertedMoney Pointer to a float representing the total amount of money inserted.
 * @pre The userSelection structure must contain valid data, including selected items, quantities,
 *      and total cost.
 */
void resetOrderAfterConfirm(UserSelection *userSelection, float *insertedMoney)
{
    // Reset the user's order details after confirming the transaction
    userSelection->count = 0;             // Clear the count of selected items
    userSelection->totalItemCost = 0.0f;  // Reset the total cost to zero
    *insertedMoney = 0.0f;                // Set the inserted money to zero

    // Print the message instructing the user to retrieve their silog
    printf("Get Natsilog from Traybin\n");
}
