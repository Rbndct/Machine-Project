#include "main_menu.h"

#include <stdio.h>

#include "constants.h"
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
    printf("\nWelcome to Nats Silog Vending Machine!!\n");
    printf("1 - Vending Machine\n");
    printf("2 - Staff Maintenance\n");
    printf("3 - Shutdown Machine\n");

    // Prompt the user for input and store it in userMenuSelection
    scanf("%d", &userMenuSelection);

    return userMenuSelection;  // Return the user's selection
}

/**
 * @brief Handles the purchase flow in the vending machine.
 * @param availableItems Array of VendingItem structures representing the items available in the
 * vending machine.
 * @param itemCount Size of the availableItems array.
 * @param insertedMoney Pointer to a float representing the user's money available for purchase.
 * @param cashRegister Array of CashRegister structures representing the available denominations in
 * the machine.
 * @param cashRegisterSize Size of the cashRegister array.
 * @param currentSelection Pointer to a UserSelection structure where user's selections will be
 * stored.
 * @param orderConfirmation Pointer to an integer to indicate whether the transaction is confirmed
 * (1 for yes, 0 for no).
 */
void processPurchase(VendingItem availableItems[], int itemCount, float *insertedMoney,
                     CashRegister cashRegister[], int cashRegisterSize,
                     UserSelection *userSelection, int *orderConfirmation)
{
    int continueVending;
    continueVending = 1;  // Variable to control the loop (1 for yes, 0 for no)

    do
    {
        // Display the items available for purchase
        displayItems(availableItems, itemCount);

        // Prompt the user to input their money
        userMoneyInput(insertedMoney, cashRegister, cashRegisterSize);

        // Allow the user to select items they wish to purchase
        selectItems(availableItems, itemCount, userSelection, insertedMoney, cashRegister,
                    cashRegisterSize);

        // Calculate the change based on user's money and total item cost
        getChange(cashRegister, insertedMoney, cashRegisterSize, &userSelection->totalItemCost,
                  orderConfirmation);

        // If the transaction is confirmed by the user
        if (*orderConfirmation)
        {
            // Reset the order details after completing the transaction
            resetOrderAfterConfirm(userSelection, insertedMoney);

            printf("\nTransaction completed.\n" SEPARATOR);
        }
        else
        {
            // If the user cancels the order, reset the order (return stock, refund money)
            resetOrderAfterCancel(userSelection, insertedMoney, availableItems, itemCount);

            printf("\nOrder has been canceled.\n");
        }

        // Ask if the user wants to start the vending process again
        int scanResult;
        printf("\nStart Vending Again?\n1. Yes\n0. Return to Main Menu: ");

        scanResult = scanf("%d", &continueVending);
        while (scanResult != 1 || (continueVending != 1 && continueVending != 0))
        {
            while (getchar() != '\n');  // Clear invalid input from the buffer
            printf(
                "Invalid input! Please enter 1 to start again or 0 to return to the main menu: ");
            scanResult = scanf("%d", &continueVending);
        }

    } while (continueVending == 1);  // Continue the loop if the user selects 1 (Yes)

    if (continueVending == 0)
    {
        printf("Returning to the main menu...\n" SEPARATOR);
    }
}

/**
 * @brief Display maintenance options and handle the user's selection.
 * @param items Array of VendingItem structures representing the inventory.
 * @param menuSize Number of items in the inventory.
 */
void handleMaintenanceOptions(VendingItem items[], int menuSize)
{
    int maintenanceSelection;
    int exitMaintenance;

    maintenanceSelection = 0;  // Initialize variable for user selection
    exitMaintenance = 0;       // Initialize flag to check if user wants to exit

    while (exitMaintenance == 0)  // Continue showing the menu until the user decides to exit
    {
        // Display maintenance menu options
        printf(SEPARATOR
               "\nMaintenance Features\n"
               "1 - View Inventory\n"
               "2 - Set Item Price\n"
               "3 - Restock Item\n"
               "0 - Exit Maintenance Menu\n"
               "\nEnter your choice: ");

        // Prompt for and capture the user's selection
        int scanResult;
        scanResult = scanf("%d", &maintenanceSelection);

        while (scanResult != 1)  // If input is not valid, request valid input
        {
            printf("Invalid input. Please enter a number between 0 and 3.\n");
            // Clear the invalid input from the buffer
            while (getchar() != '\n');  // Consume invalid input
            scanResult = scanf("%d", &maintenanceSelection);
        }

        if (maintenanceSelection < 0 || maintenanceSelection > 3)
        {
            printf("Invalid choice. Please enter a number between 0 and 3.\n");
        }
        else
        {
            // Handle the selected maintenance option
            if (maintenanceSelection == 1)
            {
                viewInventory(items, menuSize);
            }
            else if (maintenanceSelection == 2)
            {
                modifyPrice(items, menuSize);
            }
            else if (maintenanceSelection == 3)
            {
                restockInventory(items, menuSize);
            }
            else if (maintenanceSelection == 0)
            {
                exitMaintenance = 1;  // Set flag to exit the loop
                printf("Exiting Maintenance Menu...\n");
            }
        }
    }
}
