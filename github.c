#include <stdio.h>
#include <stdlib.h>

#include "github.h"

/// @brief Checks out a branch on GitHub.
/// @return True if the branch was checked out successfully.
bool checkout_branch(char* branch_name)
{
    char branch_cmd[256];
    snprintf(branch_cmd, sizeof(branch_cmd), "git checkout -b %s", branch_name);
    return system(branch_cmd) == 0;
}

bool push_branch()
{
    return system("git push origin");
}
