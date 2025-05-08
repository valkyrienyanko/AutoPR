#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "github.h"
#include "home.h"
#include "options.h"
#include "utils.h"

#define COMMIT_FALLBACK_NAME "New Feature"

/// @brief Create a new branch and switch to it.
/// @return True if the branch was checked out successfully.
bool create_new_branch(char* branch_name)
{
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "git checkout -b %s", branch_name);
    return system(cmd) == 0;
}

/// @brief Delete a branch locally and remotely
/// @return True if the branch was deleted successfully
bool delete_branch(char* branch_name)
{
    char cmd[128];
    int result;
    
    // Delete local branch
    snprintf(cmd, sizeof(cmd), "git branch -d %s", branch_name);
    result = system(cmd);
    
    if (result != 0)
        return false;
        
    // Delete remote branch
    snprintf(cmd, sizeof(cmd), "git push origin --delete %s", branch_name);
    result = system(cmd);
    
    if (result != 0)
        return false;
    
    return true;
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
    load_option(CONFIG_MERGE_TYPE, merge_type, sizeof(merge_type));
    
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

/// @brief Gets the latest commit message.
void latest_commit_message(char* message, int message_size)
{
    const char* cmd = "git log -1 --pretty=%B";
    
    FILE* fp = popen(cmd, "r");
    
    if (!fp)
    {
        perror("popen failed");
        return;
    }
    
    // fgets populates message
    char* line = fgets(message, message_size, fp);
    
    if (!line)
    {
        strncpy(message, COMMIT_FALLBACK_NAME, (size_t)message_size);
    }
    
    line[strlen(line) - 1] = '\0';
    
    pclose(fp);
}

/// @brief Create and merge a GitHub pull request.
void create_and_merge_pr()
{
    char pr_title[128], pr_description[512], branch_name[128];
    char description_prompt[4], title_prompt[4], delete_branch_option[4], merge_pr_option[4];
    
    load_option(CONFIG_DESC_PROMPT, description_prompt, sizeof(description_prompt));
    load_option(CONFIG_TITLE_PROMPT, title_prompt, sizeof(title_prompt));
    load_option(CONFIG_DELETE_FEATURE_BRANCH, delete_branch_option, sizeof(delete_branch_option));
    load_option(CONFIG_MERGE_PULL_REQUEST, merge_pr_option, sizeof(merge_pr_option));
    
    bool title_prompt_enabled = strcmp(title_prompt, "yes") == 0;
    bool description_prompt_enabled = strcmp(description_prompt, "yes") == 0;
    bool merge_enabled = strcmp(merge_pr_option, "yes") == 0;
    
    // Title prompt
    if (title_prompt_enabled)
    {
        printf("PR Title: ");
        read_line(pr_title, sizeof(pr_title));
    }
    else
    {
        latest_commit_message(pr_title, sizeof(pr_title));
    }
    
    // Branch name based on PR title or latest commit message
    strncpy(branch_name, pr_title, sizeof(branch_name));
    convert_to_camel_case(branch_name);
    
    // Description prompt
    if (description_prompt_enabled)
    {
        printf("PR Description: ");
        read_line(pr_description, sizeof(pr_description));
    }
    else
    {
        strncpy(pr_description, "No description provided", sizeof(pr_description));
    }
    
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
    if (merge_enabled)
    {
        printf("\nMerging pull request...\n");

        if (!merge_pr())
        {
            print_error("Failed to merge pull request");
            return;
        }
    }
    
    // Switch back to main
    printf("\nSwitching back to main...\n");
    
    if (!switch_to_branch("main"))
    {
        print_error("Failed to switch back to main");
        return;
    }
    
    // Delete branch
    if (strcmp(delete_branch_option, "yes") == 0)
    {
        printf("\nDeleting branch...\n");
    
        if (!delete_branch(branch_name))
        {
            print_error("Failed to delete local or remote branch");
            return;
        }
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
    
    home();
}
