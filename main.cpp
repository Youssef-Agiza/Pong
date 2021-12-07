#include "common.h"
#include "defs.h"
#include "sharedMem.h"
#include "globals.h"
#include "utils.h"

pid_t child_a, child_b;

int main(int argc, char **argv)
{

    child_a = fork();
    if (child_a == 0)
        child_logic();
    else
    {
        child_b = fork();
        if (child_b == 0)
            child_logic();
        else

            parent_logic();
    }

    clean();
    return 0;
}
