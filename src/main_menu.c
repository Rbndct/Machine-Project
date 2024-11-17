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
 * @param availableItems Array of VendingItem structures representing the items available in the
 * vending machine.
 * @param itemCount Size of the availableItems array.
 * @param userMoney Pointer to a float representing the user's money available for purchase.
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
    // Display the items available for purchase
    displayItems(availableItems, itemCount);

    // Prompt the user to input their money
    userMoneyInput(insertedMoney, cashRegister, cashRegisterSize);

    // Allow the user to select items they wish to purchase
    selectItems(availableItems, itemCount, userSelection);

    // Calculate the change based on user's money and total item cost
    getChange(cashRegister, insertedMoney, cashRegisterSize, &userSelection->totalItemCost,
              orderConfirmation);

    // If the transaction is confirmed by the user
    if (*orderConfirmation)
    {
        // Process the purchase (deduct stock, finalize purchase)
        processTransaction(availableItems, itemCount, userSelection);

        // Reset the order details after completing the transaction
        resetOrderAfterConfirm(userSelection, insertedMoney);

        printf("\nTransaction completed.\n");
    }
    else
    {
        // If the user cancels the order, reset the order (return stock, refund money)
        resetOrderAfterCancel(userSelection, insertedMoney, availableItems, itemCount);

        printf("\nOrder has been canceled.\n");
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
    int validInput = 0;            // Flag to check if input is valid

    while (!validInput)
    {
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
            // Clear the invalid input from the buffer
            while (getchar() != '\n');  // consume invalid input
        }
        else if (maintenanceSelection < 1 || maintenanceSelection > 3)
        {
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }
        else
        {
            validInput = 1;  // If valid input, exit the loop and proceed
        }
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
