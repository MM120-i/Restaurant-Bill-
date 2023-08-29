#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct items
{

    char item[20];
    float price;
    int qty;
};

struct orders
{

    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30]);
void generateBillBody(char item[30], int qty, float price);
void generateBillFooter(float total);
void generateInvoice();
void displayInvoice();
void searchInvoice();

int main()
{

    int opt, n, invoiceFound = 0;
    struct orders ord;
    struct orders order;
    float total;
    char saveBill = 'y', contFlag = 'Y';
    char name[50];
    FILE *fp;

    while (contFlag == 'Y'){
        float total = 0;
        printf("\t================ RESTURANT ================");
        printf("\n\nPlease select your prefered operation");
        printf("\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour Choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);

        switch (opt){

        case 1:

            generateInvoice();
            break;

        case 2:

            displayInvoice();
            break;

        case 3:

            searchInvoice();
            break;

        case 4:

            printf("\n\t\t Bye!\n\n");
            exit(0);
            break;

        default:

            printf("Invalid option. Please select the correct option.");
            break;
        }

        printf("Do you want to perform another operation? (Y/N)\t");
        scanf("%s", &contFlag);
        contFlag = toupper(contFlag);
    }

    printf("\n\t\t Bye!\n\n");
    printf("\n\n");

    return 0;
}

void displayInvoice(){

    FILE *fp;
    struct orders order;

    fp = fopen("ResturantBill.ram", "r");
    printf("\n   *****Your Previous Invoices*****\n");

    while (fread(&order, sizeof(struct orders), 1, fp)) {

        float total = 0.0;

        // Display the bill header
        generateBillHeader(order.customer, order.date);

        // Display the bill body and calculate total
        for (int i = 0; i < order.numOfItems; i++) {

            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
            total += order.itm[i].qty * order.itm[i].price;
        }

        // Display the bill footer
        generateBillFooter(total);
    }

    fclose(fp);
}

void searchInvoice(){

    FILE *fp;
    char name[50];
    struct orders order;
    int invoiceFound = 0;

    printf("\nEnter the name of the customer: \t");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';

    fp = fopen("ResturantBill.ram", "r");
    printf("\t   *****Invoice of %s*****", name);

    while (fread(&order, sizeof(struct orders), 1, fp)) {
        float tot = 0;

        // Check if the current order belongs to the searched customer
        int isMatchingCustomer = !strcmp(order.customer, name);
    
        if (isMatchingCustomer) {
            generateBillHeader(order.customer, order.date);

            for (int i = 0; i < order.numOfItems; i++) {
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }

        generateBillFooter(tot);
        invoiceFound = 1;
        }
    }


    if (!invoiceFound) {

        printf("The invoice for %s does not exist.\n", name);
    }

    fclose(fp);
}

void generateInvoice(){

    struct orders ord;
    int n;
    float total = 0.0;
    char saveBill = 'y';
    FILE *fp;

    // Input customer name
    printf("\nPlease enter the name of the customer:\t");
    fgets(ord.customer, sizeof(ord.customer), stdin);
    ord.customer[strcspn(ord.customer, "\n")] = '\0'; // Remove trailing newline

    // Set current date
    strcpy(ord.date, __DATE__);

    // Input number of items
    printf("\nPlease enter the number of items:\t");
    scanf("%d", &n);
    ord.numOfItems = n;

    for (int i = 0; i < n; i++) {

        char tempItem[20];  // Temporary buffer for item input

        // Clear input buffer
        while (getchar() != '\n');

        printf("\n\n");
        printf("Please enter the item %d:\t", i + 1);
        fgets(tempItem, sizeof(tempItem), stdin);
        tempItem[strcspn(tempItem, "\n")] = '\0'; // Remove trailing newline
        strcpy(ord.itm[i].item, tempItem);

        printf("Please enter the quantity:\t");
        scanf("%d", &ord.itm[i].qty);
        printf("Please enter the unit price:\t");
        scanf("%f", &ord.itm[i].price);

        total += ord.itm[i].qty * ord.itm[i].price;
    }

    generateBillHeader(ord.customer, ord.date);

    for (int i = 0; i < ord.numOfItems; i++) {

        generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
    }

    generateBillFooter(total);

    char response;
    printf("\nDo you want to save the invoice (y/n):\t");
    scanf(" %c", &response);
    response = toupper(response);

    if (response == 'Y') {

        FILE *fp = fopen("ResturantBill.ram", "a+");
        if (fp != NULL) {

            if (fwrite(&ord, sizeof(struct orders), 1, fp)) {

                fclose(fp);
                printf("\nSuccessfully saved.\n");
            }
            else {
                
                printf("\nError while saving.\n");
            }
    } 
    else {

        printf("\nError opening file for saving.\n");
    }
}

}

void generateBillHeader(char name[50], char date[30])
{

    printf("\n\n");
    printf("\t         Restaurant");
    printf("\n\t   -----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price)
{

    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%0.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total)
{

    float discount = 0.1 * total;
    float netTotal = total - discount;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst;

    printf("\n");
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", discount);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}
