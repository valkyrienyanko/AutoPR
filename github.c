#include <stdio.h>
#include <stdlib.h>

#include "github.h"

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

/// @brief Squashes and merges the active pull request
/// @return 
bool merge_pr()
{
    return system("gh pr merge --squash") == 0;
}
