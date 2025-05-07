#pragma once

#include <stdbool.h>

bool checkout_branch(char* branch_name);
bool push_branch(char* branch_name);
bool create_pr(char* branch_name, char* pr_title, char* pr_desc);
