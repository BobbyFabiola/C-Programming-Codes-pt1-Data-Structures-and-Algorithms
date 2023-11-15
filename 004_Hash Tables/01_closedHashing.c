/*  Author: Fabiola Villanueva
    Description: First Hands-on Closed Hashing (open addressing)
                    A list of students in a classroom
    Note: A bit of exploration on the data type itself
    Date: Oct 12, 2023
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMPTY -1
#define DELETED -99
#define OCCUPIED 0
#define REC_SIZE 10

typedef struct {
    int status;
    int idNum;
    char FN[15];
    char LN[15];
    char MI;
    char course[5];
    int yrLvl;
    int age;
} studType;

typedef studType Dictionary[REC_SIZE];
typedef enum {FALSE, TRUE} Bool;

//function prototypes
void initializeDict (Dictionary *D);
void displayDict (Dictionary D);
void userInput (studType *newStud);
int hashKey (studType num);                                  //get index by adding all members  % size
void insertIntoDict (Dictionary *D, studType elem);
Bool isMember (Dictionary D, int num);
void deleteFromDict (Dictionary D, int num);
void writeIntoFile (Dictionary D);

int main() {
    system("CLS");
    Dictionary classRec;            //studType arrray/ student record in heap
    studType student; 
    Bool ans = TRUE;
    int elem, i;

    printf("0. INITIALIZE\n");
    initializeDict (&classRec);
    displayDict (classRec);
    printf("\n\t");
    system("PAUSE");
    system("CLS");

    printf("1. REGISTER A STUDENT\n");
    while (ans >= 1) {
        userInput (&student);                                   //register student from user input
        insertIntoDict (&classRec, student);                    //pass the user input as copy to be inserted into the dictionary

        printf("\n\tRegister another student?\n\t<1-yes/0-no>: ");
        scanf("%d", &ans);
    }
    displayDict (classRec);
    printf("\n\t");
    system("PAUSE");
    system("CLS");

    printf("2. CHECK IF STUDENT IS REGISTERED\n");
    printf("\n\tInput ID to check: ");
    scanf("%d", &elem);
    printf("\tValue is [%d].\n", (isMember (classRec, elem)));
    printf("\t1 - found | 0 - not found\n");
    printf("\n\t");
    system("PAUSE");
    system("CLS");

    printf("3. REMOVE A STUDENT\n");
    displayDict (classRec);
    printf("\n\tInput Student ID to Remove: ");
    scanf("%d", &elem);
    deleteFromDict (classRec, elem);
    displayDict (classRec);

    printf("\n");
    return 0;
}

//function definition
void initializeDict (Dictionary *D) {           //initialize buckets to empty
    int i;                                      //i used idnum to initiaize to a value
    for (i = 0; i < REC_SIZE; ++i) {
        (*D)[i].status = EMPTY;
    }
}

void displayDict (Dictionary D) {
    int i;
    printf("\n\t<< REGISTERED STUDENTS >>\n");
    printf("\tIDX - STATUS\n");
    for (i = 0; i < REC_SIZE; ++i) {
        if ( D[i].status == -1) {
            printf("\t%d   [ EMPTY ]\n", i);
        } else if ( D[i].status == -99) {
            printf("\t%d   [ DELETED ]\n", i);
        } else {
            printf("\t%d   [ OCCUPIED ] = %8d | %15s, %15s %c. | %5s - %d | %d-yrs-old\n", 
                    i, D[i].idNum, D[i].LN, D[i].FN, D[i].MI, D[i].course, D[i].yrLvl, D[i].age);
        }
    }
}

void userInput (studType *newStud) {
    printf("\n<< Input Student Information >>\n\n");
    newStud->status = OCCUPIED;
    
    printf("\tID Number: ");
    scanf("%d", &newStud->idNum);

    printf("\tFirst Name: ");
    fflush(stdin);
    fgets(newStud->FN, sizeof(newStud->FN), stdin);
    newStud->FN[strcspn(newStud->FN, "\n")] = '\0';
    newStud->FN[0] = toupper (newStud->FN[0]);

    printf("\tLast Name: ");
    fflush(stdin);
    fgets(newStud->LN, sizeof(newStud->LN), stdin);
    newStud->LN[strcspn(newStud->LN, "\n")] = '\0';
    newStud->LN[0] = toupper (newStud->LN[0]);

    printf("\tMiddle Initial: ");
    scanf(" %c", &newStud->MI);
    newStud->MI = toupper (newStud->MI);

    printf("\tAge: ");
    scanf("%d", &newStud->age);

    printf("\tCourse / Program: ");
    fflush(stdin);
    fgets(newStud->course, sizeof(newStud->course), stdin);
    newStud->course[strcspn(newStud->course, "\n")] = '\0';
    strupr(newStud->course);

    printf("\tYear Level: ");
    scanf("%d", &newStud->yrLvl);
    fflush(stdin);
}

void insertIntoDict (Dictionary *D, studType elem)  {
    int key = hashKey (elem), i, count = 0;
    printf("\tHash Key = %d\n", key);                   //<=== debugger ===>

    for (i = (key) % REC_SIZE; count < REC_SIZE && (*D)[i].status != EMPTY && (*D)[i].status != DELETED; i = (++i) % REC_SIZE, ++count) {}  //we start traversing from index hashkey, count starts at zero to keep us
    if (count == REC_SIZE) {                                                                                                                //traversing "n" amount of times, cell check conditions if the cell is EMPTY or DELETED,
        printf("\tAll buckets are OCCUPIED. List is FULL.\n");                                                                              //we insert if cell is EMPTY or DELETED, the update keeps us going
    } else {                                                                                                                                //- starts back at zero if continues after last index
        (*D)[i] = elem;
    }
}

int hashKey (studType num) {                            //get the sum of all members and modulo to arr size
    int sum = 0;
    while (num.idNum > 0) {
        sum += num.idNum % 10;
        num.idNum /= 10;
    }
    sum = sum + strlen (num.FN) + strlen (num.LN) + num.MI + strlen (num.course) + num.yrLvl + num.age;
    return sum % REC_SIZE;
}

Bool isMember (Dictionary D, int num) {
    int i, key;
    for (i = 0; i < REC_SIZE && D[i].idNum != num; ++i) {}
    return (i != REC_SIZE)? TRUE: FALSE;
}

void deleteFromDict (Dictionary D, int num) {
    int i, key;
    if (isMember (D, num)) {
    for (i = 0; i < REC_SIZE && D[i].idNum != num; ++i) {}
        if (i != REC_SIZE) {
            key = hashKey (D[i]);
            D[key].status = DELETED;
        } else {
            printf("\tStudent does not exist.\n");
        }
    }
}

void writeIntoFile (Dictionary D) {
    Dictionary buffer;
    FILE *fp;
    int i;
    fp = fopen ("010_closedHashbrown.txt", "wb");
    if (fp != NULL) {
        for (i = 0; i < REC_SIZE; ++i) {
            fread (buffer, sizeof (studType), 1, fp);
        }
    }
    fclose (fp);
}