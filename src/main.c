/*
    Description:      This program simulates a vending machine that allows the
    user to view items, insert money, and check for stock availability.
    Programmed by:    MAAGMA, RAPHAEL S17
    Last modified:    19/10/2024
    Version:          1.0
    Link:             https://github.com/Rbndct/Machine-Project
    [Acknowledgements: <list of sites or borrowed libraries and sources>]

    This is to certify that this project is my own work, based on my personal
    efforts in studying and applying the concepts learned.  I have constructed
    the functions and their respective algorithms and corresponding code by
    myself.  The program was run, tested, and debugged by my own efforts.  I
    further certify that I have not copied in part or whole or otherwise
    plagiarized the work of other students and/or persons.

    MAAGMA, RAPHAEL C., DLSU ID 12413828
*/

#include <stdio.h>
#include <string.h>
#include "vending_machine.c"

int main()
{
  // Define items in the vending machine with item numbers, names, prices, and stock counts
  VendingItem items[] = {{1, "Hotdog", 9.50, 5}, {2, "Longganisa", 20.75, 3}, {3, "Bacon", 12.00, 2}, {4, "Sausage", 35.00, 1}, {5, "Tapa", 22.50, 0}, {6, "Tocino", 18.00, 6}, {7, "Rice", 15.00, 8}, {8, "Egg", 8.00, 10}};

  int menuSize = 8; // Number of items in the menu
  float userMoney = 0;                             // Total money inserted by the user

  // Display available items
  displayItems(items, menuSize);

  // Accept money from user
  userMoneyInput(&userMoney);
  // Select Items
  selectItems(items, menuSize);
  return 0;
}