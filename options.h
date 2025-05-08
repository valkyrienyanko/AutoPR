#pragma once

#include <stdio.h>
#include <stdbool.h>

#define MERGE_TYPE_KEY "merge_type"
#define MERGE_TYPE_VALUE_DEFAULT "squash"

bool save_option(const char* key, const char* value);
bool load_option(const char* key, char* value, size_t value_size);
