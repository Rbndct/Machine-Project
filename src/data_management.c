#include "data_management.h"  // Include the header for function declarations

#include <stdio.h>

#include "data_structures.h"  // Include your data structure definitions

#define CSV_FILE "vending_items.csv"

/**
 * @brief Saves the details of the vending items to a CSV file.
 * @param items An array of VendingItem structures, each containing the details of a vending item.
 * @param menuSize The total number of items in the items array.
 * @pre The items array must be populated with valid vending item data.
 */
void saveItemsToCSV(VendingItem items[], int menuSize)
{
    // Open the file for writing (creates or overwrites the CSV file)
    FILE *file = fopen(CSV_FILE, "w");

    // Check if the file was successfully opened
    if (file == NULL)
    {
        perror("Error opening file for writing");
    }

    // Write the CSV header with column names
    // The columns are: Item Number, Item Name, Price (PHP), and Stock Left
    fprintf(file, "\"Item Number\",\"Item Name\",\"Price (PHP)\",\"Stock Left\"\n");

    // Loop through all items and write their details to the CSV file
    for (int i = 0; i < menuSize; i++)
    {
        // Enclose item names in double quotes to handle commas or special characters in item names
        fprintf(file, "\"%d\",\"%s\",\"%.2f\",\"%d\"\n", items[i].itemNumber, items[i].name,
                items[i].price, items[i].stock);
    }

    // Close the file after writing
    fclose(file);

    // Print confirmation message that the data has been saved successfully
    printf("Data saved to %s successfully.\n", CSV_FILE);
}
