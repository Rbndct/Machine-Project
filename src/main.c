/**
 * @file main.c
 * @brief This program simulates a vending machine where the user can view items, insert money, and
 * check stock availability.
 * @version 2.0
 * @date Last modified: November 5, 2024
 * @link https://github.com/Rbndct/Machine-Project
 *
 * @section Acknowledgments
 * Resources:
 * - W3Schools: https://www.w3schools.com/c/c_intro.php
 * - Programiz: https://www.programiz.com/c-programming
 * - DevDocs: https://devdocs.io/c-error-handling/
 *
 * Acknowledgment and Certification: This project is my own work, based on personal efforts and
 * application of studied concepts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_management.c"
#include "main_menu.c"
#include "maintenance.c"
#include "vending_machine.c"

// Main function for the vending machine program
int main()
{
    // Define items in the vending machine with item numbers, names, prices, and stock counts
    VendingItem items[] = {{1, "Hotdog", 9.50, 5}, {2, "Longganisa", 20.75, 5},
                           {3, "Bacon", 12.00, 5}, {4, "Sausage", 35.00, 5},
                           {5, "Tapa", 22.50, 5},  {6, "Tocino", 18.00, 5},
                           {7, "Rice", 15.00, 10}, {8, "Egg", 8.00, 10}};

    // Define available cash denominations in the register
    CashRegister cash[] = {{500, 10}, {100, 10}, {50, 10},   {20, 10},   {10, 10},
                           {5, 10},   {1, 10},   {0.25, 10}, {0.10, 10}, {0.05, 10}};

    float userMoney = 0.0f;  // Total money inserted by the user

    // Initialize UserSelection to track the user's selected items
    UserSelection selection = {{{0}}, {0}, {0.0}, 0, 0.0};
    int registerSize = 10, menuSize = 8, userMenuSelection = 0, confirmation = 0;
    int maintenancePassword = 123456;
    int isRunning = 1;  // Condition to control the main loop

    // Loop to show the main menu until the user chooses to exit
    while (isRunning)
    {
        int displayMenu;
        displayMenu = handleMenuSelection(userMenuSelection);

        switch (displayMenu)
        {
            case 1:  // Purchase items
                processPurchase(items, menuSize, &userMoney, cash, registerSize, &selection,
                                &confirmation);
                break;
            case 2:  // Maintenance options
                if (maintenanceValidation(&maintenancePassword))
                {
                    handleMaintenanceOptions(items, menuSize, cash, registerSize);
                }
                else
                {
                    printf("Wrong password\n");
                }
                break;
            case 3:  // Exit
                if (maintenanceValidation(&maintenancePassword))
                {
                    printf("Machine going offline...\n");
                    saveItemsToCSV(items, menuSize);
                    isRunning = 0;  // Set the flag to stop the loop
                }
                else
                {
                    printf("Wrong password\n");
                }
                break;
            default:
                printf("Invalid selection. Please try again.\n");
                break;
        }
    }
    return 0;
}
