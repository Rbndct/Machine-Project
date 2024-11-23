#include "maintenance.h"

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
    // Print header for the item details table
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)",
           "Stock Left");
    printf(SEPARATOR "\n");

    int i;
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
    // Display the item list with item numbers, names, and prices
    printf("\n%-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Price (PHP)");
    printf(SEPARATOR "\n");

    int i;
    for (i = 0; i < menuSize; i++)
    {
        int itemNumber = items[i].itemNumber;
        char *itemName = items[i].name;
        float itemPrice = items[i].price;

        // Display item details
        printf("%-12d | %-15s | %-10.2f\n", itemNumber, itemName, itemPrice);
    }
    printf(SEPARATOR "\n");

    // Prompt for item selection
    int modifyItemNumber;
    printf("Enter the item number to modify: ");
    scanf("%d", &modifyItemNumber);

    // Check if the entered item number exists and update its price
    int itemFound = 0;
    int j;
    for (j = 0; j < menuSize; j++)
    {
        int currentItemNumber;
        currentItemNumber = items[j].itemNumber;

        if (currentItemNumber == modifyItemNumber)
        {
            itemFound = 1;

            // Declare and initialize the new price variable
            float newPrice;
            printf("Enter the new price: ");
            scanf("%f", &newPrice);

            // Validate the new price and apply if positive
            if (newPrice > 0)
            {
                // Set the selected index item to the user inputted price
                items[j].price = newPrice;
                printf("Price updated successfully!\n");
            }
            else
            {
                // Handle invalid price input
                printf("\nError: Please enter a positive number for the price.\n");
                j--;  // Decrease index to retry current item
            }
        }
    }

    // Error handling if there is no such item number
    if (itemFound == 0)
    {
        printf("Invalid Item Number! No item found with the entered number.\n");
    }
}

/**
 * @brief Allows staff to restock items in the vending machine inventory.
 * @param items Array of VendingItem structures representing the inventory.
 * @param menuSize Number of items in the inventory.
 */
void restockInventory(VendingItem items[], int menuSize)
{
    // Variable declaration
    int modifyItemNumber;
    int reStock;
    int isValid = 0;  // Variable to track if a valid item number was entered

    // Display the inventory with stock levels
    printf("\n%-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Stock Left");
    printf(SEPARATOR "\n");

    int i;
    for (i = 0; i < menuSize; i++)
    {
        int itemNumber = items[i].itemNumber;
        char *itemName = items[i].name;
        int itemStock = items[i].stock;

        // Display item details
        printf("%-12d | %-15s | %-10d", itemNumber, itemName, itemStock);

        // Indicate if an item is out of stock
        if (itemStock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");

    // Prompt user to select an item to restock
    printf("Input item number to modify: ");
    int result = scanf("%d", &modifyItemNumber);

    if (result != 1)
    {
        printf("Invalid input. Please enter a valid item number.\n");
    }

    else
    {
        // Search for the item and update its stock if found
        int j;
        for (j = 0; j < menuSize; j++)
        {
            int currentItemNumber = items[j].itemNumber;

            if (currentItemNumber == modifyItemNumber)
            {
                isValid = 1;  // Mark item as valid

                // Ask for the amount of stock to add
                printf("Input stock to add: ");
                int result = scanf("%d", &reStock);

                if (result != 1 || reStock <= 0)
                {
                    printf("\nYou must input a positive number for stock addition.\n");
                }

                else
                {
                    // Update the stock of the selected item
                    items[j].stock += reStock;
                    printf("Stock updated successfully.\n");
                }
            }
        }

        // Check if the item was valid and found
        if (!isValid)
        {
            // Inform user if item number is invalid
            printf("Invalid Item Number! Please try again.\n");
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
    totalAmount = 0.0;  // Initialize totalAmount

    printf("\n==================== Cash Register ====================\n");
    printf("| Denomination (PHP) | Amount Left | Total Value (PHP) |\n");
    printf(SEPARATOR "\n");

    int i;
    for (i = 0; i < cashRegisterSize; i++)
    {
        float denominationTotal;
        denominationTotal = cashRegister[i].cashDenomination * cashRegister[i].amountLeft;

        totalAmount += denominationTotal;

        // Display each denomination, the amount left, and the total value of that denomination
        printf("| %-10.2f | %-15d | %-8.2f |\n", cashRegister[i].cashDenomination,
               cashRegister[i].amountLeft, denominationTotal);
    }

    printf(SEPARATOR "\n");

    // Display the total cash in the register
    printf("| Total Cash in Register:                   PHP %-8.2f |\n", totalAmount);
    printf(SEPARATOR "\n");
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

    // Display the current cash register
    viewCashRegister(cashRegister, cashRegisterSize);

    printf("\nEnter the denomination to restock: ");
    int scanResult;
    scanResult = scanf("%f", &denomination);

    if (scanResult != 1)
    {
        printf("Invalid input. Please enter a valid denomination.\n");
        // Clear the input buffer
        while (getchar() != '\n');
    }
    else
    {
        // Search for the entered denomination in the cash register
        int i;
        validDenomination = 0;  // Reset flag before searching

        for (i = 0; i < cashRegisterSize; i++)
        {
            if (cashRegister[i].cashDenomination == denomination)
            {
                validDenomination = 1;

                printf("Enter the quantity to add (positive number only): ");

                // Separate the scanf and condition check
                int quantityScanResult;
                quantityScanResult = scanf("%d", &quantity);

                if (quantityScanResult != 1)
                {
                    printf("Invalid input. Please enter a valid quantity.\n");
                    // Clear the input buffer
                    while (getchar() != '\n');
                }
                else
                {
                    // Check if quantity is positive
                    if (quantity < 0)
                    {
                        printf("Invalid quantity. Restock quantity must be a positive number.\n");
                    }
                    else
                    {
                        // Update the quantity in the cash register
                        cashRegister[i].amountLeft += quantity;
                        printf("Successfully added %d to %.2f PHP denomination.\n", quantity,
                               cashRegister[i].cashDenomination);
                    }
                }

                // Denomination found, exit the loop
                break;
            }
        }

        // If no valid denomination was found
        if (validDenomination == 0)
        {
            printf("Invalid denomination. Please select a valid denomination from the register.\n");
        }
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

    // Prompt the user for the amount they wish to claim
    printf("\nEnter the amount you wish to claim: ");

    int scanResult;
    scanResult = scanf("%f", &amountToClaim);

    if (scanResult != 1)
    {
        printf("Invalid input. Operation canceled.\n");
    }
    else
    {
        if (amountToClaim <= 0)
        {
            printf("Invalid amount. Operation canceled.\n");
        }
        else
        {
            int dispensed[cashRegisterSize];
            int i;
            for (i = 0; i < cashRegisterSize; i++)
            {
                dispensed[i] = 0;  // Initialize dispensed denominations to 0
            }

            float remainingAmount;
            remainingAmount = amountToClaim;

            int j;
            for (int j = 0; j < cashRegisterSize; j++)
            {
                while (remainingAmount >= cashRegister[j].cashDenomination &&
                       cashRegister[j].amountLeft >= 0.05)
                {
                    remainingAmount -= cashRegister[j].cashDenomination;
                    cashRegister[j].amountLeft--;
                    dispensed[j]++;
                }
            }

            if (remainingAmount > 0)
            {
                printf("\nUnable to dispense exact stated amount. Operation canceled.\n");

                // Restore quantities in the cash register
                int z;
                for (z = 0; z < cashRegisterSize; z++)
                {
                    cashRegister[z].amountLeft += dispensed[z];
                }
            }
            else
            {
                printf("\nDispensed denominations:\n" SEPARATOR);
                int x;
                for (x = 0; x < cashRegisterSize; x++)
                {
                    if (dispensed[x] > 0)
                    {
                        printf("%d - PhP%.2f\n", dispensed[x], cashRegister[x].cashDenomination);
                    }
                }

                printf("\nTransaction completed. Total dispensed: PhP%.2f\n", amountToClaim);
            }
        }
    }
}
