#include "main_menu.h"

#include "data_structures.h"
#include "maintenance.h"
#include "vending_machine.h"

int handleMenuSelection(int userMenuSelection)
{
    printf("\n\nWelcome Nats Silog Vending Machine!!\n");
    printf("1 - Vending Machine\n");
    printf("2 - Staff Maintenance \n");
    printf("3 - Shutdown Machine\n");

    scanf("%d", &userMenuSelection);

    return userMenuSelection;
}
// Handle purchase flow
void processPurchase(VendingItem items[], int menuSize, float *userMoney, CashRegister cash[],
                     int registerSize, UserSelection *selection, int *confirmation)
{
    displayItems(items, menuSize);
    userMoneyInput(userMoney, cash, registerSize);
    selectItems(items, menuSize, selection);
    getChange(cash, userMoney, registerSize, &selection->totalItemCost, confirmation);

    if (*confirmation)
    {
        getSilog(selection);
    }
}

/**
 * @brief Display maintenance options and handle the user's selection.
 *
 * This function displays a menu of maintenance features for the vending machine
 * and executes the appropriate function based on the user's selection.
 *
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
