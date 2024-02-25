#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//structure definition
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
    studType *studList;
    int count;
} LIST;

typedef enum {TRUE, FALSE} Boolean;

//function prototypes
Boolean initialize (LIST *L);
void display (LIST L);
void insertFirst (LIST *L, studType newStudent);
void insertAt (LIST *L, studType newStudent, int pos);
void insertLast (LIST *L, studType newStudent); 
void insertSorted (LIST *L, studType newStudent);
// void deleteFirst ();
// void deleteLast ();
// void deleteAtPos ();
// void deleteAtElem ();
// Boolean isMember ();
// studType locateElem ();

//program proper
int main () {
    system ("CLS");
    printf("<< START OF PROGRAM >>\n\n");
    LIST studRecords;
    studType unregStuds[MAX] = {                                        //data to write
        {{"Villanueva", "Fabiola", 'C'}, 22103326, 2, "BSCS"},          //0
        {{"Villanueva", "Sebastian", 'C'}, 33193326, 4, "BSCS"},        //1
        {{"Villanueva", "Augustine", 'C'}, 27183329, 2, "BS ADV"},      //2 
        {{"Tiu", "Victorienne", 'C'}, 22184457, 2, "BSCS"},             //3
        {{"Navales", "Jessalie", 'O'}, 77281932, 2, "BSCS"},            //4
        {{"Abay-abay", "Christian", 'K'}, 33183326, 4, "BSCS"},         //5
        {{"Modesto", "Mary Chevel", 'L'}, 77103382, 3, "BSCS"},         //6
        {{"Haranilla", "Hailey", 'M'}, 19173284, 3, "BSCS"},            //7
        {{"Buenavista", "Estelito", 'Y'}, 62193274, 2, "BSCS"},         //8
        {{"Sayson", "Jonaz", 'S'}, 81922103, 1, "BSCS"},                //9
    };

    //initialize the list to be ready for use 
    printf("0. INITIALIZE\n");
    if (initialize (&studRecords) == TRUE) {
        printf("\tList is successfully initialized.\n");
    }

    //display the entire list
    printf("1. DISPLAY\n");
    display (studRecords);

    printf("2. INSERT FIRST\n");
    insertFirst (&studRecords, unregStuds[0]);
    insertFirst (&studRecords, unregStuds[3]);
    insertFirst (&studRecords, unregStuds[4]);
    display (studRecords);

    printf("3. INSERT AT\n");
    insertAt (&studRecords, unregStuds[1], 1);
    insertAt (&studRecords, unregStuds[5], 4);
    insertAt (&studRecords, unregStuds[6], 3);
    insertAt (&studRecords, unregStuds[7], 9);  //invalid position; off-bounds
    display (studRecords);

    printf("2. INSERT LAST\n");
    insertLast (&studRecords, unregStuds[2]);
    insertLast (&studRecords, unregStuds[8]);
    insertLast (&studRecords, unregStuds[9]);
    display (studRecords);

    printf("2. INSERT SORTED\n");
    insertSorted (&studRecords, unregStuds[7]);
    display (studRecords);

    printf("\n<< END OF PROGRAM >>\n");
    return 0;
}

//function definitions
Boolean initialize (LIST *L) {
    L->studList = (studType *) malloc (sizeof (studType) * MAX);
    if (L->studList != NULL) {
        L->count = 0;
    }
    return (L->count == 0 && L->studList != NULL)? TRUE: FALSE;
}

void display (LIST L) {
    if (L.count != 0) {
        int x;
        printf("\n\t< STUDENT RECORDS: %d Students Registered >\n", L.count);
        for (x = 0; x < L.count; ++x) {
            printf("\t[%d] %20s %16s %c. | %10d | %2d | %8s\n", 
                    x, L.studList[x].name.LName, L.studList[x].name.FName, L.studList[x].name.Mi, L.studList[x].ID, L.studList[x].year, L.studList[x].course);
        }
        printf("\n");
    } else {
        printf("\tNo student records found!\n");
    }
}

void insertFirst (LIST *L, studType newStudent) {
    if (L->count < MAX) {                           //check if there is still available space
        int x;
        for (x = L->count++; x > 0; --x) {
            L->studList[x] = L->studList[x-1];
        }
        L->studList[0] = newStudent;
    }
}

void insertAt (LIST *L, studType newStudent, int pos) {
    if (L->count < MAX && pos >= 0 && pos <= L->count) {        //test case: if pos is equal to count then insert rear
        int x;
        for (x = L->count++; x > pos; --x) {
            L->studList[x] = L->studList[x-1];
        }
        L->studList[x] = newStudent;
    }
}
 
void insertLast (LIST *L, studType newStudent) {
    if (L->count < MAX) {
        L->studList[L->count++] = newStudent;
    }
}

void insertSorted (LIST *L, studType newStudent) {      //ascending
    if (L->count < MAX) {
        int x;
        for (x = L->count++; x > 0 && strcmp(L->studList[x].name.FName, newStudent.name.LName) > 0; --x) {
            L->studList[x+1] = L->studList[x];
        }
        L->studList[x] = newStudent;
    }
}