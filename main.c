#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "github.h"
#include "options.h"

void home();
void options();
void set_merge_type();

int main()
{
    home();
    printf("Program ended normally\n");
    return EXIT_SUCCESS;
}

void home()
{
    printf("---------- GitHub Pull Request Automator ----------\n");
    printf("(1) Create and Merge Pull Request\n");
    printf("(2) Configure Options\n");
    printf("(3) Exit Program\n");

    int choice = 0;
    
    while (true)
    {
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                create_and_merge_pr();
                return;
            case 2:
                options();
                return;
            case 3:
                return;
            default:
                printf("Enter a valid choice.\n");
        }
    }
}

void options()
{
    char merge_type[10];
    load_option(MERGE_TYPE_KEY, merge_type, sizeof(merge_type));

    printf("---------- Options ----------\n");
    printf("(1) Merge Type (%s)\n", merge_type);
    printf("(2) Go Back\n");
    
    int choice = 0;
    
    while (true)
    {
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                set_merge_type();
                return;
            case 2:
                home();
                return;
            default:
                printf("Enter a valid choice.\n");
        }
    }
}

void set_merge_type()
{
    printf("---------- Set Merge Type ----------\n");
    printf("(1) Merge - Creates a new merge commit\n");
    printf("(2) Rebase - Reapplies commits linearly\n");
    printf("(3) Squash - Combines all commits into one commit\n");
    printf("(4) Go Back\n");
    
    int choice = 0;
    
    while (true)
    {
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                save_option(MERGE_TYPE_KEY, "merge");
                options();
                return;
            case 2:
                save_option(MERGE_TYPE_KEY, "rebase");
                options();
                return;
            case 3:
                save_option(MERGE_TYPE_KEY, "squash");
                options();
                return;
            case 4:
                options();
                return;
            default:
                printf("Enter a valid choice.\n");
        }
    }
}
