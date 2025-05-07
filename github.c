#include <stdio.h>
#include <stdlib.h>

#include "github.h"

#define COMMAND_SIZE 256

/// @brief Checks out a branch on GitHub.
/// @return True if the branch was checked out successfully.
bool checkout_branch(char* branch_name)
{
    char cmd[COMMAND_SIZE];
    snprintf(cmd, sizeof(cmd), "git checkout -b %s", branch_name);
    return system(cmd) == 0;
}

bool push_branch(char* branch_name)
{
    char cmd[COMMAND_SIZE];
    snprintf(cmd, sizeof(cmd), "git push --set-upstream origin %s", branch_name);
    return system(cmd) == 0;
}
