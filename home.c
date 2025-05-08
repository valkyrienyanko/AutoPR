#include <stdbool.h>
#include <string.h>

#include "github.h"
#include "home.h"
#include "options.h"
#include "utils.h"

void options()
{
    char merge_type[10];
    char merge_type_display[128];
    char merge_type_desc[64];
    
    char title_prompt[4];
    char description_prompt[4];
    char delete_feature_branch[4];
    char merge_pull_request[4];
    
    load_option(CONFIG_MERGE_TYPE, merge_type, sizeof(merge_type));
    load_option(CONFIG_TITLE_PROMPT, title_prompt, sizeof(title_prompt));
    load_option(CONFIG_DESC_PROMPT, description_prompt, sizeof(description_prompt));
    load_option(CONFIG_DELETE_FEATURE_BRANCH, delete_feature_branch, sizeof(delete_feature_branch));
    load_option(CONFIG_MERGE_PULL_REQUEST, merge_pull_request, sizeof(merge_pull_request));
    
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
    printf("(4) Delete Feature Branch (%s)\n", delete_feature_branch);
    printf("(5) Merge Pull Request (%s)\n", merge_pull_request);
    printf("(x) Go Back\n");
    
    char choice;
    
    while (true)
    {
        choice = (char)getchar();
        clear_buffer();
        
        switch (choice)
        {
            case '1':
                if (strcmp(CONFIG_MERGE_TYPE, "merge") == 0)
                {
                    save_option(CONFIG_MERGE_TYPE, "rebase");
                }
                else if (strcmp(CONFIG_MERGE_TYPE, "rebase") == 0)
                {
                    save_option(CONFIG_MERGE_TYPE, "squash");
                }
                else if (strcmp(CONFIG_MERGE_TYPE, "squash") == 0)
                {
                    save_option(CONFIG_MERGE_TYPE, "merge");
                }
                    
                options();
                return;
            case '2':
                if (strcmp(CONFIG_TITLE_PROMPT, "yes") == 0)
                    save_option(CONFIG_TITLE_PROMPT, "no");
                else
                    save_option(CONFIG_TITLE_PROMPT, "yes");
                    
                options();
                return;
            case '3':
                if (strcmp(CONFIG_DESC_PROMPT, "yes") == 0)
                    save_option(CONFIG_DESC_PROMPT, "no");
                else 
                    save_option(CONFIG_DESC_PROMPT, "yes");
                
                options();
                return;
            case '4':
                if (strcmp(CONFIG_DELETE_FEATURE_BRANCH, "yes") == 0)
                    save_option(CONFIG_DELETE_FEATURE_BRANCH, "no");
                else 
                    save_option(CONFIG_DELETE_FEATURE_BRANCH, "yes");
                
                options();
                return;
            case '5':
                if (strcmp(CONFIG_MERGE_PULL_REQUEST, "yes") == 0)
                    save_option(CONFIG_MERGE_PULL_REQUEST, "no");
                else 
                    save_option(CONFIG_MERGE_PULL_REQUEST, "yes");
                
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
