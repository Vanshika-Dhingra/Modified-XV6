#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    if (argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9')||trace(atoi(argv[1])) < 0)
    {
        printf("Error\n");
        exit(1);
    }
//printf("%s",argv[1]);

    exec(argv[2], &argv[2]);

    exit(0);
}