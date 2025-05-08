#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "dictionary.h"
#include "options.h"
#include "utils.h"

#define MAX_PATH_SIZE 256
#define MAX_LINE_SIZE 256
#define MAX_LINES 128
#define CONFIG_FOLDER_NAME "GitHub Pull Request Automator"
#define CONFIG_FILE_NAME "options.txt"

Dictionary* default_options = NULL;

bool compare_key(const void* key, const void* value)
{
    return strcmp((const char*)key, (const char*)value) == 0;
}

void init_default_options()
{
    default_options = create_dict();
    default_options->key_compare = compare_key;
    dict_set(default_options, CONFIG_MERGE_TYPE, CONFIG_MERGE_TYPE_DEFAULT);
    dict_set(default_options, CONFIG_TITLE_PROMPT, CONFIG_TITLE_PROMPT_DEFAULT);
    dict_set(default_options, CONFIG_DESC_PROMPT, CONFIG_DESC_PROMPT_DEFAULT);
    dict_set(default_options, CONFIG_DELETE_FEATURE_BRANCH, CONFIG_DELETE_FEATURE_BRANCH_DEFAULT);
    dict_set(default_options, CONFIG_MERGE_PULL_REQUEST, CONFIG_MERGE_PULL_REQUEST_DEFAULT);
}

void get_config_path(char* path, size_t path_size)
{
    const char* appdata = getenv("APPDATA");
    
    if (!appdata)
    {
        print_error("Failed to get appdata folder");
        return;
    }
    
    snprintf(path, path_size, "%s\\%s", appdata, CONFIG_FOLDER_NAME);
    
    mkdir(path);
    
    snprintf(path, path_size, "%s\\%s\\%s", appdata, CONFIG_FOLDER_NAME, CONFIG_FILE_NAME);
}

/// @brief Saves an option.
/// @return True if the option was successfully saved.
bool save_option(const char* key, const char* value) 
{
    char config_path[MAX_PATH_SIZE];
    get_config_path(config_path, sizeof(config_path));

    // Check if file exists; if not, create it
    FILE* file_check = fopen(config_path, "r");
    
    if (!file_check)
    {
        // Create empty file
        FILE* f_create = fopen(config_path, "w");
        if (!f_create)
        {
            print_error("Failed to create config file");
            return false;
        }
        
        fclose(f_create);
    }
    else
    {
        fclose(file_check);
    }

    // Open the config file for reading
    FILE* file = fopen(config_path, "r");
    if (!file)
    {
        print_error("Failed to read config");
        return false;
    }

    // Read all lines into memory
    char lines[MAX_LINES][MAX_LINE_SIZE];
    int line_count = 0;
    bool found = false;

    while (fgets(lines[line_count], sizeof(lines[line_count]), file))
    {
        // Remove newline characters
        size_t len = strlen(lines[line_count]);
        if (len > 0 && lines[line_count][len - 1] == '\n')
            lines[line_count][len - 1] = '\0';

        // Check if this line contains the key
        if (!found && strncmp(lines[line_count], key, strlen(key)) == 0 && lines[line_count][strlen(key)] == '=')
        {
            // Update this line
            snprintf(lines[line_count], sizeof(lines[line_count]), "%s=%s", key, value);
            found = true;
        }
        
        line_count++;
        
        if (line_count >= MAX_LINES)
        {
            print_error("Could not read all of config as exceeds MAX_LINES");
            break;
        }
    }

    fclose(file);

    // If key not found, add it
    if (!found)
    {
        snprintf(lines[line_count], sizeof(lines[line_count]), "%s=%s", key, value);
        line_count++;
    }

    // Write all lines back to the file
    file = fopen(config_path, "w");
    if (!file)
    {
        print_error("Failed to open config for writing");
        return false;
    }

    for (int i = 0; i < line_count; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
    return true;
}

/// @brief Loads an option.
/// @param value The buffer for value.
/// @param value_size The size of the value buffer.
void load_option(const char* key, char* value, size_t value_size)
{
    char config_path[MAX_PATH_SIZE];
    get_config_path(config_path, sizeof(config_path));

    FILE* file = fopen(config_path, "r");
    
    if (!file)
    {
        // Create empty config
        file = fopen(config_path, "w");
        fclose(file);
        
        // Read the config again
        file = fopen(config_path, "r");
        
        if (!file)
        {
            print_error("Failed to read config");
            return;
        }
    }
    
    char line[MAX_PATH_SIZE];
    bool found = false;
    
    while (fgets(line, sizeof(line), file))
    {
        // Remove trailing newline
        size_t len = strlen(line);
        
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }
            
        if (strncmp(line, key, strlen(key)) == 0 && line[strlen(key)] == '=')
        {
            strncpy(value, line + strlen(key) + 1, value_size);
            value[value_size - 1] = '\0';
            found = true;
            break;
        }
    }
    
    if (!found)
    {
        const char* default_value = (const char*)dict_get(default_options, key);
        
        strncpy(value, default_value, value_size);
        
        if (!default_value)
        {
            fprintf(stderr, "Failed to get default value for key '%s'\n", key);
        }
        else 
        {
            save_option(key, default_value);
        }
    }
    
    fclose(file);
}
