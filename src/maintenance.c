#include "maintenance.h"

#include <math.h>

#include "constants.h"
#include "data_structures.h"


/**
 * @brief Validates the maintenance password input from the user.
 * @param maintenancePassword Pointer to the stored maintenance password.
 * @return int 1 if the password is correct, 0 otherwise.
 */
int maintenanceValidation(int *maintenancePassword)
{
    // Declare variables
    int passwordInput;
    int isValid;

    // Initialize variables
    isValid = 0;  // Default to invalid (0)

    // Prompt the user for the maintenance password
    printf("\nInput maintenance password: ");

    // Check if input is valid
    if (scanf("%d", &passwordInput) != 1)
    {
        printf("Invalid input. Please enter a numerical password.\n");
    }
    else
    {
        // Compare the entered password with the stored password
        if (passwordInput == *maintenancePassword)
        {
            // Access granted
            printf("Access Granted\n");
            isValid = 1;  // Set isValid to 1 if password is correct
        }
        else
        {
            // Incorrect password
            printf("Incorrect password, please try again.\n");
        }
    }

    // Return the result of the password validation
    return isValid;
}

/**
 * @brief Displays the list of vending items with their details.
 * @param items An array of VendingItem structures containing item details.
 * @param menuSize The total number of items in the array.
 */

void viewInventory(VendingItem items[], int menuSize)
{
    int i;
    // Print header for the item details table
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)",
           "Stock Left");
    printf(SEPARATOR "\n");

    // Loop through the items array to display each item's details
    for (i = 0; i < menuSize; i++)
    {
        // Declare and initialize variables for item details
        int itemNumber = items[i].itemNumber;
        char *itemName = items[i].name;
        float itemPrice = items[i].price;
        int itemStock = items[i].stock;

        // Display item details
        printf("%-12d | %-15s | %-11.2f | %-3d",
               itemNumber,  // Item number
               itemName,    // Item name
               itemPrice,   // Item price
               itemStock    // Remaining stock
        );

        if (itemStock <= 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);  // Display out of stock message
        }
        printf("\n");  // Move to the next line after each item
    }

    // Print footer for the item details table
}

/**
 * @brief Modify the price of a specific item in the vending machine.
 * @param items     Array of VendingItem structures representing the menu items.
 * @param menuSize  Number of items in the vending machine menu.
 */
void modifyPrice(VendingItem items[], int menuSize)
{
    int modifyItemNumber;  // Variable for user input
    int itemFound;         // Flag for if item is found
    int result;            // For input validation result
    int retry;             // Flag to control retrying the process

    // Display the item list with item numbers, names, and prices
    printf("\n%-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Price (PHP)");
    printf(SEPARATOR "\n");

    int i;  // Declare loop variable for displaying items
    for (i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-10.2f\n", items[i].itemNumber, items[i].name, items[i].price);
    }
    printf(SEPARATOR "\n");

    retry = 1;  // Initialize retry flag to true

    while (retry)
    {
        // Prompt for item selection
        printf("Enter the item number to modify: ");
        result = scanf("%d", &modifyItemNumber);

        // Check if input is valid
        if (result != 1)
        {
            printf("Invalid input. Please enter a valid item number.\n");
            while (getchar() != '\n');  // Clear input buffer
            retry = 1;                  // Keep retrying until valid input
        }
        else
        {
            itemFound = 0;  // Reset flag before searching for item

            int j;  // Declare loop variable for searching item number
            for (j = 0; j < menuSize; j++)
            {
                if (items[j].itemNumber == modifyItemNumber)
                {
                    itemFound = 1;  // Mark item as found

                    // Declare and initialize the new price variable
                    float newPrice;
                    printf("Enter the new price: ");
                    result = scanf("%f", &newPrice);

                    // Validate the new price and apply if positive
                    if (result != 1 || newPrice <= 0)
                    {
                        printf("\nError: Please enter a positive number for the price.\n");
                        while (getchar() != '\n');  // Clear input buffer
                        retry = 1;                  // Retry on invalid price input
                    }
                    else
                    {
                        // Set the selected item's price to the new price
                        items[j].price = newPrice;
                        printf("Price updated successfully!\n");
                        retry = 0;  // Exit loop after successful price update
                    }
                }
            }

            // If no item was found, prompt user to retry
            if (itemFound == 0)
            {
                printf("Invalid Item Number! No item found with the entered number.\n");
                retry = 1;  // Retry on invalid item number
            }
        }
    }
}

/**
 * @brief Allows staff to restock items in the vending machine inventory.
 * @param items Array of VendingItem structures representing the inventory.
 * @param menuSize Number of items in the inventory.
 */
void restockInventory(VendingItem items[], int menuSize)
{
    int modifyItemNumber;  // Declare item number to modify
    int reStock;           // Declare restock quantity
    int isValid;           // Flag to check item validity
    int result;            // For input validation result
    int retry;             // Flag to control retrying
    int i;                 // Declare loop variable for displaying items
    int j;                 // Declare loop variable for searching item number

    // Display the inventory with stock levels
    printf("\n%-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Stock Left");
    printf(SEPARATOR "\n");

    for (i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-10d", items[i].itemNumber, items[i].name, items[i].stock);
        if (items[i].stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");

    retry = 1;  // Initialize retry flag to true

    while (retry)
    {
        // Prompt for item number
        printf("Input item number to modify: ");
        result = scanf("%d", &modifyItemNumber);

        // Check if input is valid
        if (result != 1)
        {
            printf("Invalid input. Please enter a valid item number.\n");
            while (getchar() != '\n');  // Clear input buffer
            retry = 1;                  // Keep retrying until valid input
        }
        else
        {
            isValid = 0;  // Reset validity flag before searching for the item

            for (j = 0; j < menuSize; j++)
            {
                if (items[j].itemNumber == modifyItemNumber)
                {
                    isValid = 1;  // Mark item as valid

                    // Prompt for stock to add
                    printf("Input stock to add: ");
                    result = scanf("%d", &reStock);

                    // Validate quantity input
                    if (result != 1 || reStock <= 0)
                    {
                        printf("\nYou must input a positive number for stock addition.\n");
                        while (getchar() != '\n');  // Clear input buffer
                        retry = 1;                  // Retry if quantity is invalid
                    }
                    else
                    {
                        // Update stock
                        items[j].stock += reStock;
                        printf("Stock updated successfully.\n");
                        retry = 0;  // Exit loop after successful update
                    }
                }
            }

            // If item number was invalid, ask to retry
            if (isValid == 0)
            {
                printf("Invalid Item Number! Please try again.\n");
                retry = 1;  // Retry on invalid item number
            }
        }
    }
}

/**
 * @brief Displays the contents of the cash register in a formatted manner.
 * @param cashRegister Array of CashRegister structures representing the cash register.
 * @param cashRegisterSize Number of denominations in the cash register.
 */
void viewCashRegister(CashRegister cashRegister[], int cashRegisterSize)
{
    float totalAmount;
    int i;
    totalAmount = 0.0;  // Initialize totalAmount

    // Print the header for the cash register table
    printf("\n%-12s | %-11s | %-12s |\n", "Denomination (PHP)", "Amount Left", "Total Value (PHP)");
    printf(SEPARATOR "\n");

    // Loop through each denomination in the register and print details
    for (i = 0; i < cashRegisterSize; i++)
    {
        float denominationTotal;
        denominationTotal = cashRegister[i].cashDenomination * cashRegister[i].amountLeft;

        totalAmount += denominationTotal;

        // Print each denomination, amount left, and total value of that denomination
        printf("| %-16.2f | %-12d | %-15.2f |\n", cashRegister[i].cashDenomination,
               cashRegister[i].amountLeft, denominationTotal);
    }

    printf(SEPARATOR "\n");

    // Print the total cash in the register
    printf("| %-30s PHP %-14.2f |\n", "Total Cash in Register:", totalAmount);
}

/**
 * @brief Allows the user to restock the cash register by adding quantities to valid denominations.
 * @param cashRegister Array of CashRegister structures representing the cash register.
 * @param cashRegisterSize Number of denominations in the cash register.
 */
void reStockRegister(CashRegister cashRegister[], int cashRegisterSize)
{
    float denomination;
    int quantity;
    int validDenomination = 0;  // Flag to check if the denomination is valid
    int scanResult;
    int i;
    int quantityScanResult;

    // Display the current cash register
    viewCashRegister(cashRegister, cashRegisterSize);

    // Loop until valid denomination and quantity are entered
    while (validDenomination == 0)
    {
        printf("\nEnter the denomination to restock: ");
        scanResult = scanf("%f", &denomination);

        if (scanResult != 1)
        {
            printf("Invalid input. Please enter a valid denomination.\n");
            // Clear the input buffer
            while (getchar() != '\n');
        }
        else
        {
            validDenomination = 0;  // Reset flag before searching for denomination

            // Search for the entered denomination in the cash register
            for (i = 0; i < cashRegisterSize; i++)
            {
                if (cashRegister[i].cashDenomination == denomination)
                {
                    validDenomination = 1;  // Denomination found

                    // Ask for the quantity to restock
                    printf("Enter the quantity to add (positive number only): ");
                    quantityScanResult = scanf("%d", &quantity);

                    // If quantity is not valid or not positive, prompt again
                    if (quantityScanResult != 1 || quantity <= 0)
                    {
                        printf(
                            "Invalid quantity. Restock quantity must be a positive number greater "
                            "than zero.\n");
                        while (getchar() != '\n');  // Clear input buffer
                        validDenomination = 0;      // Keep looping until valid quantity is entered
                    }
                    else
                    {
                        // Update the quantity in the cash register
                        cashRegister[i].amountLeft += quantity;
                        printf("Successfully added %d to %.2f PHP denomination.\n", quantity,
                               cashRegister[i].cashDenomination);
                    }
                }
            }

            // If the denomination is not found in the cash register
            if (validDenomination == 0)
            {
                printf(
                    "Invalid denomination. Please select a valid denomination from the "
                    "register.\n");
            }
        }
    }
}

void cashOut(CashRegister cashRegister[], int cashRegisterSize)
{
    int userOption;    // Variable to store user's choice
    int isValidInput;  // Flag for validating user input

    // Display cash-out options to the user
    printf(SEPARATOR
           "\nCash Out Options:\n"
           "1 - Cash Out by Amount\n"
           "2 - Cash Out by Denomination and Quantity\n"
           "0 - Cancel\n"
           "Enter your choice: ");

    userOption = -1;
    isValidInput = 0;  // Initialize input validation flag
    while (!isValidInput)
    {
        // Capture user input
        int scanResult;
        scanResult = scanf("%d", &userOption);

        if (scanResult != 1)
        {
            printf("Invalid input. Please enter a valid option (0, 1, or 2): ");
            while (getchar() != '\n');  // Clear invalid input from the buffer
        }
        else if (userOption < 0 || userOption > 2)
        {
            printf("Invalid option. Please enter 0, 1, or 2: ");
        }
        else
        {
            isValidInput = 1;  // Valid input received
        }
    }

    // Handle user choice
    if (userOption == 1)
    {
        handleAmountBasedCashOut(cashRegister, cashRegisterSize);
    }
    else if (userOption == 2)
    {
        handleQuantityBasedCashOut(cashRegister, cashRegisterSize);
    }
    else if (userOption == 0)
    {
        printf("Cash-out operation canceled.\n");
    }
}

/**
 * @brief Handles amount-based cash-out from the cash register.
 * @param cashRegister Array of CashRegister structures representing the cash register.
 * @param cashRegisterSize Number of denominations in the cash register.
 */
void handleAmountBasedCashOut(CashRegister cashRegister[], int cashRegisterSize)
{
    float amountToClaim;
    int scanResult;

    // Prompt the user for the amount they wish to claim
    printf("\nEnter the amount you wish to claim (in PHP): ");
    scanResult = scanf("%f", &amountToClaim);

    if (scanResult != 1 || amountToClaim <= 0)
    {
        printf("Invalid input or amount. Operation canceled.\n");
        return;  // Exit the function if the input is invalid or amount is less than or equal to
                 // zero
    }

    // Convert the amount to claim to an integer (cents) for precise calculations
    int amountToClaimCents = (int) (round(amountToClaim * 100));  // Round to nearest cent

    int dispensed[cashRegisterSize];                // Track the number of denominations dispensed
    int remainingAmountCents = amountToClaimCents;  // Remaining amount to claim in cents
    int i, j;

    // Initialize dispensed denominations to 0
    for (i = 0; i < cashRegisterSize; i++)
    {
        dispensed[i] = 0;
    }

    // Attempt to dispense denominations starting from the highest denomination
    for (j = 0; j < cashRegisterSize; j++)
    {
        int cashDenominationCents =
            (int) (round(cashRegister[j].cashDenomination * 100));  // Convert denomination to cents

        // While there is still remaining amount and enough of that denomination
        while (remainingAmountCents >= cashDenominationCents && cashRegister[j].amountLeft > 0)
        {
            remainingAmountCents -=
                cashDenominationCents;     // Subtract the denomination from remaining amount
            cashRegister[j].amountLeft--;  // Reduce the amount of that denomination
            dispensed[j]++;                // Increase the count for this denomination
        }
    }

    // If the exact amount couldn't be dispensed, revert the changes
    if (remainingAmountCents > 0)
    {
        printf("\nUnable to dispense exact stated amount. Operation canceled.\n");

        // Restore quantities in the cash register
        for (int z = 0; z < cashRegisterSize; z++)
        {
            cashRegister[z].amountLeft += dispensed[z];
        }
    }
    else
    {
        // Print dispensed denominations
        printf("\nDispensed Denominations:\n");
        printf(SEPARATOR "\n");
        for (int x = 0; x < cashRegisterSize; x++)
        {
            if (dispensed[x] > 0)
            {
                printf("  %d x PhP%.2f\n", dispensed[x], cashRegister[x].cashDenomination);
            }
        }

        // Print the total amount dispensed
        printf(SEPARATOR "\n");
        printf("Transaction Completed. Amount Dispensed: PhP%.2f\n",
               amountToClaim);  // Output the original amount in pesos
    }
}

void handleQuantityBasedCashOut(CashRegister cashRegister[], int cashRegisterSize)
{
    float denomination;
    int quantity;
    int scanResult;
    int validDenomination = 0;
    int sufficientQuantity = 0;
    int i;

    // Prompt the user for the denomination
    printf("\nEnter the denomination you wish to claim: ");
    scanResult = scanf("%f", &denomination);

    if (scanResult != 1)
    {
        printf("Invalid input. Operation canceled.\n");
    }
    else
    {
        // Search for the denomination in the cash register
        i = 0;
        while (i < cashRegisterSize && validDenomination == 0)
        {
            if (cashRegister[i].cashDenomination == denomination)
            {
                validDenomination = 1;

                // Prompt the user for the quantity
                printf("Enter the quantity you wish to claim: ");
                scanResult = scanf("%d", &quantity);

                if (scanResult != 1 || quantity <= 0)
                {
                    printf("Invalid quantity. Operation canceled.\n");
                }
                else
                {
                    // Check if there is sufficient quantity in the cash register
                    if (quantity <= cashRegister[i].amountLeft)
                    {
                        sufficientQuantity = 1;
                        // Perform the cash out
                        cashRegister[i].amountLeft -= quantity;
                        printf("Successfully dispensed %d - PhP%.2f\n", quantity, denomination);
                        printf("Remaining quantity of PhP%.2f: %d\n", denomination,
                               cashRegister[i].amountLeft);
                    }
                    else
                    {
                        printf("Insufficient quantity for PhP%.2f. Only %d remaining.\n",
                               denomination, cashRegister[i].amountLeft);
                    }
                }
            }
            i++;
        }

        // If no valid denomination was found
        if (validDenomination == 0)
        {
            printf(
                "Invalid denomination. Please choose a valid denomination from the cash "
                "register.\n");
        }

        // If the denomination is valid but the quantity is insufficient
        if (validDenomination == 1 && sufficientQuantity == 0 && scanResult == 1 && quantity > 0)
        {
            printf("Operation canceled due to insufficient quantity.\n");
        }
    }
}
