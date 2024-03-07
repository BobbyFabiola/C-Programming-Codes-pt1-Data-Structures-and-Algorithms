/*  Author:         Fabioila C. Villanueva
    Description:    Closed Hashing in ADT Set (in-class activity) 
                    - elements and hash values are declared
    Date:           Feb 26, 2o24 (09:00am-06:30pm)
*/

#include <stdio.h>
#include <stdlib.h>

//structure definition
#define MAX 10
#define EMPTY   '~'
#define DELETED '!'
typedef char Dictionary[MAX];
typedef enum {TRUE, FALSE} Boolean;

//function prototype
void initDictionary (Dictionary D);
void displayDictionary (Dictionary D);
int hashBrown (char c);
Boolean isMember (Dictionary D, char elem);
void insertUnique (Dictionary D, char elem);                //do not invoke isMember
void deleteMember (Dictionary D, char elem);                //delete if in the dictionary
int getSearchLength (Dictionary D, char elem);             //return search length of each element         

int main ()  {
    system ("cls");
    printf("<< START >>\n\n");

    Dictionary mD;
    Dictionary dummy = {'e','f', DELETED, 'a', DELETED,'d', DELETED, DELETED, DELETED,'b'};
    int sumSL = 0;
    float av = 0;

    printf("01. INITIALIZE DICTIONARY\n");
    initDictionary (mD);
    displayDictionary (mD);

    printf("\n02. IS MEMBER\n");
    printf("\tSearch for 'g' in dummy dictionary.\n");
    if (isMember (dummy, 'g') == TRUE) {
        printf("\t[bool_1] 'g' IS a member.\n");
    } else {
        printf("\t[bool_0] 'g' is NOT a member.\n");
    }

    printf("\n03. INSERT UNIQUE\n");
    insertUnique (mD, 'a');
    insertUnique (mD, 'b');
    insertUnique (mD, 'c');
    insertUnique (mD, 'd');
    insertUnique (mD, 'e');
    insertUnique (mD, 'Z');
    insertUnique (mD, 'g');
    insertUnique (mD, 'h');
    insertUnique (mD, 'i');
    insertUnique (mD, 'j');
    displayDictionary (mD);

    printf("\n04. IS MEMBER\n");
    printf("\tSearch for 'f' in dummy dictionary.\n");
    if (isMember (dummy, 'f') == TRUE) {
        printf("\t[bool_1] 'f' IS a member.\n");
    } else {
        printf("\t[bool_0] 'f' is NOT a member.\n");
    }
    printf("\n\tSearch for 'z' in dummy dictionary.\n");
    if (isMember (dummy, 'z') == TRUE) {
        printf("\t[bool_1] 'z' IS a member.\n");
    } else {
        printf("\t[bool_0] 'z' is NOT a member.\n");
    }

    printf("\n05. DELETE MEMBER\n");
    deleteMember (mD, 'Z');
    deleteMember (mD, 'Y');
    deleteMember (mD, 'a');
    deleteMember (mD, 'd');
    deleteMember (mD, 'j');
    displayDictionary (mD);

    printf("\n06. AVERAGE SEARCH LENGTH\n");
    printf("\tELEMENT   SL\n");
    sumSL += getSearchLength (mD, 'a');
    sumSL += getSearchLength (mD, 'b');
    sumSL += getSearchLength (mD, 'c');
    sumSL += getSearchLength (mD, 'd');
    sumSL += getSearchLength (mD, 'e');
    sumSL += getSearchLength (mD, 'Z');
    sumSL += getSearchLength (mD, 'g');
    sumSL += getSearchLength (mD, 'h');
    sumSL += getSearchLength (mD, 'i');
    sumSL += getSearchLength (mD, 'j');
    av = (float) sumSL / MAX;
    printf("\tAverage SL for %d elements are = %2.2f\n", MAX, av);

    printf("\n<< END >>\n");
    return 0;
}

//function definition
void initDictionary (Dictionary D) {
    int x;
    for (x = 0; x < MAX; ++x) {
        D[x] = EMPTY;
    }
}

void displayDictionary (Dictionary D) {
    printf("\t\"IDX\"\t\"ELEMENTS\"\n");
    int x;
    for (x = 0; x < MAX; ++x) {
        printf("\t [%d]\t %c\n", x, D[x]);
    }
}

int hashBrown (char c) {
    char elements[MAX] = {"abcdeZghij"};
    int hash[MAX] = {3, 9, 4, 3, 9, 0, 1, 3, 0, 3};
    int x;
    for (x = 0; x < MAX && elements[x] != c; ++x) {}
    return hash[x];
}

Boolean isMember (Dictionary D, char elem) {
    int idx, sl;
    for (idx = hashBrown (elem), sl = 1; sl != MAX && D[idx] != elem && D[idx] != EMPTY; idx = (idx + 1) % MAX, ++sl) {}
    //keep traversing if elem not found, value is not empty, and has not gone full circle
    printf("\t%d is search length\n", sl);
    return (sl != MAX)? TRUE: FALSE;
}

void insertUnique (Dictionary D, char elem) {
    int idx, sl;
    for (idx = hashBrown (elem), sl = 1; sl != MAX && D[idx] != elem && (D[idx] != EMPTY && D[idx] != DELETED); idx = (idx + 1) % MAX, ++sl) {}
    if (sl != MAX && D[idx] != elem) {
        D[idx] = elem;
    } else {
        printf("\t%c is already in the dictionary\n", elem);
    }
}

void deleteMember (Dictionary D, char elem) {
    int idx, sl;
    for (idx = hashBrown (elem), sl = 1; sl != MAX && D[idx] != elem && (D[idx] != EMPTY || D[idx] != DELETED); ++sl, idx = (idx + 1) % MAX) {}
    if (sl != MAX && D[idx] == elem) {
        D[idx] = DELETED;
    } else {
        printf("\tThe element [%c] is not found\n", elem);
    }
}

int getSearchLength (Dictionary D, char elem) {
    int sl, idx;
    for (sl = 1, idx = hashBrown (elem); sl != MAX && D[idx] != elem; ++sl, idx = (idx + 1) % MAX) {}
    printf("\t  [%c]  =  %d\n", elem, sl);
    return sl;
}