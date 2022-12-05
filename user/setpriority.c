#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    #ifdef PBS
      if(argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9')){
          printf("Error\n");
          exit(1);
      }

      int t = set_priority(atoi(argv[1]), atoi(argv[2]));

      if (t < 0) {
          printf("Error\n");
          exit(1);
      }
      else if (t == 101) {
          fprintf(2, "%s: pid %s not found\n", argv[2]);
          exit(1);
      }
    #endif

    exit(0);
}