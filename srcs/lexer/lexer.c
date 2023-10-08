#include "../../include/minishell.h"

void handle_current_char(t_lexer *lexer) {
    if (*(lexer->current) == '\\') {
        handle_escape_char(lexer);
    } else if (*(lexer->current) == '"' || *(lexer->current) == '\'') {
        handle_quoted_string(lexer, *(lexer->current));
    } else if (isspace(*(lexer->current))) {
        handle_space_char(lexer);
    } else if (*(lexer->current) == '|') {
        handle_token_end(lexer);
        handle_pipe(lexer);
    } else if (*(lexer->current) == '<') {
        handle_token_end(lexer);
        handle_redirect_in(lexer);
    } else if (*(lexer->current) == '>') {
        handle_token_end(lexer);
        handle_redirect_out(lexer);
    } else {
        lexer->buffer[lexer->bufidx++] = *(lexer->current)++;
    }
}

t_token *finalize_lexer(t_lexer *lexer) {
    if (lexer->error) {
        printf("Error: Unclosed quote found in input.\n");
        free(lexer->tokens);
        free(lexer->buffer);
        return NULL;
    }

    handle_token_end(lexer);

    t_token endtoken = {TOKEN_EOF, NULL};
    lexer->tokens[lexer->tokencount++] = endtoken;
    free(lexer->buffer);
    return lexer->tokens;
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
        handle_current_char(&lexer);
    }

    return finalize_lexer(&lexer);
}

