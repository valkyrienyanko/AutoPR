#pragma once

#include <stdbool.h>

typedef struct 
{
    const void* key;
    void* value;
} KeyValuePair;

typedef struct
{
    KeyValuePair* array;
    size_t size;
    size_t capacity;
    bool (*key_compare)(const void* key, const void* value);
} Dictionary;

Dictionary* create_dict();
void dict_set(Dictionary* dict, const void* key, void* value);
const void* dict_get(const Dictionary* dict, const void* key);
void destroy_dict(Dictionary* dict);
