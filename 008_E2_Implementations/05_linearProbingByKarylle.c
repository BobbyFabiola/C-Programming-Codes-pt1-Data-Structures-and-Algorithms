#include <stdio.h>
#include <ctype.h>

#define MAX 10
#define EMPTY       '~'
#define DELETED     '!'

typedef char Dictionary[MAX];
typedef enum {TRUE, FALSE} Boolean;

void initDict(Dictionary D){
    int i = 0;

    for(i = 0; i < MAX; i++){
        D[i] = EMPTY;
    }
}

int hash(char elem){
    return (toupper(elem) - 'A') % MAX;
}

Boolean isMember(Dictionary D, char elem){
    int i,  val;
    for(i = 0, val = hash(elem); i <  MAX && D[val] != elem && D[val] != EMPTY; i++, val = (val + 1) % MAX){}
    return (D[val] == elem) ? TRUE : FALSE;
}


// void insertDict(Dictionary D, char elem){
//     int i, val = hash(elem);
//     for(i = val; i != val && D[val] != elem && D[val] != EMPTY  && D[val] != DELETED; i++, val = (val + 1) % MAX){}
//     if(D[val] == EMPTY || D[val] == DELETED){
//         D[val] = elem;
//     }
// }




void insertDict(Dictionary D, char elem) {                                  //populate all empty first by unique elements
    if(isMember(D, elem) == FALSE){                                         //if unique
        int hashVal = hash(elem);                                           //then get hash value
        if(D[hashVal] == EMPTY){                                            //if cell at hash value is EMPTY, then insert at the EMPTY cell  
            D[hashVal] = elem;
        }else{                                                              //if cell is DELETED
            int i;                                                          //start at next cell; stop  if full circle && stop if cell is EMPTY && stop if cell is DELETED
            for(i = hashVal+1; i != hashVal && D[i] != EMPTY && D[i] != DELETED; i = (i + 1) % 10){} 
            if(i != hashVal){                                               //if not full circle
                D[i] = elem;                                                //inserts at either deleted or empty
            }else{                                                          //else then trav has done full circle, thus there was no available space
                printf("No more space at [%d] for %c.\n", i, elem);
            }
        }
    }
}




void delete(Dictionary D, char elem){
    int i, val;
    for(i = 0, val = hash(elem); i < MAX && D[val] != elem && D[val] != EMPTY; i++, val = (val + 1) % MAX){}
    if(D[val] == elem){
        D[val] = DELETED;
    }
}

void displayDict(Dictionary D){
    int i;
    for(i = 0; i < MAX; i++){
        printf("%d => %c\n", i, D[i]);
    }
    printf("\n\n");
}



int main(){
    Dictionary D;

    initDict(D);
    displayDict(D);

    insertDict(D, 'A');
    insertDict(D, 'a');
    insertDict(D, 'B');
    insertDict(D, 'E');
    insertDict(D, 'A');

    displayDict(D);

    delete(D, 'a');

    displayDict(D);

    insertDict(D, 'C');
    insertDict(D, 'J');
    insertDict(D, 'D');
    insertDict(D, 'B');
    insertDict(D, 'G');
    insertDict(D, 'F');
    insertDict(D, 'K');
    insertDict(D, 'H');




    displayDict(D);


}