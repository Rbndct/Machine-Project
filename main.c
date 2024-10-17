#include <stdio.h>

typedef struct {
    int itemNumber;
    char name[20];
    float price;
    int stock;
}
VendingItem;

void displayItems(VendingItem items[], int);
void userMoneyInput(float * );

int main() {
    VendingItem items[] = {
        {
            1,
            "Hotdog",
            9.50,
            5
        },
        {
            2,
            "Longganisa",
            20.75,
            3
        },
        {
            3,
            "Bacon",
            12.00,
            2
        },
        {
            4,
            "Sausage",
            35.00,
            1
        },
        {
            5,
            "Tapa",
            22.50,
            0
        },
        {
            6,
            "Tocino",
            18.00,
            6
        },
        {
            7,
            "Rice",
            15.00,
            8
        },
        {
            8,
            "Egg",
            8.00,
            10
        }
    };

    int menuSize = 8;
    float userMoney;
    displayItems(items, menuSize);
    userMoneyInput( & userMoney);
}

void displayItems(VendingItem items[], int menuSize) {
    // Headers
    printf("%-12s | %-15s | %-10s | %-10s\n",
        "Item Number", "Item Name", "Price (PHP)", "Stock Left");
    printf("--------------------------------------------------------------\n");

    // Display each item
    for (int i = 0; i < menuSize; i++) {
        // Print item details with fixed-width formatting
        printf("%-12d | %-15s | %-11.2f | %-3d",
            items[i].itemNumber,
            items[i].name,
            items[i].price,
            items[i].stock);

        // Check for "Out of Stock" condition
        if (items[i].stock == 0) {
            printf(" %-12s", "Out of Stock");
        }

        printf("\n");
    }
    printf("--------------------------------------------------------------\n");
}

void userMoneyInput(float * userMoney) {
    int done = 0;
    float moneyInserted;

    printf("\t\tInsert money into the vending machine.\n");
    printf("Allowed Denominations:\n");
    printf("Bills: 20, 50, 100, 200, 500 (PHP)\n");
    printf("Coins: 1, 5, 10 (PHP), 0.25, 0.10, 0.05 (Cents)\n");

    while (!done) {
        printf("\n\nEnter the cash denomination: ");
        printf("Enter 0 when done: ");
        scanf("%f", & moneyInserted);

        if (moneyInserted == 0) {
            done = 1;
        } else if (moneyInserted == 20 || moneyInserted == 50 || moneyInserted == 100 ||
            moneyInserted == 200 || moneyInserted == 500 || moneyInserted == 1 ||
            moneyInserted == 5 || moneyInserted == 10 || moneyInserted == 0.25 ||
            moneyInserted == 0.10 || moneyInserted == 0.05) {
            * userMoney += moneyInserted;
            printf("You inserted: %.2f PHP\n", moneyInserted);
            printf("Total money inserted so far: %.2f PHP\n", * userMoney);
        } else {
            printf("Invalid denomination! Please try again.\n");
        }
    }
    printf("\nTotal money inserted: %.2f PHP\n", * userMoney);
}