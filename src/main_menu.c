#include "main_menu.h"

#include <stdio.h>

#include "constants.h"
#include "data_structures.h"
#include "maintenance.h"
#include "vending_machine.h"

/**
 * @brief Displays the main menu for the vending machine and captures user input.

 * @param userMenuSelection A pointer to an integer where the user's menu selection will be stored.
 * @return The selected menu option as an integer:
 *         - 1 for "Vending Machine"
 *         - 2 for "Staff Maintenance"
 *         - 3 for "Shutdown Machine"
 */
int handleMenuSelection(int userMenuSelection)
{
    printf("\nWelcome to Silog Vending Machine!!\n");
    printf("1 - Vending Machine\n");
    printf("2 - Staff Maintenance\n");
    printf("3 - Shutdown Machine\n");

    // Prompt the user for input
    printf("Please enter your choice: ");
    int scanResult = scanf("%d", &userMenuSelection);

    // Validate user input
    if (scanResult != 1)
    {
        printf("Invalid input. Please enter a number corresponding to the menu options.\n");
        userMenuSelection = -1;  // Assign a default invalid value
    }

    return userMenuSelection;  // Return the user's selection
}

/**
 * @brief Handles the complete purchase process in the vending machine.

 * @param availableItems Array of VendingItem structures representing the items.
 * @param itemCount The number of items in the availableItems array.
 * @param insertedMoney Pointer to a float representing the user's total money available.
 * @param cashRegister Array of CashRegister structures representing the available denominations.
 * @param cashRegisterSize The number of denominations in the cashRegister array.
 * @param userSelection Pointer to a UserSelection structure to store the user's selection.
 * @param orderConfirmation Pointer to an integer indicates if transaction is confirmed.
 * @pre The arrays availableItems and cashRegister must be initialized and contain valid data.
 */
void processPurchase(VendingItem availableItems[], int itemCount, float *insertedMoney,
                     CashRegister cashRegister[], int cashRegisterSize,
                     UserSelection *userSelection, int *orderConfirmation)
{
    int continueVending = 1;  // Control flag for repeating the vending process

    do
    {
        // Display available items in the vending machine
        displayItems(availableItems, itemCount);

        // Prompt the user to input money
        userMoneyInput(insertedMoney, cashRegister, cashRegisterSize);

        // Allow the user to select items and adjust total money and stock accordingly
        selectItems(availableItems, itemCount, userSelection, insertedMoney, cashRegister,
                    cashRegisterSize);

        // Calculate change and confirm the transaction
        getChange(cashRegister, insertedMoney, cashRegisterSize, &userSelection->totalItemCost,
                  orderConfirmation);

        if (*orderConfirmation)
        {
            // Complete the transaction by finalizing the order
            resetOrderAfterConfirm(userSelection, insertedMoney);
            printf("\nTransaction completed successfully.\n" SEPARATOR);
        }
        else
        {
            // Cancel the transaction, returning stock and refunding money
            resetOrderAfterCancel(userSelection, insertedMoney, availableItems, itemCount);
            printf("\nOrder has been canceled.\n");
        }

        // Prompt the user to restart or exit the vending process
        int scanResult;
        printf("\nStart Vending Again?\n1. Yes\n0. Return to Main Menu: ");
        scanResult = scanf("%d", &continueVending);

        // Validate user input for restarting or exiting
        while (scanResult != 1 || (continueVending != 1 && continueVending != 0))
        {
            while (getchar() != '\n');  // Clear invalid input from the buffer
            printf(
                "Invalid input! Please enter 1 to start again or 0 to return to the main menu: ");
            scanResult = scanf("%d", &continueVending);
        }

    } while (continueVending == 1);  // Loop if the user chooses to continue vending

    if (continueVending == 0)
    {
        printf("Returning to the main menu...\n" SEPARATOR);
    }
}

/**
 * @brief Displays the maintenance menu, allowing the user to manage inventory and cash register.
 * @param items Array of VendingItem structures representing the inventory.
 * @param menuSize The number of items in the inventory array.
 * @param cashRegister Array of CashRegister structures representing the available denominations.
 * @param cashRegisterSize The number of denominations in the cashRegister array.
 * @pre The arrays items and cashRegister must be initialized and contain valid data.
 */
void handleMaintenanceOptions(VendingItem items[], int menuSize, CashRegister cashRegister[],
                              int cashRegisterSize)
{
    int maintenanceSelection;
    int exitMaintenance = 0;  // Control flag for exiting the maintenance menu

    while (exitMaintenance == 0)  // Continue showing the menu until the user decides to exit
    {
        // Display maintenance menu options
        printf(SEPARATOR
               "\nMaintenance Features\n"
               "1 - Inventory Features\n"
               "2 - Cash Register Features\n"
               "0 - Exit Maintenance Menu\n"
               "\nEnter your choice: ");

        int scanResult;
        scanResult = scanf("%d", &maintenanceSelection);

        // Validate menu selection input
        while (scanResult != 1)
        {
            printf("Invalid input. Please enter a number between 0 and 2.\n");
            while (getchar() != '\n');  // Clear invalid input
            scanResult = scanf("%d", &maintenanceSelection);
        }

        if (maintenanceSelection < 0 || maintenanceSelection > 2)
        {
            printf("Invalid choice. Please enter a number between 0 and 2.\n");
        }
        else
        {
            switch (maintenanceSelection)
            {
                case 1:  // Inventory Features
                {
                    int inventorySelection;
                    int exitInventory = 0;

                    while (exitInventory == 0)
                    {
                        // Display inventory menu options
                        printf(SEPARATOR
                               "\nInventory Features\n"
                               "1 - View Inventory\n"
                               "2 - Set Item Price\n"
                               "3 - Restock Item\n"
                               "0 - Back to Maintenance Menu\n"
                               "\nEnter your choice: ");

                        scanResult = scanf("%d", &inventorySelection);

                        // Validate inventory menu selection input
                        while (scanResult != 1)
                        {
                            printf("Invalid input. Please enter a number between 0 and 3.\n");
                            while (getchar() != '\n');  // Clear invalid input
                            scanResult = scanf("%d", &inventorySelection);
                        }

                        if (inventorySelection < 0 || inventorySelection > 3)
                        {
                            printf("Invalid choice. Please enter a number between 0 and 3.\n");
                        }
                        else
                        {
                            switch (inventorySelection)
                            {
                                case 1:
                                    viewInventory(items, menuSize);  // Display inventory
                                    break;
                                case 2:
                                    modifyPrice(items, menuSize);  // Modify item prices
                                    break;
                                case 3:
                                    restockInventory(items, menuSize);  // Restock inventory
                                    break;
                                case 0:
                                    exitInventory = 1;  // Exit inventory submenu
                                    break;
                            }
                        }
                    }
                    break;
                }
                case 2:  // Cash Register Features
                {
                    int cashRegisterSelection;
                    int exitCashRegister = 0;

                    while (exitCashRegister == 0)
                    {
                        // Display cash register menu options
                        printf(SEPARATOR
                               "\nCash Register Features\n"
                               "1 - View Cash Register\n"
                               "2 - Restock Cash Register\n"
                               "3 - Cash Out\n"
                               "0 - Back to Maintenance Menu\n"
                               "\nEnter your choice: ");

                        scanResult = scanf("%d", &cashRegisterSelection);

                        // Validate cash register menu selection input
                        while (scanResult != 1)
                        {
                            printf("Invalid input. Please enter a number between 0 and 3.\n");
                            while (getchar() != '\n');  // Clear invalid input
                            scanResult = scanf("%d", &cashRegisterSelection);
                        }

                        if (cashRegisterSelection < 0 || cashRegisterSelection > 3)
                        {
                            printf("Invalid choice. Please enter a number between 0 and 3.\n");
                        }
                        else
                        {
                            switch (cashRegisterSelection)
                            {
                                case 1:
                                    viewCashRegister(cashRegister,
                                                     cashRegisterSize);  // View denominations
                                    break;
                                case 2:
                                    reStockRegister(cashRegister,
                                                    cashRegisterSize);  // Restock cash register
                                    break;
                                case 3:
                                    cashOut(cashRegister, cashRegisterSize);  // Perform cash out
                                    break;
                                case 0:
                                    exitCashRegister = 1;  // Exit cash register submenu
                                    break;
                            }
                        }
                    }
                    break;
                }
                case 0:  // Exit Maintenance Menu
                    exitMaintenance = 1;
                    printf("Exiting Maintenance Menu...\n");
                    break;
            }
        }
    }
}
