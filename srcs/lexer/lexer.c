#include "../../include/minishell.h"


t_token *tokenize_with_quotes(char *input) {
  t_lexer lexer;
  lexer.tokens = malloc(sizeof(t_token) * 100);
  lexer.tokencount = 0;
  lexer.current = input;
  lexer.buffer = (char *)malloc(strlen(input) + 1);
  lexer.bufidx = 0;
  lexer.error = 0;

  while (*(lexer.current) && !lexer.error) {
    if (*(lexer.current) == '\\') {
      handle_escape_char(&lexer);
    } else if (*(lexer.current) == '"' || *(lexer.current) == '\'') {
      handle_quoted_string(&lexer, *(lexer.current));
    } else if (isspace(*(lexer.current))) {
      handle_space_char(&lexer);
    } else if (*(lexer.current) == '|') {
      handle_token_end(&lexer);
      handle_pipe(&lexer);
    } else if (*(lexer.current) == '<') {
      handle_token_end(&lexer);
      handle_redirect_in(&lexer);
    } else if (*(lexer.current) == '>') {
      handle_token_end(&lexer);
      handle_redirect_out(&lexer);
    } else {
      lexer.buffer[lexer.bufidx++] = *(lexer.current)++;
    }
  }

  if (lexer.error) {
    printf("Error: Unclosed quote found in input.\n");
    free(lexer.tokens);
    free(lexer.buffer);
    return NULL;
  }

  handle_token_end(&lexer);

  t_token endtoken = {TOKEN_EOF, NULL};
  lexer.tokens[lexer.tokencount++] = endtoken;

  free(lexer.buffer); // Don't forget to free the buffer.
  return lexer.tokens;
}


