/*   Author:        Fabiola Villanueva
 *   Description:   Queue of My Tasks To Do (Linked List Implementation)
 *   Date:          11-17-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD 30
#define MAX_SIZE 10

//structure definition
typedef char STRING[MAX_WORD];
typedef enum {FALSE, TRUE} Boolean;

typedef struct node {
     STRING data;
     struct node *next;
} nodeType, *nodePtr;

typedef struct {
     nodePtr front;
     nodePtr rear;
} queue;

//function prototypes
void intializeList (queue *Q);
void displayQueue (queue Q);
void enQueueTask (queue *Q, STRING taskElem);
void deQueueTask (queue *Q);
Boolean isEmpty (queue Q);
STRING *frontTask (queue Q);

int main () {
     system ("cls");
     queue myQ;
     Boolean ans = TRUE;
     STRING newTask;

     printf("<< BEGIN >>\n");
     printf("Welcome to your to do list!\n");

     printf("\n<< 0. Initialize List >>\n");
     intializeList (&myQ);
     if (myQ.front == NULL && myQ.rear == NULL) {
          printf("\tFront and rear of queue is initialized to NULL.\n");
     }

     printf("\n<< 1. Add Task To List (EnQueue)\n\n");
     do {
          printf("\tWould you like to add a task into the list? <1-yes/0-no>\n");
          printf("\tAnswer: ");
          scanf("%d", &ans);

          if (ans == TRUE) {
               printf("\tInput Task: ");
               fflush (stdin);
               fgets (newTask, sizeof (newTask), stdin);
               newTask [strcspn (newTask, "\n")] = '\0';

               enQueueTask (&myQ, newTask);
          }
          displayQueue (myQ);
     } while (ans == TRUE);

     printf("\n<< 2. Performing and Removing Tasks (Front and Dequeue) >>\n");
     while (isEmpty (myQ) == FALSE) {
          printf("\tPerforming Task: \"%s\"\n", frontTask (myQ));
          printf("\tTask Removed Off List (Dequeue) and Updating List...\n");
          deQueueTask (&myQ);
          displayQueue (myQ);
          printf("\t");
          system ("pause");
     }

     printf("\n<< END >>\n\n");
     return 0;
}

//function definitions
void intializeList (queue *Q) {
     Q->front = NULL;
     Q->rear = NULL;
}

void displayQueue (queue Q) {
     int i;

     printf("\t_______________________\n");
     printf("\n\t>> To Do List: \n");
     if (isEmpty (Q)) {
          printf("\tQueue is Empty.\n\tCongratulations! You've finished all your tasks!\n");   //this message prompt shall only show up in the end
     } else {
          for (i = 0; Q.front != NULL; Q.front = Q.front->next, ++i) {                         //pass by copy of queue, traverse the qeueue
               printf("\t[%d] %s\n", i, Q.front->data);
          }
     }
     printf("\t_______________________\n\n");
}

void enQueueTask (queue *Q, STRING taskElem) {         //insert via rear
     nodePtr temp;
     temp = malloc (sizeof (nodePtr));                 //create node to insert
     temp->next = NULL;
     strcpy (temp->data, taskElem);                    //string copy user input of task into node
     
     if (isEmpty(*Q)) {                                //if the queue is empty
          Q->front = temp;                             //assign front and rear to point to the very first node
          Q->rear = temp;
     } else {                                          //if the queue is not empty proceed to enqueue
          Q->rear->next = temp;                        //acces last node of the queue to point to the node to insert
          Q->rear = temp;                              //update rear pointer
     }
}

void deQueueTask (queue *Q) {                          //delete via front
     nodePtr temp;                                     //temp shall get node to delete

     temp = Q->front;                                  //temp will get first node in the queue everytime
     Q->front = temp->next;                            //redirect front pointer to next node
     free (temp);                                      //you dont touch your rear pointer as you dequeue

     if (Q->front == NULL) {                           //if all nodes have been delete and queue is now empty
          Q->rear = NULL;                              //set entire queue to null
     }
}

Boolean isEmpty (queue Q) {
     return (Q.front == NULL && Q.rear == NULL) ? TRUE: FALSE;        //will be false if there are elements in the queue
}

STRING *frontTask (queue Q) {                          //pass by copy
     STRING *temp = malloc (sizeof (STRING));          //return address of string in heap
     strcpy (*temp, Q.front->data);                    //copy first node data into temp to return
     return (isEmpty (Q) == FALSE) ? temp: NULL;       //return address of string in the heap
}