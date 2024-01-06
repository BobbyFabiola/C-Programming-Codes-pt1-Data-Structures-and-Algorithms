//*   Author:        Fabiola Villanueva
//*   Description:   Array List Version 01 Review w/ File Handling
//*   Date:          Dec 24, 2023

#include <stdio.h>
#include <stdlib.h>
#define MAX 20

//structure definition
typedef enum { female, male } gBool;
typedef enum { FALSE, TRUE } BOOL;

typedef struct {
   char FN[15], LN[25], MN[15];
} nameType;

typedef struct {
   nameType studName;
   int idNum;
   int yrLevel;
   char course[5];
   gBool gender;
} studType;

typedef struct {
   studType studArr[MAX];
   int count;
} LIST;

//function prototypes
BOOL initialize (LIST *L);
BOOL registerPrompt (LIST *L);
void insertStudent (LIST *L);
void inputStud (studType *entity);

int main () {
   system ("cls");
   LIST studList;

   printf("0. Initialize (List and File)\n");
   if (initialize (&studList)) {
      printf("\tSuccessfully initialized.\n");
   }

   printf("1. Create Student Record");
   while (registerPrompt (&studList));                         //while resgister prompt is true, promt will loop




   printf("\n\n");
   return 0;
}

//function defintions
BOOL initialize (LIST *L) {
   L->count = 0;
   return (L->count == 0) ? TRUE: FALSE;
}

BOOL registerPrompt (LIST *L) {                                //pass the studList as paremeters for case to register
   BOOL ans = FALSE;
   printf("\n\tRegister a student?\n\t<1-true / 0-false>: ");
   scanf("%d", &ans);
   if (ans) {
      insertStudent (L);                                       //argument of whatever L is pointing (the address of the list) == referencing the LIST L itself
   }
   return ans;
}

void insertStudent (LIST *L) {
   int idx, i;
   studType student;
   inputStud (&student);                                       //pass to populate student fields

   L->studArr[L->count++] = student;                           //insertRear
   
   //TODO implement inserted sorted via last name (if last names are equal then compare via first name)
   if (L->count < MAX) {                                       //if count is not reached the max number of elements (which is less than the actual size)
   
   }

}

void inputStud (studType *entity) {                            //function to populate an entity of studType via user input
   printf("\n\t<< Please fill in student information. >>\n");
   
   printf("\tFirst Name: ");
   fflush (stdin);
   gets (entity->studName.FN);

   printf("\tMiddle Name: ");
   fflush (stdin);
   gets (entity->studName.MN);

   printf("\tLast Name: ");
   fflush (stdin);
   gets (entity->studName.LN);

   printf("\tID Number: ");
   scanf("%d", &entity->idNum);

   printf("\tYear Level: ");
   scanf("%d", &entity->yrLevel);

   printf("\tCourse or Program: ");
   fflush (stdin);
   gets (entity->course);

   printf("\tGender <0-female / 1-male>: ");
   scanf("%d", &entity->gender);
   printf("\t<< >>\n");
}

//TODO sza test hello world