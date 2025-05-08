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

/// @brief Sometimes scanf will leave over some left over input which creates a headache later on so this function clears up any remaining input buffer after scanf is called
void scan_num_consume(int* num)
{
    scanf("%d", num);
        
    // Clear leftover input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
