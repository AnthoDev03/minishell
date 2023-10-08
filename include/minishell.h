#ifndef MINISHELL_H
#define MINISHELL_H

#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../libft/libft.h"
extern char **environ;
#define TMP_FILENAME "/tmp/my_temp_file"

// -- -- -- -- -- -- -- -- - LEXER -- -- -- -- -- -- -- -- -- -- -

typedef enum e_token_type {
  TOKEN_COMMAND,
  TOKEN_ARGUMENT,
  TOKEN_PIPE,
  TOKEN_REDIRECT_IN,
  TOKEN_REDIRECT_OUT,
  TOKEN_REDIRECT_IN_APPEND,
  TOKEN_REDIRECT_OUT_APPEND,
  TOKEN_ERROR,
  TOKEN_EOF
} t_token_type;

typedef struct s_token {
  t_token_type type;
  char *value;
} t_token;

typedef struct s_lexer {
  char *current;   // Pointer to the current character
  t_token *tokens; // Array of tokens
  int tokencount;  // Token count
  char *buffer;    // Buffer to hold temporary characters
  int bufidx;      // Buffer index
  int error;       // Error flag
} t_lexer;

t_token *tokenize_with_quotes(char *input);
void free_tokens(t_token *tokens);
void handle_escape_char(t_lexer *lexer);
void handle_quoted_string(t_lexer *lexer, char quote_char); 
void handle_space_char(t_lexer *lexer); 
void handle_pipe(t_lexer *lexer);
void handle_redirect_in(t_lexer *lexer); 
void handle_redirect_out(t_lexer *lexer);
void handle_token_end(t_lexer *lexer);
void handle_special_char(t_lexer *lexer, t_token_type type); 


//-- -- -- -- -- -- -- -- -- -- PARSER -- -- -- -- -- -- -- -- -- -- -

typedef enum e_nodetype {
  NODE_COMMAND,
  NODE_ARGUMENT,
  NODE_PIPE,
  NODE_REDIRECT_IN,
  NODE_REDIRECT_OUT,
  NODE_REDIRECT_IN_APPEND,
  NODE_REDIRECT_OUT_APPEND,
} t_nodetype;

typedef struct s_node {
  t_nodetype type;
  char *value;
  struct s_node *left;
  struct s_node *right;
} t_node;
t_node *create_node(t_nodetype type, char *value);
void free_tree(t_node *root);
t_node *parse_command(t_token *tokens, int *index);
t_node *parse_redirect(t_token *tokens, int *index, t_nodetype redirect_type);
t_node *parse_pipeline(t_token *tokens, int *index);
t_node *parse(t_token *tokens);
void free_tree(t_node *root);
//-- -- -- -- -- -- -- -- -- -- EXPANDER -- -- -- -- -- -- -- -- -- --

typedef struct s_expander {
  const char *current;
  int in_single_quotes;
  int in_double_quotes;
  char *write_pos;
  size_t buffer_size;
  char *expanded_str;
} t_expander;
void init_expander(t_expander *exp, char *input);
void handle_single_quote(t_expander *exp);
void handle_double_quote(t_expander *exp);
void get_env_var_name(t_expander *exp, char *var_name);
void expand_env_var(t_expander *exp);
char *expand_env_variables(char *input);
//------------------------------EXECUTOR-------------------------------

void execute(t_node *root);
void cleanup_append_redirection(int saved_stdin, FILE *tempfile);
FILE *setup_append_redirection(char *delimiter);
void setup_redirection(int oldfd, int newfd, int *saved);
int open_file_append(const char *path);
int open_file_write(const char *path);
int open_file_read(const char *path);
void execute_redirect_out_append(t_node *root);
void execute_redirect_out(t_node *root);
void execute_redirect_in_append(t_node *root);
void execute_redirect_in(t_node *root);
void parent_pipeline(int *pipe_fd, t_node *root, int *saved_stdin, pid_t pid);
void child_pipeline(int *pipe_fd, t_node *root);
void execute_pipeline(t_node *root);
int wait_for_child(pid_t pid);
void execute_command(t_node *node);
void setup_pipe(int *pipe_fd);
void restore_fd(int oldfd, int saved);
void close_pipes(int *pipe_fd);
void dup_to(int oldfd, int newfd, int *saved);

//------------------------------BUILTINS-------------------------------

void cd_command(t_node *commandNode);
void echo_command(t_node *commandNode);
void pwd_command();

void export_command(t_node *commandNode);
void print_env_vars(void);
char *create_new_entry(char *key, char *value);
void replace_existing_var(char **env, char *key, char *value);
int is_key_present(char **env, char *key, int len);
void add_new_env_var(char *key, char *value);
void handle_var_set(char *key, char *value);
void set_env_var(t_node *commandNode);

void unset_command(t_node *commandNode);
void env_command();
void exit_command();

//-----------------------------UTILS------------------------------------
int	ft_strcmp(const char *s1, const char *s2);
int ft_execvp(const char *file, char *const argv[]);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
char *ft_strcpy(char *dest, char *src);
#endif
