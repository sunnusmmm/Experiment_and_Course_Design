#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int login();

extern void function();

extern int foo();

extern void foo2();

extern char IN_NAME;
extern char IN_PWD;
extern char AUTH;
extern int INVAL;
extern char GA1;
extern char **SORTED;

char length(char *);

void Print();

int main() {
    do {
        printf("INPUT USERNAME:\n");
        scanf("%s", &IN_NAME);
        printf("INPUT PASSWORD:\n");
        scanf("%s", &IN_PWD);
    } while (login() == 0);
    if (AUTH == 'q') {
        return 0;
    }
    while (1) {
        if (AUTH == 1) {
            printf("-----------------------------------------------\n");
            printf("|                    Menu                     |\n");
            printf("|    1.Query product information              |\n");
            printf("|    2.Modify product information             |\n");
            printf("|    3.Calculate recommendation degree        |\n");
            printf("|    4.Calculate the recommendation ranking   |\n");
            printf("|    5.Output all product information         |\n");
            printf("|    6.Program exit!                          |\n");
            printf("-----------------------------------------------\n");
            printf("Please choose your number: [1~6]:");
        } else {
            printf("-----------------------------------------------\n");
            printf("|                    Menu                     |\n");
            printf("|    1.Query product information              |\n");
            printf("|    6.Program exit!                          |\n");
            printf("-----------------------------------------------\n");
            printf("Please choose your number: [1 OR 6]:");
        }
        scanf("%d", &INVAL);
        if (INVAL <= 0 || INVAL > 6) {
            printf("Enter the number 1-6 to enter the corresponding function\n");
            continue;
        } else if (INVAL == 6) {
            break;
        } else if (INVAL != 1 && AUTH == 0) {
            printf("Enter the number 1 or 6 to enter the corresponding function\n");
            continue;
        } else if(INVAL == 5){
            Print();
        } else {
            // foo2();
            function();
        }
    }
    return 0;
}

char length(char *s) {
    char l = 0;
    while ((*s) != 0 || (*s) != '\n') {
        s++;
        l++;
    }
    return l;
}

void Print() {
    char *p = &GA1;
    char name[10];
    char discount;
    int information[5];
    int last = 0, rank = 1;
    int i, j,l, k = 1;
    for (l = 0; l < 10; ++l,k++) {
        for (i = 0; i < 10; ++i, p++) {
            if (*p != 0) name[i] = *p;
            else name[i] = 0;
        }
        name[i] = 0;
        discount = *p;
        p++;
        for (j = 0; j < 5; ++j, p = p + 2) {
            information[j] = *p;
        }
        if(last != information[4]) rank = k;
        printf("%d %s ",rank, name);
        last = information[4];
        printf("%d ", discount);
        for (j = 0; j < 5; j++) { printf("%u ", information[j]); }
        printf("\n");
    }
}
