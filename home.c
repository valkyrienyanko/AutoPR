#include <unistd.h> // for chdir()
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "github.h"
#include "home.h"
#include "options.h"
#include "utils.h"

void options()
{
    system("cls");

    char merge_type[10];
    char merge_type_display[128];
    char merge_type_desc[64];
    char repo_path[512];
    
    char title_prompt[4];
    char description_prompt[4];
    char delete_feature_branch[4];
    char merge_pull_request[4];
    
    load_option(CONFIG_MERGE_TYPE, merge_type, sizeof(merge_type));
    load_option(CONFIG_TITLE_PROMPT, title_prompt, sizeof(title_prompt));
    load_option(CONFIG_DESC_PROMPT, description_prompt, sizeof(description_prompt));
    load_option(CONFIG_DELETE_FEATURE_BRANCH, delete_feature_branch, sizeof(delete_feature_branch));
    load_option(CONFIG_MERGE_PULL_REQUEST, merge_pull_request, sizeof(merge_pull_request));
    load_option(CONFIG_REPO_PATH, repo_path, sizeof(repo_path));
    
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
    
    snprintf(merge_type_display, sizeof(merge_type_display), "(2) Merge Type (%s) (%s)", merge_type, merge_type_desc);

    printf("---------- Options ----------\n");
    printf("(1) Repository Path (%s)\n", repo_path);
    printf("%s\n", merge_type_display);
    printf("(3) PR Prompt Title (%s)\n", title_prompt);
    printf("(4) PR Prompt Description (%s)\n", description_prompt);
    printf("(5) Delete Feature Branch (%s)\n", delete_feature_branch);
    printf("(6) Merge Pull Request (%s)\n", merge_pull_request);
    printf("(x) Go Back\n");
    
    char choice;
    
    while (true)
    {
        choice = (char)getchar();
        clear_buffer();
        
        switch (choice)
        {
            case '1':
                printf("Please put in the path to the repository:\n");
                
                read_line(repo_path, sizeof(repo_path));
                save_option(CONFIG_REPO_PATH, repo_path);
                options();
                return;
            case '2':
                if (strcmp(merge_type, "merge") == 0)
                {
                    save_option(CONFIG_MERGE_TYPE, "rebase");
                }
                else if (strcmp(merge_type, "rebase") == 0)
                {
                    save_option(CONFIG_MERGE_TYPE, "squash");
                }
                else if (strcmp(merge_type, "squash") == 0)
                {
                    save_option(CONFIG_MERGE_TYPE, "merge");
                }
                    
                options();
                return;
            case '3':
                if (strcmp(title_prompt, "yes") == 0)
                    save_option(CONFIG_TITLE_PROMPT, "no");
                else
                    save_option(CONFIG_TITLE_PROMPT, "yes");
                    
                options();
                return;
            case '4':
                if (strcmp(description_prompt, "yes") == 0)
                    save_option(CONFIG_DESC_PROMPT, "no");
                else 
                    save_option(CONFIG_DESC_PROMPT, "yes");
                
                options();
                return;
            case '5':
                if (strcmp(delete_feature_branch, "yes") == 0)
                    save_option(CONFIG_DELETE_FEATURE_BRANCH, "no");
                else 
                    save_option(CONFIG_DELETE_FEATURE_BRANCH, "yes");
                
                options();
                return;
            case '6':
                if (strcmp(merge_pull_request, "yes") == 0)
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
    system("cls");
    printf("---------- GitHub Pull Request Automator ----------\n");
    printf("(1) Create and Merge Pull Request\n");
    printf("(2) Configure Options\n");
    printf("(x) Exit Program\n");

    char choice;
    char repo_path[512];
    load_option(CONFIG_REPO_PATH, repo_path, sizeof(repo_path));
    
    while (true)
    {
        choice = (char)getchar();
        clear_buffer();
        
        switch (choice)
        {
            case '1':
                chdir(repo_path);
                system("cls");
                create_and_merge_pr();
                return;
            case '2':
                options();
                return;
            case 'x':
                system("cls");
                return;
            default:
                printf("Enter a valid choice.\n");
        }
    }
}
