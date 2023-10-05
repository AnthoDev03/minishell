// unset.c
#include "../../include/minishell.h"

char **find_variable(char *var_name) {
  char **env;
  int len;

  env = environ;
  len = strlen(var_name);
  while (*env) {
    if (strncmp(*env, var_name, len) == 0 && (*env)[len] == '=') {
      return env;
    }
    env++;
  }
  return NULL;
}

void shift_env_vars_left(char **start) {
  char **dest;

  dest = start;
  while (*dest) {
    *dest = *(dest + 1);
    dest++;
  }
}

void unset_command(t_node *commandNode) {
  if (commandNode->left == NULL || commandNode->left->value == NULL) {
    write(2, "unset: missing argument\n", 24);
    return;
  }

  char *var_name;
  char **var_loc;

  var_name = commandNode->left->value;
  var_loc = find_variable(var_name);
  if (var_loc) {
    shift_env_vars_left(var_loc);
  }
}
