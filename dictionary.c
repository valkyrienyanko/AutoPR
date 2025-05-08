#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

#define INITIAL_CAPACITY 2

static void resize_dict(Dictionary* dict)
{
    dict->capacity *= 2;
    dict->array = realloc(dict->array, sizeof(KeyValuePair) * dict->capacity);
}

Dictionary* create_dict()
{
    Dictionary* dict = malloc(sizeof(Dictionary));
    
    if (!dict)
    {
        perror("Malloc failed to allocate memory for dictionary");
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = INITIAL_CAPACITY;
    dict->key_compare = NULL;
    dict->array = malloc(sizeof(KeyValuePair) * dict->capacity);
    
    if (!dict->array)
    {
        perror("Malloc failed to allocate memory for array in dictionary");
        return NULL;
    }
    
    return dict;
}

void destroy_dict(Dictionary* dict)
{
    if (dict)
    {
        free(dict->array);
        free(dict);
    }
}

void dict_set(Dictionary* dict, const void* key, void* value)
{
    // Check if key exists
    for (size_t i = 0; i < dict->size; i++)
    {
        if (dict->key_compare(key, dict->array[i].key))
        {
            dict->array[i].value = value;
            return;
        }
    }
    
    // Add new key-value pair
    if (dict->size == dict->capacity)
    {
        resize_dict(dict);
    }
    
    dict->array[dict->size].key = key;
    dict->array[dict->size].value = value;
    
    dict->size++;
}

const void* dict_get(const Dictionary* dict, const void* key)
{
    for (size_t i = 0; i < dict->size; i++)
    {
        if (dict->key_compare(key, dict->array[i].key))
        {
            return dict->array[i].value;
        }
    }
    
    return NULL;
}
