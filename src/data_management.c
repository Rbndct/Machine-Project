#include "data_management.h"  // Include the header for function declarations

#include <stdio.h>

#include "data_structures.h"  // Include your data structure definitions

#define CSV_FILE "build/vending_items.csv"

/**
 * @brief Saves the vending items to a CSV file.
 * @param items An array of VendingItem structures containing item details.
 * @param menuSize The total number of items in the array.
 */
void saveItemsToCSV(VendingItem items[], int menuSize)
{
    FILE *file = fopen(CSV_FILE, "w");

    if (file == NULL)
    {
        perror("Error opening file for writing");
        return;
    }

    // Write CSV header with column names, ensuring correct alignment and spacing
    fprintf(file, "\"Item Number\",\"Item Name\",\"Price (PHP)\",\"Stock Left\"\n");

    // Write item details to CSV
    for (int i = 0; i < menuSize; i++)
    {
        // Enclose item names in double quotes to handle commas and other special characters in
        // names
        fprintf(file, "\"%d\",\"%s\",\"%.2f\",\"%d\"\n", items[i].itemNumber, items[i].name,
                items[i].price, items[i].stock);
    }

    fclose(file);
    printf("Data saved to %s successfully.\n", CSV_FILE);
}
