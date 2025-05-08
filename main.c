#include <stdio.h>
#include <stdlib.h>

#include "home.h"
#include "options.h"

int main()
{
    init_default_options();
    home();
    printf("Program ended normally\n");
    return EXIT_SUCCESS;
}
