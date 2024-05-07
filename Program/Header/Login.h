#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void login();
void registr();

int main()
{
    int choice;
    printf("==========================================================================\n");
    printf("|                             Toko Online                                |\n");
    printf("==========================================================================\n");
    printf("| 1.LOGIN\t\t\t\t\t\t\t\t |\n");
    printf("| 2.DAFTAR\t\t\t\t\t\t\t\t |\n");
    printf("| 3.Keluar\t\t\t\t\t\t\t\t |\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");
    printf("\nMasukan angka 1/2/3 :");
    scanf("%d", &choice);
    printf("\n");
    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:
        registr();
        break;
    case 3:
        printf("Thanks for using this program\n");
        break;
    default:
        system("clear");
        printf("You've made a mistake , give it a try again\n\n");
        main();
    }
    return 0;
}

void login()
{
    int count = 0;
    char user[50], pass[50], u[50], p[50];
    system("clear");
    printf("please enter the following details\n");
    printf("USERNAME :");
    scanf("%s", user);
    printf("PASSWORD :");
    scanf("%s", pass);

    FILE* input = fopen("database.txt", "r");
    while (fscanf(input, "%s %s", u, p) != EOF)
    {
        if (strcmp(u, user) == 0 && strcmp(p, pass) == 0)
        {
            count = 1;
            system("clear");
        }
    }
    fclose(input);
    if (count == 1)
    {
        printf("\nHello %s\nLOGIN SUCESS\nWe're glad that you're here.\nThanks for logging in\n", user);
        getchar();
        getchar();
        main();
    }
    else
    {
        printf("\nLOGIN ERROR\nPlease check your username and password\n");
        main();
    }
}

void registr()
{
    char reguser[50], regpass[50];
    system("clear");
    printf("Enter the username :");
    scanf("%s", reguser);
    printf("\nEnter the password :");
    scanf("%s", regpass);

    FILE* reg = fopen("database.txt", "a");
    fprintf(reg, "%s %s\n", reguser, regpass);
    fclose(reg);
    system("clear");
    printf("\nRegistration Sucessful\n");
    main();
}

