#include <stdbool.h>
#include <string.h>

#include "github.h"
#include "home.h"
#include "options.h"
#include "utils.h"

void options()
{
    char merge_type[10];
    char title_prompt[64];
    char description_prompt[4];
    char merge_type_display[128];
    char merge_type_desc[64];
    
    load_option(CONFIG_MERGE_TYPE, merge_type, sizeof(merge_type));
    load_option(CONFIG_TITLE_PROMPT, title_prompt, sizeof(title_prompt));
    load_option(CONFIG_DESC_PROMPT, description_prompt, sizeof(description_prompt));
    
    if (strcmp(merge_type, "merge") == 0)
    {
        strncpy(merge_type_desc, "Creates a new merge commit", sizeof(merge_type_desc));
    }
    else if (strcmp(merge_type, "rebase") == 0)
    {
        strncpy(merge_type_desc, "Reapplies commits linearly", sizeof(merge_type_desc));
    }
    else if (strcmp(merge_type, "squash") == 0)
    {
        strncpy(merge_type_desc, "Combines all commits into one commit", sizeof(merge_type_desc));
    }
    
    snprintf(merge_type_display, sizeof(merge_type_display), "(1) Merge Type (%s) (%s)", merge_type, merge_type_desc);

    printf("---------- Options ----------\n"); 
    printf("%s\n", merge_type_display);
    printf("(2) PR Prompt Title (%s)\n", title_prompt);
    printf("(3) PR Prompt Description (%s)\n", description_prompt);
    printf("(x) Go Back\n");
    
    char choice;
    
    while (true)
    {
        choice = (char)getchar();
        clear_buffer();
        
        switch (choice)
        {
            case '1':
                if (strcmp(merge_type, "merge") == 0)
                    save_option(CONFIG_MERGE_TYPE, "rebase");
                else if (strcmp(merge_type, "rebase") == 0)
                    save_option(CONFIG_MERGE_TYPE, "squash");
                else if (strcmp(merge_type, "squash") == 0)
                    save_option(CONFIG_MERGE_TYPE, "merge");
                    
                options();
                return;
            case '2':
                if (strcmp(title_prompt, "yes") == 0)
                    save_option(CONFIG_TITLE_PROMPT, "no");
                else
                    save_option(CONFIG_TITLE_PROMPT, "yes");
                    
                options();
                return;
            case '3':
                if (strcmp(description_prompt, "yes") == 0)
                    save_option(CONFIG_DESC_PROMPT, "no");
                else 
                    save_option(CONFIG_DESC_PROMPT, "yes");
                
                options();
                return;
            case 'x':
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
    printf("(x) Exit Program\n");

    char choice;
    
    while (true)
    {
        choice = (char)getchar();
        clear_buffer();
        
        switch (choice)
        {
            case '1':
                create_and_merge_pr();
                return;
            case '2':
                options();
                return;
            case 'x':
                return;
            default:
                printf("Enter a valid choice.\n");
        }
    }
}
