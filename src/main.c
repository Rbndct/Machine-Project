/*
 * This is to certify that this project is my own work, based on my personal efforts in studying and
 * applying the concepts learned.  I have constructed the functions and their respective algorithms
 * and corresponding code by myself.  The program was run, tested, and debugged by my own efforts.
 * I further certify that I have not copied in part or whole or otherwise plagiarized the work of
 * other students and/or persons. <Raphael Maagma>, DLSU ID #12413828
 */

/**
 * @file main.c
 * @brief This program simulates a vending machine where the user can view items, insert money, and
 * check stock availability, transact. As well as having implemented maintenance features (both cash
 * register and inventory features).
 * @version 3.0
 * @date Last modified: November 24, 2024
 * @link https://github.com/Rbndct/Machine-Project
 * @section Acknowledgments
 * Acknowledgment and Certification: This project is my own work, based on personal efforts and
 * application of studied concepts.
 *
 * This project was developed with the help of the following resources:
 * [W3Schools C Programming](https://www.w3schools.com/c/c_intro.php)
 * [Programiz C Programming](https://www.programiz.com/c-programming)
 * [Devdocs.io](https://devdocs.io/c/)
 *Lessons and videos from my Grade 12 Data Structures class at iACADEMY, provided by Sir Wilson Tiu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_management.c"
#include "main_menu.c"
#include "maintenance.c"
#include "vending_machine.c"

int main()
{
    // Initialize vending machine items with their attributes: item number, name, price, and stock
    // count
    VendingItem items[] = {{1, "Hotdog", 9.50, 10}, {2, "Longganisa", 20.75, 10},
                           {3, "Bacon", 12.00, 10}, {4, "Sausage", 35.00, 10},
                           {5, "Tapa", 22.50, 10},  {6, "Tocino", 18.00, 10},
                           {7, "Rice", 15.00, 10},  {8, "Egg", 8.00, 10}};

    // Initialize the cash register with denominations and their counts
    CashRegister cash[] = {{500, 10}, {100, 10}, {50, 10},   {20, 10},   {10, 10},
                           {5, 10},   {1, 10},   {0.25, 10}, {0.10, 10}, {0.05, 10}};

    float userMoney = 0.0f;  // Track the total money inserted by the user during transactions

    // Initialize UserSelection to store selected items, quantities, and costs
    UserSelection selection = {{{0}}, {0}, {0.0}, 0, 0.0};

    // Define additional parameters for the program
    int registerSize = 10;             // Number of cash register denominations
    int menuSize = 8;                  // Number of vending machine items
    int userMenuSelection = 0;         // Stores the user's menu selection
    int confirmation = 0;              // Tracks if a transaction is confirmed (1 for yes, 0 for no)
    int maintenancePassword = 123456;  // Predefined password for accessing maintenance features
    int isRunning = 1;  // Condition to control the main loop (1 for running, 0 for stop)

    // Main loop: Show the main menu until the user shuts down the machine
    while (isRunning)
    {
        // Display the main menu and get the user's selection
        int displayMenu;
        displayMenu = handleMenuSelection(userMenuSelection);

        // Process the user's menu selection
        switch (displayMenu)
        {
            case 1:  // Purchase items
                processPurchase(items, menuSize, &userMoney, cash, registerSize, &selection,
                                &confirmation);
                break;

            case 2:  // Maintenance options
                // Validate the password before granting access to maintenance features
                if (maintenanceValidation(&maintenancePassword))
                {
                    handleMaintenanceOptions(items, menuSize, cash, registerSize);
                }
                else
                {
                    printf("Wrong password\n");
                }
                break;

            case 3:  // Shutdown the machine
                // Validate the password before allowing machine shutdown
                if (maintenanceValidation(&maintenancePassword))
                {
                    printf("Machine going offline...\n");
                    saveItemsToCSV(items, menuSize);  // Save the inventory state to a CSV file
                    isRunning = 0;                    // Stop the main loop
                }
                else
                {
                    printf("Wrong password\n");
                }
                break;

            default:  // Invalid menu selection
                printf("Invalid selection. Please try again.\n");
                break;
        }
    }

    return 0;  // Exit the program successfully
}
