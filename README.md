# Vending Machine Simulation in C

## Description
This project simulates a vending machine that allows users to:
- View available items
- Insert money in valid denominations (bills and coins)
- Select items from the machine based on availability
- Automatically update stock and calculate the total cost after each transaction

## Features (As of 20/10/2024)
- Item selection and display
- Valid cash denomination acceptance
- Real-time stock updates after each purchase
- Input validation for both item selection and cash insertion

## Planned Features

### Silog Vending Machine Features
- [ ] Void/cancellation of transaction
- [ ] Order: calculate change for the transaction
- [ ] Get/display product

### Maintenance Features
- [ ] Account/password for staff/seller
- [ ] Inventory features:
  - [ ] View stock/inventory
  - [ ] Modify the price of the menu
  - [ ] Restock inventory

### Cash Register Features
- [ ] View cash register (number of each denomination, total amount)
- [ ] Stock/restock cash register (input denominations and quantities)
- [ ] Cash out (dispense amount or input denomination and quantity, display appropriate denominations)


## How to Run
1. Clone the repository:
    ```
    git clone https://github.com/Rbndct/Machine-Project.git
    ```
2. Navigate to the project directory:
    ```
    cd Machine-Project
    ```
3. Compile the program:
    ```
    gcc -Wall -std=c99 src/main.c -o program
    ```
4. Run the executable:
    ```
    ./program
    ```


## Acknowledgements
This project was developed with the help of the following resources:
- [W3Schools C Programming](https://www.w3schools.com/c/c_intro.php)
- [Programiz C Programming](https://www.programiz.com/c-programming)
- [Devdocs.io](https://devdocs.io/c-error-handling/)


