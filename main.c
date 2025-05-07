#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "github.h"
#include "utils.h"

/// @brief Automate a GitHub pull request.
void automate_pr()
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
    
    bool checked_branch = checkout_branch(branch_name);
    
    if (!checked_branch)
    {
        print_error("Failed to create branch");
        return;
    }
    
    bool pushed_branch = push_branch(branch_name);
    
    if (!pushed_branch)
    {
        print_error("Failed to push branch");
        return;
    }
}

int main()
{
    automate_pr();
    
    printf("Program ended normally\n");
    return EXIT_SUCCESS;
}