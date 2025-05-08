#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

/// @brief Prints an error message to `stderr` with a newline character.
void print_error(char* text)
{
    fprintf(stderr, "ERROR: %s\n", text);
}

/// @brief Reads a line of input from standard input into the provided buffer.
/// @param buffer The buffer to store the input.
/// @param size The size of the buffer.
/// 
/// Example usage:
/// ```
/// char buffer[100];
/// read_line(buffer, sizeof(buffer));
/// ```
void read_line(char* buffer, int size)
{
    char* line = fgets(buffer, size, stdin);
    
    if (!line)
    {
        print_error("Failed to read line");
        return;
    }

    size_t len = strlen(buffer);
    
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

/// @brief Clears any left over input buffer.
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/// @brief For example " hello " becomes "hello"
void trim(char* str)
{
    int start = 0;
    int end = (int)(strlen(str) - 1);
    
    // Remove leading whitespace
    while (isspace(str[start]) && start <= end) 
    {
        start++;
    }

    // Remove trailing whitespace
    while (isspace(str[end]) && end >= start) 
    {
        end--;
    }

    // Shift the string to the beginning
    int i = 0;
    
    while (start <= end) 
    {
        str[i++] = str[start++];
    }
    
    str[i] = '\0';
}

/// @brief For example " Foo Bar" becomes "foo_bar"
void convert_to_camel_case(char* str)
{
    trim(str);

    for (size_t i = 0; i < strlen(str); i++)
    {
        str[i] = (char)tolower(str[i]);
    
        if (isblank(str[i]))
        {
            str[i] = '_';
        }
    }
}
