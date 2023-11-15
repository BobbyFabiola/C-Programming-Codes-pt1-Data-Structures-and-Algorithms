/*  Author: Fabiola Villanueva
    Description: First Hands-on Open Hashing (close addressing)
    Note: A bit of exploration on the data type itself
    Date: Oct 10, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 10
#define ARR_SIZE 5

//structure definitions
typedef struct {
    int idNum;
    char FN[15];
    char LN[15];
    char MI;
    char course[5];
    int yrLvl;
    int age;
} studType;

typedef struct node {
    studType data;
    struct node *next;
} *nodePtr;

typedef nodePtr dictionary[SIZE];       //my array of head pointers to linked lists
typedef enum {FALSE, TRUE} Bool;
typedef char STRING[50];                //a string

//function prototypes
void initializeDict (dictionary *D);
void displayDict (dictionary D);
int hashKey (int num);
void insertSortedDict (dictionary *D, studType elem);
void userInput (studType *student);
Bool isMember (dictionary D, int id);
Bool deleteAtDict (dictionary *D, int id);              //deleting by the id being passed, returns TRUE if successful
nodePtr searchDict (dictionary D, int id);              //return student via id input
void displayStud (studType stud);                       //display one student only

int main() {
    system("CLS");
    dictionary studRecords;                             //array
    studType stud;
    nodePtr retStud = NULL;
    Bool ans = TRUE;
    int elem, i, choice;

    printf("0. INITIALIZE\n");
    initializeDict (&studRecords);
    displayDict (studRecords);
    printf("\n");
    system("PAUSE");
    system("CLS");

    printf("1. INSERT SORTED INTO STUDENT RECORDS\n");
    while (ans >= 1) {
        userInput (&stud);                                  //register student from user input
        insertSortedDict (&studRecords, stud);              //pass the user input as copy to be inserted into the dictionary

        printf("\n\tRegister another student?\n\t<1-yes/0-no>: ");
        scanf("%d", &ans);
    }
    system("CLS");
    displayDict (studRecords);
    printf("\n");
    system("PAUSE");
    system("CLS");

    printf("2. VERIFY REGISTRATION VIA CHECKER\n");
    printf("\n\tInput ID to check: ");
    scanf("%d", &elem);
    printf("\tValue is [%d].\n", (isMember (studRecords, elem))? 1: 0);
    printf("\t1 - found | 0 - not found\n");
    printf("\n");
    system("PAUSE");
    system("CLS");

    printf("3. REMOVE STUDENT VIA ID\n");
    printf("\n\tInput ID to remove student: ");
    scanf("%d", &elem);
    printf("\tValue is [%d].\n", (deleteAtDict (&studRecords, elem))? 1: 0);
    printf("\t1 - removed | 0 - not removed\n");
    displayDict (studRecords);
    printf("\n");
    system("PAUSE");
    system("CLS");
    
    printf("4. RETRIEVE STUDENT INFORMATION\n");
    printf("\n\tInput ID to search: ");
    scanf("%d", &elem);
    retStud = searchDict (studRecords, elem);
    if (retStud->data.idNum != 0) {                         //if retStud id is not zero, then it is populated by the returne node
        displayStud (retStud->data);
    } else {
        printf("\tStudent of ID Number does not exist.\n");
    }
    printf("\n");
    system("PAUSE");
    
    choice = 0;
    do {
        system("CLS");
        STRING menu[ARR_SIZE] = {   "Exit",
                                    "Display Student Records",
                                    "Register a Student",
                                    "Remove a Student",
                                    "Retrieve Student Info"};

        printf("5. MANIPULATION THROUGH MENU\n\n");
        for (i = 0; i < ARR_SIZE; ++i) {
            printf("\t[%d] %s\n", i, menu[i]);
        }
        printf("\tInput choice: ");
        scanf("%d", &choice);
        printf("\n");

        system("CLS");
        switch (choice) {
            case 0:
                printf("\t// [%d] %s //\n\n", choice, menu[choice]);
                printf("\tTerminating program...\n");
                break;

            case 1:
                printf("\t// [%d] %s //\n", choice, menu[choice]);
                displayDict (studRecords);
                break;
            
            case 2:
                printf("\t// [%d] %s //\n", choice, menu[choice]);
                userInput (&stud);
                insertSortedDict (&studRecords, stud);
                displayDict (studRecords);
                break;

            case 3:
                printf("\t// [%d] %s //\n", choice, menu[choice]);
                printf("\n\tInput ID to remove student: ");
                scanf("%d", &elem);
                printf("\tValue is [%d].\n", (deleteAtDict (&studRecords, elem))? 1: 0);
                printf("\t1 - removed | 0 - not removed\n");
                displayDict (studRecords);
                break;

            case 4:
                printf("\t// [%d] %s //\n", choice, menu[choice]);
                printf("\n\tInput ID to search: ");
                scanf("%d", &elem);
                retStud = searchDict (studRecords, elem);
                if (retStud->data.idNum != 0) {
                    displayStud (retStud->data);
                } else {
                    printf("\tStudent of ID Number does not exist.\n");
                }
                break;

            default:
                printf("\tInput is off menu options. Invalid.\n");
                break;
        }
        printf("\n");
        system("PAUSE");
    } while (choice != 0);

    printf("\n");
    return 0;
}

//function defintions
void initializeDict (dictionary *D) {           //visit every bucket to initialize to zero
    int i;
    for (i = 0; i < SIZE; ++i) {
        (*D)[i] = NULL;
    }
}

void displayDict (dictionary D) {
    int i;
    nodePtr trav;
    printf("\n\t<< Student Records >>");
    for (i = 0; i < SIZE; ++i) {
        printf("\n\n\t[%d]", i);
        if (D[i] == NULL) {
            printf("\n\tNULL. This bucket list is empty.", i);
        } else {
            for (trav = D[i]; trav != NULL; trav = trav->next) {
                printf("\n\t%10d | %15s, %15s %c. | %5s - %d | %d-yrs-old",            //idnum-ln-fn-mi-course-yrlvl-age
                    trav->data.idNum, trav->data.LN, trav->data.FN, trav->data.MI, trav->data.course, trav->data.yrLvl, trav->data.age);
            }
        }
    }
    printf("\n");
}

int hashKey (int num) {
    int sum = 0;
    while (num > 0)  {
        sum += num % 10;        //takes the remainder and adds it into sum
        num /= 10;              //effectively removing the last digit
    }
    return sum % SIZE;          //returns an index == key for the file cabinet
}

void userInput (studType *student) {
    printf("\n<< Input Student Information >>\n\n");
    
    printf("\tID Number: ");
    scanf("%d", &student->idNum);

    printf("\tFirst Name: ");
    fflush(stdin);
    fgets(student->FN, sizeof(student->FN), stdin);
    student->FN[strcspn(student->FN, "\n")] = '\0';
    student->FN[0] = toupper (student->FN[0]);

    printf("\tLast Name: ");
    fflush(stdin);
    fgets(student->LN, sizeof(student->LN), stdin);
    student->LN[strcspn(student->LN, "\n")] = '\0';
    student->LN[0] = toupper (student->LN[0]);

    printf("\tMiddle Initial: ");
    scanf(" %c", &student->MI);
    student->MI = toupper (student->MI);

    printf("\tAge: ");
    scanf("%d", &student->age);

    printf("\tCourse / Program: ");
    fflush(stdin);
    fgets(student->course, sizeof(student->course), stdin);
    student->course[strcspn(student->course, "\n")] = '\0';
    strupr(student->course);

    printf("\tYear Level: ");
    scanf("%d", &student->yrLvl);
    fflush(stdin);
}

void insertSortedDict (dictionary *D, studType elem) {
    int key = hashKey (elem.idNum);                         //key is now an index located in the array
    nodePtr temp = malloc (sizeof(struct node)), *trav;
    temp->data = elem;
    for (trav = &(*D)[key]; *trav != NULL && strcmp((*trav)->data.LN, temp->data.LN) < 0; trav = &(*trav)->next) {}      //comparing last name
    temp->next = *trav;
    *trav = temp;
}

Bool isMember (dictionary D, int id) {          //visit index at hash key, traverse list to browse each idNum of each node
    int key = hashKey (id);
    nodePtr trav;
    for (trav = D[key]; trav != NULL && trav->data.idNum != id; trav = trav->next) {}
    return (trav != NULL)? TRUE: FALSE;         //traverse list at key index, trav will be null if id is not found
}

Bool deleteAtDict (dictionary *D, int id) {
    Bool retVal = FALSE;
    nodePtr *trav, temp;
    if (isMember (*D, id)) {                        //if id exists then proceed to delete
        retVal = TRUE;
        int key = hashKey (id); 
        for (trav = &(*D)[key]; *trav != NULL && (*trav)->data.idNum != id; trav = &(*trav)->next) {}
        temp = *trav;
        *trav = (*trav)->next;
        free (temp);
    }
    return retVal;
}

nodePtr searchDict (dictionary D, int id) {        //return a node containing the student information
    nodePtr temp = calloc (1, sizeof (struct node));
    temp->next = NULL;
    if (isMember (D, id)) {                         //if id exists the return student
        int key = hashKey (id);
        temp->data = D[key]->data;
    }
    return temp;
}

void displayStud (studType stud) {
    printf("\tStudent of ID Number exists.\n");
        printf("\n\t[%d]", hashKey (stud.idNum));
        printf("\n\t%10d | %15s, %15s %c. | %5s - %d | %d-yrs-old\n",            //idnum-ln-fn-mi-course-yrlvl-age
                stud.idNum, stud.LN, stud.FN, stud.MI, stud.course, stud.yrLvl, stud.age);
}