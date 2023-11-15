#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char STRING[30];

//structure definitions
typedef struct {
	STRING lName;
	STRING fName;
	char MI;
} name_Type;

typedef struct {
	name_Type studName;
	STRING course;
	int year;
	int id;
} stud_Data;

typedef struct node {
	stud_Data data;
	struct node *next;
} studType, *studPtr;

//function prototypes
void enrollStuds (studPtr *studList);
void displayStuds (studPtr studList);
void retGradDcismStuds (studPtr *studList, studPtr *gradList);

int main() {
	system("CLS");
	studPtr dcismList = NULL; 		//empty list
	studPtr gradList = NULL;		//empty list
	int count = 0, choice, i;
	STRING menu[4] = {  "Exit",
                        "Enroll Student/s",
                        "Display Student/s",
                        "Graduating Student/s"};

    do {
        printf("Welcome to DCISM!\n\n");
        for (i = 0; i < 4; ++i) {
            printf("[%d]  %s\n", i, menu[i]);
        }
        printf("\nSelect a number <0 to EXIT>: ");
        scanf("%d", &choice);

        system("PAUSE");
        system("CLS");

        switch (choice) {
            case 0:
                printf("\"EXIT\"\n");
                printf("Terminating program...\nThank you.\n\n");

                break;
            
            case 1:
                printf("\"ENROLL STUDENT/S\"\n");
                enrollStuds (&dcismList);

                printf("\n\n");
                system("PAUSE");
                system("CLS");
                break;

            case 2:
                printf("\"DISPLAY LIST\"\n");
                printf("\nStudents Enrolled:");
                displayStuds (dcismList);


                printf("\n\n");
                system("PAUSE");
                system("CLS");
                break;
            
            case 3:
                printf("\"RETRIEVE GRADUATES\"\n");
                retGradDcismStuds (&dcismList, &gradList);
                printf("\nGraduating Students:");
                displayStuds (gradList);
                printf("\n\nStudents Enrolled:");
                displayStuds (dcismList);

                printf("\n\n");
                system("PAUSE");
                system("CLS");
                break;

            default:
                printf("\"ERROR\"\n");
                printf("Invalid input. Try again.");

                printf("\n\n");
                system("PAUSE");
                system("CLS");
                break;
        }

    } while (choice != 0);
	
	return 0;
}

//function definitons
void enrollStuds (studPtr *studList) {
	studPtr temp = (studPtr) malloc(sizeof (studType));
    stud_Data newStud;
    studPtr *trav;
	
	if (temp != NULL) {									//successfull allocation
		printf("\n\tNAME\n");							//populating temp data
		printf("\tLast Name: ");
        fflush(stdin);
        fgets(newStud.studName.lName, sizeof(newStud.studName.lName), stdin);
        newStud.studName.lName[strcspn(newStud.studName.lName, "\n")] = '\0';
		printf("\tFirst Name: ");
        fflush(stdin);
        fgets(newStud.studName.fName, sizeof(newStud.studName.fName), stdin);
        newStud.studName.fName[strcspn(newStud.studName.fName, "\n")] = '\0';
		printf("\tMiddle Initial: ");
		scanf("%c", &newStud.studName.MI);
		
		printf("\tStudent ID: ");
		scanf("%d", &newStud.id);
		printf("\tCourse: ");
		fflush(stdin);
		gets(newStud.course);
		printf("\tYear: ");
		scanf("%d", &newStud.year);
		
        temp->data = newStud;
        temp->next = NULL;                                  //pre assigning temp to point to NULL

        for (trav = studList; (*trav) != NULL; trav = &(*trav)->next) {}

        if ((*trav) == NULL) {
            temp->next = (*trav);
            (*trav) = temp;
        }
	}
}

void displayStuds (studPtr list) {
	int i = 0;
	
	while (list != NULL) {
		printf("\n[%d]", i++);
        printf("  ID: %d", list->data.id);
		printf("\n     Name: %s %c. %s", list->data.studName.fName, toupper (list->data.studName.MI), list->data.studName.lName);
		printf("\n     Course: %s", strupr(list->data.course));
		printf("\n     Year: %d", list->data.year);
		
		list = list->next;
	}
}

void retGradDcismStuds (studPtr *studList, studPtr *gradList) {
    studPtr *trav, temp;                                //temp is node pointer

    for (trav = studList; (*trav) != NULL;) {           //exits loop if year == 4
        if ((*trav)->data.year == 4 && (strcmp(strupr((*trav)->data.course), "BSCS") == 0 || strcmp(strupr((*trav)->data.course), "BSIT") == 0 || strcmp(strupr((*trav)->data.course), "BSIS") == 0)) {
            temp = (*trav);                             //temp hold address of graduating node
            (*trav) = temp->next;                       //trav points over graduating node to next node
            temp->next = (*gradList);                   //temp will point to whatever gradlist was previously pointing
            (*gradList) = temp;                         //gradlist will finally get temp
        } else {
            trav = &(*trav)->next;                      //if node not graduating then continue to iterate
        }
    }
}