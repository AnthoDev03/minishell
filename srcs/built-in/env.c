// env.c
#include "../../include/minishell.h"

void env_command() {
  char **env;
  env = environ;
  while (*env) {
    printf("%s\n", *env);
    env++;
  }
}
