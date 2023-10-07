#include "../../include/minishell.h"

void handle_escape_char(t_lexer *lexer) {
  (lexer->current)++;
  if (*(lexer->current) == '"' || *(lexer->current) == '\'' ||
      *(lexer->current) == '\\') {
    lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
  } else {
    lexer->buffer[(lexer->bufidx)++] = '\\';
    lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
  }
}

void handle_quoted_string(t_lexer *lexer, char quote_char) {
  (lexer->current)++;
  while (*(lexer->current)) {
    if (*(lexer->current) == '\\' && quote_char == '"') {
      (lexer->current)++;
      if (*(lexer->current) == '"' || *(lexer->current) == '\\' ||
          *(lexer->current) == '$') {
        lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
      } else {
        lexer->buffer[(lexer->bufidx)++] = '\\';
        lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
      }
    } else if (*(lexer->current) == quote_char) {
      break;
    } else {
      lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
    }
  }
  if (*(lexer->current) == quote_char) {
    (lexer->current)++;
  } else {
    lexer->error = 1;
  }
}

void handle_space_char(t_lexer *lexer) {
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
  (lexer->current)++;
}

void handle_pipe(t_lexer *lexer) {
  t_token t;
  t.value = NULL;
  t.type = TOKEN_PIPE;
  lexer->tokens[(lexer->tokencount)++] = t;
  (lexer->current)++;
}

void handle_redirect_in(t_lexer *lexer) {
  t_token t;
  t.value = NULL;
  if (*(lexer->current + 1) == '<') {
    t.type = TOKEN_REDIRECT_IN_APPEND;
    lexer->current += 2;
  } else {
    t.type = TOKEN_REDIRECT_IN;
    (lexer->current)++;
  }
  lexer->tokens[(lexer->tokencount)++] = t;
}
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
