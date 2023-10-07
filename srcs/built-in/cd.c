#include "../../include/minishell.h"

void cd_command(t_node *commandNode) {
  if (commandNode->left == NULL || commandNode->left->value == NULL)
  {
    write(2, "cd: missing argument\n", 20);
    return;
  }
  if (chdir(commandNode->left->value) != 0)
    perror("cd");
}
