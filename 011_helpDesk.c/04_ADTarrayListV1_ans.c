/*************************************************************************************************
 *  Author:         Fabiola Villanueva (Practice Code 002: 00_ADTfunk.c - 1st take)              *
 *  Description:    Array List Version 1 (can be modified to other versions)                     *
 *  Task:           Provide the function defintions                                              *
 *************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//* STRUCTURE DEFINITION
typedef struct {
    char LName[20], FName[16], Mi;
} nameType;

typedef struct {
    nameType name;
    int ID;
    int year;
    char course[8];
} studType;

typedef struct {
    studType studList[MAX];
    int count;
} LIST;

typedef enum {TRUE, FALSE} Boolean;

//* FUNCTION PROTOTYPES
Boolean initializeList (LIST *L);
void display (LIST L);
void insertSorted (LIST *L, studType newStudent);
void insertFirst (LIST *L, studType newStudent);
void insertAt (LIST *L, studType newStudent, int pos);
void insertLast (LIST *L, studType newStudent); 
void deleteFirst (LIST *L);
void deleteLast (LIST *L);
void deleteAtPos (LIST *L, int pos);
void deleteAtElem (LIST *L, char LName[]);
Boolean isMember (LIST *L, char LName[]);
studType locateElem (LIST *L, int idx);

//* NO NEED TO TOUCH MAIN
int main () {
    system ("CLS");
    printf("<< START OF PROGRAM >>\n\n");
    printf("PROBLEM 01 :: INSERT SORTED FUNCTION\n");
    printf("_____________\n\n");

    LIST studRecords;
    studType unregStuds[MAX] = {
        {{"Smith",       "John",        'A'}, 33193326, 1, "CSIT"},     //0
        {{"Doe",         "Jane",        'B'}, 27183329, 3, "MATH"},     //1 
        {{"Brown",       "Emily",       'C'}, 22103326, 2, "PHYS"},     //2
        {{"Johnson",     "Michael",     'D'}, 22184457, 4, "CHEM"},     //3
        {{"Miller",      "Sarah",       'E'}, 77281932, 4, "BIOL"},     //4
        {{"Davis",       "James",       'F'}, 33183326, 3, "ENGL"},     //5
        {{"Garcia",      "Laura",       'G'}, 77103382, 1, "HIST"},     //6
        {{"Martinez",    "Robert",      'H'}, 19173284, 1, "ARTS"},     //7
        {{"Anderson",    "Linda",       'I'}, 62193274, 2, "MUSC"},     //8
        {{"Thomas",      "William",     'J'}, 81922103, 3, "ECON"},     //9
    };

    printf("INITIALIZE\n");
    if (initializeList (&studRecords) == TRUE) {
        printf("\tList is successfully initialized.\n");
    }

    printf("\nDISPLAY TEST\n");
    printf("\tNo student has been inserted into the list.\n");
    display (studRecords);

    printf("\nINSERT SORTED & DISPLAY\n");
    insertSorted (&studRecords, unregStuds[4]);
    insertSorted (&studRecords, unregStuds[5]);
    insertSorted (&studRecords, unregStuds[6]);
    insertSorted (&studRecords, unregStuds[7]);
    insertSorted (&studRecords, unregStuds[8]);
    insertSorted (&studRecords, unregStuds[9]);
    display (studRecords);

    system("PAUSE");
    system ("CLS");
    printf("PROBLEM 02 :: OTHER INSERT FUNCTIONS\n");
    printf("_____________\n\n");

    printf("INSERT FIRST\n");
    insertFirst (&studRecords, unregStuds[0]);
    printf("INSERT AT\n");
    insertAt (&studRecords, unregStuds[1], 5);
    printf("INSERT LAST\n");
    insertLast (&studRecords, unregStuds[2]);
    display (studRecords);

    system("PAUSE");
    system ("CLS");
    printf("PROBLEM 03 :: DELETE FUNCTIONS\n");
    printf("_____________\n\n");



    system("PAUSE");
    system ("CLS");
    printf("PROBLEM 03 :: SEARCH FUNCTIONS\n");
    printf("_____________\n\n");


    printf("\n<< END OF PROGRAM >>\n");
    return 0;
}

//*FUNCTION DEFINITIONS

/*************************************************************************************************
 *  "initialize" function specs:                                                                 *
 *  The function shall initialize the list ready for use. Take note, the elements to be          *
 *  initialized will depend on the structure of your list.                                       *
 *************************************************************************************************/
Boolean initializeList (LIST *L) {
    //! start coding here

    L->count = 0;
    return (L->count == 0) ? TRUE: FALSE;
}

void display (LIST L) {
    //! start coding here

    if (L.count != 0) {
        int x;
        printf("\n\t< STUDENT RECORDS: %d Students Registered >\n", L.count);
        for (x = 0; x < L.count; ++x) {
            printf("\t[%d] %15s %10s %c. | %10d | year %2d | %8s\n", 
                    x, L.studList[x].name.LName, L.studList[x].name.FName, L.studList[x].name.Mi, L.studList[x].ID, L.studList[x].year, L.studList[x].course);
        }
        printf("\n");
    } else {
        printf("\tNo student records found!\n");
    }
}

void insertSorted (LIST *L, studType newStudent) {      //ascending
    //! start coding here

    if (L->count < MAX) {
        int x;
        for (x = L->count; x > 0 && strcmp(L->studList[x-1].name.LName, newStudent.name.LName) > 0; --x) {
            L->studList[x] = L->studList[x-1];
        }
        L->studList[x] = newStudent;
        L->count++;
        printf("\tInserted successfully!\n");
    } else {
        printf("\tInsertion failed!\n");
    }
}

void insertFirst (LIST *L, studType newStudent) {
    //! start coding here

    if (L->count < MAX) {                           //check if there is still available space
        int x;
        for (x = L->count++; x > 0; --x) {
            L->studList[x] = L->studList[x-1];
        }
        L->studList[0] = newStudent;
        printf("\tInserted successfully!\n");
    } else {
        printf("\tInsertion failed!\n");
    }
}

void insertAt (LIST *L, studType newStudent, int pos) {
    //! start coding here

    if (L->count < MAX && pos >= 0 && pos <= L->count) {        //test case: if pos is equal to count then insert rear
        int x;
        for (x = L->count++; x > pos; --x) {
            L->studList[x] = L->studList[x-1];
        }
        L->studList[x] = newStudent;
        printf("\tInserted successfully!\n");
    } else {
        printf("\tInsertion failed!\n");
    }
}
 
void insertLast (LIST *L, studType newStudent) {
    //! start coding here

    Boolean ret = FALSE;
    if (L->count < MAX) {
        L->studList[L->count++] = newStudent;
        printf("\tInserted successfully!\n");
    } else {
        printf("\tInsertion failed!\n");
    }
}

void deleteFirst (LIST *L) {
    //! start coding here


}

void deleteLast (LIST *L) {
    //! start coding here


}

void deleteAtPos (LIST *L, int pos) {
    //! start coding here


}

void deleteAtElem (LIST *L, char LName[]) {
    //! start coding here


}

Boolean isMember (LIST *L, char LName[]) {
    //! start coding here


}

studType locateElem (LIST *L, int idx) {
    //! start coding here


}
