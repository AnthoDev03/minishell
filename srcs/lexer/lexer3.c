#include "../../include/minishell.h"


void handle_redirect_out(t_lexer *lexer) {
  t_token t;
  t.value = NULL;
  if (*(lexer->current + 1) == '>') {
    t.type = TOKEN_REDIRECT_OUT_APPEND;
    lexer->current += 2;
  } else {
    t.type = TOKEN_REDIRECT_OUT;
    lexer->current++;
  }
  lexer->tokens[(lexer->tokencount)++] = t;
}

void handle_token_end(t_lexer *lexer) {
  if (lexer->bufidx > 0) {
    lexer->buffer[lexer->bufidx] = '\0';
    t_token t;
    t.value = ft_strdup(lexer->buffer);
    if (lexer->tokencount == 0) {
      t.type = TOKEN_COMMAND;
    } else {
      t.type = TOKEN_ARGUMENT;
    }
    lexer->tokens[(lexer->tokencount)++] = t;
    lexer->bufidx = 0;
  }
}

void handle_special_char(t_lexer *lexer, t_token_type type) {
  t_token t;
  t.value = NULL;
  t.type = type;
  lexer->tokens[(lexer->tokencount)++] = t;
  lexer->current++;
}

void free_tokens(t_token *tokens) {
  int i;

  i = 0;
  if (tokens == NULL)
    return;
  while (tokens[i].type != TOKEN_EOF) 
  {
    free(tokens[i].value);
    i++;
  }
  free(tokens);
}
