#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "search.h"

void login() {
    int count = 0;
    char user[50], pass[50], u[50], p[50], id[50], choice;
    printf("Choose login as:\n");
    printf("1. User\n");
    printf("2. Admin\n");
    printf("Choice :");
    scanf(" %c", &choice);

    if (choice == '1') {
        printf("USERNAME :");
        scanf("%s", user);
        printf("PASSWORD :");
        scanf("%s", pass);

        FILE *input = fopen("databaseuser.txt", "r");
        while(fscanf(input, "%s %s", u, p) != EOF)
        {
            if(strcmp(u, user) == 0 && strcmp(p, pass) == 0)
            {
                count = 1;
                system("CLS");
            }
        }
        fclose(input);
        if(count == 1)
        {
            printf("\nHello %s\nLOGIN SUCCESS\nHalo Pelanggan.\nSelamat melakukan belanja\n", user);
            system("pause");
            maintrieuser();
        }
        else
        {
            printf("\nLOGIN ERROR\nPlease check your username and password\n");
            system("pause");
            menulogin();
        }
    } else if (choice == '2') {
        printf("USERNAME :");
        scanf("%s", user);
        printf("PASSWORD :");
        scanf("%s", pass);
        printf("ID :");
        scanf("%s", id);

        FILE *input = fopen("databaseadmin.txt", "r");
        while(fscanf(input, "%s %s %s", id, u, p) != EOF)
        {
            if(strcmp(u, user) == 0 && strcmp(p, pass) == 0 && strcmp(id, id) == 0)
            {
                count = 1;
                system("CLS");
            }
        }
        fclose(input);
        if(count == 1)
        {
            printf("\nHello %s\nLOGIN SUCCESS\nHalo Admin.\nSelamat bekerja\n", user);
            system("pause");
             maintrieadmin();
        }
        else
        {
            printf("\nLOGIN ERROR\nPlease check your username, password, and ID\n");
            system("pause");
            menulogin();
        }
    } else {
        printf("Invalid choice.\n");
    }
}


void registr() {
    char reguser[50], regpass[50], choice;
    printf("Register as :\n");
    printf("1. User\n");
    printf("2. Admin\n");
    printf("Choice :");
    scanf(" %c", &choice);
    if (choice == '1') {
        printf("Enter the username: ");
        scanf("%s", reguser);
        printf("\nEnter the password: ");
        scanf("%s", regpass);

        FILE *reg = fopen("databaseuser.txt", "a");
        fprintf(reg, "%s %s\n", reguser, regpass);
        fclose(reg);
        printf("\nRegistration Successful\n");
         menulogin(); 
    } else if (choice == '2') {
        FILE *dbadmin = fopen("databaseadmin.txt", "r");
        int admin_count = 0;
        char temp_id[50];
        while (fscanf(dbadmin, "%s", temp_id) != EOF) {
            if (strstr(temp_id, "admin") != NULL) {
                admin_count++;
            }
        }
        fclose(dbadmin);

        char admin_id[50];
        if (admin_count == 0) {
            strcpy(admin_id, "admin1");
        } else {
            sprintf(admin_id, "admin%d", admin_count + 1);
        }

        printf("Your unique admin ID is: %s\n", admin_id);
        printf("Enter the username: ");
        scanf("%s", reguser);
        printf("\nEnter the password: ");
        scanf("%s", regpass);

        FILE *reg = fopen("databaseadmin.txt", "a");
        fprintf(reg, "%s %s %s\n", admin_id, reguser, regpass);
        fclose(reg);
        printf("\nRegistration Successful\n");
         menulogin(); 
    } else {
        printf("Invalid choice.\n");
    }
}

void menulogin()
{	
    int choice;
    system("CLS");
    printf("==========================================================================\n");
    printf("|                             Trie Shop                                  |\n");
    printf("==========================================================================\n");
    printf("| 1.LOGIN\t\t\t\t\t\t\t\t |\n");
    printf("| 2.DAFTAR\t\t\t\t\t\t\t\t |\n");
    printf("| 3.Keluar\t\t\t\t\t\t\t\t |\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");
    printf("\nMasukan angka 1/2/3 :");
    scanf("%d", &choice);
    printf("\n");
    switch(choice)
    {
        case 1:
            login();
            break;
        case 2:
            registr();
            break;
        case 3:
            printf("Terimakasih\n");
            break;
        default:
            system("CLS");
            printf("You've made a mistake , give it a try again\n\n");
            menulogin();
    }
}
