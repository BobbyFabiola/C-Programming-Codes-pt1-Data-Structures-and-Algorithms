Stacks and Queues Implemented in Array List, Linked List, and Cursor Based

EXAM 1: Pre-midterm Topics
1)  Abstract Data Type (ADT)
2)  ADT List 
     a. Differentiate a List from and ADT List.
     b. List Operations:  Initialize, insert, delete, member, locate, and other operations  
     c. Implementations of ADT List:
        i. Array Implementation (4 versions)
           Version 1: List is a structure containing an array and variable count
                     Note: count represents the actual number of elements in the array
                           If MAX is the size of the array, count <= MAX
           Version 2: List is a pointer to a structure containing an array  and variable count
           Version 3: List is a structure containing a pointer to the 1st element of a dynamic array, and variable count
           Version 4: List is a pointer to a structure containing a pointer to the 1st element of a dynamic array, and variable count 
        ii. Linked List Implementation (Singly Link)
       iii. Cursor-based Implementation
      d. Time Complexity of the List operations in different implementations : O(1), O(N), and O(N*N)
3) ADT Stack and Implementations
   a. What is an ADT Stack?
    b. Stack Operations:  Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull 
    c. Implementations 
        i. Array Implementation (4 versions)
       ii. Linked List Implementation
      iii. Cursor-based Implementation
    d. Time Complexity:  O(1) and O(N)
4) ADT Queue and Implementations
    a. What is an ADT Queue?
    b. Queue Operations: Front, Dequeue, Enqueue, and other utility functions such as initQueue, isEmpty, and isFull
    c. Implementations
        i. Linked List Implementation
           1. Queue is a pointer to a dynamically allocated node
           2. Queue is a structure containing front and rear pointers to dynamically allocated node/s
        ii. Circular Array Implementation
            Solution 1: Add a counter
            Solution 2:  Queue is full if there are MAX-1 elements 
                          where MAX is the size of the array
    d. Time Complexity:  O(1) and O(N)

#define MAX 10

//structure definition
typedef struct {
    char LName[20], Fname[16], Mi;
} nameType;

typedef struct {
    nameType name;
    int ID, year;
    char course[8];
} studType;

typedef struct {
    studType studList[MAX];
    int count;
} LIST;

typedef enum {TRUE, FALSE} Boolean;

//function prototypes
void initialize ();
void display ();
void insertFirst ();
void insertLast ();
void insertAt ();
void insertSorted ();
void deleteFirst ();
void deleteLast ();
void deleteAtPos ();
void deleteAtElem ();
Boolean isMember ();
studType locateElem ();