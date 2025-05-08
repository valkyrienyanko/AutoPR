#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "github.h"
#include "utils.h"

/// @brief Create and merge a GitHub pull request.
void create_and_merge_pr()
{
    // Inputs
    printf("PR Title: ");
    char pr_title[128];
    read_line(pr_title, sizeof(pr_title));
    
    printf("PR Description: ");
    char pr_description[512];
    read_line(pr_description, sizeof(pr_description));
    
    printf("Branch Name: ");
    char branch_name[128];
    read_line(branch_name, sizeof(branch_name));
    
    if (!checkout_branch(branch_name))
    {
        print_error("Failed to create branch");
        return;
    }
    
    if (!push_branch(branch_name))
    {
        print_error("Failed to push branch");
        return;
    }
    
    if (!create_pr(branch_name, pr_title, pr_description))
    {
        print_error("Failed to create pull request");
        return;
    }
    
    if (!merge_pr())
    {
        print_error("Failed to merge pull request");
    }
}

int main()
{
    create_and_merge_pr();
    
    printf("Program ended normally\n");
    return EXIT_SUCCESS;
}