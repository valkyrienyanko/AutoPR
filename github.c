#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "github.h"
#include "utils.h"
#include "options.h"

/// @brief Create a new branch and switch to it.
/// @return True if the branch was checked out successfully.
bool create_new_branch(char* branch_name)
{
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "git checkout -b %s", branch_name);
    return system(cmd) == 0;
}

/// @brief Switch to a branch.
/// @return True if the branch was successfully switched to.
bool switch_to_branch(char* branch_name)
{
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "git checkout %s", branch_name);
    return system(cmd) == 0;
}

/// @brief Publishes the branch to GitHub.
/// @return True if the branch was published successfully.
bool push_branch(char* branch_name)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "git push --set-upstream origin %s", branch_name);
    return system(cmd) == 0;
}

/// @brief Creates a pull request for the branch.
/// @return True if the pull request was created successfully.
bool create_pr(char* branch_name, char* pr_title, char* pr_desc)
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "gh pr create --base main --head %s --title \"%s\" --body \"%s\"", branch_name, pr_title, pr_desc);
    return system(cmd) == 0;
}

/// @brief Squashes and merges the active pull request.
/// @return True if the merge was successful.
bool merge_pr()
{
    char merge_type[10];
    
    if (!load_option(MERGE_TYPE_KEY, merge_type, sizeof(merge_type)))
    {
        // Fall back to default
        snprintf(merge_type, sizeof(merge_type), "%s", MERGE_TYPE_VALUE_DEFAULT);
    }
    
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "gh pr merge --%s", merge_type);
    return system(cmd) == 0;
}

/// @brief Fetches the latest changes from main.
/// @return True if the fetch command was successful.
bool fetch()
{
    return system("git fetch origin") == 0;
}

/// @brief Hard resets the local main branch.
/// @return True if the rebase was successful.
bool hard_reset()
{
    return system("git reset --hard origin/main") == 0;
}

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
    
    // Checkout branch
    printf("\nChecking out branch '%s'...\n", branch_name);

    if (!create_new_branch(branch_name))
    {
        print_error("Failed to create branch");
        return;
    }

    // Publish branch
    printf("\nPublishing branch...\n");

    if (!push_branch(branch_name))
    {
        print_error("Failed to push branch");
        return;
    }

    // Create pull request
    printf("\nCreating pull request...\n");

    if (!create_pr(branch_name, pr_title, pr_description))
    {
        print_error("Failed to create pull request");
        return;
    }

    // Merge pull request
    printf("\nMerging pull request...\n");

    if (!merge_pr())
    {
        print_error("Failed to merge pull request");
        return;
    }

    // Switch back to main
    printf("\nSwitching back to main...\n");
    
    if (!switch_to_branch("main"))
    {
        print_error("Failed to switch back to main");
        return;
    }
    
    // Fetch latest changes from main
    printf("\nFetching the latest changes from main...\n");
    
    if (!fetch())
    {
        print_error("Failed to fetch the latest changes from main");
        return;
    }
    
    // Hard reset local main
    printf("\nHard resetting local main...\n");
    
    if (!hard_reset())
    {
        print_error("Failed to hard reset local main");
        return;
    }

    printf("\nSuccessfully created and merged pull request '%s'\n", pr_title);
}
