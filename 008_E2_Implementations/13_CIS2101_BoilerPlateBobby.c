/***************************************************************************
 * Name:    Fabiola Villanueva                                             *
 * Date:    March 20, 2024                                                 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMPROGRAMS 4
#define YEARLEVELS  4
#define MAXSTUDS    100

//Data Structure Definition
typedef struct{
    char fName[64];
    char mi;
    char lName[32];
}studName;

typedef unsigned char personalInfo;
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

typedef struct{
    char idNum[9];
    studName name;
    personalInfo info;
}student;

typedef struct{
    student studs[MAXSTUDS];
    int numStuds;
}arrListStud;



typedef struct studNode{
    student stud;
    struct studNode* next;
}studNode, *studLL;

typedef studLL studDict[YEARLEVELS];

typedef struct{
    studDict programStuds;
    int studCtr;               /* refers to the total number of students in the PROGRAM. */
}dcismNode;

typedef dcismNode dcismDict[NUMPROGRAMS];

typedef struct{
    char studID[9];
    studName sName;
    personalInfo info;
}studRec;

typedef struct{
    studRec studs[MAXSTUDS];
    int count;
}sNode, *studSet;               /* array representation of a Set of studRecs */

//Function Prototypes
//? DONE
//-----Problem #1 Prototypes-----
arrListStud populateStudentList(void);
void generateStudentFile(void);
char* getProgram(personalInfo I);                                   
int yearLevelHash(personalInfo I);                                   
void displayArrListStud(arrListStud A);

//? DONE
//------Problem #2 Prototypes
int programHash(personalInfo I);
int insertStudLL(studLL* SL, student S);
void initDCISMDict(dcismDict D);
void convertToDCISMDict(dcismDict D, arrListStud SL); 
void displayStudLL(studLL SL) ; 
void displayDCISMDict(dcismDict D);

//!
//------Problem #3 Prototypes
studSet* initStudSet(void);
void insertStudSet(studSet S, studRec sRecord);
studSet* removeInactiveStudents(dcismDict D);															  		    
void displayStudSets(studSet S[]);
																			                         
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   0)  CHANGE the name of the file to:  CIS2101_YourlastNameXX.c                  *
                                     XX is the first 2 letters of your firstname    *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/                         
int main(void) {
    printf("\n\n\n<< START >>\n\n");
    /*-------------------------------------------------------------------------
    * 	Problem #1  :: 1) Populate the list by calling populateStudentList   *
    *                   2) Calls displayArrListStud()                        *
    *------------------------------------------------------------------------*/	
    printf("Problem #1:: ");
    printf("\n------------\n");

    arrListStud mAL = populateStudentList ();
    displayArrListStud (mAL);
        
    
    /*-------------------------------------------------------------------------
    * 	Problem #2  :: 1) Call initDCISMDict()                                *
    *                   2) Call convertToDCISMDict()                          *
    *                   3) Call displayDCISMDict()                            *
    *------------------------------------------------------------------------*/	    
    printf("\n\n\nProblem #2:: ");
    printf("\n------------\n");

    dcismDict mD;
    initDCISMDict (mD);
    convertToDCISMDict (mD, mAL);
    displayDCISMDict (mD);
    
  
    /*-------------------------------------------------------------------------
    * 	Problem #3  :: 1) Call removeInactiveStudents() passing dcismDict in  *
    *                          problem #2                                     *
    *                   2) Call displayDCISMDict(D);                          *
    *                   3) Call displayStudSets(inactive);                    *
    *------------------------------------------------------------------------*/	  
    printf("\n\n\nProblem #3:: ");
    printf("\n------------\n");

    studSet *mSet = removeInactiveStudents (mD);        
    // displayDCISMDict (mD);                           //! does not display but remove function works
    displayStudSets (mSet);

    printf("\n\n<< END >>\n\n\n");
    return 0;
}                                  
                                       
//? DONE
/*****************************************************************************************
 *  Functions for Problem # 1                                                            *
 *****************************************************************************************/      
//-----------------------------------------------------------------------------------------
// populateStudentList(). The function will read a file containing student records and   
// returns the student records to the calling function in the form of an arrListStud..
//
// PARTIAL CODE is provide.
//-----------------------------------------------------------------------------------------
arrListStud populateStudentList(void) {
    FILE* fp;
    student* studs;
    int dataCount;
    arrListStud retVal = {.numStuds = 0};
    
    if((fp = fopen("students.bin", "rb"))== NULL){
        puts("Unsuccessful in opening students.txt");
    }else{
        fseek(fp, 0, 2);
        dataCount = (int) ftell(fp) / sizeof(student);
        studs = (student*) malloc (sizeof(student) * dataCount);
        if(studs != NULL){
            fseek(fp, 0, 0);
            fread(studs, sizeof(student), dataCount, fp);
        }
        
		//Put your CODE here
        int x;
        for (x = 0; x < MAXSTUDS && x < dataCount; ++x) {
            retVal.studs[x] = studs[x];
            retVal.numStuds++;
        }
        fclose (fp);
    }
    return retVal;
}

//-----------------------------------------------------------------------------------------
// getProgram(). Return the string equivalent of the program of the provided personalInfo.
//-----------------------------------------------------------------------------------------
char* getProgram(personalInfo I) {
    //Write your code here 
    char *program = malloc (sizeof (char) * 7);
    if (program != NULL) {
        int num = I & 3;
        switch (num) {
            case 0:
                strcpy (program, "BSCS");
                break;
            case 1:
                strcpy (program, "BSIT");
                break;
            case 2:
                strcpy (program, "BSIS");
                break;
            case 3:
                strcpy (program, "BSMATH");
                break;
            default:
                strcpy (program, " ");
        }
    }
    return program;
}

//-----------------------------------------------------------------------------------------
// programHash(). Returns the integer equivalent of the bits that represent a student's program.
//-----------------------------------------------------------------------------------------
int yearLevelHash(personalInfo I) {
    //Write your code here
    return (((I & 12) >> 2) + 1) % YEARLEVELS;      //sauce from prof 
}

//---------------------------------------------------------------------------------------------
// displayArrListStud(). Displays the ID, Firstname, Lastname, Program (course) and year level.
//  Calls getProgram() and yearLevelHash() to determine the Program and year level.
//
//  PARTIAL CODE is provided
//-----------------------------------------------------------------------------------------
void displayArrListStud(arrListStud A) {
    int x;
    
    printf("%-15s", "IDNumber");
    printf("%-15s", "FName");
    printf("%-15s", "LName");
    printf("%-15s", "Program");         //Program and Year should be included in the display, though
    printf("%s\n", "Year");             //   it is not included in the sample display.
     
    //Write your code here.   
    for (x = 0; x < A.numStuds; ++x) {
        printf("%-14s ", A.studs[x].idNum);
        printf("%-14s ", A.studs[x].name.fName);
        printf("%-14s ", A.studs[x].name.lName);
        printf("%-14s ", getProgram (A.studs[x].info));
        printf("%d\n", yearLevelHash (A.studs[x].info));
    }
    printf("\nNum of Students: %d\n", A.numStuds);
}

//? DONE
/*****************************************************************************************
 *  Functions for Problem # 2                                                            *
 *****************************************************************************************/      
//-----------------------------------------------------------------------------------------
// programHash(). Returns the integer equivalent of the bits that represent a student's program.
//-----------------------------------------------------------------------------------------
int programHash(personalInfo I) {
    //Write your code
    return (I & 3) % NUMPROGRAMS;
}


//-----------------------------------------------------------------------------------------
// insertStudLL(). Inserts into the sorted studSet based on the student's ID number.
//  All elements in the studLL should be unique. The function will return 1 if the insert was successful and 0 if not.
//-----------------------------------------------------------------------------------------

int insertStudLL(studLL* SL, student S) {
    //Write your code
    int val = 0;
    studLL *trav, temp;
    for (trav = SL; *trav != NULL && strcmp ((*trav)->stud.idNum, S.idNum) < 0; trav = &(*trav)->next) {}
    if (*trav == NULL || strcmp ((*trav)->stud.idNum, S.idNum) != 0) {      //if there are elements and not unique == FALSE/no insert
        temp = (studLL) malloc (sizeof (studNode));
        if (temp != NULL) {
            temp->stud = S;
            temp->next = *trav;
            *trav = temp;
            val = 1;
        }
    }
    return val;
}


//-----------------------------------------------------------------------------------------
// displayStudLL(). The function will display the contents of a given studLL.
//-----------------------------------------------------------------------------------------
void displayStudLL(studLL SL) {
    if(SL != NULL){
        printf("\nYear %d\n\n", yearLevelHash (SL->stud.info) + 1);        //Complete the code and Uncomment
        printf("%-13s", "IDNumber");
        printf("%-13s", "FName");
        printf("%-13s", "LName");
        printf("%-13s", "Program");
        printf("%-10s", "Year");
        printf("%-13s", "Gender");
        printf("%-13s", "Enrollment");
        printf("%-13s", "Nationality");
        printf("%-13s\n", "Status");
        
        //Write your code here  
        personalInfo mask = 1 << (sizeof (personalInfo) * 8) - 1;           // << 7
        for (; SL != NULL; SL = SL->next) {
            printf("%-13s", SL->stud.idNum);
            printf("%-13s", SL->stud.name.fName);
            printf("%-13s", SL->stud.name.lName);
            printf("%-13s", getProgram (SL->stud.info));
            printf("%-10d", yearLevelHash (SL->stud.info) + 1);
            printf("%-13s", (SL->stud.info & (mask >> 3))? "Female": "Male");
            printf("%-13s", (SL->stud.info & (mask >> 2))? "Irregular": "Regular");
            printf("%-13s", (SL->stud.info & (mask >> 1))? "Foreigner": "Filipino");
            printf("%-13s\n", (SL->stud.info & mask)? "Active": "Inactive");
        }
    }
}

//-----------------------------------------------------------------------------------------
// initDCISMDict(). The function will initialize the given  dcismDict to be empty
//-----------------------------------------------------------------------------------------
void initDCISMDict(dcismDict D) {
    //Write your code here
    int x, n;
    for (x = 0; x < NUMPROGRAMS; ++x) {
        D[x].studCtr = 0;
        for (n = 0; n < YEARLEVELS; ++n) {
            D[x].programStuds[n] = NULL;
        }
    }

    //test
    // printf("\nDCISM DICTIONARY INIT TEST");
    // for (x = 0; x < NUMPROGRAMS; ++x) {
    //     printf("\n[%d]", x);
    //     for (n = 0; n < YEARLEVELS; ++n) {
    //         if (D[x].programStuds[n] == NULL) {
    //             printf("NULL ");
    //         }
    //     }
    // }
    // printf("\n\n");
}


//-----------------------------------------------------------------------------------------
// convertToDCISMDict(). The function will go through list of students and insert them to their proper place in the dcismDict.
//-----------------------------------------------------------------------------------------
void convertToDCISMDict(dcismDict D, arrListStud SL) {
    //Write your code here
    int x, progH, yrH;
    for (x = 0; x < SL.numStuds; ++x) {
        progH = programHash (SL.studs[x].info);
        yrH = yearLevelHash (SL.studs[x].info);
        if (insertStudLL (&(D[progH].programStuds[yrH]), SL.studs[x]) == 1) {
            D[progH].studCtr++;
        } else {
            printf("Student %s already exists.\n", SL.studs[x].idNum);
        }
    }
}



//-----------------------------------------------------------------------------------------
// displayDCISMDict(). The function will display all the students in the dcismDict by program and year level.
//-----------------------------------------------------------------------------------------
void displayDCISMDict(dcismDict D) {
    int x, n;
    printf("\n<< DCISM DICTIONARY >>\n");
    for(x = 0; x < NUMPROGRAMS; ++x){
        printf("--------------------------------------------------------------------------------------------------------------\n%s of %d Students\n", getProgram (D[x].programStuds[0]->stud.info),D[x].studCtr);  //Complete code and uncomment
        for( n = 0; n < YEARLEVELS; ++n){
            displayStudLL (D[x].programStuds[n]);
        }
    }
}

//!
/*****************************************************************************************
 *  Functions for Problem # 3                                                            *
 *****************************************************************************************/      
//-----------------------------------------------------------------------------------------
// initStudSet(). The functions initialize an empty array of studSets that can accommodate the total number of programs.
//-----------------------------------------------------------------------------------------
studSet* initStudSet(void) {
    //Write your code here
    studSet *setPtr = (studSet *) malloc (sizeof (studSet) * NUMPROGRAMS);  //arrayy of studSet or pointers to a structure
    if (setPtr != NULL) {
        int x;
        for (x = 0; x < NUMPROGRAMS; ++x) {
            setPtr[x] = (studSet) malloc (sizeof (sNode));
            if (setPtr[x] != NULL) {
                setPtr[x]->count = 0;
            }
        }
    }
    return setPtr;
}


//-----------------------------------------------------------------------------------------
// insertStudSet(). The function will insert the studRec into the studSet. Student will be inserted at the end of the set.
//-----------------------------------------------------------------------------------------
void insertStudSet(studSet S, studRec sRecord) {
    //Write your code here
    if (S->count < MAXSTUDS) {
        S->studs[S->count++] = sRecord;
    }
}


//-----------------------------------------------------------------------------------------
// removeInactiveStudents(). The function will delete all student records that have the status "inactive".
// Deleted records will be stored in an array of studSets, such that each deleted student will be stored
// in its proper index in the array of studSets based on their program. Return the array of studSets to the calling function.
//-----------------------------------------------------------------------------------------
studSet * removeInactiveStudents(dcismDict D) {
    //Write your code here
    studSet *lSet = initStudSet();      //array of studSets
    if (lSet != NULL) {
        int x, n;
        for (x = 0; x < NUMPROGRAMS; ++x) {         //x is the program
            for (n = 0; n < YEARLEVELS; ++n) {      //n is the year level
                studLL *trav, temp;
                
                for (trav = &(D[x].programStuds[n]); *trav != NULL;) {
                    personalInfo mask = 1 << (sizeof (personalInfo) * 8)-1;
                    if ((*trav)->stud.info & mask) {
                        trav = &(*trav)->next;
                    } else {
                        temp = *trav;
                        *trav = temp->next;
                        
                        studRec SR;
                        strcpy (SR.studID, temp->stud.idNum);
                        SR.sName = temp->stud.name;
                        SR.info = temp->stud.info;
                        
                        insertStudSet (lSet[x], SR);
                        (D[x].studCtr)--;
                        free(temp);
                    }
                }
            }
        }
    }
    return lSet;
}

 
 
/**********************************************************************************
 *  Displays the ID, Firstname and Lastname of inactive students for each program. *
 **********************************************************************************/
void displayStudSets(studSet S[]) {
    //Write your code 
    printf("\n<< STUDSET OF INACTIVE STUDENTS >>\n");
    printf("--------------------------------------------------------------------------------------------------------------\n");
    printf("%-13s", "IDNumber");
    printf("%-13s", "FName");
    printf("%-13s", "LName");
    printf("%-13s\n", "Status");
    int x, n;
    for (x = 0; x < NUMPROGRAMS; ++x) {
        printf("\n[%d]", x);
        for (n = 0; n < S[x]->count; ++n) {
            printf("\n%-13s", S[x]->studs[n].studID);
            printf("%-13s", S[x]->studs[n].sName.fName);
            printf("%-13s", S[x]->studs[n].sName.lName);
            printf("%-13s", (S[x]->studs[n].info & 1 << (sizeof (personalInfo) * 8) - 1)? "Active": "Inactive");
        }
        printf("\nCount: %d\n", S[x]->count);
    }   
}