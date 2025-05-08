#pragma once

#include <stdio.h>
#include <stdbool.h>

#define MERGE_TYPE_KEY "merge_type"
#define MERGE_TYPE_VALUE_DEFAULT "squash"

#define DESCRIPTION_PROMPT_KEY "description_prompt"
#define DESCRIPTION_PROMPT_VALUE_DEFAULT "no"

bool save_option(const char* key, const char* value);
bool load_option(const char* key, char* value, size_t value_size);
