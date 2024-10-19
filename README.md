# Vending Machine Simulation in C

## Description
This project simulates a vending machine that allows users to:
- View available items
- Insert money in valid denominations (bills and coins)
- Select items from the machine based on availability
- Automatically update stock and calculate total cost after each transaction

## Features
- Item selection and display
- Valid cash denomination acceptance
- Real-time stock updates after each purchase
- Input validation for both item selection and cash insertion

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
    gcc vending_machine.c -o vending_machine
    ```
4. Run the executable:
    ```
    ./vending_machine
    ```

## Program Structure
- **VendingItem struct**: Holds item number, name, price, and stock information for each item.
- **Functions**:
    - `displayItems()`: Displays available items.
    - `userMoneyInput()`: Handles money input and validates denominations.
    - `selectItems()`: Allows users to select items and updates stock.

## Acknowledgements
This project was developed with the help of the following resources:
- [W3Schools C Programming](https://www.w3schools.com/c/c_intro.php)
- [Programiz C Programming](https://www.programiz.com/c-programming)

## Certification
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

**MAAGMA, RAPHAEL C., DLSU ID 12413828**
