#pragma once

#include <stdio.h>
#include <stdbool.h>

#define CONFIG_MERGE_TYPE "merge_type"
#define CONFIG_MERGE_TYPE_DEFAULT "squash"

#define CONFIG_TITLE_PROMPT "title_prompt"
#define CONFIG_TITLE_PROMPT_DEFAULT "yes"

#define CONFIG_DESC_PROMPT "description_prompt"
#define CONFIG_DESC_PROMPT_DEFAULT "no"

void init_default_options();
bool save_option(const char* key, const char* value);
void load_option(const char* key, char* value, size_t value_size);
