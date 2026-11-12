#define ZAP_IMPLEMENTATION
#include "./zap.h"

#define DUMP()					\
  do {						\
    printf(cmd_fmt);				\
    cmd_dump(&cmd);				\
  } while (0)

int main(int argc, char **argv) {
  if (!ZAP_REBUILD_URSELF(argc, argv)) {
    fprintf(stderr, err_fmt"Rebuild failed.\n");
    return 1;
  }

  printf(info_fmt"Creating `bin` directory...\n");
  if (!mkdir_if_not_exists("bin")) {
    fprintf(stderr, err_fmt"Directory creation failed.\n");
    return 1;
  }

  printf(info_fmt"Discovering source files...\n");
  if (!file_exists("main.c")) {
    fprintf(stderr, err_fmt"No source files found.\n");
    return 1;
  }

  Cmd cmd = {0};

  cc(&cmd);
  cc_flags(&cmd);
  cc_output(&cmd, "bin/main");
  cc_inputs(&cmd, "main.c");

  printf(info_fmt"Compilation.\n");
  DUMP();

  if (!cmd_run(&cmd)) {
    fprintf(stderr, err_fmt"Compilation failed.\n");
    return 1;
  }

  cmd_append(&cmd, "./bin/main");
  printf(info_fmt"Execution.\n");
  DUMP();

  if (!cmd_run(&cmd)) {
    fprintf(stderr, err_fmt"Execution failed.\n");
    return 1;
  }

  cmd_append(&cmd, "rm");
  cmd_append(&cmd, "-rf");
  cmd_append(&cmd, "bin/main");
  cmd_append(&cmd, "bin/main.dSYM");

  printf(info_fmt"Cleanup.\n");
  DUMP();

  if (!cmd_run(&cmd)) {
    fprintf(stderr, err_fmt"Cleanup failed.\n");
    return 1;
  }
  return 0;
}
