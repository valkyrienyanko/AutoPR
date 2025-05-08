#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "github.h"
#include "utils.h"

/// @brief Create and merge a GitHub pull request.
void create_and_merge_pr()
{
    printf("Setup new Pull Request\n");
    printf("\n");

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
    
    // Checkout branch
    printf("\n");
    printf("Checking out branch '%s'...\n", branch_name);

    if (!checkout_branch(branch_name))
    {
        print_error("Failed to create branch");
        return;
    }
    
    // Publish branch
    printf("\n");
    printf("Publishing branch...\n");
    
    if (!push_branch(branch_name))
    {
        print_error("Failed to push branch");
        return;
    }
    
    // Create pull request
    printf("\n");
    printf("Creating pull request...\n");
    
    if (!create_pr(branch_name, pr_title, pr_description))
    {
        print_error("Failed to create pull request");
        return;
    }
    
    // Merge pull request
    printf("\n");
    printf("Merging pull request...\n");
    
    if (!merge_pr())
    {
        print_error("Failed to merge pull request");
        return;
    }
    
    // Switch back to main
    if (!checkout_branch("main"))
    {
        print_error("Failed to switch back to main");
        return;
    }
    
    printf("\n");
    printf("Successfully created and merged pull request '%s'\n", pr_title);
}

int main()
{
    create_and_merge_pr();
    
    printf("Program ended normally\n");
    return EXIT_SUCCESS;
}