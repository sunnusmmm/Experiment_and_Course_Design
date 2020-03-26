#include <stdio.h>
#include <string.h>
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
            printf("                |                 MENU                  |\n\
                |1. Query product information           |\n\
                |2. Modify product information          |\n\
                |3. Calculate recommendation degree     |\n\
                |4. Calculate the recommendation ranking|\n\
                |5. Output all product information      |\n\
                |6. Program exit!                       |\n");
        } else {
            printf("                |                 MENU                  |\n\
                |1. Query product information           |\n\
                |6. Program exit!                       |");
        }
        scanf("%d",&INVAL);
        if (INVAL <= 0 || INVAL > 6) {
            printf("Enter the number 1-6 to enter the corresponding function\n");
            continue;
        } else if (INVAL == 6) {
            break;
        } else if (INVAL != 1 && AUTH == 0) {
            printf("Enter the number 1 or 6 to enter the corresponding function\n");
            continue;
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