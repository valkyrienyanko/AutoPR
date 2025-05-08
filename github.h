#pragma once

#include <stdbool.h>

bool create_new_branch(char* branch_name);
bool switch_to_branch(char* branch_name);
bool push_branch(char* branch_name);
bool create_pr(char* branch_name, char* pr_title, char* pr_desc);
bool merge_pr();
bool fetch();
bool rebase();
