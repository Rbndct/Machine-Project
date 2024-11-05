#include "main_menu.h"

#include <stdio.h>

#include "data_structures.h"
#include "maintenance.h"
#include "vending_machine.h"

/**
 * @brief Displays the main menu and handles user selection.
 * @param userMenuSelection A pointer to an integer where the user's menu selection will be stored.
 * @return The selected menu option as an integer.
 */
int handleMenuSelection(int userMenuSelection)
{
    printf("\n\nWelcome to Nats Silog Vending Machine!!\n");
    printf("1 - Vending Machine\n");
    printf("2 - Staff Maintenance\n");
    printf("3 - Shutdown Machine\n");

    // Prompt the user for input and store it in userMenuSelection
    scanf("%d", &userMenuSelection);

    return userMenuSelection;  // Return the user's selection
}

/**
 * @brief Handles the purchase flow in the vending machine.
 * @param items An array of VendingItem representing the available items.
 * @param menuSize The size of the items array.
 * @param userMoney A pointer to a float representing the user's money available for purchase.
 * @param cash An array of CashRegister representing the cash available.
 * @param registerSize The size of the cash register array.
 * @param selection A pointer to a UserSelection struct where user's selections will be stored.
 * @param confirmation A pointer to an integer to indicate whether the transaction is confirmed (1
 * for yes, 0 for no).
 */
void processPurchase(VendingItem items[], int menuSize, float *userMoney, CashRegister cash[],
                     int registerSize, UserSelection *selection, int *confirmation)
{
    // Display the items available for purchase
    displayItems(items, menuSize);

    // Prompt the user to input their money
    userMoneyInput(userMoney, cash, registerSize);

    // Allow the user to select items they wish to purchase
    selectItems(items, menuSize, selection);

    // Calculate the change based on user's money and total item cost
    getChange(cash, userMoney, registerSize, &selection->totalItemCost, confirmation);

    // If the transaction is confirmed by the user
    if (*confirmation)
    {
        // Process the selected silog items for purchase
        getSilog(selection);
    }
}

/**
 * @brief Display maintenance options and handle the user's selection.
 * @param items Array of VendingItem structures representing the inventory.
 * @param menuSize Number of items in the inventory.
 */
void handleMaintenanceOptions(VendingItem items[], int menuSize)
{
    int maintenanceSelection = 0;  // Initialize variable for user selection

    // Display maintenance menu options
    printf(
        "\nMaintenance Features\n"
        "---------------------\n"
        "1 - View Inventory\n"
        "2 - Set Item Price\n"
        "3 - Restock Item\n"
        "Enter your choice: ");

    // Prompt for and capture the user's selection
    if (scanf("%d", &maintenanceSelection) != 1)
    {
        printf("Invalid input. Please enter a number between 1 and 3.\n");
        return;  // Exit the function if input is invalid
    }

    // Validate selection within the range of available options
    if (maintenanceSelection < 1 || maintenanceSelection > 3)
    {
        printf("Invalid choice. Please enter a number between 1 and 3.\n");
        return;  // Exit the function if selection is out of range
    }

    // Handle the selected maintenance option
    switch (maintenanceSelection)
    {
        case 1:
            viewInventory(items, menuSize);
            break;
        case 2:
            modifyPrice(items, menuSize);
            break;
        case 3:
            restockInventory(items, menuSize);
            break;
        default:
            // This case will not be reached due to previous validation
            printf("Invalid maintenance option.\n");
            break;
    }
}
