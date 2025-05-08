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
