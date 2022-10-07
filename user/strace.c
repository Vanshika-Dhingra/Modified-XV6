#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "no of arguments are less\n");
        return 0;
    }

    int pid = fork();

    if (pid == 0)
    {
        trace(atoi(argv[1]));
        exec(argv[2], argv + 2);
        exit(0);
    }
    wait(0);

    return 0;
}