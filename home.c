#include <stdbool.h>
#include <string.h>

#include "github.h"
#include "home.h"
#include "options.h"
#include "utils.h"

void options();

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
        scan_num_consume(&choice);
        
        switch (choice)
        {
            case 1:
                save_option(CONFIG_MERGE_TYPE, "merge");
                options();
                return;
            case 2:
                save_option(CONFIG_MERGE_TYPE, "rebase");
                options();
                return;
            case 3:
                save_option(CONFIG_MERGE_TYPE, "squash");
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


void options()
{
    char merge_type[10];
    load_option(CONFIG_MERGE_TYPE, merge_type, sizeof(merge_type));
    
    char description_prompt[4];
    load_option(CONFIG_DESC_PROMPT, description_prompt, sizeof(description_prompt));

    printf("---------- Options ----------\n"); 
    printf("(1) Merge Type (%s)\n", merge_type);
    printf("(2) PR Description Prompt (%s)\n", description_prompt);
    printf("(3) Go Back\n");
    
    int choice = 0;
    
    while (true)
    {
        scan_num_consume(&choice);
        
        switch (choice)
        {
            case 1:
                set_merge_type();
                return;
            case 2:
                if (strcmp(description_prompt, "yes") == 0)
                    save_option(CONFIG_DESC_PROMPT, "no");
                else 
                    save_option(CONFIG_DESC_PROMPT, "yes");
                
                options();
                return;
            case 3:
                home();
                return;
            default:
                printf("Enter a valid choice.\n");
        }
    }
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
        scan_num_consume(&choice);
        
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
