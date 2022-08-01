#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "functionproto.h"
#include "functiondef.c"



int main()
{
    int option, val = 1;
    while (val)
    {
        system("cls");
        userInterface();
        printf("\nSelect An Option\n"
               "(1)Login\n"
               "(2)Sign Up\n"
               "(3)Exit Program\n"
               "Enter option: ");
        fflush(stdin);
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                loginPage();
                break;
            case 2:
                if (createAccount() == 1)
                    printf("Account Has Been Created\n");
                else
                    printf("Something Went Wrong\n");
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Invalid Option!\n");
                system("pause");

        }
    }

}
