#include "../include/minishell.h"
#include <stdio.h>

/* void print_tokens(t_token *tokens) {
  if (!tokens) {
    printf("No tokens to print.\n");
    return;
  }

  for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
    printf("Token #%d:\n", i + 1);
    printf("\tType: ");

    switch (tokens[i].type) {
    case TOKEN_COMMAND:
      printf("COMMAND");
      break;
    case TOKEN_ARGUMENT:
      printf("ARGUMENT");
      break;
    case TOKEN_PIPE:
      printf("PIPE");
      break;
    case TOKEN_REDIRECT_IN:
      printf("REDIRECT_IN");
      break;
    case TOKEN_REDIRECT_OUT:
      printf("REDIRECT_OUT");
      break;
    case TOKEN_REDIRECT_IN_APPEND:
      printf("REDIRECT_IN_APPEND");
      break;
    case TOKEN_REDIRECT_OUT_APPEND:
      printf("REDIRECT_OUT_APPEND");
      break;
    case TOKEN_ERROR:
      printf("ERROR");
      break;
    case TOKEN_EOF:
      printf("EOF");
      break;
    default:
      printf("UNKNOWN");
      break;
    }

    if (tokens[i].value) {
      printf("\n\tValue: %s", tokens[i].value);
    }
    printf("\n");
  }
}
void print_tree(t_node *root) {
  static int depth = 0;

  if (!root)
    return;

  // Indentation pour une meilleure lisibilité
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }

  switch (root->type) {
  case NODE_COMMAND:
    printf("COMMAND: %s\n", root->value);
    break;
  case NODE_ARGUMENT:
    printf("ARGUMENT: %s\n", root->value);
    break;
  case NODE_PIPE:
    printf("PIPE\n");
    break;
  case NODE_REDIRECT_IN:
    printf("REDIRECT_IN: %s\n", root->value);
    break;
  case NODE_REDIRECT_OUT:
    printf("REDIRECT_OUT: %s\n", root->value);
    break;
  case NODE_REDIRECT_IN_APPEND:
    printf("REDIRECT_IN_APPEND: %s\n", root->value);
    break;
  case NODE_REDIRECT_OUT_APPEND:
    printf("REDIRECT_OUT_APPEND: %s\n", root->value);
    break;
  default:
    printf("UNKNOWN NODE\n");
    break;
  }

  depth++;
  print_tree(root->left);
  print_tree(root->right);
  depth--;
}
*/
void handle_sigint(int sig) {
  (void)sig;
  write(STDOUT_FILENO, "\nminishell> ", 12);
  rl_on_new_line_with_prompt();
  rl_replace_line("", 0);
  rl_redisplay();
}

void handle_sigquit(int sig) { (void)sig; }

int main() {
  // Configurer les gestionnaires de signaux
  struct sigaction sa_int, sa_quit;

  sa_int.sa_handler = handle_sigint;
  sigemptyset(&sa_int.sa_mask);
  sa_int.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa_int, NULL);

  sa_quit.sa_handler = handle_sigquit;
  sigemptyset(&sa_quit.sa_mask);
  sa_quit.sa_flags =
      0; // Pas de SA_RESTART pour SIGQUIT puisque nous ne faisons rien
  sigaction(SIGQUIT, &sa_quit, NULL);
  char *input;

  while ((input = readline("minishell> "))) {
    if (!input) {
      // ctrl-D a été pressé
      write(STDOUT_FILENO, "\n", 1);
      exit(0);
    }
    add_history(input);
    input = expand_env_variables(input);

    t_token *tokens = tokenize_with_quotes(input);
    // print_tokens(tokens);

    if (tokens != NULL) {
      // Utiliser fonction de parsing pour obtenir l'arbre de syntaxe
      t_node *root = parse(tokens);
      //  print_tree(root);
      // Exécuter la commande / le pipeline / la redirection
      execute(root);

      // Libérer la mémoire
      free_tree(root);
      // free_tokens(tokens);
    }

    free(input);
  }

  return 0;
}
