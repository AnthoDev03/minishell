#include "../../include/minishell.h"

void setup_redirection(int oldfd, int newfd, int *saved) {
  *saved = dup(oldfd);
  if (dup2(newfd, oldfd) == -1) {
    perror("dup2");
    exit(EXIT_FAILURE);
  }
  close(newfd);
}

FILE *setup_append_redirection(char *delimiter) {
  char buffer[1024];
  FILE *tempfile = tmpfile();
  if (!tempfile) {
    perror("tmpfile");
    return NULL;
  }
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    if (strncmp(buffer, delimiter, strlen(delimiter)) == 0 &&
        buffer[strlen(delimiter)] == '\n') {
      break;
    }
    fputs(buffer, tempfile);
  }
  rewind(tempfile);
  return tempfile;
}

void cleanup_append_redirection(int saved_stdin, FILE *tempfile) {
  restore_fd(STDIN_FILENO, saved_stdin);
  fclose(tempfile);
}

void execute(t_node *root) {
    if (!root)
        return;

    if (root->type == NODE_COMMAND) {
        execute_command(root);
    } else if (root->type == NODE_PIPE) {
        execute_pipeline(root);
    } else if (root->type == NODE_REDIRECT_IN) {
        execute_redirect_in(root);
    } else if (root->type == NODE_REDIRECT_OUT) {
        execute_redirect_out(root);
    } else if (root->type == NODE_REDIRECT_IN_APPEND) {
        execute_redirect_in_append(root);
    } else if (root->type == NODE_REDIRECT_OUT_APPEND) {
        execute_redirect_out_append(root);
    } else {
        write(2, "Error: Unknown node type\n", 23);
    }
}
