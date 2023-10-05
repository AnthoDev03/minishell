#include "../../include/minishell.h"

void dup_to(int oldfd, int newfd, int *saved) {
  *saved = dup(oldfd);
  if (dup2(newfd, oldfd) == -1) {
    perror("dup2");
    exit(EXIT_FAILURE);
  }
}

void close_pipes(int *pipe_fd) {
  close(pipe_fd[0]);
  close(pipe_fd[1]);
}

void restore_fd(int oldfd, int saved) {
  dup2(saved, oldfd);
  close(saved);
}

void setup_pipe(int *pipe_fd) {
  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
}

void execute_command(t_node *node) {
  char *builtins[] = {"cd", "echo", "env", "exit", "pwd", "unset", "export"};
  void (*funcs[])(t_node *) = {cd_command,    echo_command, env_command,
                               exit_command,  pwd_command,  unset_command,
                               export_command};
  for (int i = 0; i < 7; i++) {
    if (strcmp(node->value, builtins[i]) == 0) {
      funcs[i](node);
      return;
    }
  }

  char *args[3] = {node->value, NULL, NULL};
  if (node->left) {
    args[1] = node->left->value;
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return;
  }
  if (pid == 0) {
    ft_execvp(args[0], args);

    perror("execvp");
    exit(EXIT_FAILURE);
  }
  wait_for_child(pid);
}
