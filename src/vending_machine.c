#include "vending_machine.h"

#define OUT_OF_STOCK_MSG "Out of Stock"
#define INVALID_DENOM_MSG "Invalid denomination! Please try again."
#define SEPARATOR "--------------------------------------------------------------"

// Define valid denominations as constants
const float VALID_DENOMINATIONS[] = {20, 50, 100, 200, 500, 1, 5, 10, 0.25, 0.10, 0.05};
const int NUM_VALID_DENOMINATIONS = 11;

void displayItems(VendingItem items[], int menuSize)
{
    printf("\n\n%-12s | %-15s | %-10s | %-10s\n", "Item Number", "Item Name", "Price (PHP)", "Stock Left");
    printf(SEPARATOR "\n");

    // Loop through the items and display their details
    for (int i = 0; i < menuSize; i++)
    {
        printf("%-12d | %-15s | %-11.2f | %-3d", items[i].itemNumber, items[i].name, items[i].price, items[i].stock);
        // Check if the item is out of stock and display a message if true
        if (items[i].stock == 0)
        {
            printf(" %-12s", OUT_OF_STOCK_MSG); // Display out of stock message if items.stock is 0
        }
        printf("\n");
    }
    printf(SEPARATOR "\n");
}

int isValidDenomination(float moneyInserted)
{
    // Loops through all valid denominations
    for (int i = 0; i < NUM_VALID_DENOMINATIONS; i++)
    {
        // Checks if moneyInserted is equivalent to any valid denomination
        if (moneyInserted == VALID_DENOMINATIONS[i])
        {
            return 1; // Valid denomination
        }
    }
    return 0; // Invalid denomination
}

void updateCashRegister(CashRegister cashRegister[], int registerSize, float denomination)
{
    for (int i = 0; i < registerSize; i++)
    {
        if (cashRegister[i].cashDenomination == denomination)
        {
            cashRegister[i].amountLeft++; // Increment count of this denomination
            return;
        }
    }
}

void userMoneyInput(float *userMoney, CashRegister cashRegister[], int registerSize)
{
    float moneyInserted;

    // Display available denominations
    printf("Insert money into the vending machine.\n"
           "Allowed Denominations:\n"
           "Bills: 20, 50, 100, 200, 500 (PHP)\n"
           "Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");

    while (1)
    {
        // Prompt user for input
        printf("\nEnter the cash denomination (0 when done): ");

        // Check for valid input
        if (scanf("%f", &moneyInserted) != 1)
        {
            // Clear invalid input from buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input! Please enter a numeric value.\n");
            continue;
        }

        // Break loop if user inputs 0 to stop
        if (moneyInserted == 0)
            break;

        // Check if entered denomination is valid
        if (isValidDenomination(moneyInserted))
        {
            *userMoney += moneyInserted; // Add to user total
            printf("You inserted: %.2f PHP\nTotal so far: %.2f PHP\n", moneyInserted, *userMoney);

            // Update cash register for this denomination
            updateCashRegister(cashRegister, registerSize, moneyInserted);
        }
        else // Error message for invalid denominations
        {
            printf(INVALID_DENOM_MSG "\n");
        }
    }

    // Display total money inserted after loop ends
    printf("Total money inserted: %.2f PHP\n" SEPARATOR "\n", *userMoney);
}

void selectItems(VendingItem items[], int menuSize, UserSelection *selection)
{
    int done = 0;

    while (!done)
    {
        int selectionIndex;
        printf("\nEnter item number to order (1-%d).\nEnter 0 when done: ", menuSize);

        if (scanf("%d", &selectionIndex) != 1)
        {
            printf("Invalid input! Please enter a number between 0 and %d.\n", menuSize);
            while (getchar() != '\n')
                ;
            continue;
        }

        if (selectionIndex == 0)
        {
            if (selection->count > 0)
            {
                done = 1;
            }
            else
            {
                printf("You must select at least one item before finalizing your order.\n");
            }
        }
        else if (selectionIndex >= 1 && selectionIndex <= menuSize)
        {
            processSelection(items, selectionIndex - 1, selection);
        }
        else
        {
            printf("Invalid item number! Please try again.\n");
        }
    }

    printSelectedItems(selection);
}

void processSelection(VendingItem items[], int index, UserSelection *selection)
{
    VendingItem *selectedItem = &items[index];

    // Check stock and process selection
    if (selectedItem->stock > 0)
    {
        // Update selection if item is already chosen
        updateSelectedItems(selection, selectedItem);

        selectedItem->stock--; // Decrease stock for selected item

        printf("You have selected: %s, which costs %.2f\n", selectedItem->name, selectedItem->price);
        printf("Current total cost is %.2f\n", selection->totalItemCost);
    }
    else
    {
        printf("Sorry, %s is currently out of stock!\n", selectedItem->name);
    }
}

void updateSelectedItems(UserSelection *selection, VendingItem *selectedItem)
{
    int existingIndex = -1;

    for (int i = 0; i < selection->count; i++)
    {
        if (strcmp(selection->selectedItems[i], selectedItem->name) == 0)
        {
            existingIndex = i;
            break;
        }
    }

    if (existingIndex != -1)
    {
        selection->quantities[existingIndex]++;
        selection->subTotals[existingIndex] += selectedItem->price;
    }
    else
    {
        strcpy(selection->selectedItems[selection->count], selectedItem->name);
        selection->quantities[selection->count] = 1;
        selection->subTotals[selection->count] = selectedItem->price;
        selection->count++;
    }
    selection->totalItemCost += selectedItem->price;
}

void printSelectedItems(UserSelection *selection)
{
    printf("\n\nYou have selected:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    // Check if count is greater than 0
    if (selection->count > 0)
    {
        // Print each selected item with its quantity and total cost
        for (int i = 0; i < selection->count; i++)
        {
            printf("%-15s | %-10d | %-10.2f\n", selection->selectedItems[i], selection->quantities[i], selection->subTotals[i]);
        }
    }
    else
    {
        printf("No items selected.\n");
    }

    printf(SEPARATOR "\n");
}

void getChange(CashRegister cash[], float *userMoney, int registerSize, float *totalItemCost, int *confirmation)
{
    // Prompt for order confirmation
    printf("Order Confirmation (1 - Confirm / 0 - Cancel Order): ");
    while (scanf("%d", confirmation) != 1) // Ensure only integer input is accepted
    {
        while (getchar() != '\n')
            ; // Clear invalid input from buffer
        printf("Invalid input! Please enter 1 to confirm or 0 to cancel: ");
    }

    float userChange;
    if (*confirmation == 1) // If order is confirmed
    {
        userChange = *userMoney - *totalItemCost; // Calculate potential change
        printf("%-15s %-5.2f %-5s", "Final Total:", *totalItemCost, "PHP");
        printf("\n%-15s %-5.2f %-5s", "Money Input:", *userMoney, "PHP");
        printf("\n%-15s %-5.2f %-5s", "Change Total:", userChange, "PHP");
    }
    else // If order is canceled
    {
        userChange = *userMoney;
        printf("\n%-15s %-5.2f %-5s", "Money Input:", *userMoney, "PHP");
    }

    printf("\n" SEPARATOR);

    // Set the amount to dispense based on whether the order was confirmed
    float amountToDispense = userChange;

    // Iterate through cash register denominations to dispense change
    for (int i = 0; i < registerSize && amountToDispense >= 0.05; i++)
    {
        // Use a while loop to dispense the denomination as many times as possible
        while (amountToDispense >= cash[i].cashDenomination && cash[i].amountLeft > 0)
        {
            amountToDispense -= cash[i].cashDenomination; // Deduct denomination from remaining amount
            cash[i].amountLeft--;                         // Decrement denomination count in cash register

            printf("\n%-15s %-5.2f %-5s", "Dispensed", cash[i].cashDenomination, "PHP");

            // Check if amountToDispense is too small to dispense more of this denomination
            if (amountToDispense < 0.05) {
                break; // Break from the while loop if the amount is too low
            }
        }
    }

    printf("\n" SEPARATOR);

    // Check if exact change was dispensed or if any remains
    if (amountToDispense > 0.05)
        printf("\nUnable to dispense exact change. Remaining amount: %.2f\n", amountToDispense);
    else
        printf("\nChange successfully dispensed.\n");
}

void getSilog(UserSelection *selection)
{
    printf("\n\nOrder Summary:\n");
    printf("%-15s | %-10s | %-10s\n", "Item Name", "Quantity", "Total Cost");
    printf(SEPARATOR "\n");

    if (selection->count > 0)
    {
        for (int i = 0; i < selection->count; i++)
        {
            printf("%-15s | %-10d | %-10.2f\n", selection->selectedItems[i], selection->quantities[i], selection->subTotals[i]);
        }
        printf(SEPARATOR "\n");
        printf("Total Order Cost: %.2f PHP\n", selection->totalItemCost);
    }
    else
    {
        printf("No items selected.\n");
    }
    printf(SEPARATOR "\n");
    printf("Get silog from tray bin.\n");
}
