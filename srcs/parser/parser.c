#include "../../include/minishell.h"

t_nodetype parse_redirection_type(t_token token) {
  if (token.type == TOKEN_REDIRECT_IN) {
    return NODE_REDIRECT_IN;
  } else if (token.type == TOKEN_REDIRECT_OUT) {
    return NODE_REDIRECT_OUT;
  } else if (token.type == TOKEN_REDIRECT_IN_APPEND) {
    return NODE_REDIRECT_IN_APPEND;
  } else if (token.type == TOKEN_REDIRECT_OUT_APPEND) {
    return NODE_REDIRECT_OUT_APPEND;
  }

  char errorMsg[] = "Error: Unexpected token type in parse_redirection_type.\n";
  write(2, errorMsg, sizeof(errorMsg) - 1);
  exit(EXIT_FAILURE);
}

t_node *parse(t_token *tokens) {
  int index;
  t_node *root;

  index = 0;
  root = parse_pipeline(tokens, &index);
  while (tokens[index].type == TOKEN_REDIRECT_IN ||
         tokens[index].type == TOKEN_REDIRECT_OUT ||
         tokens[index].type == TOKEN_REDIRECT_IN_APPEND ||
         tokens[index].type == TOKEN_REDIRECT_OUT_APPEND) {
    t_node *redirect_node;
    t_nodetype redirect_type;
    redirect_type = parse_redirection_type(tokens[index]);
    index++;
    redirect_node = parse_redirect(tokens, &index, redirect_type);
    if (!redirect_node) {
      free_tree(root);
      return (NULL);
    }
    redirect_node->left = root;
    root = redirect_node;
  }
  return (root);
}
