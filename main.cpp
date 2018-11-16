
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "builtin_cmd.h"
#include "microsha_kernel.h"

int main(int argc, char **argv)
{

    loop();

    return EXIT_SUCCESS;
}
