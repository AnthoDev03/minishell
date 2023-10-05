#include "../../include/minishell.h"

void handle_escape_char(char **current, char *buffer, int *buf_idx) {
  (*current)++;
  if (**current == '"' || **current == '\'' || **current == '\\') {
    buffer[(*buf_idx)++] = *(*current)++;
  } else {
    buffer[(*buf_idx)++] = '\\';
    buffer[(*buf_idx)++] = *(*current)++;
  }
}

void handle_quoted_string(char **current, char *buffer, int *buf_idx,
                          char quote_char, int *error) {
  (*current)++;
  while (**current) {
    if (**current == '\\') {
      if (quote_char == '"') {
        buffer[(*buf_idx)++] = *(*current)++;
        buffer[(*buf_idx)++] = *(*current)++;
      } else {
        buffer[(*buf_idx)++] = *(*current)++;
      }
    } else if (**current == quote_char) {
      break;
    } else {
      buffer[(*buf_idx)++] = *(*current)++;
    }
  }
  if (**current == quote_char) {
    (*current)++;
  } else {
    *error = 1;
  }
}
void handle_space_char(char **current, char *buffer, int *bufidx,
                       t_token *tokens, int *tokencount) {
  if (*bufidx > 0) {
    buffer[*bufidx] = '\0';
    t_token t;
    t.value = strdup(buffer);
    if (*tokencount == 0) {
      t.type = TOKEN_COMMAND;
    } else {
      t.type = TOKEN_ARGUMENT;
    }
    tokens[(*tokencount)++] = t;
    *bufidx = 0;
  }
  (*current)++;
}

void handle_pipe(char **current, t_token *tokens, int *tokencount) {
  t_token t;
  t.value = NULL;
  t.type = TOKEN_PIPE;
  tokens[(*tokencount)++] = t;
  (*current)++;
}

void handle_redirect_in(char **current, t_token *tokens, int *tokencount) {
  t_token t;
  t.value = NULL;
  if (*(*current + 1) == '<') {
    t.type = TOKEN_REDIRECT_IN_APPEND;
    (*current) += 2;
  } else {
    t.type = TOKEN_REDIRECT_IN;
    (*current)++;
  }
  tokens[(*tokencount)++] = t;
}

void handle_redirect_out(char **current, t_token *tokens, int *tokencount) {
  t_token t;
  t.value = NULL;
  if (*(*current + 1) == '>') {
    t.type = TOKEN_REDIRECT_OUT_APPEND;
    (*current) += 2;
  } else {
    t.type = TOKEN_REDIRECT_OUT;
    (*current)++;
  }
  tokens[(*tokencount)++] = t;
}

void handle_token_end(char *buffer, int *bufidx, t_token *tokens,
                      int *tokencount) {
  if (*bufidx > 0) {
    buffer[*bufidx] = '\0';
    t_token t;
    t.value = strdup(buffer);
    if (*tokencount == 0) {
      t.type = TOKEN_COMMAND;
    } else {
      t.type = TOKEN_ARGUMENT;
    }
    tokens[(*tokencount)++] = t;
    *bufidx = 0;
  }
}
void handle_special_char(char **current, t_token *tokens, int *tokencount,
                         t_token_type type) {
  t_token t;
  t.value = NULL;
  t.type = type;
  tokens[(*tokencount)++] = t;
  (*current)++;
}
t_token *tokenize_with_quotes(char *input) {
  t_token *tokens = malloc(sizeof(t_token) * 100);
  int tokencount = 0;
  char *current = input;
  char buffer[strlen(input) + 1];
  int bufidx = 0;
  int error = 0;

  while (*current && !error) {
    if (*current == '\\')
      handle_escape_char(&current, buffer, &bufidx);
    else if (*current == '"' || *current == '\'')
      handle_quoted_string(&current, buffer, &bufidx, *current, &error);
    else if (isspace(*current)) {
      handle_space_char(&current, buffer, &bufidx, tokens, &tokencount);
    } else if (*current == '|') {
      handle_token_end(buffer, &bufidx, tokens, &tokencount);
      handle_pipe(&current, tokens, &tokencount);
    } else if (*current == '<') {
      handle_token_end(buffer, &bufidx, tokens, &tokencount);
      handle_redirect_in(&current, tokens, &tokencount);
    } else if (*current == '>') {
      handle_token_end(buffer, &bufidx, tokens, &tokencount);
      handle_redirect_out(&current, tokens, &tokencount);
    } else {
      buffer[bufidx++] = *current++;
    }
  }
  if (error) {
    printf("Error: Unclosed quote found in input.\n");
    free(tokens); // Libérer la mémoire allouée avant de retourner NULL
    return NULL;
  }

  handle_token_end(buffer, &bufidx, tokens, &tokencount);

  t_token endtoken = {TOKEN_EOF, NULL};
  tokens[tokencount++] = endtoken;

  return tokens;
}

void free_tokens(t_token *tokens) {
  if (tokens == NULL) {
    return;
  }
  for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
    free(tokens[i].value);
  }
  free(tokens);
}
