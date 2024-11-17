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
    int passwordInput;
    int isValid = 0;  // Default to invalid (0)

    // Prompt the user for the maintenance password
    printf("\n\nInput maintenance password: ");
    if (scanf("%d", &passwordInput) != 1)
    {
        printf("Invalid input. Please enter a numerical password.\n");
    }
    else
    {
        // Check if the entered password matches the stored password
        if (passwordInput == *maintenancePassword)
        {
            printf("Access Granted\n");
            isValid = 1;  // Password is valid
        }
        else
        {
            printf("Incorrect password, please try again.\n");
        }
    }

    return isValid;  // Return the validation result at the end
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
 * @brief Modify the price of a specific item in the vending machine.
 * @param items     Array of VendingItem structures representing the menu items.
 * @param menuSize  Number of items in the vending machine menu.
 */
void modifyPrice(VendingItem items[], int menuSize)
{
    // Display the item list with item numbers, names, and prices
    printf("\n\n %-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Price (PHP)");
    printf(SEPARATOR "\n");

    for (int i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-10.2f\n", items[i].itemNumber, items[i].name, items[i].price);
    }
    printf(SEPARATOR "\n");

    // Prompt for item selection
    int modifyItemNumber;
    printf("Enter the item number to modify: ");
    scanf("%d", &modifyItemNumber);

    // Check if the entered item number exists and update its price
    int itemFound = 0;
    for (int i = 0; i < menuSize; i++)
    {
        if (items[i].itemNumber == modifyItemNumber)
        {
            itemFound = 1;
            float newPrice;
            printf("Enter the new price: ");
            scanf("%f", &newPrice);

            // Validate the new price and apply if positive
            if (newPrice > 0)
            {
                // Set the selected index item to user inputted price
                items[i].price = newPrice;
                printf("Price updated successfully!\n");
                return;  // Exit after successful price modification
            }
            else
            {
                printf("\nError: Please enter a positive number for the price.\n");
                // Repeat item selection for invalid price entry
                i--;  // Decrease index to retry current item
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
    int modifyItemNumber;
    int reStock = 0;
    int isValid = 0;  // Variable to track if a valid item number was entered

    // Display the inventory with stock levels
    printf("\n\n %-12s | %-15s | %-10s\n", "Item Number", "Item Name", "Stock Left");
    printf(SEPARATOR "\n");

    for (int i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-10d", items[i].itemNumber, items[i].name, items[i].stock);

        // Indicate if an item is out of stock
        if (items[i].stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG);
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");

    // Prompt user to select an item to restock
    printf("Input item number to modify: ");
    if (scanf("%d", &modifyItemNumber) != 1)
    {
        printf("Invalid input. Please enter a valid item number.\n");
    }
    else
    {
        // Search for the item and update its stock if found
        for (int i = 0; i < menuSize; i++)
        {
            if (items[i].itemNumber == modifyItemNumber)
            {
                isValid = 1;  // Mark item as valid
                printf("Input stock to add: ");
                if (scanf("%d", &reStock) != 1 || reStock <= 0)
                {
                    printf("\nYou must input a positive number for stock addition.\n");
                }
                else
                {
                    items[i].stock += reStock;
                    printf("Stock updated successfully.\n");
                }
            }
        }

        if (!isValid)
        {
            // Inform user if item number is invalid
            printf("Invalid Item Number! Please try again.\n");
        }
    }
}
