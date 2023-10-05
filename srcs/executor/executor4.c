#include "../../include/minishell.h"

void execute_redirect_in_append(t_node *root) {
  FILE *tempfile;
  int saved_stdin;

  tempfile = setup_append_redirection(root->left->value);
  if (!tempfile)
    return;

  setup_redirection(STDIN_FILENO, fileno(tempfile), &saved_stdin);

  execute(root->right);

  cleanup_append_redirection(saved_stdin, tempfile);
}

void execute_redirect_out(t_node *root) {
  int fd;
  int saved_stdout;

  fd = open_file_write(root->value);
  if (fd == -1)
    return;

  setup_redirection(STDOUT_FILENO, fd, &saved_stdout);

  execute(root->left);

  restore_fd(STDOUT_FILENO, saved_stdout);
}

void execute_redirect_out_append(t_node *root) {
  int fd;
  int saved_stdout;

  fd = open_file_append(root->value);
  if (fd == -1)
    return;

  setup_redirection(STDOUT_FILENO, fd, &saved_stdout);

  execute(root->left);

  restore_fd(STDOUT_FILENO, saved_stdout);
}

int open_file_read(const char *path) {
  int fd = open(path, O_RDONLY);
  if (fd == -1) {
    perror("open");
  }
  return fd;
}

int open_file_write(const char *path) {
  int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    perror("open");
  }
  return fd;
}

int open_file_append(const char *path) {
  int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (fd == -1) {
    perror("open");
  }
  return fd;
}
