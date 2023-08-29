# Restaurant-Bill-
A C program that generates that takes a restaurant order and generates the bill along with other functionalities.

Restaurant Billing System

This repository contains a simple command-line-based restaurant billing system implemented in C. 
The program enables users to perform various operations related to generating, displaying, and searching invoices for restaurant orders. The program utilizes data structures and file I/O to manage customer orders and invoices.

Features:

1) Generate Invoice: Allows users to create and save invoices for customer orders. Users can input customer information, item details, and quantities, and the program automatically calculates the total cost and applies discounts and taxes.
2) Display All Invoices: Displays previously saved invoices, including the customer's name, date, ordered items, quantities, and calculated totals. This feature provides a record of past transactions.
3) Search Invoice: Allows users to search for a specific customer's invoice by entering the customer's name. If found, the program displays the invoice details, including items, quantities, and total cost.

Usage:

1) Run the program, and it will display a menu of available options.
2) Select an operation based on the menu options:
   - Generate Invoice: Input customer information and order details.
   - Display All Invoices: View previously saved invoices.
   - Search Invoice: Find a specific invoice by entering the customer's name.
   - Exit: Terminate the program.
3) After each operation, you can choose whether to perform another operation or exit the program.

Dependencies:
- The program uses standard C libraries for input/output, string manipulation, and file operations.

Usage Example:  
$ gcc RB.c -o restaurant_billing

$ ./restaurant_billing

Note:

-The program employs a simple console interface and file storage for demonstration purposes and may not handle extensive data or complex scenarios.
- This project was inspired by ADV.LEARNING's YouTube video, which provided valuable insights and guidance during its development.

