# Vending Machine Simulation in C

## Description
This project simulates a vending machine that allows users to:
- View available items
- Insert money in valid denominations (bills and coins)
- Select items from the machine based on availability
- Automatically update stock and calculate the total cost after each transaction

## Features (As of 05/11/2024)
- Item selection and display
- Valid cash denomination acceptance
- Real-time stock updates after each purchase
- Input validation for both item selection and cash insertion
- **Silog Vending Machine Features** fully implemented
- **Maintenance Features** fully implemented, allowing staff to manage inventory and pricing.

## Planned Features

### Silog Vending Machine Features
- [x] Void/cancellation of transaction
- [x] Order: calculate change for the transaction
- [x] Get/display product

### Maintenance Features
- [x] Account/password for staff/seller
- [x] Inventory features:
  - [x] View stock/inventory
  - [x] Modify the price of the menu
  - [x] Restock inventory
- [ ] Saving and loading the updated price and inventory count to a file in CSV format.

### Cash Register Features
- [ ] View cash register (number of each denomination, total amount)
- [ ] Stock/restock cash register (input denominations and quantities)
- [ ] Cash out (dispense amount or input denomination and quantity, display appropriate denominations)

## How to Run
1. Clone the repository:
    ```bash
    git clone https://github.com/Rbndct/Machine-Project.git
    ```
2. Navigate to the project directory:
    ```bash
    cd Machine-Project
    ```
3. Compile the program:
    ```bash
    gcc -Wall -std=c99 src/main.c -o program
    ```
4. Run the executable:
    ```bash
    ./program
    ```

## Acknowledgements
This project was developed with the help of the following resources:
- [W3Schools C Programming](https://www.w3schools.com/c/c_intro.php)
- [Programiz C Programming](https://www.programiz.com/c-programming)
- [Devdocs.io](https://devdocs.io/c-error-handling/)
- Lessons and videos from my Grade 12 Data Structures class at iAcademy, provided by Sir Wilson Tiu.
