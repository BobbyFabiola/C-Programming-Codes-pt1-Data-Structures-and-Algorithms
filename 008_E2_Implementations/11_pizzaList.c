/*  Author:         Fabioila C. Villanueva
    Description:    Sets and File Handling
    Date:           03/10/24 (0430pm-0549pm) to 1130pm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXORDERS   20
#define CUSTBUCKETS 10
#define MAXMENU     6

int lastOrderNumber = 10000;

typedef enum {OPEN, CLOSED} orderStatus;         //used in Closed Hashing of Orders
typedef enum {PREPARING, SERVED} pizzaStatus;
typedef unsigned char toppingsCW;               //Computer Word representation of toppings
typedef int toppingsBW[8];                      //Bit Vector representation of toppings

typedef struct{
    char pizzaName[32];
    toppingsBW pizzaToppings;
}pizzaType;

typedef struct pizzaNode{
    pizzaType P;
    pizzaStatus pStat;                  //PREPARING by default
    struct pizzaNode* nextPizza;
}pizzaNode, *pizzaList;

//structure of customer
typedef struct{
    char fName[64];
    char lName[32];
}nameDetails;

typedef struct{
    char customerID[9];
    nameDetails custName;
}customer;

//structure of node in linked list
typedef struct customerNode{
    customer C;                         //data
    struct customerNode* nextCust;      //link
}customerNode, *custList;

typedef custList cDict[CUSTBUCKETS];        //Open Hashing Representation of Customers (linked list)

typedef struct{
    int orderNumber;
    customer cust;
    pizzaList pList;
    orderStatus stat;                       //OPEN by default
}orderType;

typedef struct{
    orderType orderList[MAXORDERS];
    int numOrders;
}orderList;                                 //Closed Hashing Representation of Orders

//function prototypes
void createCustomerFile(void);
void initCustomerDict(cDict customers);
void displayCustOpenD (cDict openD);
int hashCustomer(char customerID[]);
void addNewCustomer(cDict customers, customer C);
void populateCustomers(cDict customers);
pizzaType buildPizza(char pizzaName[], toppingsCW toppings);
int hashOrder(int orderID);
void orderPizza(orderList* orders, cDict customers, char customerID[], pizzaType pizza);
void servePizza(orderList* orders, int orderNumber, char pizzaName[]);
void updateOrderStatus(orderList* orders, int orderNumber);
void displayOrderList(orderList orders);

int main(void) {
    system("cls");
	createCustomerFile();
    cDict mOpenD;
    int x;

    printf("<< 00 OPEN DICTIONARY OF CUSTOMERS >>\n");
    initCustomerDict (mOpenD);
    displayCustOpenD (mOpenD);
    
    //read from the file and pero customer insertSorted into the openDictionary via family name
    printf("\n\n<< 01 FROM FILE TO OPEN DICTIONARY >>\n");
    populateCustomers (mOpenD);
    displayCustOpenD (mOpenD);
    
    // printf("\n\n<< 02 PIZZA MENU BUILDING >>\n");
    // pizzaType P1 = buildPizza ("Hawaiian Pizza",      127);
    // pizzaType P2 = buildPizza ("Pepperoni Pizza",     127);
    // pizzaType P3 = buildPizza ("Wombo Combo Pizza",   255);
    // pizzaType P4 = buildPizza ("DaBudz Pizza",        239);
    // pizzaType P5 = buildPizza ("Channix Pizza",       129);
    // pizzaType P6 = buildPizza ("ChowLaw Pizza",       207);

    // for (x = 0; x < MAXMENU; ++x) {
    //     printf("\t%15s\t%c\n", pizzaMenu[x].pizzaName, pizzaMenu[x].pizzaToppings);
    // }


    printf("\n\n");
    return 0;
}

void createCustomerFile(void) {
    customer customers[] = {
            {"CUST001", {"SEAN ANSELMO", "ABELLANA"}},
            {"CUST002", {"VICTOR", "AGUHOB"}},
            {"CUST003", {"YEVGENY GRAZIO MARI", "ALBAÑO"}},
            {"CUST004", {"MIGUEL CARLOS", "BERINGUEL"}},
            {"CUST005", {"KARYLLE", "BERNATE"}},
            {"CUST006", {"RAYNOR", "BUHIAN"}},
            {"CUST007", {"NIÑO JAN", "CABATAS"}},
            {"CUST008", {"KENNETH JOHN", "CANTILLAS"}},
            {"CUST009", {"VINCEADE", "CENTINO"}},
            {"CUST010", {"JUN", "CHEONG"}},
            {"CUST011", {"CERIL", "HEYROSA"}},
            {"CUST012", {"JEREMIAH JACOB ANTHONY", "JUINIO"}},
            {"CUST013", {"JIWOO", "JUNG"}},
            {"CUST014", {"XANDER JACOB", "LABIDE"}},
            {"CUST015", {"ACHILLE LORENZO", "LANUTAN"}},
            {"CUST016", {"MATT VINCENT", "MAGDADARO"}},
            {"CUST017", {"GREGG ALEXANDER", "MARAYAN"}},
            {"CUST018", {"JASPER LEE", "MARBELLA"}},
            {"CUST019", {"DAN LIUS", "MONSALES"}},
            {"CUST020", {"SHAWN RYAN", "NACARIO"}},
            {"CUST021", {"SHANNEN", "NAZARENO"}},
            {"CUST022", {"OIEU ZHYDD", "NUÑEZA"}},
            {"CUST023", {"MARC NELSON", "OCHAVO"}},
            {"CUST024", {"RAY EMANUEL", "PATALINGHUG"}},
            {"CUST025", {"NATHAN ELDRIDGE MITNICK", "PERNITES"}},
            {"CUST026", {"LANCE JUSTIN", "RAMOS"}},
            {"CUST027", {"KENT JOSEPH", "RICONALLA"}},
            {"CUST028", {"JOSHUA LOUI", "SOQUEÑO"}},
            {"CUST029", {"ASHLENGAIL", "VICTOR"}},
            {"CUST030", {"MURLIWANI", "GANGARAM"}}
        };
        FILE* file = fopen("11_customers.txt", "w");
        if (file != NULL) {
            for (int i = 0; i < sizeof(customers) / sizeof(customers[0]); i++) {
                fwrite(&customers[i], sizeof(customer), 1, file);
            }
        }
        fclose(file);
}

/*
 initCustomerDict() = This function will receive as parameter a cDict, which is an array of custList (Linked List of Customers). 
 The function will initialize the dictionary by setting each element in cDict to be empty.
 */
//?
void initCustomerDict(cDict customers) {
    int x; 
    for (x = 0; x < CUSTBUCKETS; ++x) {
        customers[x] = NULL;
    }
}

//?
void displayCustOpenD (cDict openD) {
    printf("\tOPEN HASH TABLE");
    int x;
    for (x = 0; x < CUSTBUCKETS; ++x) {
        printf("\n\t[%d] = ", x);
        if (openD[x] == NULL) {
            printf("EMPTY");
        } else {
            custList trav;
            for (trav = openD[x]; trav != NULL; trav = trav->nextCust) {
                printf("%s", trav->C.customerID);
                if (trav->nextCust != NULL) {
                    printf(", ");
                }
            }
        }
    }
}

/*
 hashCustomer() = This function will receive as a parameter a customerID. 
 The function will add up the first 3 digits in the customerID and let the remainder of the sum 
 when divided by 10 be returned to the calling function.
 */
//?
int hashCustomer(char customerID[]) {
    int retVal = -1, x, size = strlen (customerID);
    for (x = size - 3, ++retVal; x < size; retVal = (retVal + customerID[x]) - '0', ++x) {}
    return retVal % 10;
}

/*
 addNewCustomer() = This function will add a new customer to the cDict given a customer record. 
 The function will only add the customer if the customer does not yet exist. Also, the customer is 
 inserted into its proper "bucket" (linked list at index N based on hash). The new customer should be 
 inserted in its proper place in the list, sorted ascending by family name.
 */
//?
void addNewCustomer(cDict customers, customer C) {
    int hashKey = hashCustomer (C.customerID);
    // printf("\thash value is of %d\n", hashKey);
    custList *trav, temp;
    temp = malloc (sizeof (customerNode));
    if (temp != NULL) {
        for (trav = &customers[hashKey]; *trav != NULL && strcmp ((*trav)->C.custName.lName, C.custName.lName) < 0; trav = &(*trav)->nextCust) {}
        temp->C = C;
        temp->nextCust = *trav;
        *trav = temp;
    }
}

/*
 populateCustomers() = This function will read a file "customers.txt", and populate the given 
 cDict with the customer records in the file. You may use the previously written functions for this function.
 */
//?
void populateCustomers(cDict customers) {
    FILE *fp = fopen("11_customers.txt", "r");
    if (fp != NULL) {
        int x;
        customer mCust;
        while (fread (&mCust, sizeof (customer), 1, fp) == 1) {
            addNewCustomer (customers, mCust);
        }  
    }
    fclose (fp);
}

/*
 buildPizza() = This function will receive as parameter a pizzaName, and a list of toppings 
 represented in computer word. Each bit in the CW representation represent the ff:
        0000 0000
        8765 4321
    1 - Pepperoni
    2 - Ham
    3 - Onions
    4 - Pineapples
    5 - Bacon
    6 - Olives
    7 - Bell Peppers
    8 - Mushrooms
    
    For example: A Hawaiian Pizza with mushrooms, pineapples, and pepperoni is represented as: 1000 0101.
                   Peperoni Pizza with ham, pepperoni, bacon, onions
                   Wombo Combo Pizza with all toppings
                   Vegetarian Pizza with onion, pineapple, olives, bell peppers, mushrooms
 
    Once the pizza record has been built, return it to the calling function.
 */
//!
pizzaType buildPizza(char pizzaName[], toppingsCW toppings) {
    pizzaType retVal;
    strcpy (retVal, pizzaName);
    unsigned mask mask = 1 << 7;
    int x;
    for (x = ; mask > 0; ++x, mask >>= 1) {

    }
    return retVal;
}

/*
 hashOrder() = The function will receive an orderID as parameter. 
 The function will take the last 4 digits of the orderID, and return the remainder when it is divided by 20.
 */
//?
int hashOrder(int orderID) {
    int retVal = -1, x;
    retVal = orderID % 10000;
    return retVal % 20;
}

/*
 orderPizza() = This function will receive an orderList, a cDict, a customerID, and a pizza to order. 
 The function will add a new order to the orderList for the given customerID and pizza record. Update 
 any fields as necessary. Only add the order if the customer exists. Resolve any collisions using linear probing.
 */
//!
void orderPizza(orderList* orders, cDict customers, char customerID[], pizzaType pizza) {
    
}

/*
 servePizza() = This function will receive an orderList, an orderNumber and a pizzaName. The function 
 will go through the given orderList and the pizzas for the specified orderNumber. If the pizza exists, 
 then update the pizzaStatus to be SERVED.
 */
void servePizza(orderList* orders, int orderNumber, char pizzaName[])
{
    
}

/*
 updateOrderStatus() = This function will receive an orderList and an orderID. The function will go through 
 the list of pizzas in the order record of the given orderID, and check if all of the pizzas have been SERVED. 
 If they have all been SERVED, then the function will update the orderStatus to CLOSED.
 */
void updateOrderStatus(orderList* orders, int orderNumber)
{
    
}

/*
 displayOrderList() = This function will go through each order in the orderList and display each of the orders in the ff: format:
 
    OrderNumber:
    Customer ID:
    Customer Name:
    Pizza Orders: pizzaName1(SERVED) -> pizzaName2(PREPARING)
    Order Status:
 */

void displayOrderList(orderList orders)
{
    
}


