#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <database.h>
#include <functions.h>
#include <utilities.h>

int main(){

    int choice;
    char passwd[25], *inputpass;
    const char* hash_admin = strdup(crypt("admindbpassword", "$5$"));
    const char* hash_user = strdup(crypt("userdbpassword", "$5$"));

    printf("\nLogin:\n\n1. ADMIN\n2. USER\n\n");
    printf("Enter a choice: ");
    scanf("%d", &choice);

    if(choice == 1 || choice == 2){

        strcpy(passwd, getpass("Enter password: "));

        if(choice == 1 && hashcmp(inputpass=strdup(crypt(passwd, "$5$")), hash_admin)==0){

            ADMIN = 1;
            free(inputpass);
            free((char*)hash_user);
            free((char*)hash_admin);

            for(;;){

                printf("\nBook Operations:\n\n1. Add\n2. Delete\n3. Modify\n4. Search\n5. Sort\n6. List\n\n");
                printf("Enter a choice/Enter 7 to logout: ");
                scanf("%d", &choice);

                if(choice==2 || choice==3)
                    book_ops(choice);
                else{
                    switch(choice){

                        case 1:
                            add();
                            break;

                        case 4:
                            search_books();
                            break;

                        case 5:
                            sort_books();
                            break;

                        case 6:
                            pprint();
                            break;

                        case 7:
                            return 0;

                        default:
                            printf("Enter a choice between 1-7 only.\n");
                    }
                }
            }
        }
        else if(choice == 2 && hashcmp(inputpass=strdup(crypt(passwd, "$5$")), hash_user)==0){

            free((char*)hash_user);
            for(;;){

                printf("\nBook Operations:\n\n1. Search\n2. Sort\n3. List\n4. Issue\n\n");
                printf("Enter a choice/Enter 5 to logout: ");
                scanf("%d", &choice);

                switch(choice){

                    case 1:
                        search_books();
                        break;

                    case 2:
                        sort_books();
                        break;

                    case 3:
                        pprint();
                        break;

                    case 4:
                        free(inputpass);
                        if(hashcmp(inputpass=strdup(crypt(getpass("Enter ADMIN password to issue book: "), "$5$")), hash_admin)==0)
                            book_ops(choice);
                        else
                            printf("Wrong password.\n");
                        break;

                    case 5:
                        return 0;

                    default:
                        printf("Enter a choice between 1-4 only.\n");
                }
            }
        }
        else
            printf("Invalid Credentials.\n");

    }
    else
        printf("Invalid Login.\n");
}