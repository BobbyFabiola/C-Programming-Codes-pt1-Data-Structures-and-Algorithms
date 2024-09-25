#include <stdio.h>
#include <stdlib.h>
#define MAX 9

typedef char STRING[20];

int addition (int x, int y);
int subtraction (int x, int y);
int multiplication (int x, int y);
float division (int x, int y);
int xy (int x, int y);
int nFactorial (int n);
int powerOfTen (int x);
void patterns (void);

void rectangle(int x);
void triangle(int x);
void square(int x);

int main () {
    STRING menu[MAX] = {"QUIT", "ADDITION", "SUBTRACTION", "MULTIPLICATION", "DIVISION", "X^Y", "n!", "10^X", "PATTERNS"};
    int x, ans = 1;
    int i,j;

    do {
        system("cls");
        printf("ARITHMETIC OPERATIONS & PATTERNS");
        for (x = 0; x < MAX; ++x) {
            printf("\n[%d] %s", x, menu[x]);
        }
        printf("\n\nEnter choice: [0-8]:: ");
        scanf("%d", &ans);
        system("cls");

        printf("[%d] %s\n\n", ans, menu[ans]);

        int catch = 0;
        float catch2 = 0;
        switch (ans) {
            case 0:
                //QUIT
                break;

            case 1:
                
                printf("Input x: ");
                scanf("%d",&i);

                printf("Input y: ");
                scanf("%d",&j);
                catch = addition(i,j);
                printf("Sum = %d\n", catch);
                break;

            case 2:
                
                printf("Input x: ");
                scanf("%d",&i);

                printf("Input y: ");
                scanf("%d",&j);
                catch = subtraction(i,j);
                printf("Difference = %d\n", catch);
                break;

            case 3:

                printf("Input x: ");
                scanf("%d",&i);

                printf("Input y: ");
                scanf("%d",&j);

                catch = multiplication(i,j);
                printf("Product = %d\n", catch);
                break;

            case 4:

                printf("Input x: ");
                scanf("%d",&i);

                printf("Input y: ");
                scanf("%d",&j);

                catch2 = division(i,j);
                printf("Qoutient = %.2f\n", catch2);
                break;

            case 5:

                printf("Input x: ");
                scanf("%d",&i);

                printf("Input y: ");
                scanf("%d",&j);

                catch = xy(i,j);
                printf("%d raised to the power of %d = %d\n", i, j, catch);
                break;

            case 6:

                printf("Input n: ");
                scanf("%d",&i);

                catch = nFactorial(i);
                printf("%d Factorial = %d\n", i, catch);
                break;

            case 7:

                printf("Input x: ");
                scanf("%d",&i);

                catch = powerOfTen(i);
                printf("10 raised to the power of %d  = %d\n", i, catch);
                break;

            case 8:

                patterns();
                break;

            default:
                printf("INVALID ANSWER\n");
        }
        printf("\n\n");
        system("pause");
    } while (ans != 0);

    printf("\n\n");
    return 0;
}

int addition (int x, int y) {
    return x+y;

}

int subtraction (int x, int y) {
    return  x-y;
}

int multiplication (int x, int y) {
    return x*y;
}

float division (int x, int y) {
    if(y == 0){
        return y/x;
    }
    return x/y;
}

int xy (int x, int y) {
    for(int i = 0; i < y; i++){
        x *= x;
    }
    return x;
}

int nFactorial (int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int powerOfTen (int x) {
    int a = 1;
    for(int i = 0 ; i < x; i++){
        a *= 10;
    }
    return a;
}

void patterns (void) {
    STRING shapes[4] = {"BACK", "RECTANGLE", "TRIANGLE", "SQUARE"};
    
    int x, ans, val = 0;
    for (x = 0; x < 4; ++x) {
        printf("\n[%d] %s", x, shapes[x]);
    }
    printf("\n\nEnter choice: [0-3]:: ");
    scanf("%d", &ans);
    
    printf("[%d] %s\n\n", ans, shapes[ans]);

    switch (ans) {
        case 0:
            break;
        
        case 1:
            printf("Input a value: ");
            scanf ("%d", &val);
            rectangle (val);
            break;
        
        case 2:
            printf("Input a value: ");
            scanf ("%d", &val);
            triangle (val);
            break;
        
        case 3:
            printf("Input a value: ");
            scanf ("%d", &val);
            square (val);
            break;

        default:
            printf("INVALID INPUT");
    }
}


void square(int x) {
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x * 2; j++){
            printf("*");
        }
        printf("\n");
    }
}

void triangle(int x) {
    for(int i = 0; i < x; i++){
        for(int j = i; j < x; j++){
            printf("* ");
        }
        printf("\n");
    }
}

void rectangle(int x) {
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x; j++){
            printf("*");
        }
        printf("\n");
    }
}