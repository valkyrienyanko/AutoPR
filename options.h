#pragma once

#include <stdio.h>
#include <stdbool.h>

#define CONFIG_MERGE_TYPE "merge_type"
#define CONFIG_MERGE_TYPE_DEFAULT "squash"

#define CONFIG_TITLE_PROMPT "title_prompt"
#define CONFIG_TITLE_PROMPT_DEFAULT "yes"

#define CONFIG_DESC_PROMPT "description_prompt"
#define CONFIG_DESC_PROMPT_DEFAULT "no"

#define CONFIG_DELETE_FEATURE_BRANCH "delete_feature_branch"
#define CONFIG_DELETE_FEATURE_BRANCH_DEFAULT "yes"

#define CONFIG_MERGE_PULL_REQUEST "merge_pull_request"
#define CONFIG_MERGE_PULL_REQUEST_DEFAULT "yes"

#define CONFIG_REPO_PATH "config_repo_path"
#define CONFIG_REPO_PATH_DEFAULT ""

void init_default_options();
bool save_option(const char* key, const char* value);
void load_option(const char* key, char* value, size_t value_size);
