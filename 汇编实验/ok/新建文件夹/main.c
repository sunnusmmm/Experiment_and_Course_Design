#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

#pragma inline

extern void WAN1(void);
extern void WAN2(void);
extern void WAN3(void);
extern void WAN4(void);
extern void WAN6(void);
extern char GA1;
extern char **SORTED;

int main() {
    char name[] = "NHY";
    char pwd[] = "123";
    char in_name[10];
    char in_pwd[10];
    char ch;
    int i = 0;
    int op = 1;

    printf("Please enter your name:");
    while ((ch = (char) getchar()) != '\n') {
        in_name[i] = ch;
        i++;
    }
    if (i == 0) {
        while (op) {
			printf("SHOP\n");
            printf("-----------------------------------------------\n");
            printf("|                    Menu                     |\n");
            printf("|    1.Query product information              |\n");
            printf("|    6.Program exit!                          |\n");
            printf("-----------------------------------------------\n");
            printf("Please choose your number: [1 OR 6]:");
            scanf("%d", &op);
            switch (op) {
                case 1:
                    system("pause");
                    break;
                case 6:
                    WAN6();
                    system("pause");
                    break;
            }
        }
    }
	if(in_name[0] == 'q' && i == 1){
		WAN6();
	}
	i = 0;
    printf("Please enter your pwd:");
    scanf("%s", in_pwd);
	getchar();

    while (strcmp(name, in_name) != 0 && strcmp(pwd, in_pwd) != 0) {
        printf("Your name or number not right! try again!\n");
        printf("Please enter your name:");
        while ((ch = (char) getchar()) != '\n') {
            in_name[i] = ch;
            i++;
        }
        if (i == 0) {
            while (op) {
				printf("SHOP\n");
                printf("-----------------------------------------------\n");
                printf("|                    Menu                     |\n");
                printf("|    1.Query product information              |\n");
                printf("|    6.Program exit!                          |\n");
                printf("-----------------------------------------------\n");
                printf("Please choose your number: [1 OR 6]:");
                scanf("%d", &op);
                switch (op) {
                    case 1:
                        system("pause");
                        break;
                    case 6:
                        WAN6();
                        system("pause");
                        break;
                }
            }
        }
		i = 0;
		if(in_name[0] == 'q' && i == 1){
		WAN6();
	}
        printf("Please enter your pwd:");
        scanf("%s", in_pwd);
    }

    while (op) {
		printf("SHOP\n");
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
        scanf("%d", &op);
		getchar();
        switch (op) {
            case 1:
                system("pause");
                break;
            case 2:
                WAN2();
                system("pause");
                break;
            case 3:
                WAN3();
                system("pause");
                break;
            case 4:
                WAN4();
                system("pause");
                break;
            case 5:
                WAN5();
                system("pause");
                break;
            case 6:
                WAN6();
                system("pause");
                break;
        }
    }
    return 0;
}

void WAN5(){
	char *p = *SORTED;
    char name[10];
    char discount;
    int information[5];
    int last = 0, rank = 1;
    int i, j, l, k = 1;
    for (l = 0; l < 10; ++l, k++) {
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
        if (last != information[4]) rank = k;
        printf("%d %s ", rank, name);
        last = information[4];
        printf("%d ", discount);
        for (j = 0; j < 5; j++) { printf("%u ", information[j]); }
        printf("\n");
    }
}