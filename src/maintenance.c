#include "maintenance.h"

#include <math.h>

#include "constants.h"
#include "data_structures.h"

/**
 * @brief Validates the maintenance password input from the user.
 * @param maintenancePassword Pointer to the stored maintenance password to compare against.
 * @return int Returns 1 if the entered password matches the stored password,
 *             and 0 if it does not match or if the input is invalid.
 */
int maintenanceValidation(int *maintenancePassword)
{
    // Declare variables
    int passwordInput;  // To store the user input for password
    int isValid = 0;    // Default value: invalid password (0)
    int scanfResult;

    // Prompt the user to input the maintenance password
    printf("\nInput maintenance password: ");

    // Check if the input is a valid integer
    scanfResult = scanf("%d", &passwordInput);
    if (scanfResult != 1)
    {
        // If the input is not a valid
        printf("Invalid input. Please enter a numerical password.\n");
        while (getchar() != '\n');  // Clear the input buffer to ensure clean input
    }
    else
    {
        // Compare the entered password with the stored password
        if (passwordInput == *maintenancePassword)
        {
            // Access granted if the password is correct
            printf("Access Granted\n");
            isValid = 1;  // Set isValid to 1 (valid password)
        }
        else
        {
            // Notify the user if the password is incorrect
            printf("Incorrect password, please try again.\n");
        }
    }

    // Return the result of the password validation (1 for valid, 0 for invalid)
    return isValid;
}

/**
 * @brief Displays the list of vending items with their details.
 * @param items An array of VendingItem structures containing item details.
 * @param menuSize The total number of items in the items array.
 * @pre The items array should be populated with valid `VendingItem` structures.
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
        int itemNumber = items[i].itemNumber;  // Item number
        char *itemName = items[i].name;        // Item name
        float itemPrice = items[i].price;      // Item price
        int itemStock = items[i].stock;        // Item stock

        // Display item details in a formatted table
        printf("%-12d | %-15s | %-11.2f | %-3d", itemNumber, itemName, itemPrice, itemStock);

        // Check if the item is out of stock and print an out-of-stock message if applicable
        if (itemStock <= 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);  // Display "Out of Stock" message
        }

        // Move to the next line after displaying an item's details
        printf("\n");
    }

    // Print footer for the item details table
    printf(SEPARATOR "\n");
}

/**
 * @brief Modifies the price of a specific item in the vending machine menu.
 * @param items Array of VendingItem structures representing the vending machine menu items.
 * @param menuSize The total number of items in the vending machine menu.
 * @pre The items array must be populated with valid VendingItem structures.
 */
void modifyPrice(VendingItem items[], int menuSize)
{
    int modifyItemNumber;  // Variable to store the user input for item number
    int itemFound;         // Flag indicating if the item is found in the menu
    int result;            // Result of input validation (scanf return value)
    int retry;             // Flag to control the retry process

    // Display the list of menu items with item numbers, names, and current prices
    printf("\n%-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Price (PHP)");
    printf(SEPARATOR "\n");

    // Display all items in the vending machine
    for (int i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-10.2f\n", items[i].itemNumber, items[i].name, items[i].price);
    }
    printf(SEPARATOR "\n");

    retry = 1;  // Initialize the retry flag to allow the user to try again

    while (retry)
    {
        // Prompt the user to enter the item number they wish to modify
        printf("Enter the item number to modify: ");
        result = scanf("%d", &modifyItemNumber);

        // Validate the input for item number
        if (result != 1)
        {
            printf("Invalid input. Please enter a valid item number.\n");
            while (getchar() != '\n');  // Clear the input buffer to ensure clean input
            retry = 1;                  // Keep retrying until valid input
        }
        else
        {
            itemFound = 0;  // Reset item found flag before searching

            // Search for the item in the menu based on item number
            for (int j = 0; j < menuSize; j++)
            {
                if (items[j].itemNumber == modifyItemNumber)
                {
                    itemFound = 1;  // Mark the item as found

                    // Prompt the user to enter a new price
                    float newPrice;
                    printf("Enter the new price: ");
                    result = scanf("%f", &newPrice);

                    // Validate the new price input
                    if (result != 1 || newPrice <= 0)
                    {
                        printf("\nError: Please enter a valid positive number for the price.\n");
                        while (getchar() != '\n');  // Clear input buffer on invalid price
                        retry = 1;                  // Retry on invalid price input
                    }
                    else
                    {
                        // Update the item's price with the new value
                        items[j].price = newPrice;
                        printf("Price updated successfully!\n");
                        retry = 0;  // Exit the loop after successful price update
                    }
                }
            }

            // If no item was found with the entered item number, prompt the user to retry
            if (itemFound == 0)
            {
                printf("Invalid Item Number! No item found with the entered number.\n");
                retry = 1;  // Retry if the item number is invalid
            }
        }
    }
}

/**
 * @brief Allows staff to restock items in the vending machine inventory.
 * @param items Array of `VendingItem` structures representing the inventory.
 * @param menuSize The total number of items in the vending machine inventory.
 * @pre The item` array should contain valid VendingItem structures.
 */
void restockInventory(VendingItem items[], int menuSize)
{
    int modifyItemNumber;  // Declare the item number to modify
    int reStock;           // Declare the quantity of stock to add
    int isValid;           // Flag to indicate if the item number is valid
    int result;            // For storing the result of input validation
    int retry;             // Flag to control the retry mechanism
    int i, j;              // Loop variables for displaying items and searching for item number

    // Display the inventory with item numbers, names, and current stock levels
    printf("\n%-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Stock Left");
    printf(SEPARATOR "\n");

    // Loop through the inventory and print each item's details
    for (i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-10d", items[i].itemNumber, items[i].name, items[i].stock);
        if (items[i].stock == 0)
        {
            // Indicate if the item is out of stock
            printf(" %-12s", OUT_OF_STOCK_MSG);
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");

    retry = 1;  // Initialize retry flag to allow the user to retry if input is invalid

    while (retry)
    {
        // Prompt for the item number to modify
        printf("Input item number to modify: ");
        result = scanf("%d", &modifyItemNumber);

        // Validate the input for the item number
        if (result != 1)
        {
            printf("Invalid input. Please enter a valid item number.\n");
            while (getchar() != '\n');  // Clear the input buffer to ensure clean input
            retry = 1;                  // Keep retrying until valid input is provided
        }
        else
        {
            isValid = 0;  // Reset validity flag before searching for the item

            // Search for the item based on the entered item number
            for (j = 0; j < menuSize; j++)
            {
                if (items[j].itemNumber == modifyItemNumber)
                {
                    isValid = 1;  // Mark the item as valid if it is found

                    // Prompt for the quantity of stock to add
                    printf("Input stock to add: ");
                    result = scanf("%d", &reStock);

                    // Validate the stock quantity input
                    if (result != 1 || reStock <= 0)
                    {
                        printf("\nYou must input a positive number for stock addition.\n");
                        while (getchar() != '\n');  // Clear the input buffer
                        retry = 1;                  // Retry if quantity input is invalid
                    }
                    else
                    {
                        // Update the item's stock with the added quantity
                        items[j].stock += reStock;
                        printf("Stock updated successfully.\n");
                        retry = 0;  // Exit loop after successful stock update
                    }
                }
            }

            // If the item number was invalid (not found), prompt the user to retry
            if (isValid == 0)
            {
                printf("Invalid Item Number! Please try again.\n");
                retry = 1;  // Retry on invalid item number
            }
        }
    }
}

/**
 * @brief Displays the contents of the cash register in a tabular format.
 * @param cashRegister Array of CashRegister structures.
 * @param cashRegisterSize Number of entries in the cashRegister array, corresponding to
 *                         the total number of different denominations stored.
 * @pre cashRegister must be a valid array of CashRegister structures.
 */
void viewCashRegister(CashRegister cashRegister[], int cashRegisterSize)
{
    float totalAmount = 0.0f;  // Initialize total cash amount to 0
    int i;                     // Loop variable for iterating through cash denominations

    // Print the header for the cash register table
    printf("\n%-20s | %-15s | %-15s |\n", "Denomination (PHP)", "Amount Left", "Total Value (PHP)");
    printf(SEPARATOR "\n");

    // Iterate through each denomination in the cash register
    for (i = 0; i < cashRegisterSize; i++)
    {
        float denominationTotal;  // Calculate total value for the current denomination

        // Calculate the total value for this denomination
        denominationTotal = cashRegister[i].cashDenomination * cashRegister[i].amountLeft;

        // Accumulate the total cash amount
        totalAmount += denominationTotal;

        // Print details for this denomination
        printf("| %-18.2f | %-13d | %-15.2f |\n",
               cashRegister[i].cashDenomination,  // Cash denomination value
               cashRegister[i].amountLeft,        // Amount of this denomination left
               denominationTotal);                // Total value for this denomination
    }

    printf(SEPARATOR "\n");

    // Display the total cash available in the register
    printf("| %-38s PHP %-14.2f |\n", "Total Cash in Register:", totalAmount);
}

/**
 * @brief Allows the user to restock the cash register by adding quantities to valid denominations.
 * @param cashRegister Array of CashRegister structures representing the current cash register.
 * @param cashRegisterSize Number of entries in the cashRegister array
 * @pre cashRegister must be a valid array of CashRegister, the cashDenomination values in each
 * structure must be unique and valid amounts.
 */
void reStockRegister(CashRegister cashRegister[], int cashRegisterSize)
{
    float denomination;         // Denomination to restock
    int quantity;               // Quantity to add to the denomination
    int validDenomination = 0;  // Flag to check if the entered denomination is valid
    int scanResult;             // Result of scanf for denomination
    int i;                      // Loop variable for searching through cash register
    int quantityScanResult;     // Result of scanf for quantity input

    // Display the current cash register contents
    viewCashRegister(cashRegister, cashRegisterSize);

    // Loop until a valid denomination and valid quantity are provided
    while (validDenomination == 0)
    {
        // Prompt the user to enter the denomination to restock
        printf("\nEnter the denomination to restock: ");
        scanResult = scanf("%f", &denomination);

        // Check if the input is a valid float
        if (scanResult != 1)
        {
            printf("Invalid input. Please enter a valid denomination.\n");
            while (getchar() != '\n');  // Clear the input buffer
        }
        else
        {
            validDenomination = 0;  // Reset the flag before searching for the denomination

            // Search for the entered denomination in the cash register
            for (i = 0; i < cashRegisterSize; i++)
            {
                if (cashRegister[i].cashDenomination == denomination)
                {
                    validDenomination = 1;  // Denomination found

                    // Prompt the user to enter the quantity to add
                    printf("Enter the quantity to add (positive number only): ");
                    quantityScanResult = scanf("%d", &quantity);

                    // Validate the quantity input
                    if (quantityScanResult != 1 || quantity <= 0)
                    {
                        printf(
                            "Invalid quantity. Please enter a positive number greater than "
                            "zero.\n");
                        while (getchar() != '\n');  // Clear the input buffer
                    }
                    else
                    {
                        // Update the cash register with the new quantity
                        cashRegister[i].amountLeft += quantity;
                        printf("Successfully added %d to %.2f PHP denomination.\n", quantity,
                               cashRegister[i].cashDenomination);
                    }
                }
                // If the denomination is not found in the cash register, display an error
            }
            if (validDenomination == 0)
            {
                printf(
                    "Invalid denomination. Please select a valid denomination from the "
                    "register.\n");
            }
        }
    }
}

/**
 * @brief Handles the cash-out operation from the vending machine's cash register.
 * @param cashRegister Array of CashRegister structures representing the current cash register.
 * @param cashRegisterSize Number of entries in the cashRegister array.
 * @pre cashRegister must be a valid array of CashRegister, the register must contain valid
 * denominations and quantities.
 */
void cashOut(CashRegister cashRegister[], int cashRegisterSize)
{
    int userOption;    // Stores the user's selected cash-out option
    int isValidInput;  // Flag to track input validity

    // Display cash-out options to the user
    printf(SEPARATOR
           "\nCash Out Options:\n"
           "1 - Cash Out by Amount\n"
           "2 - Cash Out by Denomination and Quantity\n"
           "0 - Cancel\n"
           "Enter your choice: ");

    userOption = -1;   // Initialize userOption to an invalid value
    isValidInput = 0;  // Initialize the input validation flag

    // Loop until valid input is provided
    while (!isValidInput)
    {
        int scanResult;  // Variable to store the result of input scanning
        scanResult = scanf("%d", &userOption);

        if (scanResult != 1)
        {
            // Handle invalid input (non-integer)
            printf("Invalid input. Please enter a valid option (0, 1, or 2): ");
            while (getchar() != '\n');  // Clear invalid input from the buffer
        }
        else if (userOption < 0 || userOption > 2)
        {
            // Handle out-of-range input
            printf("Invalid option. Please enter 0, 1, or 2: ");
        }
        else
        {
            isValidInput = 1;  // Mark input as valid
        }
    }

    // Process the user's choice
    if (userOption == 1)
    {
        // Call the function to handle amount-based cash-out
        handleAmountBasedCashOut(cashRegister, cashRegisterSize);
    }
    else if (userOption == 2)
    {
        // Call the function to handle cash-out by denomination and quantity
        handleQuantityBasedCashOut(cashRegister, cashRegisterSize);
    }
    else if (userOption == 0)
    {
        // Handle the case when the user cancels the cash-out operation
        printf("Cash-out operation canceled.\n");
    }
}

/**
 * @brief Handles amount-based cash-out from the cash register.
 * @param cashRegister Array of CashRegister structures representing the current cash register.
 * @param cashRegisterSize Number of entries in the cashRegister array, representing the total
 *                         number of denominations in the register.
 * @pre cashRegister must contain valid cash denominations with non-negative quantities.
 */
void handleAmountBasedCashOut(CashRegister cashRegister[], int cashRegisterSize)
{
    float amountToClaim;       // Amount requested by the user
    int scanResult;            // Result of input validation
    int remainingAmountCents;  // RemainingAmount val to avoid floating point precision errors
    int amountToClaimCents;    // amountToClaimCents val to avoid floating point precision errors
    int dispensed[cashRegisterSize];  // Track the number of notes/coins dispensed

    // Prompt the user for the amount they wish to claim
    printf("\nEnter the amount you wish to claim (in PHP): ");
    scanResult = scanf("%f", &amountToClaim);

    // Validate the input: amount must be a positive number
    if (scanResult != 1 || amountToClaim <= 0)
    {
        printf("Invalid input or amount. Please enter a valid option.\n");
        while (getchar() != '\n');  // Clear invalid input from the buffer
    }

    // Convert the amount to cents for precise calculations
    amountToClaimCents = (int) (round(amountToClaim * 100));  // Convert to nearest cent

    remainingAmountCents = amountToClaimCents;  // Remaining amount to fulfill in cents
    int i, j;                                   // Loop variables

    // Initialize dispensed array to zero for all denominations
    for (i = 0; i < cashRegisterSize; i++)
    {
        dispensed[i] = 0;
    }

    // Attempt to dispense denominations starting from the highest denomination
    for (j = 0; j < cashRegisterSize; j++)
    {
        int cashDenominationCents =
            (int) (round(cashRegister[j].cashDenomination * 100));  // Convert denomination to cents

        // While the denomination can still contribute to the remaining amount
        // and there are notes/coins left in the register
        while (remainingAmountCents >= cashDenominationCents && cashRegister[j].amountLeft > 0)
        {
            remainingAmountCents -= cashDenominationCents;  // Deduct denomination value
            cashRegister[j].amountLeft--;                   // Decrease available quantity
            dispensed[j]++;                                 // Track the number dispensed
        }
    }

    // Check if the exact amount was dispensed
    if (remainingAmountCents > 0)
    {
        // If not, revert the changes to the cash register
        printf("\nUnable to dispense the exact stated amount. Operation canceled.\n");

        // Restore the original quantities in the cash register
        for (int z = 0; z < cashRegisterSize; z++)
        {
            cashRegister[z].amountLeft += dispensed[z];
        }
    }
    else
    {
        // If the amount was successfully dispensed, display the breakdown
        printf("\nDispensed Denominations:\n");
        printf(SEPARATOR "\n");
        for (int x = 0; x < cashRegisterSize; x++)
        {
            if (dispensed[x] > 0)
            {
                // Display the count and value of each denomination dispensed
                printf("  %d x PhP%.2f\n", dispensed[x], cashRegister[x].cashDenomination);
            }
        }

        // Display the total amount dispensed
        printf(SEPARATOR "\n");
        printf("Transaction Completed. Amount Dispensed: PhP%.2f\n", amountToClaim);
    }
}

/**
 * @brief Handles cash-out based on denomination and quantity.
 * @param cashRegister Array of CashRegister structures representing the current cash register.
 * @param cashRegisterSize Number of entries in the cashRegister array.
 * @pre cashRegister must be properly initialized with valid denominations and non-negative
 * quantities.
 */
void handleQuantityBasedCashOut(CashRegister cashRegister[], int cashRegisterSize)
{
    float denomination;          // Denomination to be claimed
    int quantity;                // Quantity to be claimed
    int scanResult;              // Result of input validation
    int validDenomination = 0;   // Flag to check if denomination exists in the register
    int sufficientQuantity = 0;  // Flag to check if sufficient quantity is available
    int i;                       // Loop variable

    // Prompt the user for the denomination
    printf("\nEnter the denomination you wish to claim: ");
    scanResult = scanf("%f", &denomination);

    // Check for invalid input
    if (scanResult != 1)
    {
        printf("Invalid input. Operation canceled.\n");
    }

    // Search for the entered denomination in the cash register
    i = 0;
    while (i < cashRegisterSize && validDenomination == 0)
    {
        if (cashRegister[i].cashDenomination == denomination)
        {
            validDenomination = 1;  // Denomination found

            // Prompt the user for the quantity to claim
            printf("Enter the quantity you wish to claim: ");
            scanResult = scanf("%d", &quantity);

            // Validate the quantity input
            if (scanResult != 1 || quantity <= 0)
            {
                printf("Invalid quantity. Operation canceled.\n");
            }

            // Check if sufficient quantity is available
            if (quantity <= cashRegister[i].amountLeft)
            {
                sufficientQuantity = 1;  // Sufficient quantity available

                // Perform the cash-out operation
                cashRegister[i].amountLeft -= quantity;  // Deduct quantity from the register
                printf("Successfully dispensed %d - PhP%.2f\n", quantity, denomination);
                printf("Remaining quantity of PhP%.2f: %d\n", denomination,
                       cashRegister[i].amountLeft);
            }
            else
            {
                // Insufficient quantity
                printf("Insufficient quantity for PhP%.2f. Only %d remaining.\n", denomination,
                       cashRegister[i].amountLeft);
            }
        }
        i++;  // Move to the next denomination in the register
    }

    // If no valid denomination was found
    if (validDenomination == 0)
    {
        printf(
            "Invalid denomination. Please choose a valid denomination from the cash register.\n");
    }

    // If the denomination is valid but quantity is insufficient
    if (validDenomination == 1 && sufficientQuantity == 0 && scanResult == 1 && quantity > 0)
    {
        printf("Operation canceled due to insufficient quantity.\n");
    }
}
