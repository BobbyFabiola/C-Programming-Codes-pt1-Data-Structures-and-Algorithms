/****************************************************************************
 *      Author:         Fabiola Villanueva                                  *
 *      Description:    Open and Closed Dictionary with Computer Word       *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//* structure definitions
typedef unsigned char studInfo;
/*Given 8 bits: 0000 0000
 
 Bits
 8    = Status:            0 - Inactive, 1 - Active
 7    = Nationality:       0 - Filipino, 1 - Foreigner
 6    = Enrollment Status: 0 - Regular, 1 - Irregular
 5    = Gender:            0 - Male, 1 - Female
 3-4  = Year Level:        00 - 1st, 01 - 2nd, 10 - 3rd, 11 - 4th
 1-2  = Program:           00 - CS, 01 - IT, 10 - IS, 11 - MATH
 
 For example:
 1001 1001 would represent an Active Regular 3rd Year Filipino Female IT Student
*/
typedef enum { TRUE, FALSE } BOOLEAN;
typedef struct {
    char studID[9];
    char firstName[15];
    char lastName[20];
    studInfo infoSet;
} studType;

typedef struct array4 {
    studType *arr;
    int count;
} arrList;

//* setting up data set functions
void initializeArrayList (arrList *arrL);
void populateDataSet (arrList *arrL);
void displayDataAL (arrList arrL);

int main () {
    arrList myStudList;
    initializeArrayList (&myStudList);
    populateDataSet (&myStudList);
    displayDataAL (myStudList);

    return 0;
}

void initializeArrayList (arrList *arrL) {

}

void populateDataSet (arrList *arrL) {

}

void displayDataAL (arrList arrL) {

}